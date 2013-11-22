/******************************************************************************/
/*                                                                            */
/*                             ASC Interpreter                                */
/*                             ~~~~~~~~~~~~~~~                                */
/*                                                                            */
/*                             	Pawel Gburzynski, Nov. 5 1985                 */
/*				Piotr Rudnicki, Sept. 25 1989		      */
/*									      */
/*		- option -l (listing)					      */
/*		- SALLOC - allocation of variable size memory block	      */
/*		- IFERR (error set after reading and integer arithmetic)      */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

/*
  041206
  LABLENGTH 16 instead of 8
  MININT changed such that proper value is computed
  trace for RTOI changed to the correct one
  getflt corrected to allow '-' in the exponent
 */

#include	<sys/types.h>
#include	<sys/times.h>
#include	<sys/file.h>
#include	<signal.h>
#include	<ctype.h>
#include	<stdio.h>

#define		mEOF		((char) EOF)

#define		MAXINT		2147483647
#define		MININT		(-MAXINT-1)
#define		STACKSIZE	32767
#define		CODESIZE	32767
#define		NOOFREGS	16
#define		KWDSIZE		7
#define		NOOFINST	47
#define		LABLENGTH	16
#define		LNSIZE		((LABLENGTH+3)/4)
#define		CONT		0
#define		ABORT		1
#define		MAXADDR		(03777777)
#define		ADDRMASK	(07777777)
#define		SADRMASK	(037774000000)
#define		NOFREGS		16

/* Instruction opcodes */

#define		PUSH		0
#define		PUSHI		1
#define		PUSHA		2
#define		POP		3
#define		POPI		4
#define		CONSTI		5
#define		CONSTR		6
#define		ADJUST		7
#define		ALLOC		8
#define		FREE		9
#define		ADDI		10
#define		ADDR		11
#define		SUBI		12
#define		SUBR		13
#define		MULI		14
#define		MULR		15
#define		DIVI		16
#define		DIVR		17
#define		MOD		18
#define		ITOR		19
#define		RTOI		20
#define		EQI		21
#define		EQR		22
#define		LTI		23
#define		LTR		24
#define		GTI		25
#define		GTR		26
#define		OR		27
#define		AND		28
#define		NOT		29
#define		IFZ		30
#define		IFNZ		31
#define		GOTO		32
#define		STOP		33
#define		CALL		34
#define		RET		35
#define		READI		36
#define		READR		37
#define		READC		38
#define		WRITEI		39
#define		WRITER		40
#define		WRITEC		41
#define		TRACE		42
#define		DUMP		43
#define		DUP		44
#define		SALLOC		45
#define		IFERR		46

#define		ucase(x)	((((x)>='a')&&((x)<='z'))?(x)-('a'-'A'):(x))

int	stack [STACKSIZE], code [CODESIZE], sp, errcnt, org, freerl, endlabels,
	endlablim, curline, endconsts,
	ic, reg [NOFREGS], tracing, action, rf, rn, aval, mfree, mlast;

char	c;

enum	oprndtype	{ADDRESS, REGISTER, RABSENT, INT, FLOAT, LABEL, ABSENT};

union	insformat	{

	unsigned int	word;

	struct	{

		unsigned int	operation : 6,
				regflag   : 1,
				regnum    : 4,
				address   : 21;
	}		codes;

};

union	labformat	{

	char		labname [LABLENGTH];

	int		labwrds [LNSIZE];
};

union	fltformat	{

	int		integer;

	float		real;
};

union	cti		{

	int		pattern;

	struct		{
		char	ca, cb, cc, cd;
	} chs;
};

struct	instruction	{

	char	kwd [KWDSIZE];
	enum	oprndtype	oprndtype1, oprndtype2;
	char	opcode;
};

struct	instruction	*ci;		/* Instruction currently assembled */

union	insformat	cinstr;

struct	instruction	idict [NOOFINST] = {

	{"PUSH",	ADDRESS,	ABSENT,		PUSH  },
	{"PUSHI",	RABSENT,	ABSENT,		PUSHI },
	{"PUSHA",	ADDRESS,	ABSENT,		PUSHA },
	{"POP",		ADDRESS,	ABSENT,		POP   },
	{"POPI",	RABSENT,	ABSENT,		POPI  },
	{"CONSTI",	INT,		ABSENT,		CONSTI},
	{"CONSTR",	FLOAT,		ABSENT,		CONSTR},
	{"ADJUST",	INT,		ABSENT,		ADJUST},
	{"ALLOC",	INT,		ABSENT,		ALLOC },
	{"FREE",	ABSENT,		ABSENT,		FREE  },
	{"ADDI",	ABSENT,		ABSENT,		ADDI  },
	{"ADDR",	ABSENT,		ABSENT,		ADDR  },
	{"SUBI",	ABSENT,		ABSENT,		SUBI  },
	{"SUBR",	ABSENT,		ABSENT,		SUBR  },
	{"MULI",	ABSENT,		ABSENT,		MULI  },
	{"MULR",	ABSENT,		ABSENT,		MULR  },
	{"DIVI",	ABSENT,		ABSENT,		DIVI  },
	{"DIVR",	ABSENT,		ABSENT,		DIVR  },
	{"MOD",		ABSENT,		ABSENT,		MOD   },
	{"ITOR",	ABSENT,		ABSENT,		ITOR  },
	{"RTOI",	ABSENT,		ABSENT,		RTOI  },
	{"EQI",		ABSENT,		ABSENT,		EQI   },
	{"EQR",		ABSENT,		ABSENT,		EQR   },
	{"LTI",		ABSENT,		ABSENT,		LTI   },
	{"LTR",		ABSENT,		ABSENT,		LTR   },
	{"GTI",		ABSENT,		ABSENT,		GTI   },
	{"GTR", 	ABSENT,		ABSENT,		GTR   },
	{"OR", 		ABSENT,		ABSENT,		OR    },
	{"AND",		ABSENT,		ABSENT,		AND   },
	{"NOT",		ABSENT,		ABSENT,		NOT   },
	{"IFZ",		LABEL,		ABSENT,		IFZ   },
	{"IFNZ",	LABEL,		ABSENT,		IFNZ  },
	{"GOTO",	LABEL,		ABSENT,		GOTO  },
	{"STOP",	ABSENT,		ABSENT,		STOP  },
	{"CALL",	REGISTER,	LABEL,		CALL  },
	{"RET",		REGISTER,	ABSENT,		RET   },
	{"READI",	ABSENT,		ABSENT,		READI },
	{"READR",	ABSENT,		ABSENT,		READR },
	{"READC",	ABSENT,		ABSENT,		READC },
	{"WRITEI",	ABSENT,		ABSENT,		WRITEI},
	{"WRITER",	ABSENT,		ABSENT,		WRITER},
	{"WRITEC",	ABSENT,		ABSENT,		WRITEC},
	{"trace",	INT,		ABSENT,		TRACE },
	{"dump",	ABSENT,		ABSENT,		DUMP  },
	{"DUP",		ABSENT,		ABSENT,		DUP   },
	{"SALLOC",	ABSENT,		ABSENT,		SALLOC},
	{"IFERR",	LABEL,		ABSENT,		IFERR } };


FILE	*pgm, *lst;

int	listflag = 0;
char	*pname;

main	(argc, argv)

int	argc;
char	*argv [];

{
char	*fn, lfn [1024];

	/* Open the file with program */

	pgm = stdin;
	fn  = NULL;
	pname = *argv;

	while (--argc > 0) {
		if (strcmp (*++argv, "-l") == 0) {
			/* Listing */
			if (listflag++) bad_usage ();
		} else if (pgm == stdin) {
			if ((pgm = fopen (fn = *argv, "r")) == NULL) {
				fprintf (stderr,
					"%s: failed to open program file\n", pname);
				exit (1);
			}
		} else
			bad_usage ();
	}

	if (listflag) {
		if (fn == NULL)
			strcpy (lfn, "xx.lasc");
		else {
			strcpy (lfn, fn);
			for (fn = lfn + strlen (lfn); fn != lfn && *fn != '.';
				fn--);
			if (*fn == '.') *fn = '\0';
			strcat (lfn, ".lasc");
		}
		if ((lst = fopen (lfn, "w")) == NULL) {
			fprintf (stderr, "%s: failed to open listing file\n", pname);
			exit (2);
		}
	}

	if (listflag)
		fprintf (lst, "lineno  IC(d) (oct)      ---  \n");

	assemble ();		/* Read in the program */

	if (!errcnt) execute ();	/* And execute it */

}

bad_usage () {    

	fprintf (stderr, "Usage: %s [fname] [-l]\n", pname);
	exit (3);
}

getlabel	(name)

int	name [LNSIZE];
{
union	labformat	aux;
int	k;

	for (k=0; k<LNSIZE; k++) aux.labwrds [k] = 0;

	for (aux.labname [k=0] = c; ((c = getc (pgm)) != ' ') && (c != '\t') &&
		(c != '\n') && (c != '#') && (c != '!'); ) {
			
			putlist (c);
			
			if ((++k) < LABLENGTH) aux.labname [k] = c;
	}
	putlist (c);
	
	for (k=0; k<LNSIZE; k++) name [k] = aux.labwrds [k];
}

findlabel	(name, loc)

int	name [LNSIZE], *loc;
{
int	k, l;

	for (k=0; k<endlabels; k += LNSIZE + 2) {
		
		for (l=0; l <= LNSIZE; l++) {
			if (l == LNSIZE) {
				(*loc) = k;
				return (1);
			}
			if (stack [k+l] != name [l]) break;
		}
	}
	return (0);
}
		
deflabel	()
{
int	k, l, m, p, lname [LNSIZE];
union	insformat	aux;
	
	getlabel (lname);	/* Read label */

	if (findlabel (lname, &k)) {

		if (stack [k+LNSIZE]) {		/* Label already defined */
			cerror ("Duplicate label", CONT);
			return	(1);
		}

		for (p=(l=stack [k+LNSIZE+1]); ; l=stack [l+1]) {

			/* Traverse reference list */

			aux.word = code [m=stack[l]];
			aux.codes.address = org;
			code [m] = aux.word;
			if (!stack [l+1]) break;
		}

		/* Return reference list items to the free pool */

		stack [l+1] = freerl;
		freerl = p;

		/* Flag the label as defined */

		stack [k+LNSIZE] = 1;
		stack [k+LNSIZE+1] = org;

	} else {

		if (endlabels + LNSIZE + 2 >= endlablim)
			cerror ("Too many labels", ABORT);
		
		for (k=0; k<LNSIZE; k++)
			stack [endlabels + k] = lname [k];
		
		stack [endlabels+LNSIZE] = 1;
		stack [endlabels+LNSIZE+1] = org;
		endlabels += LNSIZE + 2;
	}

	return (0);
}


skiptoeol	()
{
	while ((c != '\n') && (c != mEOF)) { c = getc (pgm); putlist (c); }
}

skipspaces	()
{
	while ((c == ' ') || (c == '\t')) { c = getc (pgm); putlist (c); }
}

mnemonic	()
{
char	mnem [KWDSIZE];
int	k, l;

	for (mnem [k=0] = ucase(c); ((c = getc (pgm)) != ' ') && (c != '\t') &&
		(c != '\n') && (c != '#') && (c != '!'); ) {
			putlist (c);
			if ((++k) < KWDSIZE-1)
				mnem [k] = ucase(c);
			else {
				cerror ("Instruction mnemonic too long", CONT);
				return (1);
			}
	}
	putlist (c);
	mnem [k+1] = '\0';
	
	/* Find the mnemonic in the dictionary */

	for (k=0; k<NOOFINST; k++) {

		for (ci= &idict[k], l=0; (l<KWDSIZE) && (mnem[l]==(ci->kwd)[l]);
			l++)
				if (mnem [l] == '\0') {

					l = -1;
					break;
				}
		if (l < 0) break;
	}

	if (l >= 0) {

		cerror ("Illegal instruction", CONT);
		return (1);
	}

	return (0);
}

notdigit	()
{
	return ((c<'0') || (c>'9'));
}

getint		(v)
int	*v;
{
int	n, f;
	f = (c=='-') ? 0 : 1;
	if ((c=='-') || (c=='+')) {
		c = getc (pgm);
		putlist (c);
		skipspaces ();
	}
	if (notdigit ()) {
		cerror ("Number expected", CONT);
		return (1);
	}
	for (n=0; ! notdigit (); ) {

		n = n*10 - (c - '0');
		if ((n > 0) || (f && (n == MININT))) {
			cerror ("Integer constant overflow", CONT);
			return (1);
		}
		c = getc (pgm);
		putlist (c);
	}
	*v = f ? -n : n;
	return (0);
}

getflt		(v)
double	*v;
{
int	f;
char	ff [256], *fff;

	f = (c=='-') ? 0 : 1;
	if ((c=='-') || (c=='+')) {
		c = getc (pgm);
		putlist (c);
		skipspaces ();
	}
	if (notdigit ()) {
		cerror ("Number expected", CONT);
		return (1);
	}

	*(fff = ff) = c;
	while ((c = getc(pgm)) == '+' || c == '-' || c == '.' || c == 'e' || c =='E' ||
		isdigit (c)) {
			*++fff = c;
			putlist (c);
	}
	*++fff = '\0';
	ungetc (c, pgm);

	sscanf (ff, "%lf", v);

	c = getc (pgm);		/* Whatever follows the number */
	putlist (c);

	if (!f) *v = - (*v);
	return (0);
}

operand		(otype)
enum	oprndtype	otype;
{
int	n, k, lname [LNSIZE];
union	fltformat	aux;
double	u;

	switch (otype) {

	case	ABSENT		:

		return (0);

	case	ADDRESS		:

		if (notdigit() && (c != '[') && (c != '+') && (c != '-')) {
			cerror ("Bad address format", CONT);
			return (1);
		}

		if (c == '[')
			n = 0;
		else
			if (getint (&n)) return (1);
		
		if ((n > MAXADDR) || (n < -MAXADDR - 1)) {
			cerror ("Address constant out of range", CONT);
			return (1);
		}

		cinstr.codes.address = (n & ADDRMASK);

		skipspaces ();

		if (c == '[') {
			c = getc (pgm);
			putlist (c);
			cinstr.codes.regflag = 1;
			skipspaces ();
			if (notdigit ()) {
				cerror ("[] format bad", CONT);
				return (1);
			}
			for (n=0; ! notdigit (); ) {

				n = n*10 + (c - '0');
				if (n >= NOFREGS) {
					cerror ("[] register number too big",
						CONT);
					return (1);
				}
				c = getc (pgm);
				putlist (c);
			}
			cinstr.codes.regnum = n;

			skipspaces ();

			if (c != ']') {

				cerror ("No matching ']'", CONT);
				return (1);
			}
			c = getc (pgm);
			putlist (c);
		}
		return (0);

	case	REGISTER	:
	case	RABSENT		:

		if (notdigit ()) {
			if (otype == RABSENT) return (0);
			cerror ("Register number expected", CONT);
			return (1);
		}
		for (n=0; ! notdigit (); ) {

			n = n*10 + (c - '0');
			if (n >= NOFREGS) {
				cerror ("Register number too big", CONT);
				return (1);
			}
			c = getc (pgm);
			putlist (c);
		}
		cinstr.codes.regnum  = n;
		cinstr.codes.regflag = 1;

		return (0);
	
	case	INT		:

		if (getint (&n)) return (1);

SC:		if (endconsts <= org) {
			cerror ("Program too long", ABORT);
			return (1);
		}

		code [--endconsts] = n;
		cinstr.codes.address = endconsts;

		return (0);

	case	FLOAT		:

		if (getflt (&u)) return	(1);
		aux.real = (float) u;
		n = aux.integer;
		goto SC;

	case	LABEL		:

		if ((c == '\n') || (c == '#') || (c == '!')) {
			cerror ("Label expected\n");
			return (1);
		}
		getlabel (lname);

		if (findlabel (lname, &n)) {
			if (stack [n+LNSIZE]) {
				/* Label defined */
				cinstr.codes.address = stack [n+LNSIZE+1];
				return (0);
			} else {
				/* Label undefined */
AR:				if (!(k = freerl)) {
					cerror ("Too many labels", ABORT);
				}
				freerl = stack [freerl + 1];
				/* Append new reference */
				stack [k+1] = stack [n+LNSIZE+1];
				stack [n+LNSIZE+1] = k;
				stack [k] = org;
				cinstr.codes.address = 0;
				return (0);
			}
		} else {
			/* Label not in dictionary */

			if (((n=endlabels) + LNSIZE + 2) >= endlablim)
				cerror ("Too many labels", ABORT);
		
			for (k=0; k<LNSIZE; k++)
				stack [endlabels + k] = lname [k];
		
			stack [endlabels+LNSIZE] = 0;	/* Label undefined */
			stack [endlabels+LNSIZE+1] = 0;	/* Empty rlist */

			endlabels += LNSIZE + 2;

			goto AR;		/* Append reference */
		}
	}
}

void debug		()
{

	c = getc (pgm);
	putlist (c);
	skipspaces ();
	cinstr.word = 0;

	switch	(ucase (c)) {

	case	'T'	:

		/* Trace */
		if ((c = getc (pgm)) != '=') {
			putlist (c);
			cerror ("Invalid trace syntax", CONT);
			return;
		}
		c = getc (pgm);
		putlist (c);
		ci = &idict [TRACE];
		break;

	case	'D'	:

		/* Dump */
		ci = &idict [DUMP];
		break;
	
	default		:

		cerror ("Illegal debug instruction", CONT);
		return;

	}
	if (operand (ci->oprndtype1)) return;
	skiptoeol ();
	if (org >= endconsts) {

		cerror ("Program too big", ABORT);
	}
	cinstr.codes.operation = ci->opcode;
	code [org++] = cinstr.word;
}

putlist (c)

char	c;

{
	if (listflag) putc (c, lst);
}

cerror (t, code)
char	*t;
int	code;
{
	errcnt++;
	fprintf (stderr, "Assembly cerror (line %6d)  -- %s --\n", curline, t);
	skiptoeol ();
	if (code == ABORT) {
		fprintf (stderr, "Assembly aborted\n");
		exit (1);
	}
}

assemble	()
{
int	k, l;
union	labformat	aux;

	for (k=0; k<CODESIZE; code [k++] = -1);

	org = 0;	/* Program location counter */
	endlabels = 0;	/* Lwa+1 of label dictionary */
	curline	= 0;

	endlablim = STACKSIZE/2;
	endconsts = CODESIZE;

	/* Initialize label reference list */

	for (freerl=(k=endlablim); k < STACKSIZE - 1; k += 2)
		stack [k+1] = k + 2;
	stack [k-1] = 0;


	while ((c = getc (pgm)) != mEOF) {

		/* Read next instruction */

		curline++;

		if (listflag)
			fprintf (lst, "%5d * %5d o'%7o' ---  ",
				curline, org, org);
		putlist (c);

		if (c == '#') {

			/* A comment line */

			skiptoeol ();
			continue;
		}

		if (c == '!') {

			/* Debugging directive */

			debug ();
			continue;
		}

		if (c == '\n') continue;	/* Empty line */

		if ((c != ' ') && (c != '\t')) {

			/* Label */

			if (deflabel ()) continue;
		}

		skipspaces ();

		if (c == '#') {
			
			skiptoeol ();
			continue;
		}

		if (c == '!') {

			debug ();
			continue;
		}

		if (c == '\n') continue;

		/* Process instruction mnemonic */

		if (mnemonic ()) continue;

		skipspaces ();

		cinstr.word = 0;	/* Initialize instruction code */
		cinstr.codes.operation = ci->opcode;

		if (operand (ci->oprndtype1)) continue;

		skipspaces ();
		if (c == ',') {
			c = getc (pgm);
			putlist (c);
			skipspaces ();
		}

		if (operand (ci->oprndtype2)) continue;

		skipspaces ();

		if (org >= endconsts) {

			cerror ("Program too big", ABORT);
		}
		code [org++] = cinstr.word;

		if (c == '!') {

			debug ();
			continue;
		}
		if (c == '#') {

			skiptoeol ();
			continue;
		}
		if (c != '\n') {

			cerror ("Too many operands", CONT);
		}
	}

	/* Check for undefined labels */

	for (l=(k=0); k<endlabels; k += LNSIZE+2) 
		if (stack [k+LNSIZE] == 0) {
			if (!(l++)) cerror ("Undefined labels", CONT);

			for (l=0; l<LNSIZE; l++) aux.labwrds[l] = stack [k+l];

			for (l=0; l<LABLENGTH; l++) {
				if (aux.labname [l] == '\0') break;
				fprintf (stderr, "%c", aux.labname [l]);
			}
			fprintf (stderr, "\n");
		}
}

caddr		()
{
int	k;

	/* Calculate stack address */

	if (rf) 
		k = reg [rn] + aval;
	else
		k = aval;
	
	if ((k < 0) || (k >= STACKSIZE))
		rerror ("Address outside stack", &k);
	
	return (k);
}

caddi		()
{
int	k;

	/* Calculate stack address */

	if (sp < 0) rerror ("Empty stack", NULL);

	if (rf) 
		k = reg [rn] + stack [sp];
	else
		k = stack [sp];
	
	if ((k < 0) || (k >= STACKSIZE))
		rerror ("Address outside stack", &k);
	
	return (k);
}

csph		()
{

	/* Validate stack pointer */

	if (sp >= mlast - 1) rerror ("Stack pointer too high", &sp);
}

cspl		()
{

	/* Validate stack pointer */

	if (sp < 0) rerror ("Stack pointer below stack", &sp);
}

cspa		()
{

	/* Validate stack pointer */

	if (sp < 1) rerror ("Less than two items on stack", NULL);
}

int	error;

void sigfpe		(int junk)
{
	signal (SIGFPE, SIG_DFL);
	rerror ("Floating point exception", NULL);
}

addisubierr (a, b, r)
	int a, b, r;
{
	if (a > 0 && b > 0 && !(r > 0)) return 1;
	if (a < 0 && b < 0 && !(r < 0)) return 1;
	return 0;
}
	
execute		()
{
int	k, l, m, p, infmode, op;
union	insformat	rni;
union	fltformat	aux1, aux2;
double	auxdouble;
float	g;

	fprintf (stderr, "Running...\n");

	sp = -1;	/* Stack initially empty */
	ic = 0;		/* Instruction counter initially zero */
	mfree = 0;	/* Free list for ALLOC / FREE */
	mlast = STACKSIZE;	/* Last used by ALLOC */
	tracing = 0;	/* Tracing turned off */

	signal (SIGFPE, sigfpe); 

	for (k=0; k<NOFREGS; k++) reg [k] = 0;

	while (1) {

		/* Main loop */

		rni.word = code [ic];		/* Read next instruction */

		action   = rni.codes.operation;
		rf       = rni.codes.regflag;
		rn       = rni.codes.regnum;
		aval     = rni.codes.address;

		if (aval > MAXADDR) aval |= SADRMASK;

		if (tracing) {
			tracing--;
			infmode++;
		} else
			infmode = 0;


/* ========================================================================== */

		switch	(action) {

/* ========================================================================== */

		case	PUSH		:

	error = 0;
	csph ();

	stack [++sp] = stack [k = caddr()];

	if (infmode) trace ("PUSH", stack [sp], "from", k);

	break;

		case	PUSHI		:

	error = 0;
	stack [sp] = stack [k = caddi()];

	if (infmode) trace ("PUSHI", stack [sp], "from", k);

	break;

		case	PUSHA		:


	error = 0;
	csph ();

	stack [++sp] = caddr ();

	if (infmode) trace ("PUSHA", stack [sp], NULL, 0);

	break;

		case	DUP		:


	error = 0;
	csph ();
	cspl ();

	stack [sp+1] = stack [sp];
	sp++;

	if (infmode) trace ("DUP", stack [sp], NULL, 0);

	break;

		case	POP		:

	
	error = 0;
	cspl ();

	stack [k = caddr()] = stack [sp--];

	if (infmode) trace ("POP", stack [k], "to", k);

	break;

		case	POPI		:


	error = 0;
	cspl ();

	l = stack [sp--];

	stack [k=caddi()] = l;

	sp--;

	if (infmode) trace ("POPI", l, "to", k);

	break;

		case	CONSTI		:


	error = 0;
	csph ();

	stack [++sp] = code [aval];

	if (infmode) trace ("CONSTI", stack [sp], NULL, 0);

	break;

		case	CONSTR		:


	error = 0;
	csph ();

	stack [++sp] = code [aval];

	if (infmode) tracer ("CONSTR", stack [sp], NULL, 0);

	break;

		case	ADJUST		:


	error = 0;
	sp += code [aval];

	csph ();

	if (infmode) trace ("ADJUST", sp, NULL, 0);

	break;

		case	ALLOC		:


	error = 0;
	if ((k = code [aval]) <= 0)
		rerror ("Attempt to reserve nonpositive number of memory words",
			&k);

	for (l=mfree, m=0; l; l=stack[l+1]) {

		if (stack [l] >= k) break;
		m = l;
	}

	if (l) {
		if (m == 0) 
			mfree = stack [l+1];
		else
			stack [m+1] = stack [l+1];
	} else {
		if ((l = (mlast -= k+1)) <= sp + 1)
			rerror ("Memory overflow", NULL);

		stack [l] = k;
	}

	stack [++sp] = l+1;

	if (infmode) trace ("ALLOC", k, "at", l+1);

	break;

		case	SALLOC		:

	error = 0;
	
	if ((k = stack[sp]) <= 0)
		rerror ("Attempt to reserve nonpositive number of memory words",
			&k);

	for (l=mfree, m=0; l; l=stack[l+1]) {

		if (stack [l] >= k) break;
		m = l;
	}

	if (l) {
		if (m == 0) 
			mfree = stack [l+1];
		else
			stack [m+1] = stack [l+1];
	} else {
		if ((l = (mlast -= k+1)) <= sp + 1)
			rerror ("Memory overflow", NULL);

		stack [l] = k;
	}

	stack [sp] = l+1;

	if (infmode) trace ("SALLOC", k, "at", l+1);

	break;

		case	FREE		:


	error = 0;
	cspl ();

	p = stack [sp--] - 1;

	if ((p <= sp) || (p > STACKSIZE - 2) || ((k = stack [p]) < 1) ||
		(k >= STACKSIZE))
			rerror ("Illegal address to FREE", &k);
	
	if (p == mlast) 
		mlast += k+1;
	else {
		for (l=mfree, m=0; l; l = stack [l+1]) {
			if (stack [l] >= k) break;
			m = l;
		}

		if (m == 0) {
			stack [p+1] = mfree;
			mfree = p;
		} else {
			stack [m+1] = p;
			stack [p+1] = l;
		}
	}

	if (infmode) trace ("FREE", k, "at", p);

	break;

		case	ADDI		:

	
	cspa ();

	op = stack [sp-1];

	stack [sp-1] = stack [sp] + stack [sp-1];

	error = addisubierr (stack [sp], op, stack [sp-1]);

	sp--;

	if (infmode) trace ("ADDI", stack [sp], NULL, 0);

	break;

		case	ADDR		:


	error = 0;
	cspa ();

	aux1.integer = stack [sp];
	aux2.integer = stack [sp-1];

	aux1.real += aux2.real;

	stack [--sp] = aux1.integer;

	if (infmode) tracer ("ADDR", stack [sp], NULL, 0);

	break;

		case	SUBI		:

	
	cspa ();

	op = stack [sp-1];

	stack [sp-1] = stack [sp-1] - stack [sp];

	error = addisubierr (-stack [sp], op, stack [sp-1]);

	sp--;

	if (infmode) trace ("SUBI", stack [sp], NULL, 0);

	break;

		case	SUBR		:


	error = 0;
	cspa ();

	aux1.integer = stack [sp-1];
	aux2.integer = stack [sp];

	aux1.real -= aux2.real;

	stack [--sp] = aux1.integer;

	if (infmode) tracer ("SUBR", stack [sp], NULL, 0);

	break;

		case	MULI		:

	
	cspa ();

	auxdouble = (double) stack [sp-1] * (double) stack [sp];

	stack [sp-1] = stack [sp-1] * stack [sp];

	error = ( auxdouble != (double) stack [sp-1]);

	sp--;

	if (infmode) trace ("MULI", stack [sp], NULL, 0);

	break;

		case	MULR		:


	error = 0;
	cspa ();

	aux1.integer = stack [sp-1];
	aux2.integer = stack [sp];

	aux1.real *= aux2.real;

	stack [--sp] = aux1.integer;

	if (infmode) tracer ("MULR", stack [sp], NULL, 0);

	break;

		case	DIVI		:

	
	error = ((stack [sp] == 0) ||
		 (stack[sp-1] == MININT && stack[sp] == -1));
	cspa ();

	if (!error) stack [sp-1] = stack [sp-1] / stack [sp];

	sp--;

	if (infmode) trace ("DIVI", stack [sp], NULL, 0);

	break;

		case	DIVR		:


	error = 0;
	cspa ();

	aux1.integer = stack [sp-1];
	aux2.integer = stack [sp];

	aux1.real /= aux2.real;

	stack [--sp] = aux1.integer;

	if (infmode) tracer ("DIVR", stack [sp], NULL, 0);

	break;

		case	MOD		:

	
	error = ((stack [sp] == 0) ||
		 (stack[sp-1] == MININT && stack[sp] == -1));
	cspa ();

	if (!error) stack [sp-1] = stack [sp-1] % stack [sp];

	sp--;

	if (infmode) trace ("MOD", stack [sp], NULL, 0);

	break;

		case	ITOR		:

	
	error = 0;
	cspl ();

	aux1.real = (float) stack [sp];

	stack [sp] = aux1.integer;

	if (infmode) tracer ("ITOR", stack [sp], NULL, 0);

	break;

		case	RTOI		:

	aux1.integer = stack [sp];
	
	error = ((((double) aux1.real) > (double) MAXINT) ||
				(((double) aux1.real) < (double)MININT));

	cspl ();

	stack [sp] = (int)(aux1.real);

	if (infmode) trace ("RTOI", stack [sp], NULL, 0);

	break;

		case	EQI		:

	
	error = 0;
	cspa ();

	stack [sp-1] = (stack [sp-1] == stack [sp]);

	sp--;

	if (infmode) trace ("EQI", stack [sp], NULL, 0);

	break;

		case	EQR		:


	error = 0;
	cspa ();

	aux1.integer = stack [sp-1];
	aux2.integer = stack [sp];

	stack [--sp] = (aux1.real == aux2.real);

	if (infmode) trace ("EQR", stack [sp], NULL, 0);

	break;

		case	LTI		:

	
	error = 0;
	cspa ();

	stack [sp-1] = (stack [sp-1] < stack [sp]);

	sp--;

	if (infmode) trace ("LTI", stack [sp], NULL, 0);

	break;

		case	LTR		:


	error = 0;
	cspa ();

	aux1.integer = stack [sp-1];
	aux2.integer = stack [sp];

	stack [--sp] = (aux1.real < aux2.real);

	if (infmode) trace ("LTR", stack [sp], NULL, 0);

	break;

		case	GTI		:

	
	error = 0;
	cspa ();

	stack [sp-1] = (stack [sp-1] > stack [sp]);

	sp--;

	if (infmode) trace ("GTI", stack [sp], NULL, 0);

	break;

		case	GTR		:


	error = 0;
	cspa ();

	aux1.integer = stack [sp-1];
	aux2.integer = stack [sp];

	stack [--sp] = (aux1.real > aux2.real);

	if (infmode) trace ("GTR", stack [sp], NULL, 0);

	break;

		case	OR		:

	
	error = 0;
	cspa ();

	stack [sp-1] = (stack [sp-1] || stack [sp]);

	sp--;

	if (infmode) trace ("OR", stack [sp], NULL, 0);

	break;

		case	AND		:

	
	error = 0;
	cspa ();

	stack [sp-1] = (stack [sp-1] && stack [sp]);

	sp--;

	if (infmode) trace ("AND", stack [sp], NULL, 0);

	break;

		case	NOT		:

	
	error = 0;
	cspl ();

	stack [sp] = !stack [sp];

	if (infmode) trace ("NOT", stack [sp], NULL, 0);

	break;

		case	IFZ		:


	error = 0;
	cspl ();

	if (!stack [sp--]) ic = aval - 1;

	if (infmode) trace ("IFZ", stack [sp+1], "to", aval);

	break;

		case	IFNZ		:


	error = 0;
	cspl ();

	if (stack [sp--]) ic = aval - 1;

	if (infmode) trace ("IFNZ", stack [sp+1], "to", aval);

	break;

		case	GOTO		:


	error = 0;
	ic = aval - 1;

	if (infmode) trace ("GOTO", 0, "to", aval);

	break;

		case	STOP		:


	exit (0);

		case	CALL		:


	error = 0;
	csph ();

	stack [++sp] = ic;

	csph ();

	stack [++sp] = reg [rn];

	ic = aval - 1;

	reg [rn] = sp+1;

	if (infmode) trace ("CALL", rn, "to", aval);

	break;

		case	RET		:
	

	error = 0;
	cspa ();

	reg [rn] = stack [sp--];

	ic = stack [sp--];

	if (infmode) trace ("RET", rn, "to", ic+1);

	break;

		case	READI		:


	csph ();

	error = scanf ("%d", &k);
	
	error = (!error) || (error == EOF);

	stack [++sp] = k;

	if (infmode) trace ("READI", k, NULL, 0);

	break;

		case	READR		:


	csph ();

	error = scanf ("%f", &g);

	error = (!error) || (error == EOF);

	aux1.real = g;

	stack [++sp] = aux1.integer;

	if (infmode) tracer ("READR", stack [sp], NULL, 0);

	break;

		case	READC		:


	csph ();

	error = (stack [++sp] = getchar ()) == EOF;

	if (infmode) trace ("READC", stack [sp], NULL, 0);

	break;

		case	WRITEI		:


	error = 0;
	cspl ();

	printf ("%10d", stack [sp--]);

	if (infmode) trace ("\nWRITEI", stack [sp+1], NULL, 0);

	break;

		case	WRITER		:


	error = 0;
	cspl ();

	aux1.integer = stack [sp--];

	printf ("%f", (float)(aux1.real));

	if (infmode) tracer ("\nWRITER", stack [sp+1], NULL, 0);

	break;

		case	WRITEC		:


	error = 0;
	cspl ();

	putchar (stack [sp--]);

	if (infmode) trace ("\nWRITEC", stack [sp+1], NULL, 0);

	break;


	/* Debugging aids */

		case	TRACE		:

	
	error = 0;
	tracing = code [aval];

	break;

		case	DUMP		:
	

	error = 0;
	dumpstack (CONT);

	break;

		case	IFERR		:

	if (error) ic = aval - 1;

	if (infmode) trace ("IFERR", error, "to", aval);

	error = 0;

	break;

		default			:

	rerror ("Illegal instruction", &action);


/* ========================================================================== */


		}	/* End switch */

		ic++;
	}	/* End while */
}

dumpstack	(act)
int	act;
{
int	k, l;
union	cti		aux1;
union	fltformat	aux2;

	printf ("\n\n                    STACK CONTENTS\n");
	printf (    "                    ==============\n\n");
	printf ("Location     Integer        Octal       Floating     Char\n");

	for (k=(act?(sp>19?sp-20:0):0); k<=sp; k++) {

		aux2.integer = aux1.pattern = stack [k];
		printf ("%8d %11d  %11o %14e     %c%c%c%c\n", k, stack[k],
			stack [k], aux2.real,
	((aux1.chs.ca > 31) && (aux1.chs.ca < 127)) ? aux1.chs.ca : '-',
	((aux1.chs.cb > 31) && (aux1.chs.cb < 127)) ? aux1.chs.cb : '-',
	((aux1.chs.cc > 31) && (aux1.chs.cc < 127)) ? aux1.chs.cc : '-',
	((aux1.chs.cd > 31) && (aux1.chs.cd < 127)) ? aux1.chs.cd : '-');

	}
}

pfs	(s, n)

char	*s;
int	n;
{
int	k;

	for (k=0; k < n && *s != '\0'; s++) {
		if (*s != '\n') k++;
		putchar (*s);
	}

	while (k++ < n) putchar (' ');
}

trace	(s1, n1, s2, n2)

char	*s1, *s2;
int	n1, n2;

{
int	k;

	pfs (s1, KWDSIZE);
	printf ("(%1d o'%1o') ", n1, n1);
	if (s2 != NULL) {
		pfs (s2, 5);
		printf ("(%1d o'%1o') ", n2, n2);
	}
	printf (" sp = (%1d o'%1o') ic = (%1d o'%1o')\n", sp, sp, ic, ic);
}

tracer	(s1, n1, s2, n2)

char	*s1, *s2;
int	n1, n2;

{
int	k;

	pfs (s1, KWDSIZE);
	printf ("(%g o'%1o') ", *((float*)(&n1)), n1);
	if (s2 != NULL) {
		pfs (s2, 5);
		printf ("(%g o'%1o') ", *((float*)(&n2)), n2);
	}
	printf (" sp = (%1d o'%1o') ic = (%1d o'%1o')\n", sp, sp, ic, ic);
}

rerror (t, q)
char	*t;
int	*q;
{
int	k;

	fprintf (stderr,"Runtime error: %s", t);
	if (q != NULL) {
		fprintf (stderr,"   (%d, %o)", *q, *q);
	}
	fprintf (stderr,"\n");

	printf  (       "Runtime error: %s", t);
	if (q != NULL) {
		printf  (       "   (%d, %o)", *q, *q);
	}
	printf  (       "\n");

	k = ((sp<0) || (sp>=STACKSIZE)) ? 0 : stack [sp];

	printf(
	"Executing instruction at address %d,  SP = %d, C(SP) = %d (%o)\n",
		ic, sp, k, k);
	fprintf(stderr,
	"Executing instruction at address %d,  SP = %d, C(SP) = %d (%o)\n\n",
		ic, sp, k, k);

	dumpstack (ABORT);

	exit (1);
}



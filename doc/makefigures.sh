#/bin/sh
for f in *.eps
do
	epstopdf $f
done

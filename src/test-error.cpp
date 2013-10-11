#include <iostream>
#include "error.hpp"
#include "errormanager.hpp"
#include <iostream>
using namespace std;
int main(int argc, const char * argv[])
{
    
    Meow::Error * err = new Meow::Error("String", 1);
    Meow::Error * err2 = new Meow::Error("String2", 2);
    Meow::Error * err3 = new Meow::Error("String3", 3);
    
    Meow::ErrorManager * manager = new Meow::ErrorManager();
    manager->addError(*err);
    manager->addError(*err2);
    manager->addError(*err3);
    
    manager->printErrors();
    cout << "End of Error Printing\n";
	return 0;
}
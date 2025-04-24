#include <iostream>
#include <string>

//class : describes the structure
//object : a specific example of that structure (instance)
//instance - another name for object
//instantiating - creating an object from a class
//data members - variables
//methods - functions

//abstraction -- a concept where you make something easy by hiding the complicated stuff
//encapsulation -- grating access to private data only through controlled public interface
//inheritance -- we can create derived classes that inherit properties from their paent class
//polymorphism -- we can treat multiple different objects as their base object type

class person {
    public: 
        std::string first;
        std::string last;

        void printFullName() {
            std::cout << first << " " << last << std::endl;
        }
};

int main() {
    //create an object  (instantiating )
    person p;
    p.first = "Nikhil";
    p.last = "Mane";

    p.printFullName();
    return 0;

    // person p2;
    // p2.first = "simon";
    // p2.last  = "k";
}
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


//encapsulation -- grating access to private data only through controlled public interface
class person {

    private:
        std::string first;
        std::string last;

    public: 
        // it can have same name
        // void setFirstName(std::string firstName)
        // {
        //     first = firstName;
        // }

        void setFirstName(std::string first)
        {
            this->first = first;
        }

        void setLastName(std:: string last)
        {
            this->last = last;
        }

        std::string getName()
        {
            return first + " " + last;
        }


        void printFullName() {
            std::cout << first << " " << last << std::endl;
        }
};

int main() {
    //create an object  (instantiating )
    person p;
    p.setFirstName("Nikhil");
    p.setLastName("Mane");

    p.printFullName();
    std::cout << p.getName() << std::endl;
    return 0;

    // person p2;
    // p2.first = "simon";
    // p2.last  = "k";
};
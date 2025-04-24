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


//constructor : method , specific purpose is to instanciate objects from your class. 
//should have the exact name as your class

class person {

    private:
        std::string first;
        std::string last;

    public: 

        //initialize a constructor (1st mnethod)
        person(std::string first, std::string last) : first(first), last(last) {}

        //initialize a constructor (2nd method)
        // person(std::string first, std::string last)
        // {
        //     this->first = first;
        //     this->last = last;
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

    person p("Nikhil", "Mane");
   

    p.printFullName();
    std::cout << p.getName() << std::endl;
    return 0;

    // person p2;
    // p2.first = "simon";
    // p2.last  = "k";
};
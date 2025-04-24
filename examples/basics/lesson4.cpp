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


//inheritance:  we can create derived classes that inherit properties from their paent class

// Parent class (base class) - inherited from
// child class (derived class) - does the inheriting


class person {

    private:
        std::string first;
        std::string last;

    public: 

       
        person(std::string first, std::string last) : first(first), last(last) {}
       
        
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

// employee is the derived class
//when you inherite something all the public stuff becomes private hence add public before the parent class
class employee : public person {

    std::string department;
    public:
        employee(std::string firstName, std::string lastName, std::string department) 
            : person(firstName, lastName), department(department) {}
        std::string getDepartment(){
            return department;
        }

        void setDepartment(std::string department)
        {
            this->department = department;
        }

        void printInfo(){
            std::cout << "name: " << getName() << std::endl;
            std::cout << "department : " << department << std::endl;
        }


};

int main() {

  employee e("first", "last", "sales");
  e.printFullName();
  std::cout << e.getDepartment() << std::endl;
  e.printInfo();
  return 0;

};
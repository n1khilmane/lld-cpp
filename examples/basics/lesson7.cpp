#include <iostream>
#include <string>
#include <vector> 

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

//polymorphism : animal : dog,cat,monkey 

class person {
    protected:
        std::string first;
        std::string last;

    public: 
        person(std::string first, std::string last) : first(first), last(last) {}
        
        void setFirstName(std::string first) {
            this->first = first;
        }

        void setLastName(std::string last) {
            this->last = last;
        }

        std::string getName() {
            return first + " " + last;
        }

        void printFullName() {
            std::cout << first << " " << last << std::endl;
        }

        virtual void printInfo() {
            std::cout << "first name: " << first << std::endl;
            std::cout << "last name : " << last << std::endl; 
        }
};

class employee : public person {
    private:
        std::string department;
    public:
        employee(std::string firstName, std::string lastName, std::string department) 
            : person(firstName, lastName), department(department) {}
            
        std::string getDepartment() {
            return department;
        }

        void setDepartment(std::string department) {
            this->department = department;
        }

        void printInfo() override {
            std::cout << "first name: " << first << std::endl;
            std::cout << "last name : " << last << std::endl; 
            std::cout << "department : " << department << std::endl;
        }
};

int main() {
    std::vector<person*> people;
    person p("Nikhil", "Mane");
    employee e("first", "last", "sales");

    people.push_back(&p);
    people.push_back(&e);

    for(person* p : people) {
        p->printInfo();
    }
    return 0;
}
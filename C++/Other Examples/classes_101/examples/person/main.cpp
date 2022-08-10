#include <iostream>

using namespace std;

class Person {

public:
    //Person(){};
    void SetPerson(string person){
        m_person = person;
    }

    void SetAge(int age){
        m_age = age;

    }


protected:

    string m_person;

    int m_age;

};


class Faculty: public Person{


public:


    void CallFaculty() {


        cout << m_person << " made a call to faculty!" << endl;


    }

};


class Student: public Person {

public:


    void ReceiveGrade() {

        cout << m_person << " received a grade!" << endl;


    }


};


int main () {

    Student student1;

    student1.SetPerson("Sam");

    student1.SetAge(23);

    Faculty faculty1;

    faculty1.SetPerson("Yvonne");

    faculty1.SetAge(45);


    student1.ReceiveGrade();


    student1.CallFaculty();


    return 0;


}
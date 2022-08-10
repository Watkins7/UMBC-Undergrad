#include <iostream>
using namespace std;

class Student{

public:
    string name = "";
    string address = "";
};

void printStudent(const Student &s)
{
    cout << s.name << "  " << s.address << "  " << s.rollNo;
}

int main(){
    Student s1;
    printStudent(s1);
    return 0;
}

/*
 Explanation of "const &<variable>"

    It speeds up the code execution, it offers usage simplicity and it also ensures the caller that you can not change the value of the variable by setting const keyword.

    Work easily with object(don't think about pointers)
It does not copy the Student object(so it is fast)
You can not create a new student and assign it to s variable. if you write s=new Student(); the compiler error will happen.
 So the caller can pass the variable with more confidence.
The parameter can not be null.

    As it is known that const keyword makes the variable immutable(by programmer) in the particular part of code e.g. the function body.
    So compiler can take advantage of it and make code optimized.
Also using const keyword prevents you from modifying the variable unintentionally.
When you declare a variable as type& then the call is made by call by reference so changes made in the variable is reflected in original(variable which is passe to function) variable also.
 Note you can achieve the same by using pointer. But pointer handling is complex(both, in terms of coding like referencing, using -> operator etc; as well as logical)

 */
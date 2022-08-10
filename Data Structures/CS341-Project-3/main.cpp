// CMSC 341 - Fall 2020 - Project 3
// driver.cpp: sample driver for the PQueue class.
// Author: William Atkins
// Email: watkins7@umbc.edu
// Date: 9/10/20
// Purpose: Informational Skew Heap

#include "pqueue.h"
using namespace std;
// Priority functions compute an integer priority for a patient.  Internal
// computations may be floating point, but must return an integer.

int priorityFn1(const Patient &patient);
int priorityFn2(const Patient &patient);
int priorityFn3(const Patient &patient);
int priorityFn4(const Patient &patient);

bool copyConstructorTest();
void selfAssignmentTest();
bool mergeWithQueueTest();
void hugeTest();

int main() {

    // Create a patient queue with capacity five and priority function
    // priorityFn1()
    PQueue queue1(priorityFn1);
    PQueue queue2(priorityFn1);

    // Create some test jobs and insert them into the queue
    //Patient(string name, int triage, int temp, int ox, int rr, int hr, int bp)
    Patient patient1("Sam", 1, 37, 79,  36, 133, 75);
    Patient patient2("Liz", 5, 37, 98, 26,  70, 100);
    Patient patient3("Nick", 2, 37, 85, 34, 125, 85);
    Patient patient4("Eva", 4, 37, 95,  22, 115, 95);

    queue1.insertPatient(patient3);
    queue1.insertPatient(patient1);
    queue1.insertPatient(patient2);
    queue1.insertPatient(patient4);

    std::cout << "\nqueue1 dump after inserting 4 patients (Nick, Sam, Liz, Eva):" << std::endl;
    queue1.dump();

    Patient patient5("John", 3, 39, 91, 27, 115, 110);
    Patient patient6("Mia", 3,  33, 93, 28, 118, 98);

    queue2.insertPatient(patient5);
    queue2.insertPatient(patient6);

    std::cout << "\nqueue2 dump after inserting 2 patients (John, Mia):" << std::endl;
    queue2.dump();

    queue1.mergeWithQueue(queue2);

    // Print the queue, change priority function, print again, change
    // again, print again.  Changing the priority function should cause
    // the heap to be rebuilt.
    std::cout << std::endl << "Contents of queue1 after merging with queue2:\n";
    queue1.printPatientQueue();
    std::cout << "\nDump queue1 after merging with queue2:\n";
    queue1.dump();

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Changing priorities
    queue1.setPriorityFn(priorityFn2);

    std::cout << std::endl << "Contents of queue1 after changing the priority function to priorityFn2:\n";
    queue1.printPatientQueue();
    std::cout << "\nDump queue1 after changing the priority function to priorityFn2:\n";
    queue1.dump();

    queue1.setPriorityFn(priorityFn1);

    std::cout << std::endl << "Contents of queue1 after changing the priority function back to priorityFn1:\n";
    queue1.printPatientQueue();
    std::cout << "\nDump queue1 after changing the priority function back to priorityFn1:\n";
    queue1.dump();

    // Remove and print jobs in priority order
    std::cout << "\nFinal queue1 in priority order:\n";
    while (queue1.numPatients() > 0) {
        Patient patient = queue1.getNextPatient();
        std::cout << "[" << priorityFn1(patient) << "] " << patient << std::endl;
    }

    cout << "===========================================================================================================" << endl;
    cout << "                                William Thaddeus Atkins Extra Test Special                                 "  << endl;
    cout << "===========================================================================================================" << endl;


    // Copy constructor test
    cout << "Copy Constructor Test:  " << endl;
    if ( copyConstructorTest() ){
        cout << "Copy Constructor Test Passed.  Copy constructed a null heap, regualer heap." << endl;
    }
    else {
        cout << "Copy Constructor Test Failed." << endl;
    }
    cout << endl << endl;


    // Self Assignment test
    cout << "Self Assignment Test: " << endl;
    selfAssignmentTest();
    cout << endl << endl;


    // MergewithQueueTest
    cout << "mergeWithQueue Test: " << endl;
    if ( mergeWithQueueTest() ){
        cout << "Was able to complete mergeWithQueue Test" << endl;
    }
    else {
        cout << "Was unable to complete mergeWithQueue Test" << endl;
    }
    cout << endl << endl;

    // Huge test
    cout << "bigQueue Test:  " << endl;
    hugeTest();


    return 0;
}

bool mergeWithQueueTest(){

    PQueue queue1(priorityFn1);
    PQueue queue2(priorityFn2);

    // Create some test jobs and insert them into the queue
    //Patient(string name, int triage, int temp, int ox, int rr, int hr, int bp)
    Patient patient1("Sam", 1, 37, 79,  36, 133, 75);
    Patient patient2("Liz", 5, 37, 98, 26,  70, 100);
    Patient patient3("Nick", 2, 37, 85, 34, 125, 85);
    Patient patient4("Eva", 4, 37, 95,  22, 115, 95);

    queue1.insertPatient(patient3);
    queue1.insertPatient(patient1);
    queue2.insertPatient(patient3);
    queue2.insertPatient(patient1);

    // Different priority test
    try {
        cout << "Trying to merge different priority queues." << endl;
        queue1.mergeWithQueue(queue2);
    }
    catch (exception &err) {
        cout << "Error expected:  " << err.what();
    }
    cout << endl;

    // Merging with itself
    try {
        cout << "Trying to merge queue with itself." << endl;
        queue1.mergeWithQueue(queue1);
    }
    catch (exception &err) {
        cout << "Error expected:  " << err.what();
    }
    cout << endl;

    // Merging null queues
    PQueue queue3(priorityFn1);
    PQueue queue4(priorityFn1);
    cout << "Trying to merge two null queues: ";
    queue3.mergeWithQueue(queue4);
    cout << "Succesful" << endl;
    cout << endl << endl;

    // Suze print test
    cout << "Size test: " << endl;
    cout << "Expected size 0: " << queue3.numPatients() << endl;
    cout << endl << endl;

    // Null heap print test
    cout << "Null heap print test: " << endl;
    queue3.dump();
    queue4.printPatientQueue();
    cout << endl << endl;

    return true;
}

// Huge test
void hugeTest(){

    // Create a patient queue with capacity five and priority function
    // priorityFn1()
    PQueue queue1(priorityFn3);
    PQueue queue2(priorityFn3);

    // Create some test jobs and insert them into the queue
    //Patient(string name, int triage, int temp, int ox, int rr, int hr, int bp)
    Patient patient1("Sam", 1, 31, 78,  36, 133, 75);
    Patient patient2("Liz", 5, 32, 77, 26,  70, 100);
    Patient patient3("Nick", 2, 33, 76, 34, 125, 85);
    Patient patient4("Gene", 4, 34, 75,  22, 115, 95);
    Patient patient5("Bob", 1, 35, 74,  36, 133, 75);
    Patient patient6("Linda", 5, 36, 73, 26,  70, 100);
    Patient patient7("Louise", 2, 37, 72, 34, 125, 85);
    Patient patient8("Tina", 4, 38, 71,  22, 115, 95);

    queue1.insertPatient(patient5);
    queue1.insertPatient(patient7);
    queue1.insertPatient(patient3);
    queue1.insertPatient(patient1);

    queue2.insertPatient(patient2);
    queue2.insertPatient(patient8);
    queue2.insertPatient(patient4);
    queue2.insertPatient(patient6);

    // Insert and display
    std::cout << "\nqueue1 dump after inserting 4 patients (Bob, Louise, Nick, Sam):" << std::endl;
    cout << "Expected:  " << "((((37:Louise)35:Bob)33:Nick)31:Sam)" << endl;
    cout << "Actual: ";
    queue1.dump();
    cout << endl << endl;

    // Insert and Display
    std::cout << "\nqueue2 dump after inserting 4 patients (Liz, Tina, Gene, Linda):" << std::endl;
    cout << "Expected:  (((38:Tina)36:Linda)32:Liz(34:Gene))" << endl;
    cout << "Actual: ";
    queue2.dump();
    cout << endl << endl;

    // Merge and display
    std::cout << "\nqueue1 MERGE with queue2 dump:" << std::endl;
    cout << "Expected:  ((((38:Tina)36:Linda)32:Liz(34:Gene))31:Sam(((37:Louise)35:Bob)33:Nick))" << endl;
    queue1.mergeWithQueue(queue2);
    cout << "Actual: ";
    queue1.dump();
    cout << "See if queue2 is empty" << endl;
    queue2.dump();
    cout << endl << endl;

    // Pop min, change priority and display
    std::cout << "\nqueue1 pop min, and change priority:" << std::endl;
    cout << "Expected:  ((((77:Liz)75:Gene)73:Linda(74:Bob))71:Tina((76:Nick)72:Louise))" << endl;
    Patient PatientA = queue1.getNextPatient();
    queue1.setPriorityFn(priorityFn4);
    cout << "Actual: ";
    queue1.dump();
    cout << endl << endl;

    // Clear and display
    std::cout << "\nClear queue1:" << std::endl;
    queue1.clear();
    queue1.dump();

    cout << "Completed big test." << endl;
}

// Test for selfAssignment
void selfAssignmentTest(){

    PQueue queue1(priorityFn1);

    Patient patient1("Sam", 1, 37, 79,  36, 133, 75);
    Patient patient2("Liz", 5, 37, 98, 26,  70, 100);
    Patient patient3("Nick", 2, 37, 85, 34, 125, 85);
    Patient patient4("Eva", 4, 37, 95,  22, 115, 95);

    queue1.insertPatient(patient3);
    queue1.insertPatient(patient1);
    queue1.insertPatient(patient2);
    queue1.insertPatient(patient4);

    queue1 = queue1;

    cout << "Set Queue1 = Queue1" << endl;
    cout << "Should be no valgrind issues." << endl;
    cout << "Expected tree:  " << "(((4:Eva)2:Nick)1:Sam(5:Liz))" << endl;
    cout << "Actual tree:  ";
    queue1.dump();


}

// Test for copy constructor
bool copyConstructorTest(){

    PQueue queue1(priorityFn1);

    // Null heap test
    PQueue queue2 = queue1;

    // Make sure queue has no nodes
    if ( queue2.numPatients() != 0){
        return false;
    }

    cout << "Copy Constructed null heap contains zero nodes." << endl;

    try {
        throw queue2.getNextPatient();
    }
    catch( exception &err){

        cout << "Caught execption trying to access patients in an empty list: " << err.what() << endl;

    }

    // Regular Copy contrustion test
    Patient patient1("Sam", 1, 37, 79,  36, 133, 75);
    Patient patient2("Liz", 5, 37, 98, 26,  70, 100);
    Patient patient3("Nick", 2, 37, 85, 34, 125, 85);
    Patient patient4("Eva", 4, 37, 95,  22, 115, 95);

    queue1.insertPatient(patient3);
    queue1.insertPatient(patient1);
    queue1.insertPatient(patient2);
    queue1.insertPatient(patient4);

    // Copy test
    PQueue queue3 = queue1;

    cout << "Queue1 is: ";
    queue1.dump();
    cout << "Queue3 copy constructed: ";
    queue3.dump();

    return true;

}

int priorityFn1(const Patient&patient) {
    int pri = 5;
    if ((patient.getOxygen()<80 && (patient.getRR() > 35 || patient.getRR() < 8)) ||
        (patient.getHR() > 130 && patient.getBP() < 80))
        pri = 1;
    else if (((patient.getOxygen() >= 80 && patient.getOxygen() <= 89) &&
              (patient.getRR() >= 31 && patient.getRR() <= 35)) ||
             (patient.getTemperature() >= 40 || patient.getTemperature() <= 32))
        pri = 2;
    else if ((patient.getOxygen() >= 90 && patient.getOxygen() <= 94) &&
             (patient.getRR() >= 26 && patient.getRR() <= 30))
        pri = 3;
    else if ((patient.getOxygen() >= 95 && patient.getOxygen() <= 97) &&
             (patient.getRR() >= 21 && patient.getRR() <= 25))
        pri = 4;
    else
        pri = 5;
    return pri;
}

int priorityFn2(const Patient&patient) {
    //priority only based on triage
    //traige is set by a health care professional
    return patient.getTriage();
}

// Test priority based on temperature
int priorityFn3(const Patient&patient){
    return patient.getTemperature();
}

// Test priority based on oxygen
int priorityFn4(const Patient&patient){
    return patient.getOxygen();
}
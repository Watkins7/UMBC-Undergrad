#include "queue.h"
#include <iostream>

using namespace std;

int main() {

    // Make a queue and populate it with whatever you have around
    cout << "Empty int queue with enqueued items: " << endl;
    cout << "==============================================" << endl;
    Queue<int> intQueue;
    intQueue.enqueue(5);
    intQueue.enqueue(4);
    intQueue.enqueue(3);
    intQueue.enqueue(2);
    intQueue.enqueue(1);

    // See contents of queue
    intQueue.dump();

    cout << endl << "Copy Constructor Test of int queue: " << endl;
    cout << "==============================================" << endl;

    // Copy constructor test
    Queue<int> newQueue(intQueue);

    // See dump of constructor test
    newQueue.dump();

    cout << endl << "Assignment Operator Test of string queue: " << endl;
    cout << "==============================================" << endl;

    // Make test queues
    Queue<string> stringQueue1;
    Queue<string> stringQueue2;

    stringQueue1.enqueue("bubbles");
    stringQueue1.enqueue("bath");
    stringQueue1.enqueue("shower");
    stringQueue1.enqueue("shampoo");

    stringQueue2.enqueue("lawnmower");
    stringQueue2.enqueue("garage");
    stringQueue2.enqueue("tractor");
    stringQueue2.enqueue("mulch");

    // Show orginal queues
    cout << "Before operator assignment: " << '\n' << "String Queue 1:" << endl;
    stringQueue1.dump();
    cout << "String Queue 2:" << endl;
    stringQueue2.dump();
    cout << '\n' << '\n';

    // Assignment test
    stringQueue1 = stringQueue2;

    // Show what happens after
    cout << "After Assignment operator: " << '\n' << "String Queue 1:" << endl;
    stringQueue1.dump();
    cout << "String Queue 2:" << endl;
    stringQueue2.dump();

    return 0;
}

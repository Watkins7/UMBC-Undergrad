#include <iostream>

using namespace std;

struct Node{

    int m_data;

    Node* m_next;

};



class Queue{

public:

    Queue(){

        m_head = nullptr;

    }



    ~Queue() {

        Clear();

    }



    //Implement the copy constructor below:
    Queue(const Queue &passedQueue){

        m_head = nullptr;

        Node *temp = passedQueue.m_head;

        while (temp != nullptr){

            this->Enqueue(temp->m_data);

            temp = temp->m_next;
        }

    }


    //Implement the assignment operator below:
    Queue& operator=(const Queue &passedQueue){

        this->Clear();
        m_head = nullptr;


        Node *temp = passedQueue.m_head;

        while (temp != nullptr){
            this->Enqueue(temp->m_data);
            temp = temp->m_next;
        }

        return *this;
    }


    Queue& operator+(int newNodes){

        for(int i = 0; i < newNodes; i++){

            Enqueue(55);

        }

        return *this;

    }

    void Enqueue(int data){

        Node* newNode = new Node();
        newNode->m_data = data;
        newNode->m_next = nullptr;
        if(m_head == nullptr){
            m_head = newNode;
        }
        else {
            Node *current = m_head;
            while(current->m_next != nullptr) {

                current = current->m_next;

            }

            current->m_next = newNode;

        }

    }



    int Dequeue(){

        Node* oldHead = m_head;

        m_head = m_head->m_next;

        int data = oldHead->m_data;

        delete oldHead;

        return data;

    }



    void Clear(){

        while(m_head != nullptr) {

            Dequeue();

        }

    }



    void Print(){

        Node* temp = m_head;

        while (temp != nullptr){

            cout << temp->m_data << "->";

            temp = temp->m_next;

        }

        cout << "END" << endl;

    }



private:

    Node *m_head;

};



int main () {

    Queue q1;

    q1.Enqueue(5);

    q1.Enqueue(10);

    q1.Enqueue(20);

    Queue q2;

    q2 = q1 + 3;

    Queue q3(q1);

    q1.Print();

    q2.Print();

    q3.Print();

}
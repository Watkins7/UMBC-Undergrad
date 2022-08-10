#include <iostream>

using namespace std;



struct Node{
    Node(int data){
        m_data = data;

    }
    int m_data;
    Node* m_next;
};



class LinkedList{
public:
    LinkedList(){
        m_head = nullptr;
        m_size = 0;
    }


    void InsertBegin(Node* myNode){
        myNode->m_next = nullptr;
        if(m_head == nullptr){
            m_head = myNode;
        }else{
            myNode->m_next = m_head;
            m_head = myNode;
        }
        m_size++;
    }



//Write InsertAt
void InsertAt(Node *myNode, int location){

        Node *current = m_head;
        Node *previous = current;

        int count = 0;

        if (location == 0){
            m_head = myNode;
            myNode->m_next = previous;
            return;
        }

        while (count != location){

            previous = current;
            current = current->m_next;

            count++;

        }

        previous->m_next = myNode;
        myNode->m_next = current;





    }


    void DeleteEnd(){
        Node *cur = m_head;
        Node *prev = cur;
        if(m_head == nullptr){
            cout << "LL Empty" << endl;
            return;
        }else if(cur->m_next == nullptr){
            delete cur;
            m_head = nullptr;
        }else {
            while(cur->m_next != nullptr){
                prev = cur;
                cur = cur->m_next;
            }
            prev->m_next = nullptr;
            delete cur;
        }
        m_size--;
    }



//Write PrintList
void PrintList(){
        Node *temp = m_head;

        while (temp != nullptr){
            cout << temp->m_data << " ";
            temp = temp->m_next;
        }

        cout << endl;

    }




private:
    Node *m_head; //Head of the linked list
    int m_size; //Size of the linked list
};



int main () {
    LinkedList list;
    Node * newNode1 = new Node(5);
    Node * newNode2 = new Node(10);
    Node * newNode3 = new Node(15);
    list.InsertBegin(newNode1);
    list.InsertBegin(newNode2);
    list.InsertBegin(newNode3);
    Node * newNode4 = new Node(20);
    list.InsertAt(newNode4,0);
    list.PrintList(); //Should 20->15->10->5->END
    list.DeleteEnd();
    list.DeleteEnd();
    list.PrintList(); //Should output 15->END
    list.DeleteEnd();
    list.DeleteEnd();
    return 0;
}
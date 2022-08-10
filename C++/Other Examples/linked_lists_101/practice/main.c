#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int x;
    struct node *previous;
    struct node *next;

}node;

typedef struct listofNodes{

    struct node *Head;

}listofNodes;


void displayNodes(listofNodes *list){

    node *temp = list->Head;

    while(temp != NULL){
        printf("Value: %d  Address:%p  Previous:%p  Next:%p  \n",temp->x,&temp,&temp->previous,&temp->next);

        temp = temp->next;
    }

}


void addNode( int value , listofNodes *list){

    if (list->Head == NULL){
        list->Head = (node*)malloc(sizeof(node));
        list->Head->x = value;
        list->Head->next = NULL;
        list->Head->previous = NULL;

    }

    else{
        node *temp = list->Head;
        while (temp->next != NULL){
            temp = temp->next;
        }

        temp->next = (node*)malloc(sizeof(node));
        temp->next->x = value;
        temp->next->previous = temp;

        temp = temp->next;
        temp->next = NULL;


    }


}



void freeMemory(node *a){

    if (a == NULL){
        return;
    }

    else if (a->next == NULL)
        free(a);

    else
        freeMemory(a->next);


}



int main() {
    printf("Hello, World!\n");

    // Empty List
    typeof(listofNodes) *test;
    test = (listofNodes*)malloc(sizeof(listofNodes));
    test->Head = NULL;

    addNode(4,test);
    addNode(5,test);
    addNode(6,test);
    addNode(7,test);

    displayNodes(test);

    freeMemory(test->Head);


    return 0;
}

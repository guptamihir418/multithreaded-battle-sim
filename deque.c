#include "defs.h"

/*
  Function:  initDeque
  Purpose:   initializes the head and tail pointers to NULL
       in:   pointer to the deque
   return:   NULL
*/
void initDeque(DequeType *deque)
{
    deque->head = NULL;
    deque->tail = NULL;
}

/*
  Function:  addFighter
  Purpose:   adds fighter to the end of the deque
       in:   pointer to the deque and pointer to the fighter to be added
   return:   C_OK if successful, C_NOK if not
*/
int addFighter(DequeType *deque, FighterType *fighter){

    NodeType *currNode;
    NodeType *prevNode;
    NodeType *newNode;

    currNode = deque->head;
    prevNode = NULL;

    while(currNode != NULL){

        if(currNode == NULL){
            break;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }

    if(currNode != NULL){
        printf("Error: Current Node is not NULL\n");
        return C_NOK;
    }

    newNode = malloc(sizeof(NodeType));

    newNode->data = fighter;
    newNode->next = NULL;

    if(prevNode == NULL){
        deque->head = newNode;

        if(deque->tail == NULL){
            deque->tail = newNode;
        }
    }
    else{
        prevNode->next = newNode;
    }

    newNode->next = currNode;

    if(newNode->next == NULL){
        deque->tail = newNode;
    }

    return C_OK;

}

/*
  Function:  removeFighterFromFront
  Purpose:   removes fighter from the front of the deque
       in:   pointer to the deque
       out:   pointer to the removed fighter
   return:   C_OK if successful, C_NOK if not
*/

int removeFighterFromFront(DequeType *deque, FighterType **fighter){

    NodeType *currNode;
    currNode = deque->head;


    // Error checking, if list is empty
    if(currNode == NULL){
        printf("Error: List is empty, can't delete\n");
        *fighter = NULL;
        return C_NOK;
    }

    // base case if list has only one element
    if(currNode == deque->tail){
        
        deque->head = NULL;
        deque->tail = NULL;
        *fighter = currNode->data;
        free(currNode);
        return C_OK;
    }
    
    // if list has more than one element
    deque->head = currNode->next;
    *fighter = currNode->data;
    free(currNode);
    return C_OK;

}




/*
  Function:  removeFighterFromBack
  Purpose:   removes fighter from the back of the deque
       in:   pointer to the deque
       out:   pointer to the removed fighter
   return:   C_OK if successful, C_NOK if not
*/

int removeFighterFromBack(DequeType *deque, FighterType **fighter){

    NodeType *currNode;
    NodeType *prevNode;

    currNode = deque->head;
    prevNode = NULL;

    while(currNode != NULL){

        // that means we are at the tail, and our prevNode is the one before the tail
        if(currNode->next == NULL){
            break;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }

    if(currNode == NULL){
        printf("Error: List is empty, can't delete\n");
        *fighter = NULL;
        return C_NOK;
    }

    if(prevNode == NULL){
        deque->head = currNode->next;
    }
    else {
        prevNode->next = currNode->next;
    }

    deque->tail = prevNode;

    *fighter = currNode->data;

    free(currNode);

    return C_OK;
}


/*
  Function:  deepCopyDeque
  Purpose:   makes the deep copy of the deque
       in:   pointer to the deque
       out:   pointer to the removed fighter
   return:   C_OK if successful, C_NOK if not
*/

int deepCopyDeque(DequeType *deque, DequeType *copy){

    if(deque->head == NULL){
        printf("Error: List is empty, can't copy\n");
        return C_NOK;
    }

    NodeType *currNode;
    currNode = deque->head;

    while(currNode != NULL){
        FighterType *copyFighter;
        deepCopyFighter(currNode->data, &copyFighter);
        addFighter(copy, copyFighter);

        currNode = currNode->next;

    }

    return C_OK;

}

/*
  Function:  checkEmptyDeque
  Purpose:   Checks if the deque is empty
       in:   pointer to the deque
   return:   C_OK if successful, C_NOK if not
*/

int checkEmptyDeque(DequeType *deque){

    if(deque->head == NULL && deque->tail == NULL){
        return C_OK;
    }

    return C_NOK;
}

/*
  Function:  cleanupDeque
  Purpose:   cleans up the deque
       in:   pointer to the deque
   return:   nothing
*/

void cleanupDeque(DequeType *deque){

    NodeType *currNode;
    NodeType *nextNode;

    currNode = deque->head;

    while(currNode != NULL){

        nextNode = currNode->next;
        free(currNode->data);
        free(currNode);

        currNode = nextNode;
    }

}


//
//  LinkedList.cpp
//

#include <stdio.h>
#include "LinkedList.h"

LinkedList::LinkedList()
{// Constructor: Inits an empty singly-linked list
	head = NULL;
	listSize = 0;
}

LinkedList::~LinkedList()
{// Destructor: Destroys the singly-linked list
	for (Node* curr=head; curr!=NULL;){
		Node* to_delete = curr;
		curr=curr->next;
		delete to_delete;
	}
}

int LinkedList::size()
{// Returns the size of the singly-linked list
	return listSize;
}

bool LinkedList::contains(int x)
{// Returns true if x is in the list, otherwise returns false
	for(Node* curr = head; curr!=NULL; curr=curr->next)
		if(curr->data == x)
			return true;

	return false;
}

bool LinkedList::add(int x)
{// Adds x if not already in the list and returns true, otherwise returns false
	Node** curr; // Pointer for a pointer
	for (curr=&head; *curr!=NULL; curr=&(*curr)->next){
		if ((*curr)->data == x)
			return false;
	}

  	// Node* new_node = new Node;
  	// new_node.data = x;
  	// new_node.next = NULL;
  	(*curr) = new Node{x,NULL};
  	listSize++;
  	return true;
}    

bool LinkedList::remove(int x)
{// Removes x if in the list and returns true, otherwise returns false
	for (Node** curr = &head; *curr!=NULL; curr=&(*curr)->next){
		if ((*curr)->data == x){
			Node* to_delete = *curr;
			*curr = (*curr)->next;
			delete to_delete;
			listSize--;
			return true;
		}
	}
	
	return false;
} 

void LinkedList::print()
{// Prints the content of the singly-linked list
	for (Node* curr=head; curr!=NULL; curr=curr->next){
		printf("%d ", curr->data);
	}
	printf("\n");
}       
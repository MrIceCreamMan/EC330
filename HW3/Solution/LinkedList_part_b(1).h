//
//  LinkedList.h (ver.2)
//  Linked_List_Template
//

#ifndef LinkedList_h
#define LinkedList_h

#include <stdio.h>
#include <iostream>

using namespace std;

/* A singly-linked list node */
template <typename T>
struct Node
{
    T data;
    Node *next;
};

/* A class for a singly-linked list */
template <typename T>
class LinkedList
{
public:
  LinkedList();       // Constructor: Inits an empty singly-linked list
  ~LinkedList();      // Destructor: Destroys the singly-linked list 
  int size();         // Returns the size of the singly-linked list
  bool contains(T x);  // Returns true if x is in the list, otherwise returns false
  bool add(T x);    // Adds x if not already in the list and returns true, otherwise returns false
  bool remove(T x); // Removes x if in the list and returns true, otherwise returns false
  void print();       // Prints the content of the singly-linked list

private:
  Node<T> *head;         // Pointer to head of singly-linked list
  int listSize;       // Size of singly-linked list
};

template <typename T>
LinkedList<T>::LinkedList()
{// Constructor: Inits an empty singly-linked list
	head = NULL;
	listSize = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{// Destructor: Destroys the singly-linked list
	for (Node<T>* curr=head; curr!=NULL;){
		Node<T>* to_delete = curr;
		curr=curr->next;
		delete to_delete;
	}
}

template <typename T>
int LinkedList<T>::size()
{// Returns the size of the singly-linked list
	return listSize;
}

template <typename T>
bool LinkedList<T>::contains(T x)
{// Returns true if x is in the list, otherwise returns false
	for(Node<T>* curr = head; curr!=NULL; curr=curr->next)
		if(curr->data == x)
			return true;

	return false;
}

template <typename T>
bool LinkedList<T>::add(T x)
{// Adds x if not already in the list and returns true, otherwise returns false
	Node<T>** curr; // Pointer for a pointer
	for (curr=&head; *curr!=NULL; curr=&(*curr)->next)
		if ((*curr)->data == x)
			return false;

  	(*curr) = new Node<T>{x,NULL};
  	listSize++;
  	return true;
}    

template <typename T>
bool LinkedList<T>::remove(T x)
{// Removes x if in the list and returns true, otherwise returns false
	for (Node<T>** curr = &head; *curr!=NULL; curr=&(*curr)->next){
		if ((*curr)->data == x){
			Node<T>* to_delete = *curr;
			*curr = (*curr)->next;
			delete to_delete;
			listSize--;
			return true;
		}
	}
	
	return false;
} 

template <typename T>
void LinkedList<T>::print()
{// Prints the content of the singly-linked list
	for (Node<T>* curr=head; curr!=NULL; curr=curr->next){
		cout << curr->data << " ";
	}
	printf("\n");
}

#endif /* LinkedList_h */
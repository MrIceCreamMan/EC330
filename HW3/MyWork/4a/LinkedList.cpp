//My name is Zhuohao Yang,
//My BU ID is U01579972

#include "LinkedList.h"
#include <iostream>
using namespace std;


LinkedList::LinkedList()
{
  listSize = 0;
  head = NULL;
}

LinkedList::~LinkedList()
{
  int i = 0;
  while (i<listSize) {
    Node *temp = head;
    head = head->next;
    delete temp;
    i++;
  } 
}

int LinkedList::size(){
  return listSize;
}

bool LinkedList::contains(int x){
  Node *temp = head;
  int i = 0;
  if (listSize==0){
    return false;
  }
  while (i<listSize){
    if (temp->data==x)
      return true;
    temp = temp->next;
    i++;
  }
  return false;
}

bool LinkedList::add(int x){
  if (listSize==0){
    Node* node1 = new Node;
    node1->data = x;
    node1->next = NULL;
    head = node1;
    listSize = 1;
    return true;
  }
  if (this->contains(x)){
    cout << x << " is not added because it is already in the list" << endl;
    return false;
  }
  Node* node_more = new Node;
  node_more->data = x;
  node_more->next = NULL;
  Node *temp = head;
  int i = 0;
  for (;i<listSize-1;i++){
    temp = temp->next;
  }
  temp->next = node_more;
  listSize++;
  return true;
}

bool LinkedList::remove(int x){
  if (listSize == 0)
    return false;
  Node *temp = head;
  if (head->data == x){
    head = head->next;
    delete temp;
    listSize--;
    return true;
  }
  int i = 0;
  while (i<listSize-1){
    if (x == temp->next->data){
      Node *temp2 = temp->next;
      temp->next = temp->next->next;
      delete temp2;
      listSize--;
      return true;
    }
    temp = temp->next;
    i++;
  }
  return false;
}

void LinkedList::print(){
  Node *temp = head;
  int i = 0;
  cout << endl;
  while (i<listSize){
    cout << temp->data << " ";
    temp = temp->next;
    i++;
  }
  if (listSize==0)
    cout << "nothing yet";
  cout << endl;
}

#ifndef COLLECTION
#define COLLECTION
#include <iostream>
#include "list.hpp"

template <typename T>
class Collection;

template <typename T>
bool equal(const Collection<T>&, const Collection<T>&);

//---------[COLLECTION]---------
template <typename T>
class Collection {
public:
  Collection();
  void add(const T&);
  void remove(const T&);
  T last();
  void print();
  friend bool equal<T>(const Collection<T>&, const Collection<T>&);
private:
  node<T> *head;
};

//~~~~~~~~~~~CONSTRUCTOR~~~~~~~~~~~~~
//blank collection head is null
template <typename T>
Collection<T>::Collection() {
  head = nullptr;
}

//~~~~~~~~~~~~ADD~~~~~~~~~~~~~~~~~
//takes a value adder and adds a node to
//the collection holding value
template <typename T>
void Collection<T>::add(const T& adder) 
{
  node<T> *temp = new node<T>;
  temp->setData(adder);
  temp->setNext(head);
  head = temp;
}

//~~~~~~~~~~~~REMOVE~~~~~~~~~~~~~~~~~
//takes one const value rem and removes all
//nodes holding that value
template<typename T>
void Collection<T>::remove(const T& rem)
{

  node<T> *last = nullptr;
  node<T> *next;
  node<T> *current = head;

  while (current != nullptr) {

    next = current->getNext();
    if (current->getData() == rem) {
      if (last != nullptr)
			last->setNext(current->getNext());
      delete current; 
    }

    if (current != nullptr) 
      last = current;
    current = next;

  }
}

//~~~~~~~~~~~~LAST~~~~~~~~~~~~~~~~~
//Returns the head of the collection
template <typename T>
T Collection<T>::last() 
{
  return head->getData();
}

//~~~~~~~~~~~~PRINT~~~~~~~~~~~~~~~~~
//Prints all items in a collection
template<typename T>
void Collection<T>::print()
{
  node<T> *printer = head;

  while (printer != nullptr) 
  {
    std::cout << printer->getData() << " ";
    printer = printer->getNext();
  }

  std::cout << std::endl;
}

//~~~~~~~~~~~~EQUAL~~~~~~~~~~~~~~~~~
//returns true or false if the collections re the same
//pass two collections lhs and rhs to compare
template<typename T>
bool equal(const Collection<T>& lhs, const Collection<T>& rhs) 
{
  node<T> *left = lhs.head;
  node<T> *right = rhs.head;

  //both reached end
  if (left == nullptr && right == nullptr) 
  	return true;
  //one end one not
  else if (left == nullptr && right != nullptr) 
  	return false;
  else if (left != nullptr && right == nullptr) 
  	return false;
  //both not end
  else {
    while (left != nullptr && right != nullptr) {
      if (left->getData() != right->getData())  
      	return false;
      left = left->getNext();
      right = right->getNext();
    }
    if (left == nullptr && right != nullptr) 
    	return false;
    else if (left != nullptr && right == nullptr) 
    	return false;
  }
  return true;
}


#endif


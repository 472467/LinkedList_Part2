#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>

using namespace std;

class Student;

class Node{
 private:
  Student* info;
  Node* next;
  //int value; //G's example
 public:
  Node(Student* student);//constructor
  ~Node();//deconstructor
  Node* getNext();//get next node pointer
  Student* getStudent();//get student pointer
  Node* end();
  void erase();
  void push_back(Student* student);
  void setNext(Node* newNext);//set the next pointer to the corresponding node pointer
  //void setValue(int newValue);//G's example
  //int getValue(); //G's example
};

#endif

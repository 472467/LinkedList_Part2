/* WRITTEN BY BRENDAN
PROGRAM THAT YOU INPUT STUDENT INFO AND STUFF
NO GLOBAL VARIABLES THIS TIME
*/

#include <iostream>
#include <string>
#include <istream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iterator>
#include <iomanip>
#include "node.h"

using namespace std;


struct STUDENT{
	char fName [100];
	char lName [100];
	int id;
	float gpa;
};
bool translateMove(char* input, Node* n);
Node* copyNode(Node*, Node*, Node*);
//int studentNum = 0;

int main(){
	Student* s = new Student();
	s->setID(3333);
	Node* studentNode = new Node(s);
	
  system("clear");//initially clears command line 
  vector <STUDENT*>* v = new vector<STUDENT*>;//pointer of pointers
	char input[30];
	for(int x = 0; x < 30; x++){
		input[x]= '\0';
	}
	while(true){
		cout << "Welcome to the student directory. Please 'ADD', 'PRINT'(prints list of ALL students) or 'DELETE' a student. Type EXIT to quit.\n";
		cin.clear();
		cin.sync();//cleans cin
		cin.getline(input, 30);
		translateMove(input, studentNode);
	}
	
	
}

bool translateMove(char* input, Node* n){//converts input into a command that does stuff
	char in[100];
	if(strcasecmp(input, "ADD") == 0){//ignores capital letters
	  //system("clear");
	  Student *s = new Student();
	  char tmp [100];//work around for cin>> mixing with cin.getline segementation faults
		
		cout << "Input first name: ";
		cin.getline(in, 100);
		s->setFName(in);//uses arrow because it is a STUDENT pointer
		
		cout << "Input last name: ";
		cin.getline(in, 100);
		s->setLName(in);

		int id= 0;
		cout << "Input ID num: ";
		cin.getline(tmp, 100);
		istringstream buffer(tmp);//gets num as int first then converts it into an int
		buffer >> id;
		s->setID(id);
		
		float grade = 0;
		cout << "Input GPA: ";
		cin.getline(tmp, 100);
		istringstream buffer2(tmp);//same here
		buffer2 >> grade;
		s->setGPA(grade);

		Node* tNode = new Node(s);
		
		Node* recursedNode = n;

		while((recursedNode->getNext()) != NULL){
			
			recursedNode = recursedNode->getNext();
		}
		
		recursedNode->setNext(tNode);
		
		//(*v).push_back(s);//pushes it to end of vector
		return true;
	}else if(strcasecmp(input, "PRINT") == 0){//NEED ITERATOR THROUGH LIST HERE
	  
	    system("clear");
	    cout << fixed << showpoint;
	    cout << setprecision(2);//sets deicmal to be 5.00 even if just 5
		
		Node* recursedNode = n;
		Student* s = recursedNode->getStudent();
		try { 
			cout << endl <<  "Name: " << s->getFName() << ", ";
			cout << s->getLName();
			cout << " GPA: " << s->getGPA();
			cout << " ID: " << s->getID() << "\n\n";
		
			while((recursedNode->getNext()) != NULL){
				recursedNode = recursedNode->getNext();
				Student* s = recursedNode->getStudent();
				
				cout << "Name: " << s->getFName() << ", ";
				cout << s->getLName();
				cout << " GPA: " << s->getGPA();
				cout << " ID: " << s->getID() << "\n\n";
				
				
			}
			
		}catch (const std::exception& e) { 
			cout << "NO STUDENTS IN LIST" << endl;
		}
		
	    //cout << "\nName: " << (*(*it)).lName << ", " << (*it)->fName;
	    //cout << "\nID: " << (*it)->id;
	    //cout << "\nGPA: " << (*it)->gpa << "\n\n";//serparates the peopel
	  
	    
	}else if(strcasecmp(input, "DELETE") == 0){
		cout << "Please input the ID of the student you wish to delete: ";
		cin.getline(in,100);
		stringstream ss(in);//converts input to an int, to avoid that error
		int delID = 0;
		ss >> delID;
	  
		Node* recursedNode = n;
		Node* previousNode = NULL;
		bool nodeDeleted = false;
		int count = 0;
		bool running = true;
	  
		while(running){//makes sure it runs at least once
			if((recursedNode->getNext()) == NULL){//should run once more before it runs out of nodes
				running = false;
			}
			
			Student* s = recursedNode->getStudent();
			//cout << "Not aborted." << endl;
			cout << (recursedNode->getStudent())->getFName();
			
			if(s->getID() == delID){
				if((recursedNode->getNext()) != NULL && previousNode != NULL){//someone where between start and end, WORKS
					previousNode->setNext(recursedNode->getNext());
					
					delete recursedNode;
					running = false;
					
				}else if((recursedNode->getNext()) != NULL){//at start with things after it
					Node* currentSource = new Node(new Student());
					Node* currentNode = new Node(new Student());
					Node* nodeStore = copyNode(recursedNode->getNext(), currentSource, currentNode);
					
					delete recursedNode;
					recursedNode = nodeStore;
					running = false;
					
				}else{//at end or at start with no other nodes
					previousNode->setNext(NULL);
					
					delete recursedNode;
					running = false;
				}
				nodeDeleted = true;
			}
			if(!nodeDeleted){
				cout << "recursedNode set" << endl;
				previousNode = recursedNode;
				
				recursedNode = recursedNode->getNext();
			}
			
			count++;
		}
	  
	  return true;
	}else if(strcasecmp(input, "EXIT") == 0){
	  exit(0);//ends program
	}else{
	  return false;
	}
}

Node* copyNode(Node* toBeCloned, Node* currentSource, Node* currentNode){//OGSourceNode is the first node in list, currentSource is the current CloneList node, currentNode is node current node from toBeClonedList
	Node* OGSourceNode = new Node(new Student());
	if(currentNode != NULL){//prevents a null node from running shizzle
		
		if((currentNode->getStudent())->getID() == ((currentSource->getStudent())->getID())){//this runs if the currentNode is the first node in the list
			Student* clonedStudent = new Student();
		
			char* newFName = new char[80];
			char* newLName = new char[80];
			
			strcpy(newFName, (toBeCloned->getStudent())->getFName());
			strcpy(newLName, (toBeCloned->getStudent())->getLName());
			clonedStudent->setFName(newFName);
			clonedStudent->setLName(newLName);
			clonedStudent->setID((toBeCloned->getStudent())->getID());
			clonedStudent->setGPA((toBeCloned->getStudent())->getGPA());
			
			currentNode = new Node(clonedStudent);
			
			OGSourceNode = currentNode;//stores first of list
			currentSource = currentNode;
			if((toBeCloned->getNext()) != NULL){
				currentNode = toBeCloned->getNext();
				copyNode(toBeCloned, currentSource, currentNode);
			}
		}else{//this is all nodes after first
			Student* clonedStudent = new Student();
		
			char* newFName = new char[80];
			char* newLName = new char[80];
			
			strcpy(newFName, (currentNode->getStudent())->getFName());
			strcpy(newLName, (currentNode->getStudent())->getLName());
			clonedStudent->setFName(newFName);
			clonedStudent->setLName(newLName);
			clonedStudent->setID((currentNode->getStudent())->getID());
			clonedStudent->setGPA((currentNode->getStudent())->getGPA());
			
			Node* tmpNode = new Node(clonedStudent);
			
			currentSource->setNext(tmpNode);
			currentSource = tmpNode;
			
			if((currentNode->getNext()) != NULL){
				currentNode = currentNode->getNext();
				copyNode(toBeCloned, currentSource, currentNode);
			}
		}
		
	}
	
	if((OGSourceNode->getStudent())->getID() != 9999999){
		return OGSourceNode;
	}else{
		return NULL;
	}
}
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
bool translateMove(char* input, Node* n);//header stuff
void deleteNode(Node*, Node*, Node*, int, Node*);
Node* copyNode(Node*&, Node*, Node*);
void printNode(Node*, Node*);
void averageGPA(Node*, Node*, float&, int&);
void addSortNode(Node*, Node*, Node*, Node*);
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
		cout << "Welcome to the student directory. Please 'ADD', 'AVERAGE'(averages grades of all students), 'PRINT'(prints list of ALL students) or 'DELETE' a student. Type EXIT to quit.\n";
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

		Node* newNode = new Node(s);
		Node* previousNode = NULL;
		Node* current = n;
		
		addSortNode(n, current, newNode, previousNode);
		
		//(*v).push_back(s);//pushes it to end of vector
		return true;
	}else if(strcasecmp(input, "PRINT") == 0){//NEED ITERATOR THROUGH LIST HERE
	  
	    system("clear");
	    
		Node* currentNode = n;
		
		printNode(n, currentNode);	  
	    
	}else if(strcasecmp(input, "DELETE") == 0){
		cout << "Please input the ID of the student you wish to delete: ";
		cin.getline(in,100);
		stringstream ss(in);//converts input to an int, to avoid that error
		int delID = 0;
		ss >> delID;
		Node* tmpNode = n;
		Node* tmpPrevious = NULL;
		Node* ifAtStartWithThingsAfter = NULL;
		
		deleteNode(n, tmpNode, tmpPrevious, delID, ifAtStartWithThingsAfter);	
		
		return true;
	}else if(strcasecmp(input, "AVERAGE") == 0){//averages the gpa of the students in nodes
		float currentGPA =  0;
		int runTimes = 0;
		Node* current = n;
		averageGPA(n, current, currentGPA, runTimes);
		
		
		currentGPA/= (float)runTimes;
		
		cout << fixed << showpoint;
		cout << setprecision(2);
		cout << "\n\n AVERAGE GPA OF ALL STUDENTS: " << currentGPA << "\n\n";
		
	}else if(strcasecmp(input, "EXIT") == 0){
	  exit(0);//ends program
	}else{
	  return false;
	}
}

void addSortNode(Node* source, Node* current, Node* newNode, Node* previousNode){//adds an
	if((current->getStudent())->getID() > (newNode->getStudent())->getID()){//current node is GREATER than node to be added
		if(previousNode != NULL){
			newNode->setNext(current);
			previousNode->setNext(newNode);
		}else{
			Student* tmp = newNode->getStudent();
			if(current->getNext() != NULL){
				newNode->setNext(current->getNext());
			}
			current->setNext(newNode);//just swaps the students instead of doing some more complicated wizardry
			newNode->setStudent(current->getStudent());
			current->setStudent(tmp);
		}
	}else if((current->getStudent())->getID() < (newNode->getStudent())->getID()){//current node is LESS than node to be added
		if(current->getNext() != NULL){
			current = current->getNext();
			addSortNode(source, current, newNode, previousNode);
		}else{
			current->setNext(newNode);
		}
	}else{//current is EQUAL to newNode, means that this the first in the list(or some buffoon entered 2 identical ID numbers)
		if(current->getNext() != NULL){
			current = current->getNext();
			addSortNode(source, current, newNode, previousNode);
		}else{
			current->setNext(newNode);
		}
	}
}

void deleteNode(Node* sourceNode, Node* currentNode, Node* previousNode, int delID, Node* insurancePolicy){//deletes node through recursion
	bool running = true;
	Node* newNode = new Node(NULL);
	if((currentNode->getStudent())->getID() == delID){
		if((currentNode->getNext()) != NULL && previousNode != NULL){//someone where between start and end, WORKS
			previousNode->setNext(currentNode->getNext());
			
			delete currentNode;
			running = false;
			
		}else if((currentNode->getNext()) != NULL){//at start with things after it
		
			if((sourceNode->getNext())->getNext() !=  NULL){//have to do lots of null checking
				sourceNode->setStudent((sourceNode->getNext())->getStudent());
				sourceNode->setNext((sourceNode->getNext())->getNext());
				//cout << "Dank"<< endl;
			}else{
				sourceNode->setStudent((sourceNode->getNext())->getStudent());
				sourceNode->setNext(NULL);
			}

			delete newNode;

			running = false;
			
		}else{//at end or at start with no other nodes
			if(previousNode != NULL){
				previousNode->setNext(NULL);
				delete currentNode;
			}else{
				cout << "\nNot allowed to delete with only one student left.\n\n";
			}
			
			
			
			running = false;
		}
	}else{
		if(running){//dont want it to run again since shit gets deleted
			if(currentNode->getNext() != NULL){
				previousNode = currentNode;
				currentNode = currentNode->getNext();
				
				deleteNode(sourceNode, currentNode, previousNode, delID, insurancePolicy);//recursive
			}else{
				cout << "\n\nID not found.\n\n";
			}
		}
	}
	
}

void printNode(Node* sourceNode, Node* currentNode){//prints node thr
	if((sourceNode->getStudent())->getID() == (currentNode->getStudent())->getID()){//if the currentNode is the first node in the list
		try{//this runs to prevent an error when list is empty, probably never fails here
			cout << "\nName: " << (sourceNode->getStudent())->getLName() << ", " << (sourceNode->getStudent())->getFName();
			cout << "\nID: " << (sourceNode->getStudent())->getID();
			cout << fixed << showpoint;
			cout << setprecision(2);
			cout << "\nGPA: " <<  (sourceNode->getStudent())->getGPA() << "\n\n";
			
			if(sourceNode->getNext() != NULL){
				currentNode = sourceNode->getNext();
				printNode(sourceNode, currentNode);
			}
			
		}catch (const exception& e){
			cout << "StudentList is empty.";
		}

	}else{
		cout << "\nName: " << (currentNode->getStudent())->getLName() << ", " << (currentNode->getStudent())->getFName();
		cout << "\nID: " << (currentNode->getStudent())->getID();
		cout << fixed << showpoint;
		cout << setprecision(2);
		cout << "\nGPA: " << (currentNode->getStudent())->getGPA() << "\n\n";
		
		if(currentNode->getNext() != NULL){
			currentNode = currentNode->getNext();
			printNode(sourceNode, currentNode);
		}
	}
}

void averageGPA(Node* source, Node* current, float& currentGPA, int& runTimes){//averages gpas through recursion
	if(current->getNext() != NULL){
		currentGPA += (current->getStudent())->getGPA();
		runTimes++;//these variables remain when the function gets called again, kinda like a global but theyre local to another function
		current = current->getNext();
		averageGPA(source, current, currentGPA, runTimes);
	}else{
		currentGPA += (current->getStudent())->getGPA();
		runTimes++;
	}
	
}
//THIS FUNCTION IS UNUSED, phased out because it was unneeded wish it hadnt have spent so long on making this monstrosity
Node* copyNode(Node*& toBeCloned, Node* currentSource, Node* currentNode){//OGSourceNode is the first node in list, currentSource is the current CloneList node, currentNode is node current node from toBeClonedList
	
	Node* OGSourceNode = new Node(new Student());
	if(currentNode != NULL){//prevents a null node from running shizzle
		
		if((currentNode->getStudent())->getID() == ((currentSource->getStudent())->getID())){//this runs if the currentNode is the first node in the list
			Student* clonedStudent = new Student();
			
			char* newFName = new char[80];
			char* newLName = new char[80];

			strcpy(newFName, (toBeCloned->getStudent())->getFName());//CRASHES HERE

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
			cout << "Dank2" << endl;
		}else{//this is all nodes after first
			Student* clonedStudent = new Student();
			
			char* newFName = new char[80];
			char* newLName = new char[80];
			cout << "Dank3" << endl;
			strcpy(newFName, (currentNode->getStudent())->getFName());
			strcpy(newLName, (currentNode->getStudent())->getLName());
			clonedStudent->setFName(newFName);
			clonedStudent->setLName(newLName);
			clonedStudent->setID((currentNode->getStudent())->getID());
			clonedStudent->setGPA((currentNode->getStudent())->getGPA());
			
			Node* tmpNode = new Node(clonedStudent);
			cout << "Dank4" << endl;
			currentSource->setNext(tmpNode);
			currentSource = tmpNode;
			
			if((currentNode->getNext()) != NULL){
				currentNode = currentNode->getNext();
				copyNode(toBeCloned, currentSource, currentNode);
			}
		}
		
	}
	
	if((OGSourceNode->getStudent())->getID() != -1){//default ID is -1, as long as the default ID is changed the copy will be valid
		//clone = OGSourceNode;
		toBeCloned = OGSourceNode;
		return OGSourceNode;
	}else{
		return NULL;
	}
}
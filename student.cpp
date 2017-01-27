#include "student.h"

Student::Student(){
	fName = new char[80];
	lName = new char[80];
	id  = -1;
	gpa = 3.56;
	strcpy(fName, "Mike");// name purposelly NULL
	strcpy(lName, "Smith");

}

Student::~Student(){
	delete fName;
	delete lName;
	//delete gpa;
	//delete id;
}

char* Student::getFName(){
	return fName;
}

void Student::setFName(char* n){
	strcpy(fName, n);
}

char* Student::getLName(){
	return lName;
}

void Student::setLName(char* n){
	strcpy(lName, n);
}

int Student::getID(){
	return id;
}

void Student::setID(int i){
	id = i;
}

float Student::getGPA(){
	return gpa;
}

void Student::setGPA(float g){
	gpa  = g;
}


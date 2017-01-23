#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <cstring>

using namespace std;


class Student{
	
	private://
		char* fName;
		char* lName;
		int id;
		float gpa;
	public:
		Student();
		~Student();
		char* getFName();
		char* getLName();
		void setFName(char* );
		void setLName(char* );
		int getID();
		float getGPA();
		void setGPA(float);
		void setID(int);
		
};

#endif
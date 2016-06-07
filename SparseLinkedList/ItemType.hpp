#ifndef ITEMTYPE_HPP
#define ITEMTYPE_HPP

/*
   This header includes a generic itemtype, along with two derived classes:
     StudRecord and ClassRecord which are used for this class' assignment.

   The purpose of this is so that I could make a linked table by using different,
     and generic data types.



*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int NAME_LEN = 20;
const int STUD_ID_LEN = 10;
const int COURSE_TITLE_LEN = 33;
const int COURSE_NAME_LEN = 7;

enum RelationalType {  //Enum to keep track of objects "value" in comparison to others

  GREATER,   // Object is greater than other object
  LESS,      // Object is less than other object
  EQUAL      // Objects are equivalent

};

class ItemType
{
  public:
    ItemType();
	//Default Constructor

	inline void Read(ifstream& inFile) {inFile >> id;}
	//Reads ItemType from inFile; specifically, the id.

	inline void Write(ofstream& outFile) {outFile << id;}
	//Writes ItemType to outFile

	inline void SetId(int id) {this->id = id;}
	//Sets Id of ItemType manually

	inline void SetIdFromFile(ifstream& inFile) {inFile >> id;}
	//Sets id from inFile

	RelationalType ComparedTo(ItemType otherItem) const;
	//Compares two items based on their id

	void PrintHeader(ofstream& outFile) const;
	//Writes a header to outFile for formatting

	inline int GetId() const {return id;}
	//Returns the id of the item

  protected:
	int id;    //Identification number of item
};


enum StudStatus {
//Enum used for the different types of student standings

  FIRST = 1,   // First year student
  SECOND,      // Second year student
  THIRD,       // Third year student
  FOURTH,      // Fourth year student
  GRADUATE,    // Graduate student
  NONDEGREE    // Enrolled without pursuing degree
};

class StudRecord : public ItemType
{
  public:
	StudRecord();
	//Default constructor

	virtual void Read(ifstream& inFile);
	//Reads student record from inFile

	virtual void Write(ofstream& outFile) const;
	//Writes student record to outFile

	virtual void PrintHeader(ofstream& outFile) const;
	//Writes header for outFile formating

	void SetNameFromFile(ifstream& inFile);
	//Set the name of student name from inFile

	virtual void SetIdFromFile(ifstream& inFile);
	//Sets the id of student from inFile

	inline string GetName() const {return name;}
	//Returns name of student

	inline void SetName(string name) {this->name = name;}
	//Manually set the name of student

  protected:
	string name;        // Name of student in format  [lastname], [firstname]
	string major;       // Major of student.  N/A for not degree enrolled
	int status;         // Class year of student. See StudStatus enum.

	string GetStatus() const; 
	// Gets the students standing as a string
  
};




class ClassRecord : public ItemType
{
  public:
    ClassRecord();
	//Default constructor

	virtual void Read(ifstream& inFile);
	//Reads student record from inFile

	virtual void Write(ofstream& outFile) const;
	//Writes student record to outFile

	virtual void PrintHeader(ofstream& outFile) const;
	//Prints a header for outFile formatting

	inline void AddStudent() {numOfStudReg++;}
	//Increases numbOfStudReg by 1 Precondition: numOfStudReg < classSize

	inline void DropStudent() {numOfStudReg--;}
	//Decreases numOfStudReg by 1 PreCondition: numOfStudReg > 0


  private:
    string profName;    // Class instructor's name
	string courseName;  // Course's name ex: CS316
	string courseTitle; // Course's title ex: Programming II
	int classSize;      // Maximum size of students that can register for course
	int numOfStudReg;   // Number of students currently registered

};

#endif
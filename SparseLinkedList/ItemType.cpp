#include "ItemType.hpp"

void IgnoreWhite(ifstream& inFile);

//************************
//  Object: ItemType
//************************

ItemType::ItemType()
//Default Constructor
{
  id = -1;
}

RelationalType ItemType::ComparedTo(ItemType otherItem) const
//Compares two items based on their id
{
  if(this->id > otherItem.id)
	return GREATER;
  else if(this->id < otherItem.id)
	return LESS;
  
  return EQUAL;
}

//******************************
//  Object: StudentRecord
//******************************

StudRecord::StudRecord()
//Default constructor
{
  ItemType();

  name = "zzzzzz";
  major = "ZZ";

}

void StudRecord::Read(ifstream& inFile)
{ 
  SetIdFromFile(inFile);
  SetNameFromFile(inFile);

  inFile >> status >> major;
}

void StudRecord::Write(ofstream& outFile) const
{
  outFile << left;

  outFile << setw(STUD_ID_LEN + 3) << id << setw(NAME_LEN) << name
	      << setw(6) << major << GetStatus() << endl;
}

void StudRecord::SetNameFromFile(ifstream& inFile)
{
  char tempName[NAME_LEN + 1];  //Create temporary storage for name to get from inFile in block
  inFile.get(tempName, NAME_LEN);
  name = tempName;
}

void StudRecord::SetIdFromFile(ifstream& inFile)
{
  inFile.ignore(1);
  char intStr[STUD_ID_LEN + 1];    //Create a temporary char string to get the id
  inFile.get(intStr, STUD_ID_LEN); //Get a string of the id
  
  for(int i = 0; i < STUD_ID_LEN - 1; i++)   // Loop to make sure string is all digits
    if(!isdigit(intStr[i]))
	  cout << "Could not parse inFile correctly! Is id length 9 digits?" << endl;

  id = atoi(intStr);               //Convert that string to an integer
}

void StudRecord::PrintHeader(ofstream& outFile) const
{
  outFile << left;

  outFile << setw(STUD_ID_LEN + 3) << "ID" << setw(NAME_LEN) << "Student Name"
	      << setw(6) << "Major" << "Class Standing" << endl;
  outFile << setw(STUD_ID_LEN + 3) << "--" << setw(NAME_LEN) << "------------"
	      << setw(6) << "-----" << "--------------" << endl;
}

string StudRecord::GetStatus() const
{
  switch(status)
  {
    case FIRST:
	    return "Freshman";
	case SECOND:
	    return "Sophomore";
	case THIRD:
	    return "Junior";
	case FOURTH:
		return "Senior";
	case GRADUATE:
		return "Graduate";
	case NONDEGREE:
		return "Non-Degree";
	default:
		return "Invalid student standing, check inFile!";
  }
}

//******************************
//  Object: ClassRecord
//******************************

ClassRecord::ClassRecord()
{
  profName = "zzzzzz";
  courseName = "zzzf354";
  courseTitle = "zzzz zzzzz zzz";
  classSize = -1;
  numOfStudReg = -1;


}

void ClassRecord::Read(ifstream& inFile)
{
  inFile >> id;
  inFile.ignore(1);
  
  char tempName[NAME_LEN + 1];
  inFile.get(tempName, NAME_LEN);
  profName = string(tempName);

  inFile.ignore(1);

  char tempCourse[COURSE_NAME_LEN + 1];
  inFile.get(tempCourse, COURSE_NAME_LEN);
  courseName = string(tempCourse);
  
  inFile.ignore(1);

  char tempCourseTitle[COURSE_TITLE_LEN + 1];
  inFile.get(tempCourseTitle, COURSE_TITLE_LEN);
  courseTitle = tempCourseTitle;

  inFile >> classSize >> numOfStudReg;

}

void ClassRecord::Write(ofstream& outFile) const
{
  outFile << left;

  outFile << setw(5) << id << setw(NAME_LEN + 1) << profName 
	      << setw(COURSE_NAME_LEN + 3) << courseName << setw(COURSE_TITLE_LEN + 1)
		  << courseTitle << setw(16) << classSize << numOfStudReg << endl;
}

void ClassRecord::PrintHeader(ofstream& outFile) const
{
  outFile << left;

  outFile << setw(5) << "Id" << setw(NAME_LEN + 1) << "Instructor" 
	      << setw(COURSE_NAME_LEN + 3) << "Course" << setw(COURSE_TITLE_LEN + 1)
		  << "Description" << setw(16) << "Capacity" << "Num Registered" << endl;

  outFile << setw(5) << "--" << setw(NAME_LEN + 1) << "----------" 
	      << setw(COURSE_NAME_LEN + 3) << "------" << setw(COURSE_TITLE_LEN + 1)
		  << "-----------" << setw(16) << "--------" << "--------------" << endl;  
}


//*********************
//HELPER FUNCTIONS
//*********************

void IgnoreWhite(ifstream& inFile)
//A helper function to ignore white space
{
  for(int i = 0; inFile.get() == ' '; i++)  // To get to next piece of data
	if(i > 256)
	{
	  cout << "Problem finding state in inFile!" << endl;
	  break;
	}

  inFile.unget();
}
/*
    Author :        Matthew Panzner
	
	Course :        CS316
	Prof   :        Tai-Chi Lee
	Due    :        10/2/2013

	About  :        This program is designed to implement a generic linked list
	                  for storing small registration database. (I made a linked table, instead)


    DevLog :        9/18/2013  ---- Created ItemType class and derived classes
	                           ---- Created SparsedLinkedList class with generic pointers

					9/20/2013  ---- Decided to make list and data entering polymorphic
					                  Introduced RowNode, ColumnNode, and CellNode templates
									  vs the classNode and studentNode, to make the code reusable
									  for future code.

					9/21/2013  ---- Finished all but delete functions for table
					           ---- Created debug functions to make sure everything points where I want
							   ---- Odd bug with cells occasionally the last cell in a row has a misplaced x coordinate throwing it off
							   ---- Bug was caused from not checking if the first cell was bigger than the one tryint to insert
							          fixed with a if statement in AddCell()
							   ---- Removed row pointers in structure map due to messy and lengthy code
							          if I reused this code, I would consider rebuilding that code better.
                   
				    9/22/2013 ---- Started the DeleteCell() method, but there seems to be a small bug
					                  that I will have to look into at a later time.

				    9/23/2013 ---- In DeleteCell() I added the ability to delete a column if it had no values
					                  and fixed a bug where searching for an ID that isn't there would cause a crash
									  The problem was I had the moreToSearch = (currentNode != NULL) before I moved to the
									  next node, oops.
					  		  ---- Finished deletion method.
							  ---- Added UpdateColumn(), very specific to this assignment
					 	      ---- Finished driver.

					9/25/2013 ---- Finished headers and formatting for output.
					          ---- Begun test data

					9/28/2013 ---- Found some small bugs that happen with other test data and fixed those
					                 Mostly formatting issues with empty lists when printing
                              ---- Testing complete, all test data works correctly
							  ---- Finished commenting Objects, especially in table



   NOTES
   **********************************************************************************************************
   *I would have liked to finish the table structure map, but it's a hassle with cout and unnecessary.
   
   *Making the table have 4 pointers, so you can traverse in all directions would also be a nice added feature.

   *Also repeated code in the table structure , such as, finding the current column and row, could have been
   made into a method, and if I had more time to do so, I would create that.
    
   *There are some functions that are specific for columns, but would also like to make them work
    for rows as well, such as update, however, for this assignment it's not necessary, and I don't
	have the freetime to create a truly generic table right now.

	UpdateColumn() is an example. It only updates the name, I would like to have it detect
	changes, rather than just force one specific change on it, because that is specific to the datatype,
	and I would rather it work for ALL data types.

   *I also wish to have had a stringstream in the table object that logged all errors and inputs,
     this would have a more clear log of everythign that has happened

   *Cells having 4 pointers to go every direction would also be a nice addition, but too much work
     for 2 weeks and limited free time.

****************************************************
  Identifier Dictionary:
    preCellRow refers to previous cell to a traversing column pointer, I use row because it is above
	           the cell pointer that is traversing the column.
	preCellColumn same as preCellRow, except with the traversing of a row, and it pointing to the cell left

  last code updated 9/28/2013
*/

#include <iostream>

#include "SparseLinkedList.hpp"
#include "ItemType.hpp"

const int CLASS_CAPACITY = 25; //Size of classes

int main()
{
  ifstream inFile("in.data");
  ofstream outFile("out.data");

  if(inFile.fail() || outFile.fail())
  {
    cout << "Problem with inFile or outFile! Terminating**" << endl;
	return -1;
  }

  SparseLinkedList<StudRecord, ClassRecord> table; //Stores all the data in a table structure

  char request; //Character that tells us the action being requested
  
  inFile >> request;
  
  while(inFile)
  {
    ClassRecord classRd; //temporary ClassRecord
    StudRecord studRd;  //temporary StudRecord
    int tempId;  //Temporarily store the id for student

	switch(request)
	{
	  case 'S':
           
		  //*************************************************************************
		  //NOTE:
		  //  In the AddCell method, rather than making a boolean
		  //    I probably should have made it so I detected errors
		  //    outside of the function, instead of detecting them in the function.
		  //    By the method I did, I end up finding the same row 3 times, had 
		  //    I just made it find it once, and lock the currentRow pointer there,
		  //    I wouldn't have had to keep doing that search.  
		  //  Unfortunately I'm finding this in my last stages, and don't have time 
		  //  to fix it, but I'll look for doing that earlier in the next assignment
		  //*************************************************************************

		  classRd.SetIdFromFile(inFile); //Parse input 
		  studRd.Read(inFile);           //Parse input

		  if(table.GetRowSize(classRd) > CLASS_CAPACITY)
		  {
			outFile << "*** Class #" << classRd.GetId() << " is full! Cannot add student# " 
                    << studRd.GetId() << "!" << endl;
			break;
		  }

		  if(!table.AddCell(studRd, classRd)) //Adds cell and see if it was successful
		  {
		    outFile << "*** Stud ID " << studRd.GetId() << " could not be added to class# " 
			        << classRd.GetId();

			if(table.FindRow(classRd)) //This tells us what kind of error message to print
			  outFile << " because they are already registered for this class!" << endl;
			else
			  outFile << " because class cannot be found!" << endl;
		  }
		  else
		    outFile << "Student ID " << studRd.GetId() << " was added to class ID " << classRd.GetId() << endl;
		  
		  break;

	  case 'C':
		  
		  classRd.Read(inFile);

		  if(!table.AddRow(classRd)) //Adds row and checks if it was succesful
		    outFile << "*** Class ID " << classRd.GetId() << " is already added to table!" << endl;
		  else
			outFile << "Class ID " << classRd.GetId() << " added to table." << endl;

		  break;

	  case 'D':

		  classRd.SetIdFromFile(inFile);  //Parse inFile
		  studRd.SetIdFromFile(inFile);   //Parse inFile
		  studRd.SetNameFromFile(inFile); //Parse inFile

		  if(!table.DeleteCell(classRd, studRd)) //Deletes cell and sees if it was successful
		    outFile << "*** Student ID " << studRd.GetId() << " could not be removed from class ID " 
			        << classRd.GetId() << " because they are not registered for this class!" << endl;
		  else
			outFile << "Student ID " << studRd.GetId() << " was dropped from class ID " << classRd.GetId()
			        << endl;		 

		  break;

	  case 'W':

		  inFile >> tempId;

		  studRd.SetId(tempId);

		  if(table.ColumnLengthIs() <= 0)
			outFile << "*** There are no students enrolled! Can't print an empty list!" << endl;
		  else
		  {
			outFile << endl << endl;
			outFile << "************************" << endl;
			outFile << "Print student's schedule" << endl;
			outFile << "************************" << endl;

			outFile << endl << endl;

		    table.PrintColumn(studRd.GetId(), outFile);

			outFile << endl << endl;
			outFile << "End Print" << endl;
			outFile << "***************************************************************" << endl;
			outFile << endl << endl;
		  }

		  break;

	  case 'P':

		  classRd.SetIdFromFile(inFile);
		
		  if(table.RowLengthIs() <= 0)
			outFile << "*** There are no classes! Can't print class list!" << endl;
		  else
		  {
			outFile << endl << endl;

		    if(classRd.GetId() == 9999) //This case we print every class and student
			{
			  outFile << "*********" << endl;
			  outFile << "Print All" << endl;
			  outFile << "*********" << endl;

			  outFile << endl << endl;

			  table.PrintTable(outFile);
			}
			else //else we just print the class with the coresponding id
			{
			  outFile << "******************" << endl;
			  outFile << "Print class roster" << endl;
			  outFile << "******************" << endl;

			  outFile << endl << endl;

			  table.PrintRow(classRd.GetId(), outFile);

			}

			outFile << endl << endl;
			outFile << "End Print" << endl;
			outFile << "***************************************************************" << endl;
			outFile << endl << endl;
		  }

		  break;

	  case 'U':

		  inFile >> tempId;

		  studRd.SetId(tempId);
		  studRd.SetNameFromFile(inFile);

		  if(!table.UpdateColumn(studRd))
			outFile << "*** Student ID " << studRd.GetId() << " could not be updated!" << endl;
		  else
			outFile << "Student ID " << studRd.GetId() << " had their name updated to " 
			        << studRd.GetName() << endl;

		  break;

	  default: //This shouldn't happen in this assignment, but to keep with the practice, it's to make sure there are
		  outFile << "ERROR WITH REQUEST TYPE***" << endl;                           // no unexpected requests
		  outFile << " Check input file!" << endl << endl;
		  inFile.ignore(256, '\n'); // skip this line

	}

	inFile >> request;
  }

  ofstream test("test.data");
  table.PrintColumnList(test);
  table.PrintRowList(test);

  table.PrintTableStructure();  //For debuging (function is only half complete)
  table.~SparseLinkedList();    //Free memory

  outFile << endl << endl;
  outFile << "End File*** " << endl;

  //Close files
  outFile.close();
  inFile.close();

  return 0;
}
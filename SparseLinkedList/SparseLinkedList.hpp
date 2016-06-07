#ifndef SPARSELINKEDLIST_HPP
#define SPARSELINKEDLIST_HPP

/*
   Example of the layout and data structures

             rowHead-> [ ]-->[ ]---->[ ]--->[ ]
			            |     |       V
columnHead-> [ ] -------|-----|---->[Cell]
              |         |     |       |
			  V         V     |       |
			 [ ]----->[Cell]  |       |
			  |               |       |
			  V               V       V
			 [ ] ---------->[Cell]->[Cell]

  
    This type of list is storing all data in a row, in a column
      and where the data intersects creates a cell with the 
      shared data.  
    This requires more memory, but it is easier much faster to print
      the list of a column, or in this case, the student


	NOTE
	  For the purpose of this table and the assignment,
	  the requirement is that columns must be added first; 
	    that is, you cannot create a cell with the creation of a row, 
		but you can create a cell while creating a new row

	Admittedly, this isn't the cleanest, and probably not the most efficient code 
	 for a sparse table, but I didn't expect it to take as much time as it did
	 so that's my fault. It works, but some of the code, such as adding and deleting cells
	 I would like to look into longer and see if there's a more efficient way of doing it
	  I noted one method in how I'd change it in the driver, which is to make error detection outside
	  of the add and delete, and find the current rows and columns in that error detection zone.

	**I commented a lot in the add and delete so the reader is able to tell what's at least happening
*/

#include <iostream> 
#include <fstream>

#include <vector> // for debugger

using namespace std;

struct Pos
// A struct for coordinates in the two dimensions
{
  int x;  // x coordinate
  int y;  // y coordinate
          // (x,y) being the position, y increasing the further you go down
};



//**************
//Nodes
//**************

template<class Column, class Row>
//Contains the intersecting cells , or actual data, of the spare table
struct CellNode
{
  Column columnData;				 // The data from the column
  Row rowData;						 // The data from the row
  Pos coordinates;		             // Keeps track of place on table
  CellNode<Column, Row>* nextColumn; // The pointer to the next column
  CellNode<Column, Row>* nextRow;    // The pointer to the next row
};

template<class Column, class Row>
struct ColumnNode
//Contains the column data in table
{
  Column data;								// The column data type
  int size;									// Number of cells in column
  int xPos;                                 // How far right column is
  ColumnNode<Column, Row>* nextColumn; // The pointer to the next column
  CellNode<Column, Row>* nextCell;     // the pointer to the cells right
};

template<class Column, class Row>
//Contains the row data in table
struct RowNode
{
  Row data;							 // The row data type
  int size;							 // Number of cells in row
  int yPos;                          // How far down row is
  RowNode<Column, Row>* nextRow;     // The pointer to the next row
  CellNode<Column, Row>* nextCell;   // The pointer to the cells below
};



//**********
//Class Obj
//**********

template<class Column, class Row>
class SparseLinkedList// A sparse table linked list.
//  Templated Data Types:
//        Column is the column data type
//        Row is the row data type
{
  public:
	SparseLinkedList();
	//Default constructor 

	~SparseLinkedList();
	//Deconstructor for table

	bool AddRow(Row data);
	//Add a row to the table
	//Returns true if row was added, otherwise false

	bool AddColumn(Column data);
	//Add a column to the table
	// Returns true if column added, otherwise false

	bool AddCell(Column columnData, Row rowData);
	//Adds a cell into the table
    // Also adds Column if column wasn't already in table (assignment specific functionality)
	//Returns true if added
	//Returns false if cell column or row couldn't be found, or cell was already in table

	bool DeleteCell(Row rowData, Column columnData);
	//Deletes a cell from the table
	// note: I have no deletion of rows and  columns since that 
	//         does not seem to be a condition for this assignment
	//         nor does a single cell deletion
	// Returns true if successfully deleted
	// Returns false if could not delete because it couldn't be found
	
	bool FindRow(Row rowData);
	//Finds the row based on id 
	// Returns true if found
	// Returns false if not found

	bool UpdateColumn(Column columnData);
	//Updates the column --- specifically the name of the person in the column and all
	// related cells
	//This method is specific for the assignment. Not all data will have a "name"
    //Returns true if updated
    //False if it could not be found

    int GetRowSize(Row data);
	//Tells user how many cells are in the row
	//  There is not one for the column, since this is assignment specific
	//  returns -1 if row doesn't exist

	void MakeEmpty();
    //Deletes the entire table column, rows, and cell

	void ResetTable();
	//Resets the row and column pointers to NULL 

	inline void ResetColumn() {currentColumn = NULL;}
	//Resets column pointer to NULL

	inline void ResetRow() {currentRow = NULL;}
	//Resets row pointer to NULL

	void PrintColumn(int columnId, ofstream& outFile) const;
	//Finds the coulmn with coulmnId and prints that column to outFile

	void PrintRow(int rowId, ofstream& outFile) const;
	//Finds the row with rowId and prints that column to outFile

	void PrintTable(ofstream& outFile) const;
	//Prints the entire table in two ways
	//  ---One going through columns pointers
	//  ---Two going through row pointers and printing

	inline int RowLengthIs() const {return rowLength;}
	//Returns the number of rows there are in the table

	inline int ColumnLengthIs() const {return columnLength;}
	//Returns the number of columns there are in the table

	int NumOfCellsInRow(int rowId) const;
	//Gets number of cells in the row given

	int NumOfCellsInColumn(int columnId) const;
	//Gets number of cells in column given



	//************************
	// DEBUG FUNCTIONS
	//************************

	void PrintColumnList(ofstream& outFile) const;
	//Prints all column types to outFile

	void PrintRowList(ofstream& outFile) const;
	//Prints all row types to outFile

	void PrintTableStructure() const;
	//Prints a map of the table to cout

  private:

    RowNode<Column, Row>* rowHead;          // Head pointer to rows
	RowNode<Column, Row>* currentRow;       // Pointer to current row

	ColumnNode<Column, Row>* columnHead;    // Head pointers to columns
	ColumnNode<Column, Row>* currentColumn; // Pointer to current column

	int columnLength;          // Number of columns
	int rowLength;             // Number of rows

};







//*****************************************
//IMPLEMENTATION OF SPARSELINKEDLIST CLASS
//
//
//
//*****************************************






template<class Column, class Row>
SparseLinkedList<Column, Row> :: SparseLinkedList()
//Default constructor

{
    rowHead = NULL;  
	columnHead = NULL;     

	columnLength = 0;          
	rowLength = 0;           
}

template<class Column, class Row> 
SparseLinkedList<Column,Row> :: ~SparseLinkedList()
//Deconstructor for table

{
  MakeEmpty();
}

template<class Column, class Row>
void SparseLinkedList<Column,Row> :: ResetTable()
{
  ResetColumn();
  ResetRow();
}

template<class Column, class Row>
bool SparseLinkedList<Column, Row> :: FindRow(Row data)
//Finds the row based on id 
// Returns true if found
// Returns false if not found
{
  RowNode<Column, Row>* location = rowHead;

  while(location != NULL)
  {
    if(data.ComparedTo(location->data) == EQUAL)
	  return true;

	location = location->nextRow;
  }

  return false;
}

template<class Column, class Row>
int SparseLinkedList<Column, Row> :: GetRowSize(Row data)
//Tells user how many cells are in the row
//  There is not one for the column, since this is assignment specific
//  returns -1 if row doesn't exist

{
  RowNode<Column, Row>* location = rowHead;

  while(location != NULL)
  {
    if(data.ComparedTo(location->data) == EQUAL)
	  return location->size;

	location = location->nextRow;
  }

  return -1; //Row doesn't exist
}

template<class Column, class Row> 
bool SparseLinkedList<Column,Row> :: AddColumn(Column data)
//Add a column to the table

{
  ColumnNode<Column, Row>* newNode;                 //New node to add to column
  ColumnNode<Column, Row>* previousNode = NULL;     //Keeps track of previous node
  ColumnNode<Column, Row>* location = columnHead;   //Keeps track of where to insert newNode

  int xPos = 0;  //How far right the column is

  while(location != NULL)
  {
    if(data.ComparedTo(location->data) == EQUAL) 
	{												//If this already exists in the column
      currentColumn = location;                     // just put currentColumn there, and exit 
	  return false;
	}

	previousNode = location;
	location = location->nextColumn;

	xPos++;
  }

  newNode = new ColumnNode<Column, Row>; // New column node
  newNode->data = data;
  newNode->xPos = xPos;
  newNode->nextCell = NULL;
  
  if(previousNode == NULL) //If there are no column nodes do this
  {
    newNode->nextColumn = columnHead;
	columnHead = newNode; 
  }
  else
  {
    newNode->nextColumn = location;
	previousNode->nextColumn = newNode;
  }

  columnLength++;

  currentColumn = newNode;

  return true;
}

template<class Column, class Row>
bool SparseLinkedList<Column, Row> :: AddRow(Row data)
//Add a row to the table

{
  RowNode<Column, Row>* newNode;                //New node for row
  RowNode<Column, Row>* previousNode = NULL;    //Keeps track of previous rowNode
  RowNode<Column, Row>* location = rowHead;     //Keeps track of where to insert

  int yPos = 0;  //How far down row is

  while(location != NULL)
  {
    if(data.ComparedTo(location->data) == EQUAL) 
	{												//If this already exists in the column
      currentRow = location;                        // just put rowColumn there, and exit 
	  return false;
	}

	previousNode = location;
	location = location->nextRow;

	yPos++;
  }

  newNode = new RowNode<Column, Row>;  // Create new rowNode and set it's data
  newNode->data = data;                //*
  newNode->yPos = yPos;                //*
  newNode->nextCell = NULL;            //*
  
  if(previousNode == NULL) // If there are no row nodes, do this
  {
    newNode->nextRow = rowHead;
	rowHead = newNode; 
  }
  else
  {
    newNode->nextRow = location;
	previousNode->nextRow = newNode;
  }

  rowLength++;

  currentRow = newNode;

  return true;
}

template<class Column, class Row> 
bool SparseLinkedList<Column,Row> :: AddCell(Column columnData, Row rowData)
//Adds a cell into the table
// Precondition is columnLength > 0
//	
// Also adds Column if column wasn't already in table (assignment specific functionality)
//Returns true if added
//Returns false if cell column or row couldn't be found, or cell was already in table

{
  ResetTable();


  //***************************
  //Find which row cell belongs
  //***************************

  currentRow = rowHead;
  bool found = false;

  while(currentRow != NULL)
  // Only need to do this with row, since the column is added to
  //   the table while adding the cell.  This function is specific to 
  //   the assignment.
  { 
	if(currentRow->data.GetId() == rowData.GetId())  //Find matching row
	{
	  found = true;
	  break;
	}

	currentRow = currentRow->nextRow;
  }

  if(!found)
	return false;


  //******************************
  //Find which column cell belongs
  //  and add column if not already
  //  in table
  //******************************

  AddColumn(columnData); //Also finds column 

  //Prepare Cell
  CellNode<Column, Row>* newCell ;

  newCell = new CellNode<Column, Row>;          //Create new cell
  newCell->columnData = currentColumn->data;    //Put input columnData into node
  newCell->rowData = currentRow->data;          //Put input rowData into node
  
  newCell->coordinates.x = currentColumn->xPos;
  newCell->coordinates.y = currentRow->yPos;	  

  //Connection Prep

  CellNode<Column, Row>* previousCell;
  CellNode<Column, Row>* location;

  //***********************
  //Connected Cell to Row
  //***********************

  previousCell = NULL;                //Trailing pointer
  location = currentRow->nextCell;    //Location to insert cell

  bool moreToSearch = (location != NULL);

  if(location != NULL && !(location->coordinates.x > newCell->coordinates.x))
    //Make sure that location doesn't start off with a higher x coordinate
    while(moreToSearch) 
    {  
	  if(location->columnData.ComparedTo(currentColumn->data) == EQUAL)
	  { //Signals if a cell in this spot has already been added

	    delete newCell; 

	    return false;
      }
	  


	  if(location->coordinates.x < newCell->coordinates.x)
		  //The new node belongs further right
	  {
        previousCell = location;
	    location = location->nextColumn;
		moreToSearch = (location != NULL);
	  }
	  else //
		moreToSearch = false;
    }

  if(previousCell == NULL) //Basically means we're connecting the cell
  {                        //  straight from the column
    newCell->nextColumn = currentRow->nextCell;
	currentRow->nextCell = newCell;
  }
  else
  {
    newCell->nextColumn = location;
	previousCell->nextColumn = newCell;
  }

  currentRow->size++;
  currentRow->data.AddStudent();
  
  //************************
  //Connected Cell to Column
  //************************

  previousCell = NULL;
  location = currentColumn->nextCell;
  moreToSearch = (location != NULL);

  if(location != NULL && !(newCell->coordinates.y < location->coordinates.y))
  // Make sure the first node is not too far down
    while(moreToSearch) 
    {
	  if(location->coordinates.y < newCell->coordinates.y)
	  {
	    previousCell = location;
	    location = location->nextRow;
		moreToSearch = (location != NULL);
	  }
	  else
		moreToSearch = false;
    }
  

  if(previousCell == NULL)
  {   //Connecting cell straight from the row
    newCell->nextRow = currentColumn->nextCell;
	currentColumn->nextCell = newCell;
  }
  else
  {
    newCell->nextRow = location;
	previousCell->nextRow = newCell;
  }

  currentColumn->size++;

  //Last but not least, we need to change the class size of all
  // cells in the updated row

  CellNode<Column, Row>* temp = currentRow->nextCell;

  while(temp != NULL)
  {
    temp->rowData.AddStudent();
	temp = temp->nextColumn;
  }

  return true; //Successfully added
}

template<class Column, class Row> 
bool SparseLinkedList<Column,Row> :: DeleteCell(Row rowData, Column columnData)
//Deletes a cell from the table
// note: I have no deletion of rows or columns since that 
//         does not seem to be a condition for this assignment
// Returns true if successfully deleted
// Returns false if could not delete either because it couldn't be found


{
  CellNode<Column, Row>* tempCellRow;     //Stores the deleted cell's row pointer
  CellNode<Column, Row>* tempCellColumn;  //Stores the deleted cell's column pointer
  CellNode<Column, Row>* preCellRow;      //Deleted cell's previous column's pointer
  CellNode<Column, Row>* preCellColumn;   //Deleted cell's previous row's pointer
  ColumnNode<Column, Row>* preColumnPtr;  //Trails the column pointer in case it needs deleting

  
                                            
  ResetTable();

  //Find cell through column
  currentColumn = columnHead;
  preColumnPtr = NULL;

  bool foundColumn = false;
  bool moreToSearch = (currentColumn != NULL);

  while(moreToSearch && !foundColumn)
  { 
    if(currentColumn->data.ComparedTo(columnData) == EQUAL)
	  //Found the appropriate column
	  foundColumn = true;
	else
	{
	  preColumnPtr = currentColumn;
	  currentColumn = currentColumn->nextColumn;
	  moreToSearch = (currentColumn != NULL);
	}

  }

  //Find Cell through Row
  currentRow = rowHead;
  preCellRow = NULL;

  bool foundRow = false;
  moreToSearch = (currentRow != NULL);

  while(moreToSearch && !foundRow)
  {
    if(currentRow->data.ComparedTo(rowData) == EQUAL)
	//Found the appropriate row
	  foundRow = true;
	else
	{
	  currentRow = currentRow->nextRow;
	  moreToSearch = currentRow != NULL;
	}
  }

  if(!foundRow || ! foundColumn)
	return false;
 

  //****************************************************************************
  //FOUND THE COLUMN AND ROW CELL IS LOCATED IN, PROCEED TO FIND THE CELL*******
  //****************************************************************************
  foundRow = false;
  foundColumn = false;


  //Through column

  if(currentColumn->nextCell != NULL) //and it shouldn't
  {
	preCellRow = NULL;                        //Keeps track of cell before the deleted one
	tempCellColumn = currentColumn->nextCell; //Finds cell to be deleted

	while(tempCellColumn != NULL && !foundColumn)
	{
	  if(tempCellColumn->rowData.ComparedTo(rowData) == EQUAL)
		//Cell has found the row with matching data via column node
		foundColumn = true;

	  else
	  {
	    preCellRow = tempCellColumn;
		tempCellColumn = tempCellColumn->nextRow;
	  }

	}
  }

  //Through Row
  
  if(currentRow->nextCell != NULL) //and this shoudln't as well
  {
    preCellColumn = NULL;                //Keeps track of previous cell to the one deleted
	tempCellRow = currentRow->nextCell;  //Finds cell to be deleted

	while(tempCellRow != NULL && !foundRow)
	{
	  if(tempCellRow->columnData.ComparedTo(columnData) == EQUAL)
	  // Cell has found the column with matching data via row node
		foundRow = true;

	  else
	  {
	    preCellColumn = tempCellRow;
		tempCellRow = tempCellRow->nextColumn;
	  }

	 
	}
  }

  if(!foundRow || !foundColumn) //If a match wasn't found in both row and column
	return false;               //  bad input if this isn't true
 


  //Connect the columns

  if(preCellRow == NULL)
    currentColumn->nextCell = tempCellColumn->nextRow;
  else
	preCellRow->nextRow = tempCellColumn->nextRow;


  //Connect the rows

  if(preCellColumn == NULL)
	currentRow->nextCell = tempCellRow->nextColumn;
  else
    preCellColumn->nextColumn = tempCellRow->nextColumn;

  
  delete tempCellColumn; //Delete cell 

  currentRow->size--;             //Row magnitude goes down
  currentColumn->size--;          //Column magnitude goes down
  currentRow->data.DropStudent(); //Dropped student


  //Check to make sure there's data left in the column
  // This is assignment specific, since rows are input just once
  // whereas column is input every time a student is add, so I can just
  // delete the column, or student in this case, and readd it if they register again

  if(currentColumn->nextCell == NULL)
  {
	if(currentColumn->nextColumn == NULL)
	{ 
	  preColumnPtr->nextColumn = NULL;	

	  delete currentColumn; //Delete unused column
	  currentColumn = NULL;
	}

	else
	{ //DID NOT ACCOUNT FOR DELETION OF HEAD**********
	  //Remove column
      preColumnPtr->nextColumn = currentColumn->nextColumn; 
	  delete currentColumn; //Delete unused column

	  preColumnPtr = preColumnPtr->nextColumn;


	  //FIX COORDINATES
	  while(preColumnPtr != NULL)
		  //Loop to adjust the x coordinates of the columns
	  { 
	    preColumnPtr->xPos--;     

		CellNode<Column, Row>* tempCell = preColumnPtr->nextCell;

		while(tempCell != NULL)
		  //Loop to adjust all the cell x coordinates in the column
		{
		  tempCell->coordinates.x = preColumnPtr->xPos;
		  tempCell = tempCell->nextRow;
		}

	    preColumnPtr = preColumnPtr->nextColumn;
	  }

    }


  }


  //Last but not least, we need to change the class size of all
  // cells in the updated row

  CellNode<Column, Row>* temp = currentRow->nextCell;

  while(temp != NULL)
  {
    temp->rowData.DropStudent();
	temp = temp->nextColumn;
  }

  return true; //Succesfully deleted
}

template<class Column, class Row> 
void SparseLinkedList<Column,Row> :: MakeEmpty()
//Deletes the entire table column, rows, and cell

{
  ColumnNode<Column, Row>* tempColPtr;
  RowNode<Column, Row>* tempRowPtr;             
  CellNode<Column, Row>* tempCellPtr;  
  CellNode<Column, Row>* trail;        // Trails the cell nodes for deletion since
                                           //  there is no head cell pointer


  while(rowHead != NULL)  // This loop deletes all of the rows and cells
  {
	tempCellPtr = rowHead->nextCell;


	while(tempCellPtr != NULL)
	{
	  trail = tempCellPtr;
	  tempCellPtr = tempCellPtr->nextColumn;
	  delete trail;
	}

    tempRowPtr = rowHead;
	rowHead = rowHead->nextRow;
	delete tempRowPtr;
  }
  
  rowLength = 0;

  while(columnHead != NULL) //Deletes the column list
  {
    tempColPtr = columnHead;
	columnHead = columnHead->nextColumn;
	delete tempColPtr;
  }

  columnLength = 0;
}

template<class Column, class Row>
bool SparseLinkedList<Column,Row> :: UpdateColumn(Column columnData)
//Updates the column --- specifically the name of the person in the column and all
// related cells
//This method is specific for the assignment. Not all data will have a "name"
//Returns true if updated
//False if it could not be found

{
  ResetTable();
  currentColumn = columnHead;
  bool found = false;

  while(currentColumn != NULL && !found)
  {
    if(currentColumn->data.ComparedTo(columnData) == EQUAL)
	  found = true;
	else
	{
	  currentColumn = currentColumn->nextColumn;
	}
  }

  if(!found)
	return false;

  currentColumn->data.SetName(columnData.GetName());

  CellNode<Column, Row>* cellPtr; //Traverses the cells in column

  cellPtr = currentColumn->nextCell;

  while(cellPtr != NULL)
  {
    cellPtr->columnData.SetName(currentColumn->data.GetName());
	cellPtr = cellPtr->nextRow;
  }

  return true; //Updated successfully
}

template<class Column, class Row> 
void SparseLinkedList<Column,Row> :: PrintColumn(int columnId, ofstream& outFile) const
//Finds the coulmn with coulmnId and prints that column

{
  ColumnNode<Column, Row>* columnPtr = columnHead;  //Pointer to print column
  
  bool found = false;
  
  while(columnPtr != NULL)
  {
	if(columnPtr->data.GetId() == columnId)
	{
	  found = true;  //Found matching id
	  break;         //break from loop
	}

    columnPtr = columnPtr->nextColumn; //Get next in column
  }


  if(found)
  {
	outFile << "Student |" << endl;
	outFile << "--------" << endl << endl;

	columnPtr->data.PrintHeader(outFile);
	columnPtr->data.Write(outFile); // Prints the column's data
	 
    CellNode<Column, Row>* tempCell;
	tempCell = columnPtr->nextCell; 

	outFile << endl;
	outFile << "Classes student is enrolled in |" << endl;
	outFile << "------------------------------- " << endl << endl;

	tempCell->rowData.PrintHeader(outFile);

	while(tempCell != NULL)
	{ 
	  tempCell->rowData.Write(outFile);  //Prints all the rows associated with column
	  tempCell = tempCell->nextRow;
	}
  }
  else //Wording is for clarity on the assignment
	outFile << "Could not find student# " << columnId << " to print!" << endl;
   

}


template<class Column, class Row> 
void SparseLinkedList<Column,Row> :: PrintRow(int rowId, ofstream& outFile) const
//Finds the row with rowId and prints that column

{
  RowNode<Column, Row>* rowPtr = rowHead;  //Pointer to print column
  
  bool found = false;
  
  while(rowPtr != NULL)
  {
	if(rowPtr->data.GetId() ==  rowId)
	{
	  found = true; //Found matching row id
	  break;        // break from loop
	}

    rowPtr = rowPtr->nextRow; // Get next in row 
  }


  if(found)
  {
	outFile << "Course |" << endl;
	outFile << "------- " << endl << endl;

	rowPtr->data.PrintHeader(outFile);
	rowPtr->data.Write(outFile); // Prints the column's data
	 
    CellNode<Column, Row>* tempCell;  // A temp pointer to all the cells in row
	tempCell = rowPtr->nextCell;     

	outFile << endl;
	outFile << "Students enrolled |" << endl;
	outFile << "------------------ " << endl << endl;

	tempCell->columnData.PrintHeader(outFile);

	while(tempCell != NULL)
	{ 
	  tempCell->columnData.Write(outFile);  //Prints all the rows associated with column
	  tempCell = tempCell->nextColumn;
	}
  }
  else //Wording is for clarity on the assignment
	outFile << "Could not find class# " << rowId << " to print!" << endl;

}

template<class Column, class Row> 
void SparseLinkedList<Column,Row> :: PrintTable(ofstream& outFile) const
//Prints the entire table in two ways
//  ---One going through columns pointers
//  ---Two going through row pointers and printing 

{
  outFile << "************************************" << endl;
  outFile << "PRINT ENTIRE TABLE     *************" << endl;
  outFile << "************************************" << endl << endl << endl;

  outFile << "******************" << endl;
  outFile << "Printing From Rows" << endl;
  outFile << "******************" << endl << endl << endl;

  CellNode<Column, Row>* cellPtr;
  RowNode<Column, Row>* rowPtr;

  rowPtr = rowHead;

  if(rowHead == NULL)
	outFile << "*** There are no classes! Cannot print table!" << endl;

  while(rowPtr != NULL)
  {
	outFile << "Course|" << endl;
	outFile << "------ " << endl << endl;

    rowPtr->data.PrintHeader(outFile);
	outFile << endl;

	rowPtr->data.Write(outFile);
	outFile << endl << endl;

	cellPtr = rowPtr->nextCell;

	outFile << "Students Enrolled|" << endl;
	outFile << "----------------- " << endl << endl;

	if(cellPtr != NULL) //Make sure the cell actually exists
	  cellPtr->columnData.PrintHeader(outFile); //Print header
	else
	  outFile << "*** There are no students enrolled in this class!" << endl;
	
	while(cellPtr != NULL)
	{
	  cellPtr->columnData.Write(outFile);
	  cellPtr = cellPtr->nextColumn;
	}

	outFile << endl;
	outFile << "---------------------------------------------------------" 
		    << endl << endl << endl;

	rowPtr = rowPtr->nextRow;
  }

  outFile << endl << endl;

  outFile << "*********************" << endl;
  outFile << "Printing from Columns" << endl;
  outFile << "*********************" << endl << endl << endl;


  ColumnNode<Column, Row>* columnPtr;
  columnPtr = columnHead;

  if(columnHead == NULL) //Error if students aren't in list
	outFile << "*** There are no students in table! cannot print" << endl;

  while(columnPtr != NULL)
  {
	outFile << "Student|" << endl;
	outFile << "------- " << endl << endl;

    columnPtr->data.PrintHeader(outFile);
	outFile << endl;

	columnPtr->data.Write(outFile);
	outFile << endl << endl;

	cellPtr = columnPtr->nextCell;

	outFile << "Courses Taken|" << endl;
	outFile << "------------- " << endl << endl;

	if(cellPtr != NULL) //Make sure the cell has data
	  cellPtr->rowData.PrintHeader(outFile);
	else
	  outFile << "*** This student isn't registered in any classes!" << endl;
	
	while(cellPtr != NULL)
	{ 
	  cellPtr->rowData.Write(outFile);
	  cellPtr = cellPtr->nextRow;
	}

	outFile << endl;
	outFile << "----------------------------------------------------------------------------------" 
		    << endl << endl << endl;

	columnPtr = columnPtr->nextColumn;
  }
}


//**************************************************
// DEBUG
//**********************

template<class Column, class Row> 
void SparseLinkedList<Column,Row> :: PrintColumnList(ofstream& outFile) const
{
  ColumnNode<Column, Row>* columnPtr = columnHead;

  while(columnPtr != NULL)
  {
	outFile << columnPtr->xPos << endl;
    columnPtr->data.Write(outFile);
	columnPtr = columnPtr->nextColumn;
  }
}

template<class Column, class Row> 
void SparseLinkedList<Column,Row> :: PrintRowList(ofstream& outFile) const
{
  RowNode<Column, Row>* rowPtr = rowHead;

  while(rowPtr != NULL)
  {
	outFile << rowPtr->yPos << endl;
    rowPtr->data.Write(outFile);
	rowPtr = rowPtr->nextRow;
  }
}

template<class Column, class Row> 
void SparseLinkedList<Column,Row> :: PrintTableStructure() const
/*

  This function is a huge mess, and could probably be coded better.
  However, It was simply a tool to tell if everything structured the 
  way I want; 
    I would have deleted it afterwards, but I figured I might as well
	show the process in which I debugged my program, which was through
	this map

  This function helped me realize a coordination bug with my AddCell

  This function was intended to have column pointers as well, and did for the most part
   but I removed them because they're a huge pain and it adds a 200 lines of unncessary code
   since both the columns and rows operate the same way, if one works, then in all likelyhood
   the other works as well. If I were to use this table more, I would re-introduce it and try
   for a more efficient method.


*/
{

  ofstream debug("debug.data");

  RowNode<Column, Row>* rowPtr;
  ColumnNode<Column, Row>* columnPtr;

  rowPtr = rowHead;
  columnPtr = columnHead;

  vector<bool> draw;
  draw.resize(ColumnLengthIs());

  string line; // Keeps track of what to put in cout
  int loopCount = 0;

  //INITIALIZE COLUMNS
  //*************************

  while(columnPtr != NULL)
  {

	for(int i = 0; i < 5; i++)
	  line = line + "-"; //Spaces nodes

	line = line + ">";

	line = line + "[ ]"; //Draws node

	if(columnPtr->nextCell != NULL)
	  draw[loopCount] = true;
	else
	  draw[loopCount] = false;


    columnPtr = columnPtr->nextColumn; 

	loopCount++;
  }

  debug << " X " << line << endl; //Corner of the map
  
  debug << endl << endl;

  CellNode<Column, Row>* currentCell;

  //DRAW LOGIC
  //*******************

  while(rowPtr != NULL)
  {

    debug << "[ ]";

	//**********************
	//ROW LOGIC
	//**********************

	int lastX = 0; // last x coordinate

	if(rowPtr->nextCell != NULL)
	  currentCell = rowPtr->nextCell;
	else
	  currentCell = NULL;

	while(currentCell != NULL)
	{
	  string temp; //temporarily holds the pointer arrow

	  if(currentCell == rowPtr->nextCell)
        for(int i = 0; i < (currentCell->coordinates.x  - lastX) * 9 + 9; i++)
			//This loop is here because of the zero case where the length would be zero,
			// even though it needs that initial 9 on the first node
		  temp += "-";
	  else  
	    for(int i = 0; i < (currentCell->coordinates.x - lastX) * 9; i++) //Draw the arrow base to that position
		  temp += "-"; //Draw arrow depending on x coordinate

	  temp[temp.length() - 4] = '>'; //Change the last four 
	  temp[temp.length() - 3] = ' '; // characters
	  temp[temp.length() - 2] = 'o'; // to the collision point
	  temp[temp.length() - 1] = ' '; // of the arrow

	  debug << temp;

	  lastX = currentCell->coordinates.x;    //Stores the last x coordinate found
	  currentCell = currentCell->nextColumn;
	}

	
	debug << endl;

	debug << endl;

	debug << endl;


	rowPtr = rowPtr->nextRow;

	loopCount++;
  }		

  debug << endl << endl << endl << endl;
}

#endif


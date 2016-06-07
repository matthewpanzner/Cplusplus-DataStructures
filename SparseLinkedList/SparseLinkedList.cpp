

template<class TypeOne, class TypeTwo>
SparseLinkedList<TypeOne, TypeTwo> :: SparseLinkedList()
//Default constructor

{
    rowHead = NULL;  
	columnHead = NULL;     

	columnLength = 0;          
	rowLength = 0;           
}

template<class TypeOne, class TypeTwo> 
SparseLinkedList<TypeOne,TypeTwo> :: ~SparseLinkedList()
//Deconstructor for table

{
  MakeEmpty();
}

template<class TypeOne, class TypeTwo>
void SparseLinkedList<TypeOne,TypeTwo> :: ResetTable()
{
  currentRow = NULL;
  currentColumn = NULL;
}

template<class TypeOne, class TypeTwo> 
void SparseLinkedList<TypeOne,TypeTwo> :: AddColumn(TypeOne data)
//Add a column to the table

{
  
}

template<class TypeOne, class TypeTwo>
void SparseLinkedList<TypeOne, TypeTwo> :: AddRow(TypeTwo data)
//Add a row to the table

{

}

template<class TypeOne, class TypeTwo> 
void SparseLinkedList<TypeOne,TypeTwo> :: AddCell(TypeOne dataT1, TypeTwo dataT2)
//Adds a cell into the table
{}

template<class TypeOne, class TypeTwo> 
void SparseLinkedList<TypeOne,TypeTwo> :: DeleteCell(TypeOne column, TypeTwo row)
//Deletes a cell from the table
// note: I have no deletion of rows or columns since that 
//         does not seem to be a condition for this assignment

{

}

template<class TypeOne, class TypeTwo> 
void SparseLinkedList<TypeOne,TypeTwo> :: MakeEmpty()
//Deletes the entire table column, rows, and cell

{
  ColumnNode<TypeOne, TypeTwo>* tempColPtr;
  RowNode<TypeOne, TypeTwo>* tempRowPtr;             
  CellNode<TypeOne,TypeTwo>* tempCellPtr;  
  CellNode<TypeOne,TypeTwo>* trail;        // Trails the cell nodes for deletion since
                                           //  there is no head cell pointer


  while(rowHead != NULL)  // This loop deletes all of the rows and cells
  {
	tempCellPtr = rowHead->nextCell;


	while(tempRowPtr != NULL)
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

template<class TypeOne, class TypeTwo> 
void SparseLinkedList<TypeOne,TypeTwo> :: PrintColumn(int columnId, ofstream& outFile) const
//Finds the coulmn with coulmnId and prints that column

{

}


template<class TypeOne, class TypeTwo> 
void SparseLinkedList<TypeOne,TypeTwo> :: PrintRow(int rowId, ofstream& outFile) const
//Finds the row with rowId and prints that column

{

}

template<class TypeOne, class TypeTwo> 
void SparseLinkedList<TypeOne,TypeTwo> :: PrintTable(ofstream& outFile) const
//Prints the entire table in two ways
//  ---One going through columns pointers
//  ---Two going through row pointers and printing 

{

}

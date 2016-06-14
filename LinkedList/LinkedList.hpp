#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

/*
  LinkedList.hpp

  Last Update: 12/4/2014

  Author:         Matthew Panzner
  
  DevLog:         9/30/2013  ---- Started object
                             ---- In deconstructor got an error code 52 -- "debug-assertion-failed-expression-block-type-is-valid"
							        The problem was the last node did not point to NULL, so I fixed it by creating a temporary
									node at the end of the list and making it point next to NULL during deletion of list.
							 ---- Finished Add and Delete, some small bugs I came across were:
							        not attaching end nodes to the newly moved head, often involving the loop from start to end
					
				 10/30/2013  ---- Changed current, head, and size to protected
							 ---- Added derived class SortedList for a list that in ascending order based on id value
				 12/4/2014	 ---- Added Swap function to swap two elements
							 ---- Swap seems functional and working
							 ---- Overloaded = and created Copy constructor
							 ---- Overload and copy constructor seem functional and working
				 12/6/2014   ---- Made Add and Delete boolean functions
							 ---- Found issue with delete; did not work if deleting object
							      that isn't there.  Resulted in segment fault.
						     ---- Fixed segmentation fault
							 ---- Made boolean out of Get and GetNext functions
							 ---- Found potential bugs and fixed them in Get and GetNext
							 ---- Changed swap to boolean, and fixed segementation issue of a NULL head
							 ---- Changed UpdateCurrent to boolean
							 ---- Added Update function *Untested, but uses same logic as get item, only updates instead of 
									retrieves.  MARK AS TESTED AFTER TESTED




 Structure:


     head-->[ ]<-->[ ]<-->[ ]<-->[ ]<-
	         ^                        \
             \ ------------------------

  Notes:

    The list consists of both a previous and next pointer and the last cell 
	  loops around and points to the head.

	The data type used for the node and list MUST be based off of the ItemType.hpp, otherwise
	  it will crash when trying to access functions such as: GetId(), SetId(), and comparedTo().
      Or else ItemType must use function "comparedTo()"
	  This does NOT work with data types such as, int, float, etc.  They must be custom classes
 */

#include <iostream>

using namespace std;

template<class ItemType>
struct NodeType
{
  ItemType data;
  NodeType* next;
  NodeType* prev;
};

template<class ItemType>
class List
{
  public:
    List();
	//Default constructor of List

	~List();
	//Deconstructor of List

	List( const List& otherList );
	//Copy constructor of List

    List& operator=(const List& otherList);
	//Overload =

	void Empty();
	// Empties , or deletes, all data in the list and 
	//  sets head to null and size to 0

	void Reset();
	// Resets where user currently is in the list; that is
	//  it sets current to null

	bool Add(ItemType data);
	// Adds an item to the list
	//  Returns true of added, false otherwise

	bool Delete(ItemType data);
	// Deletes an item from the list
	//  Returns true if deleted, false otherwise

	bool Get(ItemType& data);
	// Retrieves an item from the list based on id
	//  Returns true if found, false otherwise

	bool GetNext(ItemType& data);
	// Get next item in list
	//  Returns true if found, false otherwise

	bool Update(ItemType data);
	//Updates the itemtype with the same id
	//  returns true if updated, false otherwise

	bool UpdateCurrent(ItemType data);
	// Update the current item
	//  Returns true if updated, false otherwise
	
	bool Swap(int pos1, int pos2);
	//Swaps the two items from their locations

	bool isFull() const;
	// True if there's enough memory to create another cell
	// False if there is not enough memory

	inline int lengthIs() const {return size;}
	//Returns the size, or length, of list


	//****************************************
	//These are primiarily used for debugging
	//****************************************

	void PrintStart() const;  // Both of these functions
	//Prints left to right    // are printing the IDs

	void PrintEnd() const;    // of the given data type
	//Prints right to left

  protected:
    NodeType<ItemType>* head;     //Head of list
	NodeType<ItemType>* current;  //Keeps track of where user is currently in list
								  
	int size;           //Size of list
};


//***********************************
//
// IMPLEMENTATION OF LIST
//
//***********************************

template<class ItemType>
List<ItemType> :: List()
// Default Constructor of List
{
  head = NULL;
  current = NULL;
  size = 0;
}

template<class ItemType>
List<ItemType> :: ~List()
// Deconstructor of List
{ 
  Empty();
}

template<class ItemType>
List<ItemType>& List<ItemType>::operator=(const List& otherList)
{ 
  this->size = 0;
  NodeType<ItemType>* location; //Traverses the list

  location = otherList.head;    //Node to create copies

  for(int i = 0; i < otherList.size; i++)
  {
	this->Add(location->data);
	location = location->next;
  }

  return *this;
}

template<class ItemType>
List<ItemType> :: List(const List& otherList) 
// Copy constructor of List
{
  *this = otherList;
}

template<class ItemType>
void List<ItemType> :: Empty()
// Empties , or deletes, all data in the list and 
//  sets head to null and size to 0
{
  size = 0;
  
  if(head == NULL) //Don't need to delete anything
	return;

  NodeType<ItemType>* end; //Keeps track of the very end of the list

  end = head->prev;
  end->next = NULL;

  while(head != NULL)
  {
    NodeType<ItemType>* previous = head;
	head = head->next;

    delete previous;
  }

}

template<class ItemType>
void List<ItemType> :: Reset()
// Resets where user currently is in the list; that is
//  it sets current to null
{
  current = head;
}

template<class ItemType>
bool List<ItemType> :: isFull() const
// True if there's enough memory to create another cell
// False if there is not enough memory
{
  NodeType<ItemType>* temp;
  temp = NULL;
  temp = new NodeType<ItemType>; //Try to make a new node

  if(temp == NULL)
	return true;
  
  delete temp; //The node was created so we delete it 
               // and return true because we have enough memory for it

  return false;
}

template<class ItemType>
bool List<ItemType> :: Add(ItemType data)
// Adds an item to the list

{
  NodeType<ItemType>* location; //Insertion location
  NodeType<ItemType>* preLoc;   //Previous node

  location = head;
  preLoc = NULL;

  if(location != NULL) //If there is something in list already
  {
    bool moreToSearch = true; // We know it's not NULL, so we have at least one iteration

    while(moreToSearch) 
    {
	  
      if(location->data.comparedTo(data) == EQUAL)
	    return false; //For now, I will just end the function, though
	            //  some sort of error message should be sent, just haven't
	            //  thought of how I want to do that


	  preLoc = location;
	  location = location->next;
	  moreToSearch = location != head;

    }
  }
  

  NodeType<ItemType>* newNode; //New node to add to list
  newNode = new NodeType<ItemType>;
  newNode->data = data;
  

  if(preLoc == NULL) //If nothing is in the list then ....
  {  
	head = newNode;
    head->next = head;  //Wraps around
	head->prev = head;
  }

  else //There already is things in the list, add to it...
  { 
    newNode->next = head;   //Wraps to head
	newNode->prev = preLoc; //Points to node before it
	preLoc->next = newNode; //Connects previous node to newNode
	head->prev = newNode;   //Wraps head around to end of list
  }

  size++;
  return true;

}

template<class ItemType>
bool List<ItemType> :: Delete(ItemType data)
// Deletes an item from the list
{
  bool found = false;

  NodeType<ItemType>* location = head; //Finds node to delete
  NodeType<ItemType>* preLoc = NULL;   //Keeps track of previous node form location

  if(head == NULL) //Make sure driver didn't forget to check
	return false; 

  if(head->data.comparedTo(data) == EQUAL)
   //Head case std
  {
    //adjust head

	if(head->next == head) //If there's only the head
      head = NULL;
	else
	{
      head = head->next;

	  if(head->next == location) 
	  {
		//if the list is just two elements
	    head->prev = head;
		head->next = head;
	  }
	  else
	  {
		//otherwise
	    head->prev = location->prev;
		location->prev->next = head;
	  }
	}

  }
  else
  {
    //find and delete
	for(int i = 0; (i < size) && (location->data.comparedTo(data) != EQUAL); i++) //Use length
	{
	  preLoc = location;
	  location = location->next;
	}
	
	preLoc->next = location->next; //Connect previous node to next node
	location->next->prev = preLoc; //Connect the next node to the previous
  }

  if(location->data.comparedTo(data) != EQUAL) 
  //If it didn't find the data
	  return false;
 
  //If it did find the data
  if(current)
  //Incase that current was never initialized
	if(current->data.comparedTo(location->data) == EQUAL)
		current = current->prev;


  delete location;
  size--;

  return true;
}

template<class ItemType>
bool List<ItemType> :: Swap(int pos1, int pos2)
{
  NodeType<ItemType>* travNode1 = head; //Traces through the array to pos1
  NodeType<ItemType>* travNode2 = head; //Traces through the array to pos2
  
  if(head == NULL)
	return false;

  for(int i = 0; i < pos1; i++)
	travNode1 = travNode1->next;
  for(int i = 0; i < pos2; i++)
	travNode2 = travNode2->next;

  ItemType temp;  //For swapping data around
 
  temp = travNode1->data;
  travNode1->data = travNode2->data;
  travNode2->data = temp;

  return true;

}

template<class ItemType>
bool List<ItemType> :: Get(ItemType& data)
// Retrieves an item from the list based on id
{

  if(head == NULL) // Just making sure driver didn't mess up
	return false;

  current = head;

  bool moreToSearch = true; //We want to iterate once
                            // do while loop would work, but moreToSearch is 
                            // more organized for what we're doing

  while(moreToSearch)
  {
    if(current->data.comparedTo(data) == EQUAL)
	{
	  data = current->data;
	  return true;
	}

	current = current->next;
	moreToSearch = current != NULL;
  }
  
  return false;
}

template<class ItemType>
bool List<ItemType> :: GetNext(ItemType& data)
// Get next item in list
{
  if(current != NULL)
  {
	current = current->next;
	data = current->data;
	return true;
  }

  return false;
}

template<class ItemType>
bool List<ItemType> :: Update(ItemType data)
{
  if(head == NULL)
	  return false;

  bool moreToSearch = true; //We want to iterate once
                            // do while loop would work, but moreToSearch is 
                            // more organized for what we're doing

  while(moreToSearch)
  {
    if(current->data.comparedTo(data) == EQUAL)
	{
	  current->data = data;
	  return true;
	}

	current = current->next;
	moreToSearch = current != NULL;
  }
  
  return false;
}

template<class ItemType>
bool List<ItemType> :: UpdateCurrent(ItemType data)
// Update the current item
{
  if(current->data.comparedTo(data) == EQUAL)
  {
	current->data = data;
	return true;
  }

  return false;

}


//********************************************************************************
//Debug
//
//________________________________________________________________________________

template<class ItemType>
void List<ItemType> :: PrintStart() const
{
  if(head == NULL) // Nothing to print
	return;

  NodeType<ItemType>* travNode; //Traverses the list
  travNode = head;

  bool moreToSearch = true; // We know it's not NULL, so we have at least one iteration

  while(moreToSearch)
  {
    cout << travNode->data.GetId() << "   " << endl; //travNode->data.GetAge() << endl;
	travNode = travNode->next;
    moreToSearch = travNode != head;
  }
}

template<class ItemType>
void List<ItemType> :: PrintEnd() const
{
  if(head == NULL) // Nothing to print
	return;

  NodeType<ItemType>* travNode; //Traverses the list
  travNode = head->prev; //Want to start at the last element

  bool moreToSearch = true; // We know it's not NULL, so we have at least one iteration

  while(moreToSearch)
  {
    cout << travNode->data.GetId() << endl;
	travNode = travNode->prev;
    moreToSearch = travNode != head->prev;
  }
}

	






//*******************************************************************************************
/* End List
    

   Object: SortedList

   Derived from List, this will keep all data sorted based on Id of ItemType





*/

template<class ItemType>
class SortedList : public List<ItemType>
{
  public:
	SortedList();
	//Default constructor of SortedList

	virtual void Add(ItemType data);
	//Add ItemType to SortedList, insertion based on id value

	virtual void Delete(ItemType data);
	//Delete data from list, based on Id, and list is !Empty()
	// Function will use median value to find node to delete fast

	virtual void Get(ItemType& data);
	//Get data from list from id, and store it in data
	// Function will use median value to find node to delete fast

  private:
};

//******************************
// IMPLEMENTATION OF SORTEDLIST
//******************************

#endif

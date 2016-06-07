#ifndef DECK_HPP
#define DECK_HPP

/*
  Deck.hpp

  Creation date: 10/30/2013

  Description:
     This class works like a deck of cards; that is, you have a stack of cards laying down, you
	   can insert a card to the bottom of the deck, or draw a card from the top of the deck.  You
	   may also shuffle the deck.

  DevLog:  10/30/2013  --  Created basic class function declarations
           
		   10/31/2013  --  Copy constructor created and tested
		                   Deconstructor created and tested
						   TakeTop created and tested
						   PutOnBottom created and tested
						   Peek created and tested
						   MakeEmpty created and tested
						   sizeIs created and tested
						   isEmpty created and tested
						   isEnoughMemory created and tested
						   PutOnTop created and tested

						   Come across a very strange bug with TakeTop. [1]

  DebugLog:
        
	When making the copy constructor I came across an issue I often forget; that is, I create the copy pointers
	  to point to the data it's trying to copy, rather than actually copy it.

	[1] In doing testing of these functions, there was one bug that came across strange. Given the syntax
	    cout << deck.TakeTop() << " " << deck.TakeTop(); it would print them in reverse order, however
		cout << deck.TakeTop(); cout << deck.TakeTop(); worked just fine.

*/

#include <iostream>

template<class DataType>
class Deck
{
  public:
    Deck();
	//Default constructor of the deck

	~Deck();
	//Clears up memory used by the deck

	Deck(const Deck& otherDeck);
	//Copies a given deck based on otherDeck

	void MakeEmpty();
	//Clears all nodes in the deck, making it empty

	void Shuffle();
	//Shuffles the deck

    void TakeTop(DataType& data)
    //Takes the top of the deck and puts it in data and sends back while deleting top

	void PutOnBottom(DataType card);
	//Puts card to the bottom of the deck

	void PutOnTop(DataType card);
	//Puts card on top of the deck

	inline DataType Peek() const {return top->data;}
	//Peek at what's on top of the card deck

	bool isEnoughMemory() const;
	//Tells us if there's enough memory to allocated a new node

	inline bool isEmpty() const {if(size == 0) return true; else return false;}
	//Returns false there is something in deck
	//Returns true if there is nothing in deck

	inline int sizeIs() const {return size;}
	//Returns size of deck


  private:

    struct NodeType
    // A basic NodeType to link our cards in the deck
    {
      NodeType* next; //Next card in deck
	  NodeType* prev; //Previous card in deck

	  DataType data;  //Data the card holds
    };

	NodeType* top;     //Points to top of deck
	NodeType* bottom;  //Points to bottom of deck

	int size;          //Size of deck
};

template<class DataType>
Deck<DataType> :: Deck()
//Default constructor of the Deck
{
  size = 0;
  top = NULL;
  bottom = NULL;
}

template<class DataType>
Deck<DataType> :: ~Deck()
//Clears memory used by the deck
{
  MakeEmpty();
}

template<class DataType>
Deck<DataType> :: Deck(const Deck& otherDeck)
//Copies a deck into a given deck
{
  NodeType* trav = otherDeck.top; //Traverses otherDeck

  this->top = NULL;
  this->bottom = NULL;
  size = 0;

  while(trav != NULL)
  {
	NodeType* newNode;
	newNode = new NodeType;
	newNode->data = trav->data;

    if(this->top == NULL)
	{
	  this->top = newNode;
	  this->top->prev = NULL;
	  this->top->next = NULL;

	  this->bottom = this->top; // top == bottom
	}
	else
	{
	  newNode->next = this->bottom->next;       //Makes next in newNode bottom, which is just NULL
	  newNode->prev = this->bottom;             //Connects it to previous node
      this->bottom->next = newNode;

   	  if(this->top->next == NULL)
	    this->top->next = newNode; //If the top still hasn't connected to anything

	  this->bottom = this->bottom->next;	
	}

	size++;
    trav = trav->next;
	
  }

}

template<class DataType>
void Deck<DataType> :: MakeEmpty()
//Deletes all nodes in the deck, clearing up memory
{
  NodeType* temp = top;

  while(top != NULL)
  {
    top = top->next;
	delete temp;
	temp = top;
  }

  bottom = NULL;
  size = 0;
}

template<class DataType>
void Deck<DataType> :: TakeTop(DataType& data)
//Takes the top of the deck and puts it in data and sends back while deleting top

{
  if(top == NULL)
  {
	throw "Deck is empty, cannot take from top";

	DataType errCard;
	return errCard;
  }

  DataType store = top->data; //Stores the top data

  system("PAUSE");
  if(top == bottom)
  { 
	delete top;
    top = NULL;
	bottom = NULL;
  }
  else
  {
    NodeType* temp = top;
	top = top->next;
	delete temp;
  }

  size--;

  data = store;
}

template<class DataType>
void Deck<DataType> :: PutOnBottom(DataType card)
//Puts card to the bottom of the deck
{
  NodeType* newNode;
  newNode = new NodeType;
  newNode->data = card;

  if(size == 0)
  {
	newNode->next = top; //Basically makes them null
	newNode->prev = top;

    top = newNode;    //Makes top the new node
	
	bottom = top;    //Make bottom and top equal

  }
  else
  {
	newNode->next = bottom->next;       //Makes next in newNode bottom, which is just NULL
	newNode->prev = bottom;             //Connects it to previous node
    bottom->next = newNode;

	bottom = bottom->next;
  }
  
  size++;
}
 
template<class DataType>
void Deck<DataType> :: PutOnTop(DataType card)
//Puts card to the top of the deck
{
  NodeType* newNode;
  newNode = new NodeType;
  newNode->data = card;

  if(size == 0)
  {
	newNode->next = top; //Basically makes them null
	newNode->prev = top;

    top = newNode;    //Makes top the new node

	bottom = top;    //Make bottom and top equal

  }
  else
  {
	newNode->next = top;                //Connects the newNode to the next in the deck
	newNode->prev = top->prev;          //Connects it to previous node (NULL in this case)
    top->prev = newNode;

	top = top->prev;

  }
  
  size++;
}
 
template<class DataType>
bool Deck<DataType> :: isEnoughMemory() const
//Tells us if there's enough memory to allocated a new node
{
  NodeType* newNode;
  newNode = new NodeType;

  if(newNode == NULL)
	return false;
  
  return true;
}

#endif

#ifndef GRAPHTYPE_HPP
#define GRAPHTYPE_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

#define INFINITY 10000000


template<class DataType>
struct Edge
{
  int length;          //length of edge
  DataType* vertice;   //connection to vertice
};

struct Vertex
{
  vector<Edge<Vertex>> connects;  //Contains all edges in given vertex
  int id; //number associated with vertex, or id
};

class GraphType
{
  public:
	GraphType();
	//Default constructor

	~GraphType();
	//Deconstructor

	void Read(ifstream& inFile);
	//Read in a graph from inFile

	void Empty();
	//Empties graph

	void PrintGraph(ofstream& outFile);
	//Prints the graph

	void PrintShortest(ofstream& outFile);
	//Print the shortest path to outFile

	stringstream FindShortest(int source, stringstream& ss);
	//Find the shortest path

	inline int numOfVertices() const {return numOfPoints;}
	//returns the number of vertices in graph

  private:
	vector<Vertex> vertices;       //Vertices

	int numOfPoints; //Number of vertices

};

#endif
#include "GraphType.hpp"


int dist(vector<int> Q);
//Keeps track of all the distances being used

int distanceBetween(Vertex u, Vertex v);
//Returns distances between two vertices

GraphType::GraphType()
{
  numOfPoints = 0;

  vertices.resize(numOfPoints);

  for(int i = 0; i < numOfPoints; i++)
  {
    vertices[i].connects.resize(numOfPoints);
	vertices[i].id = i;

    for(int j = 0; j < numOfPoints; j++)
	{ 
	  vertices[i].connects[j].length = 0;
	  vertices[i].connects[j].vertice = &vertices[j];
	}
  }
}


GraphType::~GraphType()
{ 
  Empty();
}

void GraphType::Empty()
{
  for(int i = 0; i < numOfPoints; i++)
    vertices[i].connects.empty();
  
  vertices.empty();
}

void GraphType::Read(ifstream& inFile)
{
  Empty();

  inFile >> numOfPoints;

  vertices.resize(numOfPoints);

  for(int i = 0; i < numOfPoints; i++)
  {
	vertices[i].connects.resize(numOfPoints);
	vertices[i].id = i;

    for(int j = 0; j < numOfPoints; j++)
	{ 
	  inFile >> vertices[i].connects[j].length;
	  vertices[i].connects[j].vertice = &vertices[j];
	}
  }
}

void GraphType::PrintGraph(ofstream& outFile)
{
  for(int i = 0; i < numOfPoints; i++)
  {
	outFile << "Vertice #" << i << " connects to: ";

    for(int j = 0; j < numOfPoints; j++)
	{
	  if(vertices[i].connects[j].length != 0)
		outFile << j << " ";
	}

	outFile << endl;
  }

  outFile << endl << endl;

  outFile << "Adjacency matrix: " << endl;
  outFile << endl;

  outFile << left << setw(3) << "";

  for(int i = 0; i < numOfPoints; i++)
	outFile << "V" <<  setw(2) << i;

  outFile << endl << endl;

  for(int i = 0; i < numOfPoints; i++)
  {

	outFile << "V" << setw(3) << i;

    for(int j = 0; j < numOfPoints; j++)
	{
	  outFile << setw(3) << vertices[i].connects[j].length;
	}

	outFile << endl;

  }

  outFile << endl;
}

stringstream GraphType::FindShortest(int source)
{
  stringstream log;

  vector<int> distances(numOfPoints);        //distance from source
  vector<bool> visited(numOfPoints);         //visited or not
  vector<int> previous(numOfPoints);         //keeps track of previous node

  for(int i = 0; i < numOfPoints; i++)
  {
	previous[i] = -1;
    distances[i] = INFINITY;
	visited[i] = false;
  }

  distances[source] = 0; //source
  vector<Vertex> Q;
  Q.push_back(vertices[source]); //Insert the source

  log << "Source Vertex #" << source << "\n\n";

  while(Q.size() != 0)
  {
	int smallest = INFINITY;
	Vertex u;

    for(int i = 0; i < Q.size(); i++)
	{
	  if(distances[Q[i].id] < smallest)
	  {
	    smallest = distances[Q[i].id];
		u = Q[i];
	  }
	}
	
	for(int i = 0; i < Q.size(); i++)
	{
	  if(Q[i].id == u.id)
		Q.erase(Q.begin() + i);
	}

	
	visited[u.id] = true;
	
	//*******************
	
	for(int v = 0; v < numOfPoints; v++)
	{
	  Vertex next = vertices[v];

	  if(distanceBetween(u,next) == 0)
		continue;

	  int altPath = distances[u.id] + distanceBetween(u, next);
	  
	  
	  if(altPath < distances[v])
	  {
	    distances[v] = altPath;
		previous[v] = u.id;

		if(!visited[v])
		  Q.push_back(next);
	  }
	}
  }

  //*********************************
  //  Log formatting
  //

  int edgeCount = 0;

  for(int i = 0; i < numOfPoints; i++)
  { 
	if(previous[i] != -1)
	{
      log << "(" << previous[i] << "," << i << ") with edge length of: "
	      << vertices[previous[i]].connects[i].length << "\n";

	  edgeCount += vertices[previous[i]].connects[i].length;
	}
  }

  log << "\n" << "Edges add up to: " << edgeCount << "\n\n";

  return log;
}

int distanceBetween(Vertex u, Vertex v)
//Returns distances between two vertices
{
  return u.connects[v.id].length;
}

int dist(vector<int> Q)
//Keeps track of all the distances being used
{
  int distance = 0;
 
  for(int i = 0; i < Q.size(); i++)
    distance += Q[i];

  return distance;
}
#define _CRTDBG_MAP_ALLOC  //for memory leak debugging
#include <stdlib.h>
#include <crtdbg.h>

/*

      Author :   Matthew Panzner

	  Course : CS316
	  Prof   : Dr. Lee
	  Due    : 11/11/2013

	  About  : To take an adjacency matrix and find the minimum spanning tree

  DevLog:    11/23/2013  --  Started making GraphType declartions
             11/30/2013  --  Wrote entire code for GraphType
			             --  Added a string stream log for easier output
			 12/1/2013   --  Finished formatting the outputs
						 

  Note: **************************************************
   
        Although this program does work, it's definetly not 
		  as good as it could be.  That is, I check every 
		  source point individually rather than backtrack
		  when a circuit can't be formed.  This increases
		  complexity to a higher amount than needed.  

		  Will look into fixing that if I have enough time.
*/

#include "GraphType.hpp"

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

  ifstream inFile("in.data");
  ofstream outFile("out.data");

  
  GraphType graph;
  graph.Read(inFile);

  outFile << "The graph will have these connections: " << endl << endl;
  graph.PrintGraph(outFile);

  outFile << "--------------------------------" << endl << endl;
  outFile << "A minimal spanning tree would will look something like this: " <<endl << endl;

  for(int i = 0; i < graph.numOfVertices(); i++)
  {
	outFile << "For ";

    string shortestPath;
	string = graph.FindShortest(i);

    while(shortestPath)
    {
      char temp[256];
	  shortestPath.getline(temp, 255);

	  outFile << temp << endl;
    }

	outFile << "------------------------------------" << endl << endl;
  }
  
  outFile.close();
  inFile.close();
  
  return 0;
}
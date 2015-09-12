// test 1: tests graph construction and node insertion 

#include "Graph.h"

int main() {
	
	try {
		// create 3 graphs
		cs6771::Graph<int,int> g;
		g.addNode(1);
		g.addNode(2);
		g.addEdge(1,2,10);
		g.addEdge(2,1,10);

		std::cout << g.isNode(2) << std::endl;
		g.replace(2,7);
		std::cout << g.isNode(2) << std::endl;
		//g.deleteNode(7);
		//g.deleteEdge(1,2,10);
		g.printGraph();


	} catch (...) {
		std::cout << "caught exception" << std::endl;
	}
}

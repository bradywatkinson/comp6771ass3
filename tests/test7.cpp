// test 7: tests deleting data

#include "../Graph.h"

int main() {
	cs6771::Graph<std::string,int> gCopy;
	
	// add this data into the graph
	gCopy.addNode("a");
	gCopy.addNode("b");
	gCopy.addNode("c");
	gCopy.addNode("d");
	
	gCopy.addEdge("b","a",3);
	gCopy.addEdge("b","a",5);
	gCopy.addEdge("c","a",3);
	
	std::cout << "Graph before node/edge deletion" << std::endl;
	gCopy.printNodes();
	gCopy.printEdges("b");
	gCopy.printEdges("c");
	
	std::cout << "deleteing edge between b and a" << std::endl;
	gCopy.deleteEdge("b","a",5);
	gCopy.printEdges("b");
	
	std::cout << "deleting node a" << std::endl;
	gCopy.deleteNode("a");
	//gCopy.printGraph();
	gCopy.printEdges("b");
	std::cout << "Graph after node/edge deletion" << std::endl;
	gCopy.printNodes();
	
	try {
		gCopy.deleteNode("a");
	} catch( const std::exception &ex ) {
		std::cout << "exception caught 1" << std::endl;
	}
	
	try {
		gCopy.deleteEdge("c","a",5);
	} catch( const std::exception &ex ) {
		std::cout << "exception caught 2" << std::endl;
	}
}

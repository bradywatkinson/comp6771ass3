// test 6: tests merge replace

#include "../Graph.h"

int main() {
	cs6771::Graph<std::string,int> gCopy;
	
	// add this data into the graph
	gCopy.addNode("a");
	gCopy.addNode("b");
	gCopy.addNode("c");
	gCopy.addNode("d");
	
	gCopy.addEdge("b","a",3);
	gCopy.addEdge("b","d",4);
	gCopy.addEdge("b","a",5);
	
	gCopy.addEdge("c","a",3);
	
	std::cout << "Graph before node merge" << std::endl;
	gCopy.printNodes();
	gCopy.printEdges("b");
	gCopy.printEdges("c");
	gCopy.mergeReplace("b","c");
	std::cout << "Graph after node merge" << std::endl;
	gCopy.printNodes();
	gCopy.printEdges("c");
	
	std::cout << "checking that node b has been destroyed" << std::endl;
	try {
		gCopy.mergeReplace("b","c");
	} catch( const std::exception &ex ) {
		std::cout << "exception caught" << std::endl;
	}
	
	try {
		gCopy.mergeReplace("c","b");
	} catch( const std::exception &ex ) {
		std::cout << "exception caught" << std::endl;
	}
	std::cout << std::boolalpha << gCopy.isNode("b") << std::endl;
}

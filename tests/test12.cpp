// test 12: tests edgeIterators

#include "../Graph.h"

int main() {
	cs6771::Graph<std::string,int> gCopy;
	
	// create some data to store as nodes.
	std::string s = "a";
	std::string t = "b";
	std::string u = "c";
	
	// add this data into the graph
	gCopy.addNode(s);
	gCopy.addNode(t);
	gCopy.addNode(u);
	
	gCopy.addEdge(u,t,1);
	gCopy.addEdge(u,t,2);	
	
	// trying iterator over edges attached to this node. 
	for (auto edge = gCopy.edgeIteratorBegin("c"); edge != gCopy.edgeIteratorEnd(); ++edge) {
		std::cout << (*edge).first << " " << (*edge).second << std::endl;
	}
	
	std::cout << "trying -> overload on iterator" << std::endl;
	for (auto edge = gCopy.edgeIteratorBegin("c"); edge != gCopy.edgeIteratorEnd(); ++edge) {
		std::cout << edge->first << " " << edge->second << std::endl;
	}
}

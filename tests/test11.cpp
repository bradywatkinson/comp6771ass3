// test11: tests graph iterators

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
	
	// trying iterator
	for (auto node = gCopy.begin(); node != gCopy.end(); ++node) {
		std::cout << *node << std::endl;
	}
}

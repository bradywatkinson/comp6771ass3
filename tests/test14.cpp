// Test 14: tests iterators with std::algorithm

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
	
	auto result = std::find(gCopy.begin(), gCopy.end(), "a");
	if (result != gCopy.end()) {
		std::cout << "Node a found" << std::endl;
	}
	
	result = std::find(gCopy.begin(), gCopy.end(), "d");
	if (result == gCopy.end()) {
		std::cout << "Node d not found" << std::endl;
	}
	
	gCopy.clear();
	result = std::find(gCopy.begin(), gCopy.end(), "a");
	if (result != gCopy.end()) {
		std::cout << "Node a found" << std::endl;
	} else {
		std::cout << "Node a not found" << std::endl;
	}
}

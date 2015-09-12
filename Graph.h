
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <iostream>
#include <exception>
#include <map>
#include <set>

#define DEBUG true

namespace cs6771
{
	template <typename N, typename E>
	class Graph
	{
		private:
			struct Node;
			struct Edge;

			struct Node
			{
				N val;
				std::set<std::shared_ptr<Edge>> edges_;
				Node() {}
				Node(const N x) : val{x} {}
				void printNode (N n) {
					if (n!=val) throw std::runtime_error("Node corruption: index != val");
					std::cout << val << ": ";
					for (std::shared_ptr<Edge> e : edges_) (*e).printEdge();
					std::cout << std::endl;
				} 
				// Node& makeNode (N val) {
				// 	return Node{val};
				// }
				// Node& operator=(const Node &n)
				// {
				// 	val = n.val;
				// 	edges_ = n.edges_;
				// 	return *this;
				// }
				//bool operator<(const Node& n) const {return val<n.val;}
				//static bool nodeCome(const Node& lhs, const Node& rhs) {return lhs.val<rhs.val;}
			};

			struct Edge
			{
				std::weak_ptr<Node> orig;
				std::weak_ptr<Node> dest;
				E val;
				Edge(std::shared_ptr<Node> o, std::shared_ptr<Node> d, E x) : val{x} {//orig{o}, dest{d}, 
					//orig = std::make_shared<Node>(o);
					//dest = std::make_shared<Node>(d);
					orig = o;
					dest = d;
				}
				Edge() {};
				void printEdge () {
					//auto tmp = std::make_shared<Node>(dest);
					if (auto tmp = dest.lock())
						std::cout << "[" << val << "] " << tmp->val << " ";
				}
			};

		public:

			Graph() :
				nodes_{}
				//edges_{},
				//graph_{}
				{};

			//copy constructor
			Graph(const Graph &g) :
				nodes_{g.nodes_}
				// edges_{g.edges_},
				// graph_{g.graph_}
				{};

			//move constructor
			Graph(Graph &&g) :
				nodes_{std::move(g.nodes_)}
				// edges_{std::move(g.edges_)},
				// graph_{std::move(g.graph_)}
				{};
			
			//Destructor
			~Graph()
			{
				//delete nodes_;
				//delete edges_;
				//delete graph_;
			};

			//=copy Operator
			Graph& operator=(const Graph &g)
			{
				if (this != g) {
					nodes_ = g.nodes_;
					// edges_ = g.edges_;
					// graph_ = g.graph_;
				}
				return *this;
			}

			//=move Operator
			Graph& operator=(Graph &&g)
			{
				if (this != g) {
					nodes_ = std::move(g.nodes_);
					// edges_ = std::move(g.edges_);
					// graph_ = std::move(g.graph_);
				}
				return *this;
			}

			bool addNode(const N& val)
			{
				if (nodes_.find(val) == nodes_.end()) {
					if (DEBUG) std::cout << "adding: " << val << std::endl;
					nodes_[val] = std::make_shared<Node>(Node{val});
				} else if (DEBUG) {
					std::cout << val << ": not added. Already exists" << std::endl;
				}

				return true;
			}

			// bool addNode(const N& n)
			// {
			// 	auto result = std::find_if(nodes_.begin(),nodes_.end(),
			// 				[n] (const Node node) {return node.val == n;});

			// 	if (result == nodes_.end()) {
			// 		if (DEBUG) std::cout << "adding: " << n << std::endl;
			// 		Node tmp{n};
			// 		nodes_.insert(tmp);
			// 		return true;
			// 	} else if (DEBUG) {
			// 		std::cout << n << ": not added. Already exists" << std::endl;
			// 	}
			// 	return true;
			// }
/*
A method to add an Edge between two nodes. The method will be passed the origin and
destination nodes and the weight object. The method returns true if the edge is added,
false if there is already an edge between the two nodes with the same weight object.
A std::runtime_error is thrown if either the origin or destination node is not found in the graph.
*/
			bool addEdge(const N& orig, const N& dest, const E& val)
			{
				// check that both orig and dest exist
				auto findOrig = nodes_.find(orig);
				if (findOrig == nodes_.end()) throw std::runtime_error("addEdge: origin DNE");
				auto findDest = nodes_.find(dest);
				if (findDest == nodes_.end()) throw std::runtime_error("addEdge: dest DNE");
				//if (findDest == nodes_.end()) std::runtime_error("cannot add edge from"+orig+" to "+dest+", "+dest+" does not exist");

				// check if the edge between already exists
				auto findEdge = std::find_if(findOrig->second->edges_.begin(),findOrig->second->edges_.end(),
											[val] (std::shared_ptr<Edge> e) {return e->val==val;});

				if (findEdge == findOrig->second->edges_.end()) {
					if (DEBUG) std::cout << "adding edge: " << orig << " " << dest << " " << val << std::endl;
					
					findOrig->second->edges_.insert(std::make_shared<Edge>(Edge(findOrig->second,findDest->second,val)));
					return true;
				} else if (DEBUG) {
					std::cout << orig << "->" << dest << " not added. Already exists" << std::endl;
				}
				return false;
			}

			// bool addEdge(const N& orig, const N& dest, const E& edge)
			// {
			// 	auto result1 = find_if(nodes_.begin(),nodes_.end(),
			// 				[orig] (const Node n) {return n.val==orig;});
			// 	auto result2 = find_if(nodes_.begin(),nodes_.end(),
			// 				[dest] (const Node n) {return n.val==dest;});

			// 	if (result1 == nodes_.end()) std::runtime_error("cannot add edge from"+orig+" to "+dest+", "+orig+" does not exist");
			// 	if (result2 == nodes_.end()) std::runtime_error("cannot add edge from"+orig+" to "+dest+", "+dest+" does not exist");

			// 	if (result1->edges_)

			// 	return true;
			// }	

/*
Replaces the data stored at a node. If the current node cannot be found a std::runtime_error
is thrown. If the replacement node data already exists on a different node in the graph the
method returns false. Otherwise return true.
*/
			bool replace(const N& node, const N& val)
			{
				// check the node exists
				auto findNode = nodes_.find(node);
				if (findNode == nodes_.end()) throw std::runtime_error("replace: Node DNE");

				// check if the new val exists
				auto findVal = nodes_.find(val);
				// auto findVal = std::find_if(nodes_.begin(),nodes_.end(),
				//					[val] (std::pair<N,std::shared_ptr<Node>> n) {return n.second->val == val;});

				//if (nodes_[val] == NULL) {

				if (findVal == nodes_.end()) {
					if (DEBUG) std::cout << "replacing " << findNode->second->val << " with " << val << std::endl;
					nodes_[val] = nodes_[node];
					nodes_[val]->val = val;
					nodes_.erase(findNode);
					//findNode->second->val = 66;	
					return false;
				}
				if (DEBUG) std::cout << "replace: " <<val << " already exists" << std::endl;
				return true;
			} 
/*
;	Deletes a given node and all edges connected to and from it.
Hint: if you are using weak ptrs for edges you may be able to do this
quite simply. This method should not throw any exceptions.
*/			
			void deleteNode(const N& node) noexcept
			{
				auto findNode = nodes_.find(node);
				if (findNode != nodes_.end()) {
					if (DEBUG) std::cout << "deleting " << node << std::endl;
					//delete findNode->second->edges_;
					nodes_.erase(findNode);
				} else {
					if (DEBUG) std::cout << "could not find " << node << std::endl;
				}
			}
/*
Deletes an edge between two nodes with a given weight. This method
should not throw any exceptions. If the given edge is not found do nothing.
*/
			void deleteEdge(const N& orig, const N& dest, const E& val) noexcept
			{
				// find the origin node
				auto findNode = nodes_.find(orig);
				// find the destination node: Must have same dest AND val
				if (findNode != nodes_.end()) {
					auto findEdge = std::find_if(findNode->second->edges_.begin(), findNode->second->edges_.end(),
											[dest, val] (std::shared_ptr<Edge> e) {
												if (auto tmp = e->dest.lock())
													if (tmp->val == dest && e->val == val)
														return true;
												return false;
											});
					if (findEdge != findNode->second->edges_.end()) {
						findNode->second->edges_.erase(findEdge);
					} else if (DEBUG) {
						std::cout << "deleteEdge: no edge was found" << std::endl;
					}
				} else if (DEBUG) {
					std::cout << "deleteEdge: origin: " << orig << " not found" << std::endl;
				}
			}

/*
Removes all nodes and edges from the graph. New nodes and edges can
be added to the graph after the clear command.
*/

			void clear() noexcept
			{
				nodes_.clear();
			}
/*
Returns true if the data value passed into the function is
already stored as a node in the graph.
*/
			bool isNode(const N& node) const
			{
				return nodes_.find(node) != nodes_.end();
			}

/*
Returns true if there is an edge between two nodes, false
otherwise. Throws a std::runtime_error if there is either
node is not in the graph.
*/
			bool isConnected(const N& orig, const N& dest) const
			{
				// auto findOrig = nodes_.find(orig);
				// if (findOrig == nodes_.end()) throw std::runtime_error("addEdge: origin DNE");
				// auto findDest = nodes_.find(dest);
				// if (findDest == nodes_.end()) throw std::runtime_error("addEdge: dest DNE");


			}

			void printGraph ()
			{
				std::cout << "Printing Graph" << std::endl;
				for (std::pair<N,std::shared_ptr<Node>> n : nodes_) {
					n.second->printNode(n.first);
				}
			}

		private:
			//std::set<Node> nodes_;
			//std::vector<std::shared_ptr<Node>> nodes_;
			//std::vector<std::shared_ptr<Edge>> edges_;

			std::map< N, std::shared_ptr<Node> > nodes_;
			//std::vector< std::vector<*Node> > graph;
	};
}

#endif
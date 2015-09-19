
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
#include <typeinfo>

#define DEBUG false

namespace cs6771
{
	template <typename N, typename E> class Graph;

	template <typename N, typename E> class Node_Iterator
	{
		public:
			typedef typename Graph<N,E>::Node Node;

			typedef std::ptrdiff_t                     difference_type;
			typedef std::forward_iterator_tag          iterator_category;
			typedef N                                  value_type;
			const typedef N*                           pointer;
			const typedef N&                           reference;

			// value type
			reference operator*() const {
				if (DEBUG) std::cout << "testing *: "<< (*it)->val_ << std::endl;
				return (*it)->val_;
			}
			// reference type
			pointer operator->() const {
				return &(operator*());
			}
			// pre increment
			Node_Iterator& operator++() {
				++it;
				if (it==mynodes_.end()) end = true;
				return *this;
			}
			// post increment
			Node_Iterator operator++(int) {
				Node_Iterator tmp = *this;
				++it;
				if (it==mynodes_.end()) end = true;
				return tmp;
			}
			// equals
			bool operator==(const Node_Iterator& other) const {
				if (DEBUG) std::cout << "testing ==: " << end << " " << other.end << std::endl;
				if (end && other.end) {
					return true;
				} else if (end || other.end) {
					return false;
				}
				return operator*() == (*other.it)->val_;
			};
			// not equals
			bool operator!=(const Node_Iterator& other) const {
				if (DEBUG) std::cout << "testing !=" << std::endl;
				return !operator==(other);
			}

			//Node_Iterator(std::vector<std::shared_ptr<Node>> v)
			Node_Iterator(const std::map<N,std::shared_ptr<Node>> *nodes = nullptr)
			{
				
				if (nodes == nullptr) {
					end = true;
				} else {
					//nodes_ = new std::vector<std::shared_ptr<Node>>();
					std::for_each((*nodes).begin(),(*nodes).end(),
						[this] (const std::pair<N,std::shared_ptr<Node>>& p) 
							{ mynodes_.push_back(p.second); });

					std::sort(mynodes_.begin(),mynodes_.end(),
						[] (const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
							return a->numEdges_ != b->numEdges_ ?
								a->numEdges_ > b->numEdges_ : a->val_ < b->val_;
							});
					it = mynodes_.begin();
					end = false;
				}
			}

		private:
			bool end;
			typename std::vector<std::shared_ptr<Node>>::iterator it;
			typename std::vector<std::shared_ptr<Node>> mynodes_;

	};

	template <typename N, typename E> class Edge_Iterator
	{
		public:
			friend class Graph<N,E>;

			typedef typename Graph<N,E>::Node Node;
			typedef typename Graph<N,E>::Edge Edge;

			typedef std::ptrdiff_t                     difference_type;
			typedef std::forward_iterator_tag          iterator_category;
			typedef E                                  value_type;
			const typedef E*                           pointer;
			const typedef E&                           reference;

			// value type
			reference operator*() const {
				if (DEBUG) std::cout << "testing *: "<< (*it)->val_ << std::endl;
				return (*it)->val_;
			}
			// reference type
			pointer operator->() const {
				return &(operator*());
			}
			// pre increment
			Edge_Iterator& operator++() {
				++it;
				if (it==myedges_.end()) end = true;
				return *this;
			}
			// post increment
			Edge_Iterator operator++(int) {
				Edge_Iterator tmp = *this;
				++it;
				if (it==myedges_.end()) end = true;
				return tmp;
			}
			// equals
			bool operator==(const Edge_Iterator& other) const {
				if (DEBUG) std::cout << "testing ==: " << end << " " << other.end << std::endl;
				if (end && other.end) {
					return true;
				} else if (end || other.end) {
					return false;
				}
				return operator*() == (*other.it)->val_;
			};
			// not equals
			bool operator!=(const Edge_Iterator& other) const {
				if (DEBUG) std::cout << "testing !=" << std::endl;
				return !operator==(other);
			}

			//Edge_Iterator(std::vector<std::shared_ptr<Edge>> v)
			Edge_Iterator(const std::shared_ptr<Node> node = nullptr)
			{
				if (node == nullptr || node->edges_.empty()) {
					end = true;
				} else {
					std::for_each(node->edges_.begin(),node->edges_.end(),
						[this] (const std::shared_ptr<Edge>& e) 
							{ myedges_.push_back(e); });				

					std::sort(myedges_.begin(),myedges_.end(),
						[] (const std::shared_ptr<Edge>& a, const std::shared_ptr<Edge>& b) {
							if (a->val_ == b->val_) {
								if (auto tmpa = a->dest.lock()) {
									if (auto tmpb = b->dest.lock()) {
										return tmpa->val_ < tmpb->val_;
									}
								}
							}
							return a->val_ < b->val_;
						});
					it = myedges_.begin();
					end = false;
				}
			}

		private:
			N getDest () {
				if (auto tmp = (*it)->dest.lock()) {
					return tmp->val_;
				}
				throw std::runtime_error("getDest: Node DNE");
			}

			bool end;
			typename std::vector<std::shared_ptr<Edge>>::iterator it;
			typename std::vector<std::shared_ptr<Edge>> myedges_;

	};


	template <typename N, typename E>
	class Graph
	{
		private:
			struct Node;
			struct Edge;

			struct Node
			{
				N val_;
				int numEdges_;
				std::set<std::shared_ptr<Edge>> edges_;
				Node() {}
				Node(const N x) : val_{x} {numEdges_=0;}
				void printNode (N n) {
					if (n!=val_) throw std::runtime_error("Node corruption: index != val_");
					std::cout << val_ << ": ";
					for (std::shared_ptr<Edge> e : edges_) (*e).printEdge();
					std::cout << std::endl;
				} 
			};

			struct Edge
			{
				std::weak_ptr<Node> orig;
				std::weak_ptr<Node> dest;
				E val_;
				Edge(std::shared_ptr<Node> o, std::shared_ptr<Node> d, E x) : val_{x} {//orig{o}, dest{d}, 
					orig = o;
					dest = d;
				}
				Edge() {};
				void printEdge () {
					if (auto tmp = dest.lock())
						std::cout << "[" << val_ << "] " << tmp->val_ << " ";
				}
			};

		public:

			friend class Node_Iterator<N,E>;
			typedef Node_Iterator<N,E> Node_Iterator;
			
			friend class Edge_Iterator<N,E>;
			typedef Edge_Iterator<N,E> Edge_Iterator;
			
			Graph() :
				nodes_{}
				{};

			//copy constructor
			Graph(const Graph &g) :
				nodes_{g.nodes_}
				{};

			//move constructor
			Graph(Graph &&g) :
				nodes_{std::move(g.nodes_)}
				{};
			
			//Destructor
			~Graph()
			{
			};

			//=copy Operator
			Graph& operator=(const Graph &g)
			{
				if (this != g) {
					nodes_ = g.nodes_;
				}
				return *this;
			}

			//=move Operator
			Graph& operator=(Graph &&g)
			{
				if (this != g) {
					nodes_ = std::move(g.nodes_);
				}
				return *this;
			}

			bool addNode(const N& val_)
			{
				if (nodes_.find(val_) == nodes_.end()) {
					if (DEBUG) std::cout << "adding: " << val_ << std::endl;
					nodes_[val_] = std::make_shared<Node>(Node{val_});
				} else if (DEBUG) {
					std::cout << val_ << ": not added. Already exists" << std::endl;
				}

				return true;
			}

			bool addEdge(const N& orig, const N& dest, const E& val)
			{
				// check that both orig and dest exist
				auto findOrig = nodes_.find(orig);
				if (findOrig == nodes_.end()) throw std::runtime_error("addEdge: origin DNE");
				auto findDest = nodes_.find(dest);
				if (findDest == nodes_.end()) throw std::runtime_error("addEdge: dest DNE");
				//if (findDest == nodes_.end()) std::runtime_error("cannot add edge from"+orig+" to "+dest+", "+dest+" does not exist");

				// check if the edge between already exists
				// auto findEdge = std::find_if(findOrig->second->edges_.begin(),findOrig->second->edges_.end(),
				// 							[val_] (const std::shared_ptr<Edge>& e) {return e->val_==val_;});

				auto findEdge = std::find_if(findOrig->second->edges_.begin(),findOrig->second->edges_.end(),
											[val,dest] (const std::shared_ptr<Edge>& e) {
												if (e->val_ == val)
													if (auto tmp = e->dest.lock())
														if (tmp->val_ == dest)
															return true;
												return false;
											});

				if (findEdge == findOrig->second->edges_.end()) {
					if (DEBUG) std::cout << "adding edge: " << orig << " " << dest << " " << val << std::endl;
					findOrig->second->edges_.insert(std::make_shared<Edge>(Edge(findOrig->second,findDest->second,val)));
					++findOrig->second->numEdges_;
					return true;
				} else if (DEBUG) {
					std::cout << orig << "->" << dest << " not added. Already exists" << std::endl;
				}
				return false;
			}

			bool replace(const N& node, const N& val)
			{
				// check the node exists
				auto findNode = nodes_.find(node);
				if (findNode == nodes_.end()) throw std::runtime_error("replace: Node DNE");

				// check if the new val_ exists
				auto findval_ = nodes_.find(val);

				if (findval_ == nodes_.end()) {
					if (DEBUG) std::cout << "replacing " << findNode->second->val_ << " with " << val << std::endl;
					nodes_[val] = nodes_[node];
					nodes_[val]->val_ = val;
					nodes_.erase(findNode);
					//findNode->second->val_ = 66;	
					return false;
				}
				if (DEBUG) std::cout << "replace: " <<val << " already exists" << std::endl;
				return true;
			} 

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

			void deleteEdge(const N& orig, const N& dest, const E& val) noexcept
			{
				// find the origin node
				auto findNode = nodes_.find(orig);
				// find the destination node: Must have same dest AND val_
				if (findNode != nodes_.end()) {
					auto findEdge = std::find_if(findNode->second->edges_.begin(), findNode->second->edges_.end(),
											[dest, val] (const std::shared_ptr<Edge>& e) {
												if (e->val_ == val)
													if (auto tmp = e->dest.lock())
														if (tmp->val_ == dest)
															return true;
												return false;
											});
					if (findEdge != findNode->second->edges_.end()) {
						findNode->second->edges_.erase(findEdge);
						++findNode->second->numEdges_;
					} else if (DEBUG) {
						std::cout << "deleteEdge: no edge was found" << std::endl;
					}
				} else if (DEBUG) {
					std::cout << "deleteEdge: origin: " << orig << " not found" << std::endl;
				}
			}

			void clear() noexcept
			{
				nodes_.clear();
			}

			bool isNode(const N& node) const
			{
				return nodes_.find(node) != nodes_.end();
			}

			bool isConnected(const N& orig, const N& dest) const
			{
				auto findOrig = nodes_.find(orig);
				if (findOrig == nodes_.end()) throw std::runtime_error("addEdge: origin DNE");
				auto findDest = nodes_.find(dest);
				if (findDest == nodes_.end()) throw std::runtime_error("addEdge: dest DNE");

				auto findEdge = std::find_if(findOrig->second->edges_.begin(), findOrig->second->edges_.end(),
											[dest] (const std::shared_ptr<Edge>& e) {
												if (auto tmp = e->dest.lock())
													if (tmp->val_ == dest)
														return true;
												return false;
											});
				return findEdge != findOrig->second->edges_.end()? true : false;
			}

			/*
			 * Prints the nodes in descending number of edges order
			 */
			void printNodes()
			{
				for (auto it = begin(); it != end(); ++it ) {
					std::cout << *it << std::endl;
				}
			}

			void printEdges(const N& node) const
			{
				std::cout << "Edges attached to Node " << node << std::endl;
				bool tmp = false;
				for (auto it = edgeIteratorBegin(node); it != edgeIteratorEnd(node); ++it) {
					std::cout << it.getDest() << " " << *it << std::endl;
					tmp = true;
				}
				if (!tmp) std::cout << "(null)" << std::endl;
			}

			void printGraph ()
			{
				std::cout << "Printing Graph" << std::endl;
				for (auto n : nodes_) {
					n.second->printNode(n.first);
				}
			}

			Node_Iterator begin() const
			{

				return Node_Iterator(&nodes_);
			};


			Node_Iterator end() const
			{
				return Node_Iterator(nullptr);
			}

			Edge_Iterator edgeIteratorBegin(const N& node) const
			{
				auto findNode = nodes_.find(node);
				if (findNode != nodes_.end()) {
					//if (findNode->second)
					return Edge_Iterator(findNode->second);
				}
				throw std::runtime_error("edgeIteratorBegin: edge DNE");
			}

			Edge_Iterator edgeIteratorEnd (const N& node) const 
			{
				return Edge_Iterator(nullptr);
			}

		private:
			std::map< N, std::shared_ptr<Node> > nodes_;
	};
}

#endif
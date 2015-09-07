
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <algorithm>

namespace cs6771 {
	template <typename N, typename E>
	class Graph {
		private:

		public:

			Graph() :
				nodes_{},
				edges_{}
				{};

			//copy constructor
			Graph(const Graph &g) :
				nodes_{g.nodes_},
				edges_{g.edges_}
				{};

			//move constructor
			Graph(Graph &&g) :
				nodes_{std::move(g.nodes_)},
				edges_{std::move(g.edges_)}
				{};
			
			//Destructor
			~Graph()
			{
				//delete nodes_;
				//delete edges_;
			};

			//=copy Operator
			Graph& operator=(const Graph &g)
			{
				if (this != g) {
					nodes_ = g.nodes_;
					edges_ = g.edges_;
				}
				return *this;
			}

			//=move Operator
			Graph& operator=(Graph &&g)
			{
				if (this != g) {
					nodes_ = std::move(g.nodes_);
					edges_ = std::move(g.edges_);
				}
				return *this;
			}

		private:
			std::vector<N> nodes_;
			std::vector<E> edges_;
	};
}

#endif
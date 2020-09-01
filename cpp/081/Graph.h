#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>
#include <iostream>
#include <utility>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <limits>
#include <string>
#include <sstream>

using std::noskipws;
using std::ostream;
using std::istream;
using std::set;
using std::map;
using std::vector;
using std::list;
using std::stack;
using std::queue;
using std::pair;
using std::make_pair;
using std::endl;
using std::numeric_limits;
using std::string;
using std::stringstream;

typedef size_t size_type;

template <typename id, typename weight> class Graph;
template <typename id, typename weight> ostream& operator<<( ostream& os, const Graph<id,weight>& graph );
template <typename id, typename weight> istream& operator>>( istream& is, Graph<id,weight>& graph );

template <typename id, typename weight> class Graph {
	public:
		typedef map<id,weight> edgeMap;
		typedef map<id,pair<edgeMap,edgeMap> > vertexMap;
	private:
		vertexMap adjacencies;
		size_type numEdges;
		
		edgeMap& inNeighbors( id v ); // given a vertex, return all neighbors on in-edges
		edgeMap& outNeighbors( id v ); // given a vertex, return all neighbors on out-edges
		const edgeMap& inNeighbors( id v ) const; // given a vertex, return all neighbors on in-edges
		const edgeMap& outNeighbors( id v ) const; // given a vertex, return all neighbors on out-edges

		void depthFirstSearch( id v, list<id>& L, set<id>& vis ) const;
		void shortestPath( id v, size_type i, set<id>& vis, map<id,size_type>& M ) const;
		void minimumPath( id v, weight l, set<id>& vis, map<id,weight>& M ) const;
		void fixEdges ();
	public:
		friend ostream& operator<< <> ( ostream& os, const Graph<id,weight>& graph ); // the overloaded stream insertion global friend operator
		friend istream& operator>> <> ( istream& is, Graph<id,weight>& graph ); // the overloaded stream extraction global friend operator
		Graph();
		void addVertex( id v ); // should add the vertex to the graph with no initial edges
		void addEdge( id v1, id v2, weight w ); // should add a directed edge to the graph from vertex v1 to vertex v2
		void removeVertex( id v ); // should remove the vertex and all directed edges that involve the vertex everywhere in the graph
		void removeEdge( id v1, id v2 ); // should remove the edge from the graph
		size_type vertexCount() const; // the number of vertices in the graph
		size_type edgeCount() const; // the number of edges in the graph
		bool empty() const; // true if there are no vertices or edges in the graph
		void clear(); // remove all vertices and edges from the graph
		const size_type inDegree( id v ) const; // given a vertex, return the count of its in-edges
		const size_type outDegree( id v ) const; // given a vertex, return the count of its out-edges
		Graph<id,weight> reverseEdges() const; // returns a new graph with all edges in the graph reversed
		list<id> topologicalSort() const; // should return an empty vector if a cycle is detected
		map<id,size_type> shortestPaths( id v ) const; // single-source shortest paths based on hops only
		map<id,weight> minimumPaths( id v ) const; // single-source minimum paths based on weights; must implement Dijkstra's algorithm; inaccessible (infinite distance) vertices should simply not be included in the map; you do *NOT* need to use priority queues to achieve a maximally efficient implementation
		size_type eccentricity( id v ) const; // should be based on hops alone, not weights
		size_type diameter() const; // the maximum eccentricity in the graph
		list<Graph<id,weight> > stronglyConnectedComponents() const; // should return each component as a separate Graph object in the list; must implement Kosaraju's algorithm
		list<Graph<id,weight> > weaklyConnectedComponents() const; // should return each component as a separate Graph object in the list
		list<id> isolates() const; // should return the set of vertices that have no connections
		list<id> breadthFirstSearch( id v ) const; // should perform a breadth-first search from the given vertex returning vertices in the list in the order they were found
		list<id> depthFirstSearch( id v ) const; // should perform a pre-order depth-first search from the given vertex
		bool eulerTour() const; // returns true if an Euler tour exists; false otherwise
};

#endif

template <typename id,typename weight>
Graph<id,weight>::Graph() {
	numEdges = 0;
}

template <typename id,typename weight>
void Graph<id,weight>::addVertex( id v ) {
	adjacencies.insert (make_pair(v, make_pair(edgeMap(), edgeMap())));
}

template <typename id,typename weight>
void Graph<id,weight>::addEdge( id v1, id v2, weight w ) {
	bool result;

	if (v1 != v2)
	  {
		// If they dont exist, create them
		result = adjacencies[v1].second.insert (make_pair(v2, w)).second; // out-edge
		adjacencies[v2].first.insert (make_pair(v1, w)); // in-edge

		if (result == true)
		  {
			++numEdges;
		  }
	  }
}

template <typename id,typename weight>
void Graph<id,weight>::removeVertex( id v ) {
	// remove in-edges
	for (typename edgeMap::iterator it = adjacencies[v].first.begin(); it != adjacencies[v].first.end(); ++it)
	  {
		removeEdge (it->first, v);
	  }
	// remove out-edges
	for (typename edgeMap::iterator it = adjacencies[v].second.begin(); it != adjacencies[v].second.end(); ++it)
	  {
		removeEdge (v, it->first);
	  }

	adjacencies.erase (v);
}

template <typename id,typename weight>
void Graph<id,weight>::removeEdge( id v1, id v2 ) {
	if ((adjacencies.count (v1) == 1) && (adjacencies.count (v2) == 1))
	  {
		size_type result;

		result = adjacencies[v1].second.erase (v2); // out-edge
		adjacencies[v2].first.erase (v1); // in-edge

		if (result == 1)
		  {
			--numEdges;
		  }
	  }
}

template <typename id,typename weight>
size_type Graph<id,weight>::vertexCount() const {
	return adjacencies.size();
}

template <typename id,typename weight>
size_type Graph<id,weight>::edgeCount() const {
	return numEdges;
}

template <typename id,typename weight>
bool Graph<id,weight>::empty() const {
	return (adjacencies == 0);
}

template <typename id,typename weight>
void Graph<id,weight>::clear() {
	adjacencies.clear();
	numEdges = 0;
}

template <typename id,typename weight>
map<id,weight>& Graph<id,weight>::inNeighbors( id v ) {
	typename vertexMap::const_iterator vit = adjacencies.find(v);
	if (vit == adjacencies.end())
	  {
		throw (0);
	  }
	return vit->second.first;
}

template <typename id,typename weight>
const map<id,weight>& Graph<id,weight>::inNeighbors( id v ) const {
	typename vertexMap::const_iterator vit = adjacencies.find(v);
	if (vit == adjacencies.end())
	  {
		throw (0);
	  }
	return vit->second.first;
}

template <typename id,typename weight>
map<id,weight>& Graph<id,weight>::outNeighbors( id v ) {
	typename vertexMap::const_iterator vit = adjacencies.find(v);
	if (vit == adjacencies.end())
	  {
		throw (0);
	  }
	return vit->second.second;
}

template <typename id,typename weight>
const map<id,weight>& Graph<id,weight>::outNeighbors( id v ) const {
	typename vertexMap::const_iterator vit = adjacencies.find(v);
	if (vit == adjacencies.end())
	  {
		throw (0);
	  }
	return vit->second.second;
}

template <typename id,typename weight>
const size_type Graph<id,weight>::inDegree( id v ) const {
	if (adjacencies.count (v) == 1)
	  {
		return adjacencies[v].first.size();
	  }
	else
	  {
		return 0;
	  }
}

template <typename id,typename weight>
const size_type Graph<id,weight>::outDegree( id v ) const {
	if (adjacencies.count (v) == 1)
	  {
		return adjacencies[v].second.size();
	  }
	else
	  {
		return 0;
	  }
}

template <typename id,typename weight>
Graph<id,weight> Graph<id,weight>::reverseEdges() const {
	typedef typename vertexMap::iterator vmapiter;

	Graph<id,weight> newgraph = *this;

	for (vmapiter it = newgraph.adjacencies.begin (); it != newgraph.adjacencies.end (); ++it)
	  {
		edgeMap tmp = it->second.first;
		it->second.first = it->second.second;
		it->second.second = tmp;
	  }

	return newgraph;
}

template <typename id,typename weight>
ostream& operator<<( ostream& os, const Graph<id,weight>& graph ) {
	typedef typename Graph<id, weight>::vertexMap::const_iterator vmapiter;
	typedef typename Graph<id, weight>::edgeMap::const_iterator emapiter;
	for (vmapiter it = graph.adjacencies.begin (); it != graph.adjacencies.end (); ++it)
	  {
		os << it->first << " ";
		for (emapiter it2 = it->second.second.begin (); it2 != it->second.second.end (); ++it2)
		  {
			os << it2->first << "," << it2->second << " ";
		  }
		os << endl;
	  }
	return os;
}

template <typename id,typename weight>
istream& operator>>( istream& is, Graph<id,weight>& graph ) {
	graph.clear();

	string str;

	while (getline (is, str), !is.eof())
	  {
		id v1;
		stringstream ss1 (str);

		ss1 >> v1;
		graph.addVertex (v1);

		while (ss1 >> str, !ss1.eof())
		  {
			size_t index = str.find (',');
			str[index] = ' ';

			id v2;
			weight w;
			stringstream ss2 (str);

			ss2 >> v2 >> w;

			graph.addEdge (v1, v2, w);
		  }
	  }

	return is;
}

template <typename id,typename weight>
list<id> Graph<id,weight>::topologicalSort() const {
	Graph<id,weight> g = *this; // This is because we will be removing edges
	list<id> L;
	list<id> S;

	// Fill S with the vertices that have no in-edges
	for (typename vertexMap::iterator it = g.adjacencies.begin(); it != g.adjacencies.end(); ++it)
	  {
		if (it->second.first.empty())
		  {
			S.push_back (it->first);
		  }
	  }

	while (!S.empty())
	  {
		// remove n from S and add to L
		id n = S.front();
		S.pop_front();
		L.push_back (n);

		// for each out-edge
		for (typename edgeMap::iterator it = g.adjacencies[n].second.begin(); it != g.adjacencies[n].second.end(); ++it)
		  {
			// erase the in-edge from n
			id m = it->first;
			g.removeEdge (n, m);

			// if there are no more in-edges, add m to S
			if (g.adjacencies[m].first.empty())
			  {
				S.push_back (m);
			  }
		  }
	  }

	// If there are edges, the graph is cyclic, return an empty list
	if (g.edgeCount() != 0)
	  {
		return list<id>();
	  }
	else
	  {
		return L;
	  }
}

template <typename id,typename weight>
map<id,size_type> Graph<id,weight>::shortestPaths( id v ) const {
	map<id,size_type> M;
	set<id> vis;

	shortestPath (v, 0, vis, M);

	return M;
}

template <typename id,typename weight>
void Graph<id,weight>::shortestPath( id v, size_type i, set<id>& vis, map<id,size_type>& M ) const {
	typename vertexMap::const_iterator vit = adjacencies.find (v);

	if (vit != adjacencies.end())
	  {
		vis.insert (v);
		M.insert (make_pair (v, i));

		for (typename edgeMap::const_iterator it = vit->second.second.begin(); it != vit->second.second.end(); ++it)
		  {
			if (vis.count (it->first) == 0)
			  {
				shortestPath (it->first, i+1, vis, M);
			  }
		  }
	  }
}

template <typename id,typename weight>
map<id,weight> Graph<id,weight>::minimumPaths( id v ) const {
	map<id,weight> M;
	set<id> vis;

	M[v] = 0;

	minimumPath (v, 0, vis, M);

	return M;
}

template <typename id,typename weight>
void Graph<id,weight>::minimumPath( id v, weight l, set<id>& vis, map<id,weight>& M ) const {
	typename vertexMap::const_iterator vit = adjacencies.find (v);

	if (vit != adjacencies.end())
	  {
		vis.insert (v);

		for (typename edgeMap::const_iterator it = vit->second.second.begin(); it != vit->second.second.end(); ++it)
		  {
			if (vis.count (it->first) == 0)
			  {
				if (M.count (it->first) == 0)
				  {
					M[it->first] = ((numeric_limits<weight>::has_infinity)?(numeric_limits<weight>::infinity()):(numeric_limits<weight>::max()));
				  }

				if (l + it->second < M[it->first])
				  {
					M[it->first] = l + it->second;
				  }
			  }
		  }

		// find minimum
		typename map<id, weight>::iterator min = M.end();
		for (typename map<id,weight>::iterator it = M.begin(); it != M.end(); ++it)
		  {
			if (vis.count (it->first) == 0)
			  {
				if (min == M.end() || it->second < min->second)
				  {
					min = it;
				  }
			  }
		  }
		if (min != M.end())
		  {
			minimumPath (min->first, min->second, vis, M);
		  }
	  }
}

template <typename id,typename weight>
size_type Graph<id,weight>::eccentricity( id v ) const {
	map<id,size_type> M = shortestPaths (v);
	size_type max = 0;

	for (typename map<id,size_type>::const_iterator it = M.begin(); it != M.end(); ++it)
	  {
		if (max < it->second)
		  {
			max = it->second;
		  }
	  }

	return max;
}

template <typename id,typename weight>
size_type Graph<id,weight>::diameter() const {
	size_type max = 0;
	for (typename vertexMap::const_iterator it = adjacencies.begin(); it != adjacencies.end(); ++it)
	  {
		size_type curr = eccentricity (it->first);
		if (max < curr)
		  {
			max = curr;
		  }
	  }
	return max;
}

template <typename id,typename weight>
list<id> Graph<id,weight>::isolates() const {
	list<id> L;

	for (typename vertexMap::const_iterator it = adjacencies.begin(); it != adjacencies.end(); ++it)
	  {
		if (it->second.first.empty() && it->second.second.empty())
		  {
			L.push_back (it->first);
		  }
	  }

	return L;
}

template <typename id,typename weight>
list<id> Graph<id,weight>::breadthFirstSearch( id v ) const {
	list<id> L;
	queue<typename vertexMap::const_iterator> q;
	typename vertexMap::const_iterator vit = adjacencies.find (v);
	set<id> vis;

	if (vit != adjacencies.end())
	  {
		vis.insert (vit->first);
		q.push (vit);

		while (!q.empty())
		  {
			if (q.front() != adjacencies.end ())
			  {
				L.push_back (q.front()->first);
			  }

			for (typename edgeMap::const_iterator it = q.front()->second.second.begin(); it != q.front()->second.second.end(); ++it)
			  {
				if (vis.count (it->first) == 0)
				  {
					vis.insert (it->first);
					q.push (adjacencies.find (it->first));
				  }
			  }

			q.pop ();
		  }
	  }

	return L;
}

template <typename id,typename weight>
list<id> Graph<id,weight>::depthFirstSearch( id v ) const {
	list<id> L;
	set<id> vis;

	depthFirstSearch (v, L, vis);

	return L;
}

template <typename id,typename weight>
void Graph<id,weight>::depthFirstSearch( id v, list<id>& L, set<id>& vis ) const {
	L.push_back (v);
	vis.insert (v);

	typename vertexMap::const_iterator vit = adjacencies.find (v);
	if (vit != adjacencies.end())
	  {
		for (typename edgeMap::const_iterator it = vit->second.second.begin(); it != vit->second.second.end(); ++it)
		  {
			// if it hasn't been visted, run a dfs on that vertex
			if (vis.count (it->first) == 0)
			  {
				depthFirstSearch (it->first, L, vis);
			  }
		  }
	  }

}

template <typename id,typename weight>
list<Graph<id,weight> > Graph<id,weight>::weaklyConnectedComponents() const {
	list<Graph<id,weight> > ret;
	set<id> vis;
	Graph g = *this;

	for (typename vertexMap::iterator i = g.adjacencies.begin(); i != g.adjacencies.end(); ++i)
	  {
		i->second.first.insert (i->second.second.begin(), i->second.second.end());
		i->second.second.insert (i->second.first.begin(), i->second.first.end());
	  }

	while (vis.size() != g.adjacencies.size())
	  {
		Graph newg;

		typename vertexMap::const_iterator it = g.adjacencies.begin();
		while (vis.count (it->first) != 0)
		  {
			++it;
		  }
		list<id> dfs = g.depthFirstSearch (it->first);

		for (typename list<id>::const_iterator it = dfs.begin(); it != dfs.end(); ++it)
		  {
			newg.adjacencies.insert (*(adjacencies.find (*it)));
		  }
		vis.insert (dfs.begin(), dfs.end());

		ret.push_back (newg);
	  }

	return ret;
}

template <typename id,typename weight>
list<Graph<id,weight> > Graph<id,weight>::stronglyConnectedComponents() const {
	list<Graph<id,weight> > ret;
	list<id> s;
	set<id> vis;
	Graph rev = reverseEdges();

	while (s.size() != adjacencies.size())
	  {
		typename vertexMap::const_iterator it = adjacencies.begin();
		while (vis.count (it->first) != 0)
		  {
			++it;
		  }
		list<id> dfs = depthFirstSearch (it->first);

		s.insert (s.end(), dfs.begin(), dfs.end());
		vis.insert (dfs.begin(), dfs.end());
	  }

	while (!s.empty())
	  {
		Graph newg;
		id i = s.front();
		s.pop_front();
		list<id> dfs = rev.depthFirstSearch (i);

		for (typename list<id>::const_iterator it = dfs.begin(); it != dfs.end(); ++it)
		  {
			s.remove (*it);
			rev.removeVertex (*it);
			newg.adjacencies.insert (*(adjacencies.find (*it)));
		  }

		newg.fixEdges();

		ret.push_back (newg);
	  }

	return ret;
}

template <typename id,typename weight>
bool Graph<id,weight>::eulerTour() const {
	// If a vertex has an odd number of edges, there is no euler tour
	for (typename vertexMap::const_iterator it = adjacencies.begin(); it != adjacencies.end(); ++it)
	  {
		if (it->second.first.size()%2 == 1 || it->second.second.size()%2 == 1)
		  {
			return false;
		  }
	  }

	return true;
}

template <typename id,typename weight>
void Graph<id,weight>::fixEdges() {
	numEdges = 0;

	for (typename vertexMap::iterator i = adjacencies.begin(); i != adjacencies.end(); ++i)
	  {
		list<id> inRem;
		list<id> outRem;

		// in nodes
		for (typename edgeMap::iterator j = i->second.first.begin(); j != i->second.first.end(); ++j)
		  {
			if (adjacencies.count (j->first) == 0 || i->first == j->first)
			  {
				inRem.push_back (j->first);
			  }
		  }
		// out nodes, increment numEdges for valid edges
		for (typename edgeMap::iterator j = i->second.second.begin(); j != i->second.second.end(); ++j)
		  {
			if (adjacencies.count (j->first) == 0 || i->first == j->first)
			  {
				outRem.push_back (j->first);
			  }
			else
			  {
				++numEdges;
			  }
		  }

		// actually remove the invalid edges now
		for (typename list<id>::iterator j = inRem.begin(); j != inRem.end(); ++j)
		  {
				i->second.first.erase (*j);
		  }
		for (typename list<id>::iterator j = outRem.begin(); j != outRem.end(); ++j)
		  {
				i->second.second.erase (*j);
		  }
	  }
}

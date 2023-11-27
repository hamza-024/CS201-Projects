#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <limits>
#include <queue>
#include <stack>

class Vertex {
public:
	bool visited;
	int distance;
	int previous;
	int finish;
	std::list<int> adj;
};

class Graph {
public:
	Graph(int V, int E, std::pair<int, int> *edges) {
		_V = V;
		_E = E;
		vertices = new Vertex[_V];
		for (int i = 0; i < _V; i++) {
                    vertices[i].visited = false;
                    vertices[i].distance = std::numeric_limits<int>::max();
                    vertices[i].previous = -1;
		}
		for (int i = 0; i < _E; i++) {
		    addEdge(edges[i].first, edges[i].second);
		}
	}

	virtual ~Graph() {
		for (int i=0; i<_V; ++i) {
		    auto adj = vertices[i].adj;
		    adj.clear(); // clear list
		}

		delete[] vertices; // delete array of vertices
	}

	int V() {
		return _V;
	}

	int E() {
		return _E;
	}

	void addEdge(int u, int v) {
		vertices[u].adj.push_back(v);
	}

	std::list<int> getEdges(int u) {
		return vertices[u].adj;
	}

	int degree(int u) {
		return vertices[u].adj.size();
	}

	void bfs(int s) {
		// your implementation goes here
    for (int i = 0; i < _V; i++) {
        vertices[i].visited = false;
        vertices[i].distance = std::numeric_limits<int>::max();
        vertices[i].previous = -1;
    }

    std::queue<int> q;

    vertices[s].visited = true;
    vertices[s].distance = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
		std::cout << u << " ";
        for (const int& v : vertices[u].adj) {
            if (!vertices[v].visited) {
                vertices[v].visited = true;
                vertices[v].distance = vertices[u].distance + 1;
                vertices[v].previous = u;
                q.push(v);
            }
        }
    }

	std::cout << std::endl;
	}

	void dfs() {
		// your implementation goes here
        for (int i = 0; i < _V; i++) {
            vertices[i].visited = false;
            vertices[i].previous = -1;
        }

        int time = 0;

        for (int i = 0; i < _V; i++) {
            if (!vertices[i].visited) {
                dfs_visit(i, time);
            }
        }
	}

	void dfs_visit(int u, int& time) {
		// your implementation goes here
        time++;
        vertices[u].distance = time;
        vertices[u].visited = true;
		std::cout << u << " ";

        for (const int& v : vertices[u].adj) {
            if (!vertices[v].visited) {
                vertices[v].previous = u;
                dfs_visit(v, time);
            }
        }

        time++;
        vertices[u].finish = time;
    }


	void print_path(int s, int v) {
		if (v == s)
		   std::cout << s;
		else if (vertices[v].previous == -1)
		   std::cout << "not connected";
		else {
		   print_path(s,vertices[v].previous);
		   std::cout << "->" << v;
		}
	}

	std::string toString() {
		std::stringbuf buffer;
		std::ostream os(&buffer);
		os << "Vertices = " << _V << ", Edges = " << _E << std::endl;
		for (int i = 0; i < _V; ++i) {
		    os << i << "(" << degree(i) << "): ";
		    for (const auto& l : vertices[i].adj) 
			os << l << " ";
		    os << std::endl;
		}

		return buffer.str();
	}
private:
	int _V; // no. of vertices
	int _E; // no. of edges
	Vertex *vertices; // array of vertices
};

#endif

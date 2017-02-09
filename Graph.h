#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

using Vertex = int;

class Graph
{
	size_t V_count;
	size_t E_count;
	std::vector<int> Vdeg;
	std::list<Vertex>* neighbours;
	bool findEdge(const Vertex& v1, const Vertex& v2) const;
	size_t Newton(const size_t& n, const size_t& k) const;
public:
	Graph(const int& V);
	~Graph();
	void makeEdge(const Vertex& v1, const Vertex& v2);
	bool isIsomorphic(const Graph& other, Vertex* V_toPerm) const;
	size_t VertexCount() const;
};
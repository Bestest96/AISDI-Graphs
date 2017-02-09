#include "Graph.h"


Graph::Graph(const int& V): V_count(V), E_count(0)
{
	for (int i = 0; i < V; ++i)
		Vdeg.push_back(0);
	neighbours = new std::list<Vertex>[V];
}

Graph::~Graph()
{
	delete[] neighbours;
}

size_t Graph::VertexCount() const
{
	return V_count;
}

size_t Graph::Newton(const size_t& n, const size_t& k) const
{
	size_t result = 1;
	for (size_t i = 1; i <= k; ++i)
	{
		result *= n - i + 1;
		result /= i;
	}
	return result;
}



void Graph::makeEdge(const Vertex& v1, const Vertex& v2)
{
	if (findEdge(v1, v2))
		return;
	neighbours[v1].push_back(v2);
	if (v1 != v2)
		neighbours[v2].push_back(v1);
	++Vdeg[v1];
	++Vdeg[v2];
	++E_count;
}

bool Graph::findEdge(const Vertex& v1, const Vertex& v2) const
{
	if (std::find(neighbours[v1].begin(), neighbours[v1].end(), v2) != neighbours[v1].end())
		return true;
	return false;
}


bool Graph::isIsomorphic(const Graph& other, Vertex* V_toPerm) const
{
	if (V_count != other.V_count)
        return false;
	if (E_count != other.E_count)
        return false;
	std::vector<int> sortDeg(Vdeg);
	std::vector<int> otherSortDeg(other.Vdeg);
	std::sort(sortDeg.begin(), sortDeg.end());
	std::sort(otherSortDeg.begin(), otherSortDeg.end());
	for (size_t i=0;i<V_count;++i)
		if (sortDeg[i]!=otherSortDeg[i])
			return false;
	for (size_t i = 0; i < V_count; ++i)
		V_toPerm[i] = i;
	if (E_count == Newton(V_count, 2) + V_count)
		return true;
	do
	{
		size_t v = 0;
		while (v != V_count)
		{
			if (Vdeg[v] != other.Vdeg[V_toPerm[v]])
				break;
			++v;
		}
		if (v != V_count)
			continue;
		size_t i = 0;
		while (i != V_count)
		{
			auto it = neighbours[i].begin();
			while (it != neighbours[i].end())
			{
				if (std::find(other.neighbours[V_toPerm[i]].begin(), other.neighbours[V_toPerm[i]].end(), V_toPerm[*it]) == other.neighbours[V_toPerm[i]].end())
					break;
				++it;
			}
			if (it != neighbours[i].end())
				break;
			++i;
		}
		if (i == V_count)
			return true;
	} while (std::next_permutation(V_toPerm, V_toPerm + V_count));
	return false;
}

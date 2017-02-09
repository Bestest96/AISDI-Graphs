#include "Graph.h"
#include <chrono>

Graph readGraph(std::ifstream& file)
{
    int G_size = 0;
	Vertex v1, v2;
    file >> G_size;
	Graph G(G_size);
	while (!file.eof())
	{
		file >> v1 >> v2;
		v1 < v2 ? G.makeEdge(v1, v2) : G.makeEdge(v2, v1);
	}
	return G;
}

int main(int argc, char* argv[])
{
	if (argc<3)
	{
		std::cerr << "Za malo argumentow! Podaj dwa pliki z grafami" << std::endl;
#ifdef _WIN32
		system("PAUSE");
#endif
		return 1;
	}
	std::string graph1 = argv[1], graph2 = argv[2];
	std::ifstream file1(graph1), file2(graph2);
	if (!file1 || !file2)
	{
		std::cerr << "Blad otwarcia jednego z plikow!" << std::endl;
#ifdef _WIN32
		system("PAUSE");
#endif
		return 2;
	}
    Graph G1 = readGraph(file1);
    Graph G2 = readGraph(file2);
	Vertex* VPerm=new Vertex[G1.VertexCount()];
	auto start = std::chrono::steady_clock::now();
	if (G1.isIsomorphic(G2, VPerm))
	{
		std::cout << "Izomorficzne!" << std::endl;
		for (size_t i = 0; i < G1.VertexCount(); ++i)
			std::cout << i << "--->" << VPerm[i] << std::endl;
	}
	else
		std::cout << "Nieizomorficzne!" << std::endl;
	delete[] VPerm;
	auto end = std::chrono::steady_clock::now();
	double diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()/1000.0;
	std::cout << "Czas wykonania: " << diff << " s" << std::endl;
	file1.close();
	file2.close();
#ifdef _WIN32
	system("PAUSE");
#endif
	return 0;
}

// Author: Qiang Ren 
// E-mail: renq654321@gmail.com
// All rights reserved
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<utility>
#include<fstream>
#include<sstream>

using namespace std;

struct Edge
{
	int start, end;
	//char label;
	bool operator<(const Edge & rhs) const
	{
		if(start == rhs.start)
			return end < rhs.end;
		return start < rhs.start; 
	}
	bool operator!=(const Edge & rhs) const
	{
		if(start == rhs.start)
			if(end == rhs.end)
				return false;
		return true;
	}
};

struct Vertex
{
	int id;
	char label;
	bool operator<(const Vertex & rhs) const
	{
		return id < rhs.id;
	}
	bool operator!=(const Vertex & rhs) const
	{
		return id != rhs.id;
	}
};

class Graph
{
	public:
		set<Vertex>	V;//vector<Vertex> V;
		set<Edge>	E;//vector<Edge>	E;
		map< int, vector< Edge > > AdjList;
		map<int, int>	pre;//map< Vertice, int>	pre;
		map<int, int>	post;//map< Vertice, int>	post;
		map<int, bool>	visited;//vector<bool>	visited;
		map<int, int>	ccnum;//identify which component the node v belongs to
		int clock;
		int cc;
	
		void ReadGraph();	
		void DFSearch();
		void BFSearch();
		void Explore(int v);
		void Previsit(int v);
		void Postvisit(int v);
		Graph ReversedGraph();
};

void Graph::ReadGraph()
{
	int start = 0, end = 0;
	ifstream in("./data/3.9.txt");
	if(!in)
	{
		cerr << "error: unable to open input file:" << endl;
	}
	string line;
	Vertex tmp_vertex;
	Edge tmp_edge;
	while(in >> tmp_edge.start >> tmp_edge.end)
	{
		//cout << "start : " << tmp_edge.start << " end : " << tmp_edge.end << endl;
		tmp_vertex.id = tmp_edge.start;	//insert start vertice to vertice set
		tmp_vertex.label = (char)('A'+tmp_vertex.id - 1);
		V.insert(tmp_vertex);
		tmp_vertex.id = tmp_edge.end;		//insert end vertice to vertice set
		tmp_vertex.label = (char)('A'+tmp_vertex.id - 1); 
		V.insert(tmp_vertex);

		E.insert(tmp_edge);
		AdjList[tmp_edge.start].push_back(tmp_edge);
		//cout << "AdjList[" << tmp_edge.start <<"] push back : (" << tmp_edge.start << ", " << tmp_edge.end << ")" << endl;
	}
	clock = 1;
	cc = 0;
	in.close();
	//cout << "file closed ..." << endl;
}

void Graph::DFSearch()
{
	for(set<Vertex>::iterator it = V.begin(); it != V.end(); it++) //for all v in V	
	{
		visited[it->id] = false;
	}
	for(set<Vertex>::iterator it = V.begin(); it != V.end(); it++) //for all v in V	
	{
		if(! visited[it->id])
		{
			cc++;
			Explore(it->id);
		}
	}	
}

void Graph::Explore(int v)
{
	//Input: vertex v to explore
	//Output: visited[u] is set to true for all nodes u reachable from v 

	visited[v] = true;	
	Previsit(v);
	for(vector<Edge>::iterator it = AdjList[v].begin(); it != AdjList[v].end(); it++)//for each edge (u,v) in E
	{
		if(! visited[it->end]) // if not visited(u)
		{
			Explore(it->end);
		}
	}
	Postvisit(v);
}

void Graph::Previsit(int v)
{
	pre[v] = clock;
	//cout << "pre[" << v << "] = " << pre[v] << endl;
	ccnum[v] = cc;
	cout << "ccnum[" << (char)('A'+v-1) << "] = " << ccnum[v] << endl;
	clock++;
}

void Graph::Postvisit(int v)
{
	post[v] = clock;
	//cout << "post[" << v << "] = " << post[v] << endl;
	clock++;
}

Graph Graph::ReversedGraph()
{
	Graph result;
	result.V = V;
	result.clock = 1;
	result.cc = 0;
	//cout << "Vertex set size :" << V.size() << endl;
	//result.AdjList.resize(g.V.size());
	Edge tmp_edge;
	for(set<Vertex>::iterator v = V.begin(); v != V.end(); v++)
	{
		//cout << "vertex id :" << v->id << " vertex label : " << v->label << endl;
		for(vector<Edge>::iterator e = AdjList[v->id].begin(); e != AdjList[v->id].end(); e++)//for each edge (v,u) in g.E
		{//add edge (u,v) to E
			tmp_edge.start = e->end;
			tmp_edge.end = v->id;
			result.AdjList[e->end].push_back(tmp_edge);
			//cout << "reversed graph: " << tmp_edge.start << " " << tmp_edge.end << endl;
		}
	}
	return result;	
}

int main()
{
	Graph g;	
	g.ReadGraph();

	Graph r;
	r = g.ReversedGraph();
	
	r.DFSearch();
	
	return 0;
}

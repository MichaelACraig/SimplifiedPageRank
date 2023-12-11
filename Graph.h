//
// Created by Michael Craig on 10/31/23.
//
#include <vector>
#include <string>
#include <map>
#include <forward_list>

#ifndef PROJECT2PAGERANK_GRAPH_H
#define PROJECT2PAGERANK_GRAPH_H

struct Vertex{ //Essentially a node
    std::string webpage;
    double rank; //When we create vertices, update this
    int outDegree; //When we create edges, update this
};

class Graph{
private: //Child functions of what's in public
    int V; //Number of vertices in the graph
    int E; //Number of edges in the graph
    std::vector<std::forward_list<Vertex*>> adjList; //since we're not deleting vertices, forward_list functionality is better for overhead memory usage

public:
    Graph();
    Graph(int v);
    std::map<std::string, std::pair<int, Vertex*>> vertices; //Key is the URL, with values being a pair<unique ID, Vertex stored under keyname>

    void insertVertex(const std::string& input, int count); //Creates a vertex, updates the size of adjacency list to support.
    void insertEdge(const std::string& from, const std::string& to); //Creates an edge to the from_page -> to_page

    void PageRank(int n);
    void printRanks();

    //Test functions
    void printUniqueIDs();
    void printAdjList();
    void printOutDegrees();
};

#endif //PROJECT2PAGERANK_GRAPH_H

//
// Created by Michael Craig on 10/31/23.
//
#include "Graph.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <forward_list>

Graph::Graph(){
    V = 0;
    E = 0;
}
Graph::Graph(int v){
    V = v;
    adjList.resize(V);
}

void Graph::insertVertex(const std::string &input, int count) {
    //Essentially a constructor for a vertex
    vertices[input].first = count;
    vertices[input].second = new Vertex;
    vertices[input].second->webpage = input;
    vertices[input].second->rank = 1.0;
    vertices[input].second->outDegree = 0;
    adjList.resize(++V);

    //std::cout << "Adjacency List Size:" << adjList.size() << std::endl;
}
void Graph::insertEdge(const std::string &from, const std::string &to) {
    //Indices in the Adjacency List represent the unique IDs in the map (i.e if key www.google.com's unique ID is 0, that corresponds to 0 index on adjList
    //Each index on the Adjacency List is a doubly linked list

    int fromID = vertices[from].first;
    int toID = vertices[to].first;

    //Check for parallel edges
    for(Vertex* adjacentVertex : adjList[toID]){
        //If a parallel edge is found, do not insert the edge
        if(adjacentVertex == vertices[from].second){
            return;
        }
    }

    //Stores incoming nodes under the adjacency list index, which represents the uniqueID of the vertex
    adjList[toID].push_front(vertices[from].second);

    //increments from_page outDegree. Will be used to calculate PageRank
    vertices[from].second->outDegree++;

    E++; //Increments the number of edges in the graph
}

void Graph::PageRank(int n) {
    //Initialize r, which represents r(0)
    int power_iterations = n;
    std::vector<double> r(V, 1.0 / V);

    //std::cout << r.size() << std::endl;

    //Loop for the number of power iterations shown
    for (int iter = 0; iter < power_iterations - 1; ++iter) {
        std::vector<double> newR(V, 0.0);  // Initialize newR inside the loop

        // Matrix-vector multiplication: newR = M * r
        for (int i = 0; i < V; ++i) {
            for (Vertex* adjacentVertex : adjList[i]) {
                // Division by 0 check to avoid errors, skip this if outDegree is 0. Else do Matrix Multiplication.
                if (adjacentVertex->outDegree != 0) {
                    //At the correct uniqueID, multiply the M[][] * r[i], with i = uniqueID in the map to matrix multiply correctly
                    //std::cout << "Current Vertex: " << adjacentVertex->webpage << std::endl;
                    //std::cout << "Current Rank: " << adjacentVertex->rank << std::endl;
                    //std::cout << "Current OutDegree: " << adjacentVertex->outDegree << std::endl;

                    //std::cout << "-------------------------" << std::endl;
                    //std::cout << "Current index being multiplied in r is: " << vertices[adjacentVertex->webpage].first << std::endl;
                    //std::cout << "Current value at that index in r is: " << r[vertices[adjacentVertex->webpage].first] << std::endl;

                    //double result = (adjacentVertex->rank / adjacentVertex->outDegree) * r[vertices[adjacentVertex->webpage].first];

                    newR[i] += (adjacentVertex->rank / adjacentVertex->outDegree) * r[vertices[adjacentVertex->webpage].first];

                    //std::cout << "-------------------------" << std::endl;
                    //std::cout << "Result of matrix multiplication is: " << result << std::endl;
                    //std::cout << "The result value is being added to newR at index: " << i << std::endl;
                    //std::cout << "-------------NEXT VALUE-------------" << std::endl;
                }
                else{ //When the outdegree of a Vertex is 0

                }
            }
        }
        // Update the rank vector for the next iteration
        r = newR;
    }

    // Update the final ranks in your vertices
    for (auto& iter : vertices) {
        iter.second.second->rank = r[iter.second.first];
    }
}

void Graph::printUniqueIDs() {
    for(auto iter = vertices.begin(); iter != vertices.end(); ++iter){
        std::cout << iter->first << " Unique ID is equal to: " << iter->second.first << std::endl;
    }
}

void Graph::printRanks(){
    for(auto iter = vertices.begin(); iter != vertices.end(); ++iter){
        std::cout << iter->first << " " << std::fixed << std::setprecision(2) << iter->second.second->rank << std::endl;
    }
}

void Graph::printAdjList() {
    for(int i = 0; i < adjList.size(); i++){
        std::cout << "Vertex " << i << "'s Incoming Nodes are:";
        for(Vertex* adjacent : adjList[i]){
            std::cout << " " << adjacent->webpage;
        }
        std::cout << std::endl;
    }
}

void Graph::printOutDegrees(){
    for(auto iter = vertices.begin(); iter != vertices.end(); ++iter){
        std::cout <<"Outdegree of " << iter->first << " is: " << iter->second.second->outDegree << std::endl;
    }
}
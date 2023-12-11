#include <iostream>
#include <map>
#include "Graph.h"

int main() {
    Graph call;

    int no_of_lines, power_iterations;

    std::string from, to;
    int count = 0;
    bool isDupe = false;

    std::cin >> no_of_lines;
    std::cin >> power_iterations;

    //Populates the map, giving each URL a unique ID. Will be used to create edges to the from_page m[i] and to_page m[i+1]. from_page->to_page.
    for (int i = 0; i < no_of_lines; i++) {
        std::cin >> from;
        std::cin >> to;

        //First insertion into map (Check for self-loop edge case)
        if(call.vertices.empty() && from != to){
            call.insertVertex(from, count);
            count++;
            call.insertVertex(to,count);
            count++;
        }

        else{
            //Checks for duplicates when inserting from_page in order to avoid index/value duplication
            for(auto iter = call.vertices.begin(); iter != call.vertices.end(); ++iter){
                if(iter->first == from){
                    isDupe = true;
                    break;
                }
            }
            if(isDupe){
                isDupe = false;
            }
            else { //If not a new
                call.insertVertex(from, count);
                count++;
                isDupe = false;
            }

            //Checks for duplicates when inserting to_page in order to avoid index/value duplication; Needs to be separate from the from_page insertion
            for(auto iter = call.vertices.begin(); iter != call.vertices.end(); ++iter){
                if(iter->first == to){
                    isDupe = true;
                    break;
                }
            }
            if(isDupe){
                isDupe = false;
            }
            else {
                call.insertVertex(to, count);
                count++;
                isDupe = false;
            }
        }
        call.insertEdge(from, to);
    }
    //Test function calls
    //call.printUniqueIDs();
    //call.printAdjList();
    //call.printOutDegrees();

    //Create a graph object (Required calls)
    call.PageRank(power_iterations);
    call.printRanks();
}
/*

Print Input:
7 2
google.com gmail.com
google.com maps.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
gmail.com maps.com

Broken Case (Randomly Generated, NAN issue):
4 4
pcbuildinguf.com reactjs.org
python.org facebook.com
stackoverflow.com python.org
stackoverflow.com pcbuildinguf.com

Broken Case (Test Case 5, Arithmetic issue):
7 5
google.com gmail.com
google.com maps.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
maps.com quora.com

//Self-loop test case
 1 10
github.com github.com
*/
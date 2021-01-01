/*
Amrit Adhikari
CSCE3110 Data Structures
Fall20
Project 4
Instructor: Dr.Thompson

*/

#include <iostream>
#include "Graph.h"

void start()
{
    // graph instance
    Graph graph;

    cout << "Enter the name of the input file: ";
    // string to save the file name of the contents
    string name;
    cin >> name;
    graph.load_vertices(name);
    while (true)
    {
        cout << ("Enter option choice 1 - 5:            \n"
                 "(1) Print Adjacency List              \n"
                 "(2) Print Single-Source Shortest Path \n"
                 "(3) Print Indegree of Each Vertex     \n"
                 "(4) Print Topological Sort of Graph   \n"
                 "(5) Exit Program           \n> ");
        int userIN;
        char name;
        cin >> userIN;
        switch (userIN)
        {
        case 1:
            graph.print_adjacency_list();
            break;
        case 2:
            cout << "Enter Source Vertex (char) for Shortest Path: ";
            cin >> name;
            graph.print_single_source_shortest_path(name);
            break;
        case 3:
            graph.print_indegree_of_each_vertex();
            break;
        case 4:
            graph.print_topological_sortof_graph();
            break;
        case 5:
            puts("Terminating Program... ");
            exit(0);

        default:
            puts("Invalid input, try again");
        }
    }
}
int main(int argc, char *argv[])
{
    start();
}
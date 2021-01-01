#ifndef GRAPH_CLASS
#define GRAPH_CLASS
#include <string>
#include "Vertex.h"

class Graph
{
public:
    /*
	 * load vertices from the file name and save them on vertices_
	 */
    void load_vertices(std::string file_name);
    /*
	 * print the adj list
	 */
    void print_adjacency_list();
    /*
	 * print_single_source_shortest_path
	 */
    void print_single_source_shortest_path(char name);
    /*
	 * print_indegree_of_each_vertex
	 */
    void print_indegree_of_each_vertex();
    /*/
	 * print the top sort of the DAG
	 */
    void print_topological_sortof_graph();

private:
    /*
	 * helper function to mark all the nodes as unknown for the  Shortest Path algorithm
	 */
    void mark_as_unknown();
    /*
	 * loop over the vertices and clculate the indegree
	 */
    void calculate_indegree();
    map<char, Vertex> vertices_;
};
#endif

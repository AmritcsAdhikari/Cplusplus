#ifndef VERTEX_CLASS
#define VERTEX_CLASS
#include <map>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;
class Vertex
{
public:
    std::map<char, int> get_adj() const;

    // getters and setters for the class
    int get_dist() const;

    void set_dist(int dist);

    int get_indegree() const;

    void set_indegree(int indegree);
    void decrement_indegree();
    bool is_known() const;

    void set_known(bool known);

    char get_name() const;

    void set_name(char name);

    char get_path() const;

    void set_path(char path);
    //--------------------------
    // print the adj list of the vertex
    void print_adjacency_list();
    // print the indegree of the vertex
    void print_indegree();

    Vertex() = default;
    ~Vertex() = default;
    Vertex(char name, map<char, int> adj);
    /*
	 * return the edge value or minus inf  to tell that no edge 
	 * 
	 */
    int find_edge(char name);
    vector<char> path_rout;

private:
    char name;
    std::map<char, int> adj;
    bool known{};
    int dist{};
    char path{};
    int indegree{};
};

#endif
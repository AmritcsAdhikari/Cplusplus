#include "Graph.h"

#include <fstream>
#include <iostream>
#include <sstream>

void Graph::load_vertices(std::string file_name)
{
    fstream in(file_name);
    string line;
    try
    {
        if (!in.good())
            throw -1;
        while (getline(in, line))
        {
            char name = line[0];
            stringstream z(line);
            string holder;
            vector<string> vertices;
            z >> holder; // skip the node name
            while (z >> holder)
            {
                vertices.push_back(holder);
            }
            map<char, int> adj;
            for (int i = 0; vertices.size() && i < vertices.size() - 1; i += 2)
            {
                adj[vertices[i + 1][0]] = stoi(vertices[i]);
            }
            auto vertex = new Vertex(name, adj);
            vertices_[name] = *vertex;
        }
        // calculte the indegree of all vertices
        calculate_indegree();
    }
    catch (...)
    {
        cout << "Could not open files" << endl;
        exit(0);
    }
    cout << "File " << file_name << " successfully loaded into graph. \n";
}

void Graph::print_adjacency_list()
{
    puts("Adjacency List:");
    for (auto &vertex : vertices_)
    {
        vertex.second.print_adjacency_list();
        cout << "\n";
    }
}

void Graph::mark_as_unknown()
{
    for (auto &vertex : vertices_)
    {
        vertex.second.set_known(false);
        vertex.second.path_rout.clear();
    }
}

void Graph::print_single_source_shortest_path(char name)
{
    // set all vertices as unknown
    mark_as_unknown();
    if (vertices_.find(name) == vertices_.end())
    {
        cout << "Node is not present is the graph, returning...\n";
        return;
    }
    char src = name;
    // mark the src as known
    vertices_[name].set_known(true);
    vertices_[name].set_dist(0);
    vertices_[name].path_rout.push_back(name);
    // priority queue initialized with "greater" so that it saves the largest smallest size at the top
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
    q.push({0, name});
    while (q.size())
    {
        name = q.top().second;
        q.pop();
        auto adj = vertices_[name].get_adj();
        for (auto e : adj)
        {
            char v = e.first;
            int c = e.second;
            if (vertices_[v].is_known() == 0 || vertices_[v].get_dist() > vertices_[name].get_dist() + c)
            {
                vertices_[v].set_known(true);
                vertices_[v].set_dist(vertices_[name].get_dist() + c);
                vertices_[v].path_rout = vertices_[name].path_rout;
                vertices_[v].path_rout.push_back(v);
                q.push({vertices_[v].get_dist(), v});
            }
        }
    }

    // print the unkown vertices
    for (auto &&vertex : vertices_)
    {
        if (!vertex.second.is_known())
        {
            puts("Warning: Not All Vertices May Be Reached.");
        }
    }
    vertices_[src].path_rout.push_back(src);

    // print the distance of each node from the src node
    for (auto &&vertex : vertices_)
    {
        if (vertex.second.is_known())
        {

            for (int i = 0; i < vertex.second.path_rout.size() - 1; ++i)
            {
                cout << vertex.second.path_rout[i] << " -> ";
            }
            cout << vertex.second.path_rout.back() << " : " << vertex.second.get_dist() << endl;
        }
    }
}

void Graph::print_indegree_of_each_vertex()
{
    // print the indegree of each vertex
    for (auto &vertex : vertices_)
    {
        vertex.second.print_indegree();
    }
}

void Graph::print_topological_sortof_graph()
{
    vector<char> topSorted;
    queue<Vertex> q;

    // find the vertex with 0 in degree
    for (const auto &vertex : vertices_)
    {
        if (vertex.second.get_indegree() == 0)
            q.push(vertex.second);
    }
    while (!q.empty())
    {
        // get the top vertex
        Vertex topVertex = q.front();
        q.pop();

        topSorted.push_back(topVertex.get_name());
        auto adj = topVertex.get_adj();
        // decrement all the neighbors indegree value
        for (const auto neighbor : adj)
        {
            for (auto &&tmp_v : vertices_)
            {
                if (tmp_v.second.get_name() == neighbor.first)
                {
                    tmp_v.second.decrement_indegree();
                    if (tmp_v.second.get_indegree() == 0)
                        q.push(tmp_v.second);
                }
            }
        }
    }
    // calculate the indegree again, as they were missed up during calculating the topological order
    calculate_indegree();

    if (topSorted.size() != vertices_.size())
    {
        puts("Error sorting the graph, Topological sorting is for Directed Acyclic Graph (DAG) Only");
        return;
    }
    puts("Topological Sort of Graph:");
    for (char node : topSorted)
    {
        cout << node;
        if (node == topSorted.back())
        {
            cout << "\n";
        }
        else
            cout << " -> ";
    }
}

void Graph::calculate_indegree()
{
    for (auto &vertex : vertices_)
    {
        int indegree = 0;
        for (auto &vertex1 : vertices_)
        {
            // if there's an edge, increase the counter
            if (vertex1.second.find_edge(vertex.second.get_name()) != INT32_MIN)
                indegree += 1;
        }
        vertex.second.set_indegree(indegree);
    }
}
#include "Vertex.h"

#include <iostream>

std::map<char, int> Vertex::get_adj() const
{
    return adj;
}

int Vertex::get_dist() const
{
    return dist;
}
void Vertex::decrement_indegree()
{
    indegree--;
}
void Vertex::set_dist(int dist)
{
    this->dist = dist;
}

int Vertex::get_indegree() const
{
    return indegree;
}

void Vertex::set_indegree(int indegree)
{
    this->indegree = indegree;
}

bool Vertex::is_known() const
{
    return known;
}

void Vertex::set_known(bool known)
{
    this->known = known;
}

char Vertex::get_name() const
{
    return name;
}

void Vertex::set_name(char name)
{
    this->name = name;
}

char Vertex::get_path() const
{
    return path;
}

void Vertex::set_path(char path)
{
    this->path = path;
}

void print__(pair<char, int> p)
{
    printf("->(%c,%d)", p.first, p.second);
}

void Vertex::print_adjacency_list()
{
    cout << name << " : ";
    for_each(adj.begin(), adj.end(), print__);
}

void Vertex::print_indegree()
{
    printf("%c : %d\n", name, indegree);
}

Vertex::Vertex(char name, map<char, int> adj)
{
    this->name = name;
    this->adj = adj;
}

int Vertex::find_edge(char name)
{
    if (adj.find(name) == adj.end())
        return INT32_MIN;
    return adj[name];
}
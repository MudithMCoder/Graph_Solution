#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <string>

class Graph {
private:
    std::unordered_map<long long, std::vector<long long>> adjacencyList;

public:
    Graph() = default;

    void readFromCsv(const std::string& filepath);
    void addEdge(long long source, long long target);
    void printEdges() const;
};

#endif // GRAPH_H

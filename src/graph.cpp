#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

void Graph::addEdge(long long source, long long target) {
    adjacencyList[source].push_back(target);

    if (adjacencyList.find(target) == adjacencyList.end()) {
        adjacencyList[target] = std::vector<long long>();
    }
}

void Graph::readFromCsv(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            try {
                std::string sourceStr = line.substr(0, commaPos);
                std::string targetStr = line.substr(commaPos + 1);

                long long source = std::stoll(sourceStr);
                long long target = std::stoll(targetStr);

                addEdge(source, target);
            } catch (const std::exception& e) {
                // Ignore malformed lines
                std::cerr << "Warning: Skipping malformed line: " << line << std::endl;
            }
        }
    }
}

/*  
 * Print the edges of the graph in the specified format.
 * Only nodes with more than 1 target are printed.

void Graph::printEdges() const {
    std::cout << "{\n";

    // Collect nodes with more than 1 target
    std::vector<std::pair<long long, std::vector<long long>>> multiTarget;
    for (const auto& pair : adjacencyList) {
        if (pair.second.size() > 1) {
            multiTarget.push_back(pair);
        }
    }

    for (std::size_t i = 0; i < multiTarget.size(); i++) {
        long long source = multiTarget[i].first;
        const std::vector<long long>& targets = multiTarget[i].second;

        std::cout << "Node " << source << " -> [ ";
        for (long long target : targets) {
            std::cout << target << " ";
        }
        std::cout << "]";

        if (i == multiTarget.size() - 1) {
            std::cout << "}";
        }
        std::cout << "\n";
    }

    if (multiTarget.empty()) {
        std::cout << "}\n";
    }
}
    
*/

long long Graph::getMaxOutDegree() const {
    long long maxOutDegree = 0;
    for (const auto& pair : adjacencyList) {
        long long currentOut = static_cast<long long>(pair.second.size());
        if (currentOut > maxOutDegree) {
            maxOutDegree = currentOut;
        }
    }
    return maxOutDegree;
}

long long Graph::getMaxInDegree() const {
    long long maxInDegree = 0;
    std::unordered_map<long long, long long> inDegrees;
    
    // Initialize in-degrees for all nodes to 0 
    for (const auto& pair : adjacencyList) {
        inDegrees[pair.first] = 0;
    }
    
    for (const auto& pair : adjacencyList) {
        for (long long target : pair.second) {
            inDegrees[target]++;
            if (inDegrees[target] > maxInDegree) {
                maxInDegree = inDegrees[target];
            }
        }
    }
    return maxInDegree;
}

// Kahn's algorithm to determine if the graph is a DAG
std::string Graph::isDag() const {
    std::unordered_map<long long, long long> inDegrees;

    // Initialise in-degree to 0 for every node
    for (const auto& pair : adjacencyList) {
        inDegrees[pair.first] = 0;
    }

    // Sum in-degrees from all edges
    for (const auto& pair : adjacencyList) {
        for (long long target : pair.second) {
            inDegrees[target]++;
        }
    }

    // Enqueue all nodes that currently have no incoming edges
    std::queue<long long> zeroInDegree;
    for (const auto& pair : inDegrees) {
        if (pair.second == 0) {
            zeroInDegree.push(pair.first);
        }
    }

    long long visited = 0;
    while (!zeroInDegree.empty()) {
        long long node = zeroInDegree.front();
        zeroInDegree.pop();
        visited++;

        // Remove the node's outgoing edges and decrement neighbours' in-degrees
        if (adjacencyList.count(node)) {
            for (long long target : adjacencyList.at(node)) {
                inDegrees[target]--;
                if (inDegrees[target] == 0) {
                    zeroInDegree.push(target);
                }
            }
        }
    }

    // All nodes processed means the graph is a DAG; otherwise, it contains cycles
    return (visited == static_cast<long long>(inDegrees.size())) ? "true" : "false";
}

#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

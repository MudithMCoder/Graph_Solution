#include <iostream>
#include "graph.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file_name>" << std::endl;
        return 1;
    }
    std::string file_name = argv[1];
    Graph g;
    g.readFromCsv(file_name);

    // Uncomment the following line to print the edges of the graph
    // g.printEdges();
    
    std::cout << "Is DAG: " << g.isDag() << std::endl;
    std::cout << "Max Out-Degree: " << g.getMaxOutDegree() << std::endl;
    std::cout << "Max In-Degree: " << g.getMaxInDegree() << std::endl;

    return 0;
}

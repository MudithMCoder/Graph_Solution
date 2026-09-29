#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "graph.h"
#include "PageRank.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file_name>" << std::endl;
        return 1;
    }
    std::string file_name = argv[1];
    Graph g;
    g.readFromCsv(file_name);


    // Determine output file name
    size_t last_slash = file_name.find_last_of("/\\");
    std::string base_name = (last_slash == std::string::npos) ? file_name : file_name.substr(last_slash + 1);

    std::string out_file = "test_cases/graph_output.txt";
    size_t graph_pos = base_name.find("graph");
    size_t csv_pos = base_name.rfind(".csv");
    if (graph_pos != std::string::npos && csv_pos != std::string::npos && csv_pos >= (graph_pos + 5)) {
        std::string num = base_name.substr(graph_pos + 5, csv_pos - (graph_pos + 5));
        out_file = "test_cases/graph"+num+ "_output.txt";
    }

    std::ofstream outfile(out_file, std::ios::app);
    if (!outfile) {
        std::cerr << "Error: Could not open " << out_file << " for writing." << std::endl;
    }

    // Save outputs to intermediate variables to prevent recalculation
    std::string is_dag = g.isDag();
    long long max_out = g.getMaxOutDegree();
    long long max_in = g.getMaxInDegree();

    std::cout << "Is DAG: " << is_dag << std::endl;
    std::cout << "Max Out-Degree: " << max_out << std::endl;
    std::cout << "Max In-Degree: " << max_in << std::endl;

    if (outfile) {
        outfile << "Is DAG: " << is_dag << std::endl;
        outfile << "Max Out-Degree: " << max_out << std::endl;
        outfile << "Max In-Degree: " << max_in << std::endl;
    }

    PageRank pr(g);
    pr.pageRankScore();

    double max_pr = pr.Max_pageRank();
    double min_pr = pr.Min_pageRank();

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Max PageRank: " << max_pr << std::endl;
    std::cout << "Min PageRank: " << min_pr << std::endl;

    if (outfile) {
        outfile << std::fixed << std::setprecision(6);
        outfile << "Max PageRank: " << max_pr << std::endl;
        outfile << "Min PageRank: " << min_pr << std::endl;
    }

    return 0;
}

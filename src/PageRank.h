#ifndef PAGERANK_H
#define PAGERANK_H

#include "graph.h"
#include <unordered_map>
#include <vector>

class PageRank {
private:
    const Graph& graph;
    std::unordered_map<long long, double> scores;
    bool calculated = false;

public:
    explicit PageRank(const Graph& g);

    void pageRankScore();
    double Max_pageRank();
    double Min_pageRank();

    const std::unordered_map<long long, double>& getScores() const;
};

#endif // PAGERANK_H

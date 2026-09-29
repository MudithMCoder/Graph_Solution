#include "PageRank.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>

PageRank::PageRank(const Graph& g) : graph(g), calculated(false) {}

void PageRank::pageRankScore() {
    const auto& adjList = graph.getAdjacencyList();
    if (adjList.empty()) {
        scores.clear();
        calculated = true;
        return;
    }

    // 1. Collect all unique nodes and assign contiguous indices
    std::vector<long long> node_ids;
    std::unordered_map<long long, int> id_to_index;

    for (const auto& pair : adjList) {
        if (id_to_index.find(pair.first) == id_to_index.end()) {
            id_to_index[pair.first] = static_cast<int>(node_ids.size());
            node_ids.push_back(pair.first);
        }
        for (long long target : pair.second) {
            if (id_to_index.find(target) == id_to_index.end()) {
                id_to_index[target] = static_cast<int>(node_ids.size());
                node_ids.push_back(target);
            }
        }
    }

    size_t N = node_ids.size();
    if (N == 0) {
        scores.clear();
        calculated = true;
        return;
    }

    // 2. Build outgoing edge lists and out-degree arrays for row-stochastic transitions
    std::vector<std::vector<int>> outgoing(N);
    std::vector<int> out_degree(N, 0);

    for (const auto& pair : adjList) {
        int u = id_to_index[pair.first];
        for (long long target : pair.second) {
            int v = id_to_index[target];
            outgoing[u].push_back(v);
        }
        out_degree[u] = static_cast<int>(outgoing[u].size());
    }

    // 3. Initialize PageRank distribution vector (1/N for each node)
    std::vector<double> PR_old(N, 1.0 / static_cast<double>(N));
    std::vector<double> PR_new(N, 0.0);

    const double d = 0.85;
    const int max_iterations = 20;

    // 4. Power iteration using the row-stochastic transition matrix formula
    for (int iter = 0; iter < max_iterations; ++iter) {
        double dangling_sum = 0.0;
        for (size_t i = 0; i < N; ++i) {
            if (out_degree[i] == 0) {
                dangling_sum += PR_old[i];
            }
        }

        double base_val = (1.0 - d) / static_cast<double>(N) + d * (dangling_sum / static_cast<double>(N));
        std::fill(PR_new.begin(), PR_new.end(), base_val);

        for (size_t i = 0; i < N; ++i) {
            if (out_degree[i] > 0) {
                double share = d * (PR_old[i] / static_cast<double>(out_degree[i]));
                for (int v : outgoing[i]) {
                    PR_new[v] += share;
                }
            }
        }

        PR_old = PR_new;
    }

    // 5. Store the final scores
    scores.clear();
    for (size_t i = 0; i < N; ++i) {
        scores[node_ids[i]] = PR_old[i];
    }

    calculated = true;
}

double PageRank::Max_pageRank() {
    if (!calculated) {
        pageRankScore();
    }

    if (scores.empty()) {
        return 0.0;
    }

    double max_val = std::numeric_limits<double>::lowest();
    for (const auto& pair : scores) {
        if (pair.second > max_val) {
            max_val = pair.second;
        }
    }

    return std::round(max_val * 1e6) / 1e6;
}

double PageRank::Min_pageRank() {
    if (!calculated) {
        pageRankScore();
    }

    if (scores.empty()) {
        return 0.0;
    }

    double min_val = std::numeric_limits<double>::max();
    for (const auto& pair : scores) {
        if (pair.second < min_val) {
            min_val = pair.second;
        }
    }

    return std::round(min_val * 1e6) / 1e6;
}

const std::unordered_map<long long, double>& PageRank::getScores() const {
    return scores;
}

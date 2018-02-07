// Copyright (C) 2018- Bo Han (bowhan@me.com)

#include <string>
#include <vector>
#include <Rcpp.h>
#include <lemon/list_graph.h>
#include <lemon/connectivity.h>

using namespace Rcpp;

bool IsHammingDistanceShorterThan(const std::string& a, const std::string& b, int mm) {
    const char* pa = a.c_str();
    const char* pb = b.c_str();
    int diff = 0;
    while(*pa && *pb) {
        if(toupper(*pa) != toupper(*pb)) {
            if(++diff > mm) return false;
        }
        ++pa, ++pb;
    }
    if(*pa || *pb) return false;
    return true;
} 

// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]
int NumberConnectedComponents(std::vector<std::string> strs, int mmallowed) {
    lemon::ListGraph g;
    std::vector<lemon::ListGraph::Node> nodes;
    nodes.reserve(strs.size());
    // add all nodes
    for(int i = 0; i < strs.size(); ++i) {
        nodes.push_back(g.addNode());
    }
    // compare each pair of string and add edge if their hamming distance is shorter or equal to threshold
    for(int i = 0; i < strs.size()-1; i++) {
        for(int j = i + 1; j < strs.size(); j++) {
            if(IsHammingDistanceShorterThan(strs[i], strs[j], mmallowed)) {
                g.addEdge(nodes[i], nodes[j]);
            }
        }
    }
    return lemon::countConnectedComponents(g);
}
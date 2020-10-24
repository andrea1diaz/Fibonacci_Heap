#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <set>

#include "Lector.hpp"
#include "FibonacciHeap.hpp"
#include "Node.hpp"
#include "CImg.h"
#include "UnionFind.h"

struct Graph {
    private:
        std::vector<std::pair<std::vector<float>, CImg<float> > > nodes;
        std::vector<std::vector<float>> edges;
        FibonacciHeap<float> fh;
        UnionFind u;
        
    public:
        Graph() : u{0} {
            nodes = lector.Vectorizar();
			edges = std::vector<std::vector<float>>(nodes.size(), std::vector<float>(nodes.size()));;
            for(int i = 0; i < nodes.size(); ++i) {
                for(int j = 0; j < nodes.size(); ++j) {
                    if(i == j) {
                        edges[i][j] = 0;
                        continue;
                    }
                    else if(edges[i][j])
                        continue;
                    edges[i][j] = fh.distance(nodes[i].first, nodes[j].first);
                    edges[j][i] = edges[i][j];
                    Node<float>* cur = fh.insert(edges[i][j]);
                    cur->coordenadas = {nodes[i].first, nodes[j].first};
                    cur->imagenes = {nodes[i].second, nodes[j].second};
                    cur->uv = {i, j};
                }
            }
            u = UnionFind(nodes.size());
        }

        std::set<Node<float>*> Kruskal() {
            std::set<Node<float>*> F;
            while(!fh.empty()) {
                Node<float>* cur = fh.extract_min();
                int i{cur->uv.first}, j{cur->uv.second};
                if(u.findSet(i) != u.findSet(j)) {
                    F.insert(cur);
                    u.unionSet(u.findSet(i), u.findSet(j));
                }
            }
            return F;
        }

        
};

#endif

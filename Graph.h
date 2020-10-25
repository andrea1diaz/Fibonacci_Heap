#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <set>
#include <tuple>
#include <chrono>

#include "Lector.hpp"
#include "FibonacciHeap.hpp"
#include "Node.hpp"
#include "CImg.h"
#include "UnionFind.h"

struct Graph {
    private:
        std::vector<std::tuple<std::vector<float>, CImg<float>, std::string > > nodes;
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
                    edges[i][j] = fh.distance(std::get<0>(nodes[i]), std::get<0>(nodes[j]));
                    edges[j][i] = edges[i][j];
                    Node<float>* cur = fh.insert(edges[i][j]);
                    cur->coordenadas = {std::get<0>(nodes[i]), std::get<0>(nodes[j])};
                    cur->imagenes = {std::get<1>(nodes[i]), std::get<1>(nodes[j])};
                    cur->uv = {i, j};
                }
            }
            u = UnionFind(nodes.size());
        }

        std::set<Node<float>*> Kruskal() {
            auto t1 = std::chrono::high_resolution_clock::now();
            std::set<Node<float>*> F;
            while(!fh.empty()) {
                Node<float>* cur = fh.extract_min();
                int i{cur->uv.first}, j{cur->uv.second};
                if(u.findSet(i) != u.findSet(j)) {
                    F.insert(cur);
                    u.unionSet(u.findSet(i), u.findSet(j));
                }
            }
            auto t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds> (t2 - t1).count();
            std::cout << "Duration: " << duration << endl;
            return F;
        }

        void drawMST() {
            auto mst = Kruskal();
            std::ofstream file("grafo.vz");
            file << "digraph\n{" << std::endl;
            file << "graph [compound=true, labelloc=\"b\", layout=neato];" << std::endl;
            file << "node [shape=none];" << std::endl;
            file << "edge [dir=none];" << std::endl;

            for(int i = 0; i < nodes.size(); ++i) {
                file << i << " [label=\"\", image=\"" << std::get<2>(nodes[i]) << "\", height=0.1, width=0.1]" << std::endl;
            }

            for(auto e : mst) {
                file << e->uv.first << "->" << e->uv.second << "[len=" << e->key/100 << "]" << std::endl;
            }

            file << "}" << std::endl;
            file.close();
            system("dot -Tpdf grafo.vz -o grafo.pdf");
        }
};

#endif

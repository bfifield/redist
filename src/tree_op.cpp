#include "tree_op.h"

/*
 * Generate a random vertex (integer) among unvisited vertices
 */
// TESTED
int rvtx(const std::vector<bool> &visited, int size, int remaining) {
    int idx = floor(runif(1, 0, remaining))[0];
    int accuml = 0;
    for (int i = 0; i < size - 1; i++) {
        accuml += 1 - visited[i];
        if (accuml - 1 == idx) return i;
    }
    return size - 1;
}

/*
 * Generate a random neighbor to a vertex, except for the `last` vertex.
 */
// TESTED
int rnbor(const List &g, int vtx) {
    std::vector<int> node = as<std::vector<int>>(g[vtx]);
    return node[std::floor(runif(1, 0, node.size())[0])];
}

/*
 * Make a county graph from a precinct graph and list of counties
 */
// TESTED
Multigraph county_graph(const List &g, const IntegerVector &counties) {
    int n_county = max(counties);
    Multigraph cg = init_multigraph(n_county);

    int V = g.size();
    for (int i = 0; i < V; i++) {
        std::vector<int> nbors = as<std::vector<int>>(g[i]);
        int length = nbors.size();
        int county = counties[i] - 1;
        for (int j = 0; j < length; j++) {
            int nbor_cty = counties[nbors[j]] - 1;
            if (county == nbor_cty) continue;
            std::vector<int> el = {nbor_cty, i, nbors[j]};
            cg[county].push_back(el);
        }
    }

    return cg;
}

/*
 * Initialize empty multigraph structure on graph with `V` vertices
 */
// TESTED
Multigraph init_multigraph(int V) {
    Multigraph g;
    for (int i = 0; i < V; i++) {
        std::vector<std::vector<int>> el;
        g.push_back(el);
    }
    return g;
}

/*
 * Initialize empty tree structure on graph with `V` vertices
 */
// TESTED
Tree init_tree(int V) {
    Tree tree;
    for (int i = 0; i < V; i++) {
        tree.push_back(std::vector<int>());
    }
    return tree;
}


/*
 * Count population below each node in tree
 */
// TESTED
double tree_pop(Tree &ust, int vtx, const IntegerVector &pop,
                std::vector<int> &pop_below, std::vector<int> &parent) {
    double pop_at = pop[vtx];
    std::vector<int> *nbors = &ust[vtx];
    int length = nbors->size();
    for (int j = 0; j < length; j++) {
        int nbor = (*nbors)[j];
        pop_at += tree_pop(ust, nbor, pop, pop_below, parent);
        if (parent.size()) parent[nbor] = vtx;
    }

    pop_below[vtx] = pop_at;
    return pop_at;
}

/*
 * Assign `district` to all descendants of `root` in `ust`
 */
// TESTED
void assign_district(const Tree &ust, IntegerMatrix::Column districts,
                     int root, int district) {
    districts[root] = district;
    int n_desc = ust[root].size();
    for (int i = 0; i < n_desc; i++) {
        assign_district(ust, districts, ust[root][i], district);
    }
}

/*
 * Find the root of a subtree.
 */
// TESTED
int find_subroot(const Tree &ust, const std::vector<bool> &ignore) {
    int V = ust.size();
    std::vector<bool> visited(V, false);
    for (int j = 0; j < V; j++) {
        const std::vector<int>* nbors = &ust[j];
        for (int k = 0; k < nbors->size(); k++) {
            visited[(*nbors)[k]] = true;
        }
    }
    int root;
    for (root = 0; root < V; root++) {
        if (!visited[root] && !ignore[root]) break;
    }
    return root;
}

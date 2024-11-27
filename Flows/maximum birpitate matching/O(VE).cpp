#include bitsstdc++.h
using namespace std;
using ll = long long;
bool dfs(int boy, vectorvectorint& adj, vectorint& match, vectorbool& visited) {
    if (visited[boy]) return false;
    visited[boy] = true;

    for (int girl  adj[boy]) {
         If the girl is not matched or we can find an alternative match for her current partner
        if (match[girl] == -1  dfs(match[girl], adj, match, visited)) {
            match[girl] = boy;
            return true;
        }
    }
    return false;
}

int main() {
    iossync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin  n  m  k;

    vectorvectorint adj(n + 1);  Adjacency list for boys and girls
    for (int i = 0; i  k; ++i) {
        int a, b;
        cin  a  b;
        adj[a].push_back(b);
    }

    vectorint match(m + 1, -1);   Matches for girls (1-indexed)
    int max_pairs = 0;

     Maximum bipartite matching
    for (int boy = 1; boy = n; ++boy) {
        vectorbool visited(n + 1, false);
        if (dfs(boy, adj, match, visited)) {
            ++max_pairs;
        }
    }

    cout  max_pairs  'n';
    for (int girl = 1; girl = m; ++girl) {
        if (match[girl] != -1) {
            cout  match[girl]     girl  'n';
        }
    }

}
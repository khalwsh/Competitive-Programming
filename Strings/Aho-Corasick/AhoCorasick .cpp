struct AhoCorasick {
    // make sure the patterns are unique
    /*  // iterating over the outlinks
        int u = 0;
        for (int i = 0; i < n; i++) {
            char c = s[i];
            u = aho.advance(u, c);
            for (int node = u; node; node = aho.out_link[node]) {
                for (auto PatIdx : aho.out[node]) {
                    res[PatIdx]++;
                }
            }
        }
     */
    int N, P;
    const int A = 26;
    vector <vector <int>> next;
    vector <int> link, out_link;
    vector <vector <int>> out;
    AhoCorasick(): N(0), P(0) {node();}
    int node() {
        next.emplace_back(A, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(0);
        return N++;
    }
    inline int get (char c) {
        return c - 'a';
    }
    int add_pattern (const string &T) {
        int u = 0;
        for (auto c : T) {
            if (!next[u][get(c)]) next[u][get(c)] = node();
            u = next[u][get(c)];
        }
        out[u].push_back(P);
        return P++;
    }
    void compute() {
        queue <int> q;
        for (q.push(0); !q.empty();) {
            int u = q.front(); q.pop();
            for (int c = 0; c < A; ++c) {
                int v = next[u][c];
                if (!v) next[u][c] = next[link[u]][c];
                else {
                    link[v] = u ? next[link[u]][c] : 0;
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }
    int advance (int u, char c) {
        while (u && !next[u][get(c)]) u = link[u];
        u = next[u][get(c)];
        return u;
    }
    vector<int> FirstPos(string &text , vector<string>&patterns) {
        P = 0;
        int n = (int)patterns.size();
        map<string,int>last;
        vector<int>ans(n);
        for(int i = 0;i < patterns.size();i++) {
            if(last.count(patterns[i]))ans[i] = last[patterns[i]] , patterns[i] = "$";
            else last[patterns[i]] = i , ans[i] = i;
        }
        vector<int> len(n + 3, 0);
        for (auto &pat: patterns) {
            if(pat == "$")P++;
            else len[add_pattern(pat)] = (int)pat.size();
        }
        compute();
        vector<int>res(n , 1e9);
        n = (int)text.size();
        int u = 0;
        for (int i = 0; i < n; i++) {
            char c = text[i];
            u = advance(u, c);
            for (int node = u; node; node = out_link[node]) {
                for (auto PatIdx : out[node]) {
                    res[PatIdx] = min(res[PatIdx] , i - len[PatIdx] + 1);
                }
            }
        }
        for(int i = 0;i < res.size();i++)res[i] = (res[i] == 1e9 ? -2 : res[i]);

        for(int i = 0;i < res.size();i++) {
           res[i] = res[ans[i]];
        }
        return res;
    }
    vector<int> match(string &text , vector<string>&patterns) {
        P = 0;
        int n = (int)patterns.size();
        map<string,int>last;
        vector<int>ans(n);
        for(int i = 0;i < patterns.size();i++) {
            if(last.count(patterns[i]))ans[i] = last[patterns[i]] , patterns[i] = "$";
            else last[patterns[i]] = i , ans[i] = i;
        }
        vector<int> len(n + 3, 0);
        for (auto &pat: patterns) {
            if(pat == "$")P++;
            else len[add_pattern(pat)] = (int)pat.size();
        }
        compute();
        vector<int>res(n);
        n = (int)text.size();
        int u = 0;
        for (int i = 0; i < n; i++) {
            char c = text[i];
            u = advance(u, c);
            for (int node = u; node; node = out_link[node]) {
                for (auto PatIdx : out[node]) {
                    res[PatIdx]++;
                }
            }
        }
        for(int i = 0;i < res.size();i++) {
            res[i] = res[ans[i]];
        }
        return res;
    }
};
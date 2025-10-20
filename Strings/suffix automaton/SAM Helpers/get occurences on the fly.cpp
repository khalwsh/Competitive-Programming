// you already built SAM and Link tree with binary lifting
// then you need to count freqnecy of the string {s} as substring
// in the string SAM represents 
// you call this function then query on [in[state] , out[state]]
// where {state} is the state represent this string in the SAM
// if you don't have the queries persistent , undo the updates
void update_string(const string &s) {
    int node = 0;
    for (int i = 0; i < s.size(); i++) {
        node = st[node].nxt[s[i] - 'a'];
        // fen.add(in[node], 1);
    }
}
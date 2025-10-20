
// ------------------------- Suffix Automaton Template -------------------------
//
// A state in the Suffix Automaton (SAM):
// len        : Length of the longest substring in this equivalence class
// link       : Suffix link (points to the largest proper suffix state , another class)
// first_pos  : End position of the substring's first appearance in the text
// nxt[26]    : Transitions for each character (fixed for lowercase 'a'–'z')
// is_clone   : True if this state is a clone (created during split).
//              → Clone states are technical duplicates; skip them if you only
//                want distinct end positions.
//
// Optional auxiliary arrays (not included in this template but often useful):
// cnt[cur]       : Initialize as 1 for each state. After propagating through
//                  suffix links, it stores the number of occurrences of all
//                  substrings represented by this state.
// is_terminal[cur]: Marks this state as terminal (i.e., corresponds to a suffix).
//                  → A suffix in SAM is a path from the root to a terminal state.
// pos_state[pos] : Maps text position `pos` to the state representing the
//                  prefix ending at that position.
//                  → A prefix in SAM is a path from the root to pos_state[pos].
//
// ------------------------------------------------------------------------------
struct state {
    int len, link, first_pos;
    bool is_clone;
    int nxt[26];
};

const int MAXN = 4e5 + 9;
state st[2 * MAXN];
int sz, last;
ll cnt[2 * MAXN], is_terminal[2 * MAXN], pos_state[2 * MAXN];

struct Change {
    int node;
    int letter;
    int old;
};

struct Frame {
    int prev_last;
    int prev_sz;
    int cur;
    int clone_idx;
    int q_idx;
    int old_q_link;
    int pos;
    int old_pos_state;
    vector<Change> changes;
};

vector<Frame> history;

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    fill(st[0].nxt, st[0].nxt + 26, -1);
    int limit = 2 * MAXN;
    for (int i = 0; i < limit; ++i) {
        cnt[i] = 0;
        is_terminal[i] = 0;
        pos_state[i] = -1;
        st[i].is_clone = false;
        st[i].first_pos = -1;
    }
    sz = 1;
    last = 0;
    history.clear();
}

void sa_extend(char c, int pos) {
    Frame frame;
    frame.prev_last = last;
    frame.prev_sz = sz;
    frame.clone_idx = -1;
    frame.q_idx = -1;
    frame.old_q_link = -1;
    frame.pos = pos;
    frame.old_pos_state = pos_state[pos];

    int cur = sz++;
    frame.cur = cur;
    st[cur].len = st[last].len + 1;
    st[cur].first_pos = pos;
    st[cur].is_clone = false;
    fill(st[cur].nxt, st[cur].nxt + 26, -1);

    cnt[cur] = 1;
    is_terminal[cur] = 1;
    pos_state[pos] = cur;

    int p = last;
    int letter = c - 'a';
    while (p != -1 && st[p].nxt[letter] == -1) {
        frame.changes.push_back({p, letter, st[p].nxt[letter]});
        st[p].nxt[letter] = cur;
        p = st[p].link;
    }

    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].nxt[letter];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            frame.clone_idx = clone;
            st[clone].len = st[p].len + 1;
            copy(st[q].nxt, st[q].nxt + 26, st[clone].nxt);
            st[clone].link = st[q].link;
            st[clone].first_pos = st[q].first_pos;
            st[clone].is_clone = true;
            while (p != -1 && st[p].nxt[letter] == q) {
                frame.changes.push_back({p, letter, st[p].nxt[letter]}); // old is q
                st[p].nxt[letter] = clone;
                p = st[p].link;
            }
            frame.q_idx = q;
            frame.old_q_link = st[q].link;

            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;

    history.push_back(std::move(frame));
}

void sa_rollback() {
    if (history.empty()) return;

    Frame f = history.back();
    history.pop_back();
    for (auto it = f.changes.rbegin(); it != f.changes.rend(); ++it) {
        st[it->node].nxt[it->letter] = it->old;
    }
    if (f.q_idx != -1) {
        st[f.q_idx].link = f.old_q_link;
    }
    pos_state[f.pos] = f.old_pos_state;
    if (f.cur >= 0 && f.cur < 2 * MAXN) {
        cnt[f.cur] = 0;
        is_terminal[f.cur] = 0;
        st[f.cur].first_pos = -1;
        st[f.cur].is_clone = false;
    }
    sz = f.prev_sz;
    last = f.prev_last;
}
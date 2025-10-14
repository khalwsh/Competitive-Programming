// get smallest cyclic shift , build the sam on s + s , n = |s|
string cur;
int n;

void get() {
    int i = 0;
    while (cur.size() != n) {
        for (int j = 0; j < 26; j++) {
            if (st[i].nxt[j] != -1) {
                cur += 'a' + j;
                i = st[i].nxt[j];
                break;
            }
        }
    }
}
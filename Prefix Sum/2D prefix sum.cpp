const int siz = 1000;
int pre[siz + 1][siz + 1];
int arr[siz + 1][siz + 1];
void build() {
    memset(pre, 0, sizeof pre);
    for (int i = 1; i < siz + 1; i++) {
        for (int j = 1; j < siz + 1) {
            pre[i][j] = arr[i][j];
            pre[i][j] += pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
        }
    }
}
int query(int from_x ,int to_x ,int from_y ,int to_y;){
    int ans = pre[to_x][to_y] - pre[from_x - 1][to_y] - pre[to_x][from_y - 1] + pre[from_x - 1][from_y - 1];
}
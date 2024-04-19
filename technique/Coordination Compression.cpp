int comp[N],CompSize = 0;
int v[N],n;
void compress(){
    //note that comp should have all the values you want to compress and CompSize express the actual size used from the array
    sort(comp, comp + CompSize);
    CompSize = (int)(unique(comp, comp + CompSize) - comp);
    for (int i = 0; i < n; i++) {
        v[i] = (int)(lower_bound(comp, comp + CompSize, v[i]) - comp);
    }
    //replaced the values in v with it's compression and if you want the original value say comp[v[i]];
}
----- Directed Euler cycle -----
class DirectedEulerCycle{
public:
    vector<vector<int>>adj;
    vector<int>in,out;
    vector<int>tour;
    int n;
    int s=-1;
    DirectedEulerCycle(int n,vector<pair<int,int>>&edges){
        this->n=n;
        adj.resize(n);
        in.resize(n),out.resize(n);
        for(auto &val:edges){
            adj[val.first].emplace_back(val.second);
            out[val.first]++,in[val.second]++;
        }
    }
    void dfs(int node){
        while(!adj[node].empty()){
            int x=adj[node].back();
            adj[node].pop_back();
            dfs(x);
        }
        tour.emplace_back(node);
    }
    bool Get(){
        int counter1=0;
        for(int i=0;i<n;i++){
            if(in[i]==out[i])counter1++;
            else {
                return false;
            }
        }
        for(int i=0;i<n;++i){
            if(in[i]||out[i]){
                s=i;break;
            }
        }
        dfs(s);
        bool all=false;
        for(int i=0;i<n;i++){
            all=all||(int)adj[i].size();
        }
        if(!all){
            reverse(tour.begin(),tour.end());
            return true;
        }else
            return false;
    }
};

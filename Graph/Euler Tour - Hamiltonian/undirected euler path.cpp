----- code for Euler path for undirected graph -----
class UnDirectedEulerPath{
public:
    int n;
    vector<vector<int>>adj;
    vector<int>deg;
    vector<int>tour;
    map<pair<int,int>,int>edges;
    int StartingNode=-1,EndingNode=-1;
    UnDirectedEulerPath(int n,vector<pair<int,int>>&edges){
        this->n=n;
        adj.resize(n);
        deg.resize(n);
        for(auto &val:edges){
            this->edges[val]++;
            pair<int,int>p=val;
            swap(p.first,p.second);
            this->edges[p]++;
        }
        for(auto &val:edges){
            adj[val.first].emplace_back(val.second);
            adj[val.second].emplace_back(val.first);
            deg[val.first]++,deg[val.second]++;
        }
    }
    void component(int node,vector<bool>&vis){
        vis[node]=true;
        for(auto &val:adj[node]){
            if(!vis[val])
                component(val,vis);
        }
    }
    bool check(){
        vector<bool>vis(n,false);
        for(int i=0;i<n;i++){
            if(deg[i]){
                component(i,vis);
                break;
            }
        }
        for(int i=0;i<n;i++){
            if(!vis[i]&&deg[i]){
                return false;
            }
        }
        for(int i=0;i<n;i++){
            if(deg[i]&1^1)continue;
            else if(StartingNode==-1)StartingNode=i;
            else if(EndingNode==-1)EndingNode=i;
            else return false;
        }
        if(StartingNode==-1){
            for(int i=0;i<n;i++){
                if(deg[i]){
                    StartingNode=i;
                    break;
                }
            }
        }
        return true;
    }
    void DFS(int node){
        for(auto &val:adj[node]){
            if(this->edges[make_pair(node,val)])
              this->edges[make_pair(node,val)]--,this->edges[make_pair(val,node)]--,DFS(val);
        }
        tour.emplace_back(node);
    }
    void Get(){
        map<pair<int,int>,int>TempEdges=edges;
        DFS(StartingNode);
        edges=TempEdges;
        reverse(tour.begin(),tour.end());
    }
};

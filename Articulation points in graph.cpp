int counter=0;
  void dfs(int node,int parent,vector<bool>&vis,vector<int>adj[],vector<int>&time,vector<int>&low,vector<int>&res)
  {
      vis[node]=true;
      time[node]=low[node]=counter++;
      int child=0;
      for(auto &val:adj[node])
      {
          if(parent==val)continue;
          if(!vis[val]){
          dfs(val,node,vis,adj,time,low,res);
          low[node]=min(low[node],low[val]);
          if(low[val]>=time[node]&&parent!=-1)
             res[node]=1;
          child++;
          }
          else
          {
              low[node]=min(low[node],time[val]);
          }
      }
      if(parent==-1&&child>1)
      res[0]=true;
  }
    vector<int> articulationPoints(int n, vector<int>adj[]) {
        // Code here
        vector<bool>vis(n,false);
        vector<int>res(n),time(n),low(n);
        dfs(0,-1,vis,adj,time,low,res);
      
        vector<int>final_res;
        for(int i=0;i<n;i++)
        {
            if(res[i])final_res.emplace_back(i);
        }
        if(final_res.empty())return {-1};
        return final_res;
    }

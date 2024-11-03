    int start , finish;
    cin>>start>>finish;
 
    vector<int> dis(n+2,1e18);
    priority_queue<pair<int,int> , vector<pair<int,int>> , greater<>>q;
    vector<int> vis(n+2,false);
    dis[start] = 0;
    q.push({0,start});
    while (!q.empty()){
        auto v = q.top();
        q.pop();
        if (vis[v.second]==true){
            continue;
        }
        vis[v.second] = true;
        for(auto u : adj[v.second]){
            if (dis[u.first]>dis[v.second]+u.second){
                dis[u.first] = dis[v.second] + u.second;
                q.push({dis[u.first],u.first});
            }
        }
    }
    if(vis[finish]==false){
        cout<<-1<<endl;
    }
    else{
        cout<<dis[finish]<<endl;
    }

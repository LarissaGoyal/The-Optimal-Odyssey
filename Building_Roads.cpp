#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<unordered_map>
#include<cmath>
#include<algorithm>
#include<numeric>
#include<tuple>
#include<queue>
#include<set>
#define loop(i,n) for(long long i=0;i<n;i++)
#define endl "\n"
#define int long long
using namespace std;

void dfs(int s, vector<bool>&visited, vector<vector<int> >&adj){
    if(visited[s])return;
    visited[s]=true;
    for(auto x:adj[s]){
        dfs(x,visited,adj);
    }
}

int32_t main(){
int T=1; //cin >> T;
while(T--){
int n,m; cin >> n>>m;
vector<bool>visited(n+1,0);
vector<vector<int> >adj(n+1);
for(int i=0; i<m; i++){
    int a,b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
}
vector<int>road;
for(int i=1; i<=n; i++){
    if(!visited[i]){
        road.push_back(i);
        dfs(i,visited,adj);
    }
}


cout << road.size()-1 << endl;
for(int i=0; i<road.size()-1; i++){
    cout << road[i] << " " << road[i+1] << endl;
}


//END OF while(T--)
}
}
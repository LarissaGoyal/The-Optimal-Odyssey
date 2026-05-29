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
    for (auto u: adj[s]) {
        dfs(u,visited,adj);
    }
    return;
}

int32_t main(){
int T=1; //cin >> T;
while(T--){
int n,m; cin >> n >> m;
vector<string>a(n);
for(int i=0; i<n; i++){
    cin >> a[i];
}
vector<vector<int> >adj(n*m);

for(int i=0; i<n; i++){
    for(int j=0; j<m-1; j++){
        if(a[i][j]=='.' && a[i][j+1]=='.'){
            adj[m*i+j].push_back(m*i+j+1);
            adj[m*i+j+1].push_back(m*i+j);
        }
    }
}
for(int i=0; i<n-1; i++){
    for(int j=0; j<m; j++){
        if(a[i][j]=='.' && a[i+1][j]=='.'){
            adj[m*i+j].push_back(m*(i+1)+j);
            adj[m*(i+1)+j].push_back(m*i+j);
        }
    }
}

int N=n*m;
vector<bool>visited(N,false);
int ans=0;

for(int i=0; i<N; i++){
    if(a[i/m][i%m]=='.'){
        if(!visited[i]){
            ans++; 
            dfs(i,visited,adj);
        }
    }
}

cout << ans << endl;
//END OF while(T--)
}
}

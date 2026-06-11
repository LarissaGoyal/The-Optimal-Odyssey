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
int32_t main(){
int T=1; //cin >> T;
while(T--){
int n,m; cin >> n >> m;
vector<vector<pair<int,int> > >adj(n+1);
for(int i=0; i<m; i++){
    int a,b,c; cin >> a >> b >> c;
    adj[a].push_back({b,c});
    adj[b].push_back({a,c});
}
vector<int>d(n+1,1e16);
vector<bool>visited(n+1,0);
vector<int>parent(n+1,0);
d[1]=0;
priority_queue<pair<int,int> >q;
q.push({0,1});
bool yes=false;
while(!q.empty()){
    int s = q.top().second;
    q.pop();
    if(s==n){
        yes=true;
        break;
    }
    if(visited[s])continue;
    visited[s]=1;
    for(auto u: adj[s]){
        int v=u.first;
        int w=u.second;
        if(d[s]+w<d[v]){
            parent[v]=s;
            d[v]=d[s]+w;
            q.push({-d[v],v});
        }
    }
}

if(yes){
    vector<int>ans(1,n);
    int curr=n;
    while(curr!=1){
        curr=parent[curr];
        ans.push_back(curr);
    }
    for(int i=ans.size()-1; i>=0; i--){
        cout << ans[i] << " ";
    }
}
else cout << -1;
cout << endl;
//END OF while(T--)
}
}
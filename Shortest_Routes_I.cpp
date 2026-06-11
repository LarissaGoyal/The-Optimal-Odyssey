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
}
vector<int>d(n+1,1e16);
vector<bool>visited(n+1,0);
d[1]=0;
priority_queue<pair<int,int> >q;
q.push({0,1});
while(!q.empty()){
    int s = q.top().second;
    q.pop();
    if(visited[s])continue;
    visited[s]=1;
    for(auto u: adj[s]){
        int v=u.first;
        int w=u.second;
        if(d[s]+w<d[v]){
            d[v]=d[s]+w;
            q.push({-d[v],v});
        }
    }
}

for(int i=1; i<=n; i++)cout << d[i] << " ";
cout << endl;
//END OF while(T--)
}
}
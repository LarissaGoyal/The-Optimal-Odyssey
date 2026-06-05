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
int n,m; cin >> n>>m;
vector<bool>visited(n+1,0);
vector<vector<int> >adj(n+1);
for(int i=0; i<m; i++){
    int a,b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
}
vector<int>p(n+1,0);
queue<int> q;
q.push(1);
visited[1]=1;
int d=1;
bool found=false;
while(!q.empty()){
    int l=q.size();
    while(l--){
    int s=q.front();
    q.pop();
    if(s==n){
        found=true;
        break;
    }
    for(auto x:adj[s]){
        if(!visited[x]){
            q.push(x);
            visited[x]=1;
            p[x]=s;
        }
    }
    
    }
    if(found)break;
    d++;
}
if(found){
cout << d << endl;
vector<int>ans(d,n);
for(int i=d-2; i>=0; i--){
    ans[i]=p[ans[i+1]];
}
for(auto x:ans) cout << x << " ";
}
else cout << "IMPOSSIBLE";
cout << endl;
//END OF while(T--)
}
}
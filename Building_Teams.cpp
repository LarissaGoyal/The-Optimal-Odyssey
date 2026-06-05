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
vector<vector<int> >adj(n+1);
for(int i=0; i<m; i++){
    int a,b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
}
vector<bool>visited(n+1,0);
vector<int>part(n+1,0);
bool possible=true;
for(int i=1; i<=n; i++){
if(!visited[i]){
queue<int> q;
q.push(i);
visited[i]=1;
part[i]=1;
int current=2;

while(!q.empty()){
    int l=q.size();
    while(l--){
        int s=q.front();
        q.pop();
        for(auto x:adj[s]){
            if(visited[x]){
                if(part[x]!=current){
                    possible=false;
                    break;
                }
            }
            else{
                visited[x]=true;
                q.push(x);
                part[x]=current;
            }
        }
    }
    if(!possible)break;
    current=3-current;
}
}
if(!possible)break;
}

if(possible){
    for(int i=1; i<=n; i++)cout << part[i] <<" ";
}
else cout << "IMPOSSIBLE";
cout << endl;

//END OF while(T--)
}
}
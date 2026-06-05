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

/*
void dfs(int s, vector<bool>&visited, vector<vector<int> >&adj){
    if(visited[s])return;
    visited[s]=true;
    for (auto u: adj[s]) {
        dfs(u,visited,adj);
    }
    return;
}
*/

int32_t main(){
int T=1; //cin >> T;
while(T--){
int n,m; cin >> n >> m;
vector<string>a(n);
for(int i=0; i<n; i++){
    cin >> a[i];
}

int start=0,end=0;
loop(i,n){
    loop(j,m){
        if(a[i][j]=='A'){ 
            start=m*i+j;
            a[i][j]='.';
        }
        if(a[i][j]=='B') {
            end=m*i+j;
            a[i][j]='.';
        }
    }
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
int d=0;
vector<int>parent(N,0);
queue<int>q;
q.push(start);
visited[start]=true;
bool found=false;
while((!q.empty()) && (!found)){
    int l=q.size();
    d++;
    while(l--){
        int front=q.front();
        for(auto x:adj[front]){
            if(!visited[x]){
                q.push(x);
                visited[x]=true;
                parent[x]=front;
            }
            if(x==end){
                found=true;
                break;
            }
        }
        q.pop();
    }
}

if(found){
cout <<"YES" << endl << d << endl;
vector<int>ans(d+1,end);
for(int i=d-1; i>=0; i--){
    ans[i]=parent[ans[i+1]];
}
for(int i=0; i<d; i++){
    if(ans[i+1]==ans[i]+1)cout << "R";
    if(ans[i+1]==ans[i]-1)cout << "L";
    if(ans[i+1]==ans[i]+m)cout << "D";
    if(ans[i+1]==ans[i]-m)cout << "U";
}
}
else cout << "NO";
cout << endl;
//END OF while(T--)
}
}
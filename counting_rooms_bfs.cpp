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
        queue<int>q;
        q.push(i);
        visited[i]=true;
        while(!q.empty()){
            int l=q.size();
            while(l--){
                int front=q.front();
                for(auto x:adj[front]){
                    if(!visited[x]){
                        q.push(x);
                        visited[x]=true;
                    }
                }
                q.pop();
            }
        }
    }
    }
}
 
 
cout << ans << endl;
//END OF while(T--)
}
}

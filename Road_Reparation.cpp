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
int find(int v,vector<int>&parent){
    while(parent[v]!=0)v=parent[v];
    return v;
}
void unite(int a, int b, vector<int>&size,vector<int>&parent){
    a=find(a,parent);
    b=find(b,parent);
    if(size[a]<=size[b]){
        parent[a]=b;
        if(size[a]==size[b])size[b]++;
    }
    else{
        parent[b]=a;
        if(size[a]==size[b])size[a]++;
    }
}
bool same(int a, int b, vector<int>&parent){
    return find(a,parent)==find(b,parent);
}
int32_t main(){
int T=1; //cin >> T;
while(T--){
int n,m; cin >> n >> m;
vector<vector<int> >edge(m,vector<int>(3,0));
for(int i=0; i<m; i++){
    int a,b,c;
    cin >> a >> b >> c;
    edge[i][0]=c;
    edge[i][1]=a;
    edge[i][2]=b;
}
sort(edge.begin(),edge.end());
vector<int>parent(n+1,0),size(n+1,1);
int ans=0;
int components=n;
for(int i=0;i<m; i++){
    int u=edge[i][1];
    int v=edge[i][2];
    if(!same(u,v,parent)){
        unite(u,v,size,parent);
        ans+=edge[i][0];
        components--;
    }
}
if(components==1)
cout << ans << endl;
else cout << "IMPOSSIBLE" << endl;
//END OF while(T--)
}
}
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
int find(int x, vector<int>&parent){
    while(parent[x]!=0)x=parent[x];
    return x;
}
void unite(int a, int b,vector<int>&size,vector<int>&parent,int&max_size){
    a=find(a,parent);
    b=find(b,parent);
    if(size[a]<=size[b]){
        parent[a]=b;
        size[b]+=size[a];
        max_size=max(max_size,size[b]);
    }
    else{
        parent[b]=a;
        size[a]+=size[b];
        max_size=max(max_size,size[a]);
    }
}

bool same(int a, int b, vector<int>&parent){
    return find(a,parent)==find(b,parent);
}
int32_t main(){
int T=1; //cin >> T;
while(T--){
int n,m; cin >> n >> m;
vector<vector<int> >e(m,vector<int>(2,0));
for(int i=0; i<m; i++){
    int a,b; cin >> a >> b;
    e[i][0]=a;
    e[i][1]=b;
}
int ans=n;
int max_size=1;
vector<int>parent(n+1,0),size(n+1,1);
for(int i=0; i<m; i++){
    int u=e[i][0];
    int v=e[i][1];
    if(!same(u,v,parent)){
        unite(u,v,size,parent,max_size);
        ans--;
    }
    cout << ans <<" "<< max_size << endl;
}
//END OF while(T--)
}
}
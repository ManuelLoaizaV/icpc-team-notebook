#include<bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0); cin.tie(nullptr)
#define rall(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int>
#define pb push_back
#define ss second
#define ff first
#define endl '\n'
using namespace std;

const int N=2e4;
int gid=1, rch=0, id[N], lo[N];
bool is_art[N+1];
vector<int> adj[N];
vector<pair<int, int>> bridges;
void clear(int n){
  bridges.clear();
  for(int i=0; i<=n; ++i){
    adj[i].clear();
    id[i]=lo[i]=0;
    is_art[i]=0;
  }
}
//resetear rch (gid opcional) para cada llamada
void dfs(int u, int p=-1){
  id[u]=lo[u]=gid++;
  for(int v: adj[u]){
    if(!id[v]){
      if(p==-1) rch++;
      dfs(v, u);
      if(lo[v] >= id[u]) is_art[u]=1;
      if(lo[v] > id[u]) bridges.pb({u, v});
      lo[u] = min(lo[u], lo[v]);
    } else if(v != p) lo[u]=min(lo[u], id[v]);
  }
  if(p == -1) is_art[u]=(rch>1);
}

void solve(){
  int n; cin>>n;
  clear(n);
  for(int i=0; i<n; ++i){
    int u, k; char a, c;
    cin>>u>>a>>k>>c;
    for(int j=0; j<k; ++j){
      int v; cin>>v;
      adj[u].pb(v);
      adj[v].pb(u);
    }
  }
  for(int i=0; i<n; ++i){ 
    if(!id[i]){
      rch=0;
      gid=1;
      dfs(i);
    }
  }
  cout<<bridges.size()<<" critical links"<<endl;
  for(pii &p: bridges){
    int u=p.ff, v=p.ss;
    if(u>v) p={v, u};
  }
  sort(all(bridges));
  for(pii p: bridges){
    int u=p.ff, v=p.ss;
    cout<<u<<" - "<<v<<endl;
  }
}


int main(){
  FAST_IO;
  int t; cin>>t;
  int ind=t;
  while(t--){
    cout<<"Case "<<ind-t<<":"<<endl;
    solve();
  }
}

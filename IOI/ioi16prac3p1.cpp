#include <bits/stdc++.h>
using namespace std;

#define RE(i,n) for(int i = 1;i <= n;i++)
#define REP(i,n) for(int i= 0;i < n;i++)
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define int long long
#define pii pair<int,int> 

const int lg = 18;
const int N = 1e5+1;
vector<int> adj[N];
vector< pair<int,int> > vals[N];
int pre[N][lg];
set<int > g[N];
bool marked[N];
int dep[N];
int n,m;
int ans = 0;

int lca(int u,int v){
    if(dep[v] > dep[u])swap(u,v);
    for(int i = lg-1;i > -1;i--){
        if(dep[pre[u][i]] >= dep[v])u = pre[u][i];
    }
    for(int i = lg-1;i > -1;i--){
        if(pre[u][i] != pre[v][i]){
            u = pre[u][i];
            v = pre[v][i];
        }
    }
    return (u==v)?u:pre[u][0];
}

void dfs0(int u,int p){
    pre[u][0] = p;
    RE(i,lg-1)pre[u][i] = pre[pre[u][i-1]][i-1];
    for(int v:adj[u]){
        if(v == p)continue;
        dep[v] = dep[u]+1;
        dfs0(v,u);
    }
}

void marksub(int u,int p){
    marked[u] = 1;
    for(int v:adj[u]){
        if(v == p)continue;
        if(!marked[v])marksub(v,u);
    }
}


void dfs1(int u,int p){
    for(int v:adj[u]){
        if(v != p)dfs1(v,u);
    }
    for(auto it:vals[u]){
        if(!marked[it.f] and !marked[it.s]){
            ans++;
            marksub(u,p);
            break;
        }
    }
}

signed main() {
    cin >> n >> m;
    RE(i,n-1){
        int a,b;cin >> a >> b;
        adj[a].pb(b);adj[b].pb(a);
        g[a].insert(b);
        g[b].insert(a);
    }
    dep[1] = 1;
    dfs0(1,0);
    RE(i,m){
        int a,b;cin >> a >> b;
        vals[lca(a,b)].pb({a,b});
    }
    dfs1(1,0);
    cout << ans;
    return 0;
}
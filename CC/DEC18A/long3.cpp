/*input
2
4 4
1 2
1 3
2 4
3 4
3 3
1 2
2 3
1 3
*/
#include<bits/stdc++.h>
using namespace std;

#define int long long 
#define double long double
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define REP(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define remax(a,b) a = max(a,b)
#define remin(a,b) a = min(a,b)
#define all(v) v.begin(),v.end()
#define pii pair<int,int>
#define mii map<int,int>
#define vi vector<int>
#define vvi vector<vi>
#define WL(t) while(t --)
#define gcd(a,b) __gcd((a),(b))
#define lcm(a,b) ((a)*(b))/gcd((a),(b))
#define print(arr) for (auto it = arr.begin(); it != arr.end(); ++it) cout << *it << " "; cout << endl;
#define debug(x) cout << x << endl;
#define debug2(x,y) cout << x << " " << y << endl;
#define debug3(x,y,z) cout << x << " " << y << " " << z << endl;
const int INF = 1e18+1;
const int MOD = 1e9+7;
const double PI = 3.14159265358979323846264338;

int fast_ex(int a,int n,int m){
  if(n == 0)return 1;
  if(n == 1)return a;
  int x = 1;
    x *= fast_ex(a,n/2,m);
    x %= m;
    x *= x;
    x %= m;
    if(n%2)x*= a;
    x %= m;
    return x;
}

const int N = 1e5+1;

int t,n,m;
vector<int> adj[N];
int in[N];
vector<pii> edges;
int ans[N];
bool vis[N];
int pref[N];
vi qs;
set< pair<int,int> > one;

void dfs(int u,int p){
     vis[u] = 1;
     for(int v:adj[u]){
     	if(vis[v]){
     		continue;
     	}
     	dfs(v,u);
     	pref[u]+=pref[v];
     }
     if(pref[u]%2){
     	one.insert(mp(min(u,p),max(u,p)));
     }
}

void ini(){
	one.clear();
	qs.clear();
	edges.clear();
	REP(i,N){
		pref[i] = 0;
		in[i] = 0;
		vis[i] = 0;
		adj[i].clear();
		ans[i] = 0;
	}
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  cin >> t;
  while(t--){
  	ini();
  	string here = "here";
  	cin >> n >> m;
  	REP(i,m){
  		int a,b;cin >> a >> b;
  		in[b]++;
        adj[a].pb(b);
        adj[b].pb(a);
        edges.pb(mp(min(a,b),max(a,b)));
  	}
  	REP(i,n){
  		if(in[i+1]%2)qs.pb(i+1);
  	}
  	if(qs.size()%2){
  		cout << -1 << endl;
  		continue;
  	}
  	for(int i = 0;i < qs.size();i+=2){
  		pref[qs[i+1]]++;
  		pref[qs[i]]++;
  	}
    dfs(1,1);
    REP(i,m){
       if(one.find(edges[i]) != one.end())cout << "1 ";
       else cout << "0 ";
    }
    cout << endl;
  }
  return 0;
}
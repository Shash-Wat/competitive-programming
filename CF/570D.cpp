/*input
5 6
1 1 2 3
cbcab
3 1
5 2
1 3
4 1
4 2
1 1
*/
#include<bits/stdc++.h>
using namespace std;


//#define int long long 
#define double long double
#define f first
#define s second
#define mp make_pair
#define pb push_back

#define RE(i,n) for (int i = 1; i <= n; i++)
#define RED(i,n) for (int i = n; i > 0; i--)
#define REPS(i,n) for(int i = 1; (i*i) <= n; i++)
#define REP(i,n) for (int i = 0; i < (int)n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)

#define all(v) v.begin(),v.end()
#define pii pair<int,int>
#define vi vector<int>
#define vvi vector<vi>
#define print(arr) for (auto it = arr.begin(); it != arr.end(); ++it) cout << *it << " "; cout << endl;
#define debug(x) cout << x << endl;
#define debug2(x,y) cout << x << " " << y << endl;
#define debug3(x,y,z) cout << x << " " << y << " " << z << endl;


const int MOD = 1e9+7;
const double PI = 3.14159265358979323846264338;

const int N = 5e5+1;
bool freq[N][26];
int heavy[N];
int dep[N];
int sub[N];
vector<int> adj[N];
int q;
vector<pii> qs[N];
bool ans[N];
bool skip[N];
int n;
string r;

void dfs0(int u){
     sub[u] = 1;
     if(u == 1)dep[1] = 1;
     int mxind = -1;
	 for(int v:adj[u]){
	 	dep[v] = dep[u]+1;
	 	dfs0(v);
	 	sub[u] += sub[v];
	 	if(mxind == -1)mxind = v;
	 	else {
	 		if(sub[mxind] < sub[v])mxind = v;
	 	}
	 }
	 heavy[u] = mxind;
}

void add(int u){
     freq[dep[u]][r[u-1]-'a'] ^= 1;
     for(int v:adj[u]){
     	if(skip[v])continue;
       
     	add(v);
     }
}

void dfs(int u,bool keep){
	 for(int v:adj[u]){
	 	if(v == heavy[u])continue;
	 	dfs(v,0);
	 }
	 if(heavy[u] != -1){
	 	skip[heavy[u]] = 1;
	 	dfs(heavy[u],1);
	 	
	 }
	 
	 add(u);

	 REP(i,qs[u].size()){
	 	int H = qs[u][i].f;
	 	int odd = 0;
	 	REP(i,26){
           if(freq[H][i])odd++;
	 	}
	 	if(odd > 1)ans[qs[u][i].s] = 0;
	 	else ans[qs[u][i].s] = 1;
	 }
	 if(heavy[u] != -1)skip[heavy[u]] = 0; 
	 if(keep == 0){
	 	add(u);
	 }
}

void solve(){
     cin >> n >> q;
     RE(i,n-1){
     	int a;cin >> a;
     //	cout << a << endl;
     	adj[a].pb(i+1);
     }
    // string r;
     cin >> r;
     //cout << r << endl;
     RE(i,q){
     	int x,y;cin >> x >> y;
     	//cout << x << " " << y << endl;
     	qs[x].pb({y,i});
     }
     dfs0(1);
     dfs(1,0);
     RE(i,q){
     	if(ans[i])cout << "Yes";
     	else cout << "No";
     	cout << endl;
     }

}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen("inp.txt","r",stdin);
  //freopen(".out","w",stdout);
  int t = 1;
  //cin >> t;
  while(t--){
    solve();
  }
  return 0;
}
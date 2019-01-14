/*input
1
4
1 2 
1 3 
1 4
*/
#include<bits/stdc++.h>
using namespace std;

#define int long long 
#define double long double
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define RE(i,n) for (int i = 1; i <= n; i++)
#define RED(i,n) for (int i = n; i > 0; i--)
#define REPS(i,n) for(int i = 1; (i*i) <= n; i++)
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

const int N = 10001;
vector<int> adj[N];
int parity[N];
bool done[N];
int n;
int randchild = 0;

void ini(){
     REP(i,N){
     	adj[i].clear();
     	parity[i] = 0;
     	done[i] = 0;
     }
}

void dfs(int u,int p){
	 for(int v:adj[u]){
	 	if(v == p)continue;
	 	if(!done[u]){
	 		if(u == 1)randchild = v;
	 		done[u] = 1;
	 		done[v] = 1;
	 	}
	 	parity[v] = parity[u]^1;
	 	dfs(v,u);
	 }
}

void solve(){
	 ini();
	 cin >> n;
	 REP(i,n-1){
        int a,b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
	 }
	 dfs(1,0);
	 int even = 0;
	 int odd = 0;
	 RE(i,n){
	 	if(parity[i])odd++;
	 	else even++;
	 }
	 bool ok = (odd == even);
	 if(odd > even){
	 	int req = odd-(n/2);
        for(int i = 2;i <= n;i++){
        	if(req == 0)break;
        	if(!parity[i] || done[i])continue;
        	done[i] = 1;
        	parity[i] = 0;
        	req--;
        }
	 }
	 else if(odd < even){
	 	 int req = even-n/2;
	 	 for(int i = 2;i <= n;i++){
        	if(req == 0)break;
        	if(parity[i] || done[i])continue;
        	done[i] = 1;
        	parity[i] = 1;
        	req--;
        }
	 }
	 else{
	 }
     if(!ok)cout << 2 << endl;
     else cout << 1 << endl;
     RE(i,n){
	 	 	if(parity[i])cout << i << " ";
	 }
	 cout << endl;
	 RE(i,n){
	 	 if(!parity[i])cout << i << " ";
	 }
	 cout << endl;
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;cin >> t;
  WL(t)solve();
  return 0;
}
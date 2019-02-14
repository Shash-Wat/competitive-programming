/*input
7 1
0 0 0 0 0 0 1
1 2
1 3
2 4
2 5
3 6
3 7
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

const int N = 1e5+1;
int odd[N];
int even[N];
vi adj[N];
vi tradj[N];
int comp[N];
set<pii> na;
int timer = 0;
int val[N];
int a[N];
int lel;
int n,x;
int cnt = 0;

void dfs(int u,int p){
	 vi childs;
	 for(int v:adj[u]){
         if(v == p)continue;
         childs.pb(v);
         dfs(v,u);
	 }
	 if(!childs.size()){
	 	odd[u] = (val[u] == 1);
	 	even[u] = !odd[u];
	 	return;
	 }
	 int sz = childs.size();
	 int f[sz][2];
	 f[0][0] = even[childs[0]]+odd[childs[0]];f[0][0] %= MOD;
	 f[0][1] = odd[childs[0]];
     RE(i,sz-1){
        f[i][1] = f[i-1][1]*(odd[childs[i]]+even[childs[i]])+f[i-1][0]*odd[childs[i]];
        f[i][0] = f[i-1][0]*(odd[childs[i]]+even[childs[i]])+f[i-1][1]*odd[childs[i]];
        f[i][0] %= MOD;
        f[i][1] %= MOD;
     }
     if(val[u]){
     	odd[u] = f[sz-1][0];
     	even[u] = f[sz-1][1];
     }
     else{
     	odd[u] = f[sz-1][1];
     	even[u] = f[sz-1][0];
     }
}

int get(int u,int p){
    int cur = a[u];
    for(int v:tradj[u]){
       if(v == p)continue;
       int haha = get(v,u);
       if(haha == x || !haha){
         na.insert({u,v});na.insert({v,u});
       }
       else cur ^= haha;
    }
    return cur;
}

void decomp(int u,int p){
     comp[u] = timer;
     lel ^= a[u];
     for(int v:tradj[u]){
        if(v == p || (na.find({v,u}) != na.end()))continue;
        decomp(v,u);
     }
}

void solve(){
	 cin >> n >> x;
	 RE(i,n){
	 	cin >> a[i];
	 }
	 RE(i,n-1){
	 	int xe,y;cin >> xe >> y;
	 	tradj[xe].pb(y);
	 	tradj[y].pb(xe);
	 }
   int now = get(1,1);
   if(now != x && now){
     cout << 0;
     return;
   }
   RE(i,n){
     if(!comp[i]){
      lel = 0;
      timer++;
      decomp(i,i);
      val[timer] = (lel == x);
     }
   }
   auto it = na.begin();
   while(it != na.end()){
        int one = it->f;
        int two = it->s;
        one = comp[one];
        two = comp[two];
        adj[one].pb(two);
        it++;
   }
   dfs(1,1);
   if(x == 0){
      odd[1] = fast_ex(2,timer-1,MOD);
   }
   cout << odd[1];
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;//cin >> t;
  WL(t)solve();
  return 0;
}
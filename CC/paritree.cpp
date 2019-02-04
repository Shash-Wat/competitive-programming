/*input
3
3 2
1 2
1 3
1 2 0
1 3 0
3 0
1 2
2 3
3 1
1 2
2 3
1 2 1

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
int n,qi;
int col[N];
set<int> adj[N];
int par[N];
int sz[N];
vector<pii> edges;
bool flag = 0;


int find(int x){
	 if(par[x] != x){
	    par[x] = par[par[x]];
	    return find(par[x]);
	 }
	 return x;
}

void merge(int x,int y){
	 x = find(x);
	 y = find(y);
	 if(x == y)return;
	 if(sz[x] < sz[y])swap(x,y);
	 par[y] = x;
	 sz[x] += sz[y];
	 return;
}

void bfs(int s){
	 queue<int> q;
	 q.push(s);
	 col[s] = 0;
	 while(!q.empty()){
	 	int u = q.front();q.pop();
        auto it = adj[u].begin();
        while(it != adj[u].end()){
        	if(col[*it] == col[u])flag = 1;
        	if(col[*it] == -1){
        		col[*it] = col[u]^1;
        		q.push(*it);
        	}
        	it++;
        }
	 }
}

void solve(){
	 edges.clear();
	 flag = 0;
	 cin >> n >> qi;
	 RE(i,n-1){
	 	int sf,sl;cin >> sf >> sl;
	 }
	 RE(i,n){
	 	adj[i].clear();
	 	par[i] = i;sz[i] = 1;
	 	col[i] = -1;
	 }
	 while(qi--){
	 	int a,b,x;cin >> a >> b >> x;
	 	if(!x){
           merge(a,b);
	 	}
	 	else{
            edges.pb({a,b});
	 	}
	 }
	 int haha = edges.size();
	 REP(i,haha){
	 	 int one = find(edges[i].f);
	 	 int two = find(edges[i].s);
         if(one == two)flag = 1;
         else{
         	adj[one].insert(two);
         	adj[two].insert(one);
         }
	 }
	 int comp = 0;
     RE(i,n){
     	if(col[find(i)] == -1){bfs(find(i));comp++;}
     }
     if(flag)cout << 0 << endl;
     else cout << fast_ex(2,comp-1,MOD) << endl;
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;cin >> t;
  WL(t)solve();
  return 0;
}
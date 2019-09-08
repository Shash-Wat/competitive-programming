/*input
2 2
00 11
01 10
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long 
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

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

const int INF = 1e18+1;
const int MOD = 1e9+7;
const double PI = 3.14159265358979323846264338;

int raise(int a,int n,int m = MOD){
  if(n == 0)return 1;
  if(n == 1)return a;
  int x = 1;
    x *= raise(a,n/2,m);
    x %= m;
    x *= x;
    x %= m;
    if(n%2)x*= a;
    x %= m;
    return x;
}

int floor1(int n,int k){
    if(n%k == 0 || n >= 0)return n/k;
    return (n/k)-1;
}

int ceil1(int n,int k){
    return floor1(n+k-1,k);
}

const int N = 2<<22;
int n,k;
int x,y;
map<int,bool> a,b;

int conv(string s){
	reverse(all(s));
	int res = 0;
	REP(i,n){
		if(s[i] == '1')res += (1LL)<<i;
	}
	return res;
}

queue<int> q;
queue<int> q1;

void solve(){
	 cin >> n >> k;
	 string x1;cin >> x1;
	 x = conv(x1);cin >> x1;
	 y = conv(x1);
	 REP(i,k){
	 	cin >> x1;
	 	a[conv(x1)] = 1;
	 	b[conv(x1)] = 1;
	 }
	 bool f = 0;
	 REP(i,n){
	 	if(a[x^(1LL<<i)])continue;
	 	f = 1;
	 }
	 bool wow = 0;
	 REP(i,n){
	 	if(a[y^(1LL<<i)])continue;
	 	wow = 1;
	 }
	 if(!x or !f){
	 	cout << "NIE";
	 	return;
	 }
	 int d = 0;
	 a[x] = 1;
	 q.push(x);
	 int okay = 0;

	 while(!q.empty()){
	 	int u = q.front();
	 	q.pop();
	 	d++;
	 	if(__builtin_popcount(u) > 5 and __builtin_popcount(u) < 55){
	 		okay++;
	 	}	
	 	if(okay >= 20000)break;
	 	for(int i = 0;i < n;i++){
	 		int v = (1LL<<i)^u;
	 		if(a[v])continue;
	 		
	 		a[v] = 1;
	 		q.push(v);
	 	}
	 }
	 if(a[y]){
	 	cout << "TAK";
	 	return;
	 }
	 int d1 = 0;
	 b[y] = 1;
	 q1.push(y);
	 while(!q1.empty()){
	 	int u = q1.front();
	 	q1.pop();
	 	if(__builtin_popcount(u) > 5 and __builtin_popcount(u) < 55){
	 		d1++;
	 	}
	 	if(d1 >= 20000)break;
	 	for(int i = 0;i < n;i++){
	 		int v = (1LL<<i)^u;
	 		if(b[v])continue;
	 		
	 		b[v] = 1;
	 		q1.push(v);
	 	}
	 }
	 if(b[x] or (min(okay,d1) >= 20000))cout << "TAK";
	 else cout << "NIE";
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;
  //cin >> t;
  while(t--){
    solve();
  }
  return 0;
}
/*input
4 10 20
15 17 16 18
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

const int N = 2e5+1;
int n,l,u;
pair<int,int> a[N];
int pref[N];
int sum = 0;
set<pii> in;
set<pii> out;


void solve(){
	cin >> n >> l >> u;
	RE(i,n){
		cin >> a[i].f;
		a[i].s = i;
	}
	pref[0] = 0;
	sort(a+1,a+n+1);
	RE(i,n){
		pref[i] = pref[i-1]+a[i].f;
	}
	int len = 1;
	bool ok = 0;
	for(len = 1;len <= n;len++){
		int lowest = pref[len];
		int highest = pref[n]-pref[n-len];
		//cout << len << " " << lowest << " " << highest << endl;
		if(lowest > u or l > highest)continue;
		ok = 1;
		break;
	}
	//cout << ok << endl;
	if(!ok){
		cout << 0;
		return;
	}
	int cursum = 0;
	RE(i,n){
		if(i <= len){
			in.insert(a[i]);
			cursum += a[i].f;
		}
		else out.insert(a[i]);
	}
	while(cursum > u or cursum < l){
		if(cursum > u){
			// take highest and add lowest
			auto it = in.end();it--;
			cursum -= it->f;
			in.erase(*it);
			out.insert(*it);
			auto it1 = out.begin();
			out.erase(*it1);
			in.insert(*it1);
			cursum += it1->f;
		}
		else{
			auto it = in.begin();
			cursum -= it->f;
			in.erase(*it);
			out.insert(*it);
			auto it1 = out.end();it1--;
			out.erase(*it1);
			in.insert(*it1);
			cursum += it1->f;
		}
	} 
	cout << in.size() << "\n";
	for(auto it:in){
		cout << it.s-1 << " ";
	}
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
//help the old king
/*input
*/
#include<bits/stdc++.h>
using namespace std;

#define int long long 
#define double long double

typedef pair<int,int> pi;

typedef vector<int> vi;
typedef vector<pi> vpi;

#define f first
#define s second
#define mp make_pair
#define pb push_back

#define gcd __gcd

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

int par[100001];
int size[100001];

int find(int x){
    if(par[x] == x){
    	return x;
    }
    return par[x] = find(par[x]);
}

void merge(int a,int b){
	 int x = find(a);
	 int y = find(b);
	 if(x == y)return;
	 if(size[y] > size[x])swap(x,y);
	 par[y] = x;
	 size[x] += size[y];
	 return;
}

int n,m,i,j,k;

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  int t;cin >> t;
  while(t--){
    cin >> n >> m;
    vector < pair< int,pair<int,int> > > edges;
    for(i = 1;i <= n;i++){
  	par[i] = i;
  	size[i] = 1;
    }
    for(i = 0;i < m;i++){
    	int a,b,c;
    	cin >> a >> b >> c;
    	int nc = log2(c);
    	edges.pb(mp(nc,mp(a,b)));
    }
    int ans = 0;
    sort(edges.begin(),edges.end());
    for(i = 0;i < m;i++){
        if(find(edges[i].s.f) != find(edges[i].s.s)){
        	merge(edges[i].s.f,edges[i].s.s);
        	ans += edges[i].f;
        }
    }
    cout << ans+1 << endl; 
  }
  return 0;
}

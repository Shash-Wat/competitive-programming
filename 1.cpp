/*input
4 3
1 2 3
2 3 2
2 4 4
1 2
4 1
3 1
*/
#include<bits/stdc++.h>
using namespace std;

//#define int long long 
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
const int N = 1e5+1;

int n,q,i,k,l,m;
vector < pair< int,pair<int,int> > > a;
vector < pair< pair<int,int> , int > > b;
int size[N],par[N],ans[N];

int find(int a){
    if(par[a] != a){
    	par[a] = find(par[a]);
    }
    return par[a];
} 

void merge(int a,int b){
	int x = find(a);
	int y = find(b);
	if(x == y)return;
	if(size[y] > size[x])swap(x,y);
	size[x] += size[y];
	par[y] = x;
}

void ini(){
	for(i = 1;i <= n;i++){
		par[i] = i;
		size[i] = 1;
	}
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  freopen("mootube.in","r",stdin);
  freopen("mootube.out","w",stdout);
  cin >> n >> q;
  for(i = 0;i < n-1;i++){
    int x,y,z;
    cin >> x >> y >> z;
    a.pb(mp(z,mp(x,y)));
  	//cin >> a[i].s.f >> a[i].s.s >> a[i].f;
  }
  ini();
  sort(a.begin(),a.end());
  for(i = 0;i < q;i++){
  	int x,y;
    cin >> x >> y;
    b.pb(mp(mp(x,y),i));
  }
  sort(b.begin(),b.end());
  int j = n-2;
  for(i = q-1;i > -1;i--){
      while(j >= 0 && a[j].f >= b[i].f.f){
         merge(a[j].s.f,a[j].s.s);
         j--;
      }
      ans[b[i].s] = size[find(b[i].f.s)]-1;
  }
  for(i = 0;i < q;i++)cout << ans[i] << endl;
  return 0;
}
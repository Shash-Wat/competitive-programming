// roads not only in berland 
/*input
7
1 2
2 3
3 1
4 5
5 6
6 7
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

int expo(int a,int n,int m){
	if(n == 0)return 1;
	if(n == 1)return a;
	int x = 1;
    x *= expo(a,n/2,m);
    x %= m;
    x *= x;
    x %= m;
    if(n%2)x*= a;
    x %= m;
    return x;
}

int par[1001];
int size[1001];
vpi spare;

int n,i,j,k;

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

#define int long long

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  cin >> n;
  for(i = 1;i <= n;i++){
  	 par[i] = i;
  	 size[i] = 1;
  }
  int u = n-1;
  while(u--){
  	cin >> j >> k;
  	if(find(j) == find(k)){
  		spare.pb(mp(j,k));
  	}
  	merge(j,k);
  }
  int best = 1;
  for(i = 1;i <= n;i++){
     if(size[find(i)] > size[best]){
     	best = find(i);
     }
  }
  cout << spare.size() << endl;
  int j = 0;
  for(i = 1;i <= n;i++){
  	if(find(i) != find(best)){
      merge(i,best);
      cout << spare[j].f << " " << spare[j].s << " " << i << " " << best << endl;
      j++;
  	}
  }
  return 0;
}
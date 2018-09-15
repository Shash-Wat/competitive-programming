//cf 999 E
/*input
9 9 1
1 2
1 3
2 3
1 5
5 6
6 1
1 8
9 8
7 1
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

int n,m,s,i,j,k;
vi adj1[5001],adj2[5001];
bool vis[5001] = {0};
int comp[5001] = {0};
stack<int> ord;
int timer = 0;
set<int> ans;

void dfs1(int u){
	vis[u] = 1;
	for(auto v : adj1[u]){
		if(!vis[v])dfs1(v);
	}
	ord.push(u);
}

void dfs2(int u){
     comp[u] = timer;
     for(auto v : adj2[u]){
     	if(!comp[v])dfs2(v);
     }
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  cin >> n >> m >> s;
  for(i = 0;i < m;i++){
  	int a,b;
  	cin >> a >> b;
  	adj1[a].pb(b);
  	adj2[b].pb(a);
  }
  for(i = 1;i <= n;i++){
  	if(!vis[i])dfs1(i);
  }
  while(!ord.empty()){
  	j = ord.top();
  	ord.pop();
  	if(!comp[j]){
  		timer++;
  		dfs2(j);
  	}
  }
  for(i = 1;i <= n;i++){
  	for(auto j : adj1[i]){
  		if(comp[i]!= comp[j]){
  			ans.insert(comp[j]);
  		}
  	}
  }
  ans.insert(comp[s]);
  cout << timer-ans.size();
  return 0;
}

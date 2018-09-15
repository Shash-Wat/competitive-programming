// free ticket inoi
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

 signed main(){
   ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n,m;
	cin >> n >> m;
	int a,b,c;
    int adj[n+1][n+1];
	for(int i = 1;i <= n;i++){
	    for(int j = 1;j <= n;j++){
	        adj[i][j] = INF;
	    }
	}
	for(int i = 1;i <= n;i++)adj[i][i] = 0;
	for(int i = 0;i < m;i++){
	    cin >> a >> b >> c;
	    adj[a][b] = c;
	    adj[b][a] = c;
	}
	for(int i = 1;i <= n;i++){
	    for(int j = 1;j <= n;j++){
	        for(int k = 1;k <= n;k++){
	            if(adj[j][i] != INF && adj[i][k] != INF && adj[j][i]+adj[i][k] < adj[j][k]){
	            adj[j][k] = adj[j][i]+adj[i][k];
	          }
	        }
	    }
	}
	int maxw = -1;
	for(int i = 1;i <= n;i++){
	    for(int j = 1;j <= n;j++){
	        maxw = max(maxw,adj[i][j]);
	    }
	}
    cout << maxw;
    return 0;
    }

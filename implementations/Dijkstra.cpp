//poi sums : wont pass due to long long
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

int a[10001];
priority_queue < pair<int,int> > pq;
int dist[100001];
bool vis[100001];
int n,k,i,x;
int inf = 2000000001;

void dijkstra(){
    pq.push(make_pair(0,0));
    dist[0] = 0;
    while(!pq.empty()){
        int u = pq.top().second;
        int no = -pq.top().first;
        pq.pop();
        if(dist[u] < no || vis[u])continue;
        vis[u] = 1;
        for(int i = 1;i < n;i++){
            int d = no+a[i];
            int v = d;
            v %= x;
            if( d < dist[v] ){
                dist[v] = d;
                pq.push(make_pair(-d,v));
            }
        }
    }
}

signed main() {
    cin >> n;
    for(i = 0;i < n;i++)cin >> a[i];
    x = a[0];
    for(i = 0;i < x;i++){dist[i] = inf;vis[i] = 0;}
    dijkstra();
    cin >> k;
    while(k--){
        cin >> i;
        if(dist[i%x] <= i)cout << "TAK" << endl;
        else if(dist[i%x] > i)cout << "NIE" << endl;
    }
	return 0;
}

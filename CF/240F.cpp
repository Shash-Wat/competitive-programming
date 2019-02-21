/*input
7 2
aabcbaa
1 3
5 7
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
int freq[4*N][26];
int lazy[4*N];
int buf[26];
int ans[N];
string s;
int n,q;

void build(int node,int l,int r){
     REP(i,26)freq[node][i] = 0;
     lazy[node] = -1;
     if(l == r){
        int ok = s[l-1]-'a';
        //debug2(l,ok);
        freq[node][ok] = 1;
        return;
     }
     int mid = (l+r)/2;
     build(2*node,l,mid);build(2*node + 1,mid+1,r);
     REP(i,26){
        freq[node][i] = freq[2*node][i]+freq[2*node+1][i];
     }
     return;
}

void update(int node,int l,int r,int start,int end,int x){
     
     if(lazy[node] != -1){
        REP(i,26)freq[node][i] = 0;
        freq[node][lazy[node]] = r-l+1;
        if(l!= r){
            lazy[2*node + 1] = lazy[node];
            lazy[2*node] = lazy[node]; 
        }
        lazy[node] = -1;
     }
     if(l >= start && end >= r){
        REP(i,26)freq[node][i] = 0;
        freq[node][x] = r-l+1;
        if(l!= r){
            lazy[2*node + 1] = x;
            lazy[2*node] = x;
        }
        return;
     }
     if(end < l || start > r)return;
     int mid = (l+r)/2;
     update(2*node,l,mid,start,end,x);
     update(2*node+1,mid+1,r,start,end,x);
     REP(i,26){
        freq[node][i] = freq[2*node][i]+freq[2*node+1][i];
     }
}

void get(int node,int l,int r,int start,int end){
  
     if(lazy[node] != -1){
        REP(i,26)freq[node][i] = 0;
        freq[node][lazy[node]] = r-l+1;
        if(l!= r){
            lazy[2*node + 1] = lazy[node];
            lazy[2*node] = lazy[node]; 
        }
        lazy[node] = -1;
     }
     if(end < l || start > r)return;
     if(l >= start && end >= r){
        for(int i = 0;i < 26;i++){
            buf[i] += freq[node][i];
        }
        return;
     }
     int mid = (l+r)/2;
     get(2*node,l,mid,start,end);get(2*node+1,mid+1,r,start,end);
}

void final(int node,int l,int r){
     if(lazy[node] != -1){

        REP(i,26)freq[node][i] = 0;
        freq[node][lazy[node]] = r-l+1;
        if(l!= r){
            lazy[2*node + 1] = lazy[node];
            lazy[2*node] = lazy[node]; 
        }
        lazy[node] = -1;
     }
     if(l == r){
        REP(i,26){
            if(freq[node][i]){ans[l] = i;break;}
        }
        return;
     }
     int mid = (l+r)/2;
     final(2*node,l,mid);
     final(2*node + 1,mid+1,r);
}

string alpha = "abcdefghijklmnopqrstuvwxyz";

void solve(){
     cin >> n >> q >> s;
     build(1,1,n);
     while(q--){
          int l,r;cin >> l >> r;
          REP(i,26)buf[i] = 0;
          get(1,1,n,l,r);
          int odd = 0;
          int pos =0 ;
          REP(i,26){
            odd += buf[i]%2;
            if(buf[i]%2)pos = i;
          }
          if(odd > 1)continue;
          if(odd){
            int beech = (l+r)/2;
            update(1,1,n,beech,beech,pos);
            buf[pos]--;
          }
          int one = l;
          int two = r;
          int now = 0;
          while(now < 26){
            if(buf[now]){
                int sz = buf[now]/2;
                update(1,1,n,one,one+sz-1,now);
                update(1,1,n,two-sz+1,two,now);
                one += sz;
                two -= sz;
            }
            now++;
          }
     }
     final(1,1,n);
     RE(i,n)cout << alpha[ans[i]];
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  cin.exceptions(ios::badbit | ios::failbit);
 // freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
  int t = 1;//cin >> t;
  WL(t)solve();
  return 0;
}
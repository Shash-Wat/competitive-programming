#include<bits/stdc++.h>
using namespace std;
 
#define int long long
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define RE(i,n) for(int i = 1;i <= (int)(n);i++)
#define REP(i,n) for(int i = 0;i < (int)(n);i++)
#define FOR(i,a,b) for(int i = (int)a;i <= (int)(b);i++)
#define debug(a) cout << a << endl;
#define debug2(a,b)cout << a << " " << b << endl;
#define debug3(a,b,c)cout <<  a << " " << b << " " << c << endl;
#define print(a) for(auto it:a)cout << it << " ";cout << endl;
 
const int INF = 1e18;
const int MOD = 1e9+7;
const int N = 401;
 
int n;
int x[N];
int y[N];
int ox,oy;
int o;
int o1;
 
bool where(int i,int j,int k){
     // returns 1 if k lies above i->j
     int cross = (y[k]-y[i])*(x[j]-x[i])-(y[j]-y[i])*(x[k]-x[i]);
     if(cross > 0)return 1;
     return 0;
}
 
bool comp(int i,int j){
     return where(o,i,j);
}
 
int getsize(vector<int> &a){
    sort(a.begin(),a.end(),comp);
    stack<int> pts;
    pts.push(o);
    for(int i = 0;i < a.size();i++){
        while(pts.size() > 1){
             int x = pts.top();pts.pop();
             int x1 = pts.top();
             pts.push(x);
             if(where(x1,a[i],x)){
                pts.pop();
             }
             else break;
        }
        pts.push(a[i]);
    }
    return pts.size();
}
 
int check(int p,int q){
    vector<int> left,right;
    for(int i = 1;i <= n;i++){
        if(i == p or i == q)continue;
        if(where(p,q,i) == 1)left.pb(i);
        else right.pb(i);
    }
    right.pb(q);
    left.pb(p);
    o = p;
    o1 = q;
    int res = getsize(right);
    o = q;
    o1 = p;
    res += getsize(left);
    return res-2;
}
 
void solve(){
    cin >> n;
    for(int i = 1;i <= n;i++)cin >> x[i] >> y[i];
    int ans = 0;
    for(int p = 1;p <= n;p++){
        for(int q = 1;q < p;q++){
            if(y[p] > y[q])ans = max(ans,check(q,p));
            else ans = max(ans,check(p,q));
        }
    }
    cout << ans << endl;
}
 
signed main(){
    int t;cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define int long long 

const int N = 8000 + 69;
const int M = 800  + 69;
const int inf = 1e18 + 69;

int n,m,i,j,k,l,r,s,t,u,v;

int pref[N];
int dp[M][N];

int c(int i,int j){
    return (pref[j]-pref[i-1])*((j-i)+1);
}

void solve(int i,int jleft,int jright,int kleft,int kright){
    int jmid = (jleft+jright)/2;
    dp[i][jmid] = inf;
    int bestk = 0;
    for(j = kleft;j <= min(jmid,kright);j++){
        if(dp[i][jmid] >= dp[i-1][j-1] + c(j,jmid)){
            dp[i][jmid] = dp[i-1][j-1] + c(j,jmid);
            bestk = j;
        }
    }
    if(jleft < jmid){
    solve(i,jleft,jmid-1,kleft,bestk);
    }    
    if(jright > jmid){
    solve(i,jmid+1,jright,bestk,kright);
    }
}


signed main() {
    cin >> n >> m;
    pref[0] = 0;
    for(i = 1;i <= n;i++){
        cin >> pref[i];
        pref[i] += pref[i-1];
        dp[1][i] = pref[i] * i;
    }
    for(i = 2;i <= m;i++){
        solve(i,1,n,1,n);
    }
    
   /* for (int i = 0; i < n+1; i++) {
        for (int j = 0; j < m+1; j++) {
            cout << dp[j][i] << " ";
        }
        cout  << endl;
    }*/
    cout << dp[m][n];
    return 0;
}

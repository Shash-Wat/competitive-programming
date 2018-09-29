#include <bits/stdc++.h>
using namespace std;

const int T = 5e6+2;
int t,a,b,i,j,k;
int cache[T][2];

int  rec(int fullness,bool done){
     if(fullness+a > t && fullness+b > t && done)return fullness;
     if(cache[fullness][done] != -1)return cache[fullness][done];
     int x = 0,y = 0,z = 0;
     if(!done)x = rec(fullness/2,1);
     if(fullness+a <= t)y = rec(fullness+a,done);
     if(fullness+b <= t)z = rec(fullness+b,done);
     cache[fullness][done] = max(x,max(y,z));
     return max(x,max(y,z));
}

int main() {
     freopen("feast.in","r",stdin);
     freopen("feast.out","w",stdout);
	cin >> t >> a >> b;
	for(i = 0;i <= t;i++)cache[i][0] = cache[i][1] = -1;
	cout << rec(0,0);
	return 0;
}

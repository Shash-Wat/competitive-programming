/*input

*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
//#include "cave.h"
using namespace std;
using namespace __gnu_pbds;

#define double long double
#define f first
#define s second
#define mp make_pair
#define pb push_back

#define RE(i,n) for (int i = 1; i <= n; i++)
#define RED(i,n) for (int i = n; i > 0; i--)
#define REPS(i,n) for(int i = 1; (i*i) <= n; i++)
#define REP(i,n) for (int i = 0; i < (int)n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)

#define all(v) v.begin(),v.end()
#define pii pair<int,int>
#define vi vector<int>
#define vvi vector<vi>
#define print(arr) for (auto it = arr.begin(); it != arr.end(); ++it) cout << *it << " "; cout << endl;
#define debug(x) cout << x << endl;
#define debug2(x,y) cout << x << " " << y << endl;
#define debug3(x,y,z) cout << x << " " << y << " " << z << endl;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

const int INF = 1e18+1;
const int MOD = 1e9+7;
const double PI = 3.14159265358979323846264338;

int raise(int a,int n,int m = MOD){
  if(n == 0)return 1;
  if(n == 1)return a;
  int x = 1;
    x *= raise(a,n/2,m);
    x %= m;
    x *= x;
    x %= m;
    if(n%2)x*= a;
    x %= m;
    return x;
}

int floor1(int n,int k){
    if(n%k == 0 || n >= 0)return n/k;
    return (n/k)-1;
}

int ceil1(int n,int k){
    return floor1(n+k-1,k);
}

const int K = 4;
int door[K];// which door corresponds to this switch
int swit[K];// which switch corresponds to this door
int ans[K];//what is right orientation for this door 

int tryCombination(int s[]){
	int minn = -1;
	for(int i = 0;i < K;i++){
		if(ans[door[i]] != s[i])minn = min(minn,i);
	}
	return minn;
}

int answer(int s[],int d[]){
	for(int i = 0;i < K;i++){
		if(d[i] != door[i])return 0;
		if(s[i] != ans[door[i]])return 0;
	}
	return 1;
}

void exploreCave(int N){
	int stick[N];
	int cur[N];
	int door[N];
	int aux[N];
	REP(i,N){
		stick[i] = 0;
		door[i] = -1;
		aux[i] = 1;
		cur[i] = 0;
	}
	int find = 0;
	while(find < N){
		int rightnow = tryCombination(cur);
		if(rightnow == -1)rightnow = N+1;
		int lo = 0;
		int hi = N-1;
		if(rightnow > find){
			//look for first i such that rightnow becomes find
			while(lo < hi){
				int mid = (lo+hi)/2;
				REP(i,mid+1){
					if(!stick[i])aux[i] = cur[i]^1;
				}
				for(int i = mid+1;i < N;i++){
					aux[i] = cur[i];
				}
				int lookwhatyoumademedo = tryCombination(aux);
				if(lookwhatyoumademedo == -1)lookwhatyoumademedo = N+1;
				if(lookwhatyoumademedo == find)hi = mid;
				else lo = mid+1;
			}
			door[lo] = find;
			stick[lo] = 1;
		}
		else{
			// look for first i such that rightnow becomes more than find
			while(lo < hi){
				int mid = (lo+hi)/2;
				REP(i,mid+1){
					if(!stick[i])aux[i] = cur[i]^1;
				}
				for(int i = mid+1;i < N;i++){
					aux[i] = cur[i];
				}
				int lookwhatyoumademedo = tryCombination(aux);
				if(lookwhatyoumademedo == -1)lookwhatyoumademedo = N+1;
				if(lookwhatyoumademedo > find)hi = mid;
				else lo = mid+1;
			}
			door[lo] = find;
			stick[lo] = 1;
			cur[lo] ^= 1;
		}
		find++;
	}
	answer(cur,door);
}

int main(){
	exploreCave(K);
}

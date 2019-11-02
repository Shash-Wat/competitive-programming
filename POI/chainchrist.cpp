/*input
- Atmost N edges can change the answer
- Maintain DSU parent array for each index
- Binary search on the first position where the parents of the corresponding subarrays differ
- Check function of binary search uses hashing 
- X = a_i 
  Y = b_i 
  while(X < a_i+l_i):
        binary search for smallest K such that  hash[X,X+K-1]  != hash[Y,Y+K-1]
        merge(X+K-1,Y+K-1)
        X = X+K
        Y = Y+K
- Maintain BIT for hashing as they keep changing , but because parent can only change Log N times, complexity is amortized
  O(N log2 N) which fits because TLs are quite strange.
  
10 3
1 6 3
5 7 4
3 8 1
*/
#include<bits/stdc++.h>
using namespace std;

#define pb push_back

#define int long long
#define RE(i,n) for(int i = 1;i<= n;i++)
#define REP(i,n) for(int i = 0;i < n;i++)

const int pol = 5e5+9;
const int prs[] = {999999937,1000000007};

const int N = 5e5+1;
int par[N];
int sz[N];
int val[N][2];
vector<int> all[N];
int bit[N][2];
int rais[N][2];
int n,q;
int ans;
// ith element is par[i]*prs[i-1]^(i-1) compute mod both

void hashpre(){
	rais[0][0] = rais[0][1] =1;
	RE(i,n){
		REP(j,1){
			rais[i][j] = rais[i-1][j]*pol;
			rais[i][j] %= prs[j];
		}
	}
}

void updbit(int wh,int ind,int diff){
	while(ind <= n){
		bit[ind][wh] += diff;
	//	bit[ind][wh] %= prs[wh];
		ind += ind&(-ind);
	}
}

int pref(int wh,int ind){
	int res = 0;
	while(ind){
		res += bit[ind][wh];
	//	res %= prs[wh];
		ind -= ind&(-ind);
	}
	return res;
}

int sum(int wh,int l,int r){
	int one = pref(wh,r)-pref(wh,l-1);
	one %= prs[wh];
	if(one < 0)one += prs[wh];
	return one;
}

void change(int wh,int ind,int now){
	int old = val[ind][wh];
	int newval = now*rais[ind-1][wh];
	newval %= prs[wh];
	int diff = newval-old;diff %= prs[wh];
	if(diff < 0)diff += prs[wh];
	updbit(wh,ind,diff);
	val[ind][wh] = newval;
	par[ind] = now;
}

int find(int x){
	if(par[x] == x)return x;
	return find(par[x]);
}

bool compare(int wh,int l,int r,int l1,int r1){
	int one = sum(wh,l,r);// divide by a^(l-2)
	int two = sum(wh,l1,r1);// divide by a^(l1-2)
	if(l >= 2)two *= rais[l-2][wh];
	if(l1 >= 2)one *= rais[l1-2][wh];
	one %= prs[wh];
	two %= prs[wh];
	return one == two;
}

inline void merge(int a,int b){
	ans--;
	if(sz[a] < sz[b])swap(a,b);
	sz[a] += sz[b];
	for(int v:all[b]){
		all[a].pb(v);
		//change hash now
		REP(j,1)change(j,v,a);
	}
	all[b].clear();
}

void solve(){
	
	cin >> n >> q;
	ans = n;
	hashpre();
	RE(i,n){
		par[i] = i;
		sz[i] = 1;
		all[i].pb(i);
		REP(j,1)change(j,i,i);
	}
	while(q--){
		int a,b,l;cin >> a >> b >> l;
		int ea = a+l-1;
		int eb = b+l-1;

		while(a <= ea){
		   // cout << a << " " << b << endl;
			int lo = 1;
			int hi = ea-a+1;
			while(lo < hi){
				int mid = (lo+hi)/2;
				int na = a+mid-1;
				int nb = b+mid-1;
				bool ok = 1;
				REP(j,1){
					ok &= compare(j,a,na,b,nb);
				}
				if(ok)lo = mid+1;
				else hi = mid;
			}
			int pos1 = a+lo-1;
			int pos2 = b+lo-1;
			if(pos1 > ea)break;
			if(par[pos1] != par[pos2])merge(par[pos1],par[pos2]);
			a = pos1+1;
			b = pos2+1;
		}
	}
	cout << ans;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	solve();
	return 0;
}

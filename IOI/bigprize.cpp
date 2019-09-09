#include "prize.h"
#include<bits/stdc++.h>
using namespace std;
 
#define REP(i,n) for(int i = 0;i < n;i++)
#define RE(i,n) for(int i = 1;i <= n;i++)
 
const int N = 2e5+1;
 
int blocksize = 1001;
int block[N];
int blockstart[N];
 
int find_best(int n) {
	int curblock = 1;
	int cursize = 0;
	blockstart[1] = 0;
	for(int i = 0;i < n;i++){
		block[i] = curblock;
		cursize++;
		if(cursize == blocksize){
			curblock++;
			cursize = 0;
			blockstart[curblock] = i+1;
		}
	}
	int i = 0;
	while(i < n){
		int lo = i;
		int hi = min(n-1,blockstart[block[i]]+blocksize-1);
		vector<int> res = ask(i);
		if(res[1] > (hi-lo)){
			i = hi+1;
			continue;
		}
		if(!(res[0]+res[1]))return i;
		bool lmao = 0;
		for(int j = i+1;j < min(n,i+4);j++){
			if(ask(j) != res){
				i = j;
				lmao = 1;
				break;
			}
		}
		if(lmao)continue;
		while(lo < hi){
			int mid = (lo+hi+1)/2;
			vector<int> wow = ask(mid);
			if(wow == res)lo = mid;
			else hi = mid-1;
		}
 
		i = lo+1;
	}
	return 0;
}
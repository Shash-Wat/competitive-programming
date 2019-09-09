#include <vector>
#include <bits/stdc++.h>
#include "messy.h"
using namespace std;

#define mid (l+r+1)/2
int N;
string xd = "";
vector<int> ans;

void recurseadd(int l,int r){
	if(l == r)return;
	string cur = xd;
	for(int i = 0;i < l;i++)cur[i] = '1';
	for(int i = r+1;i < N;i++)cur[i] = '1';
	for(int i = l;i < mid;i++){
		cur[i] = '1';
		add_element(cur);
		cur[i] = '0';
	}
	recurseadd(l,mid-1);
	recurseadd(mid,r);
}	

void recurseget(int l,int r,string anc){
	string cur = anc;
	if(l == r){
		for(int i = 0;i <N;i++){
			if(cur[i] == '0')ans[l] = i;
		}
		return;
	}
	string lu = anc;
	string ru = anc;
	for(int i = 0;i < N;i++){
		if(cur[i] == '0'){
			cur[i] = '1';
			if(check_element(cur)){
				lu[i] = '1';
			}
			else{
				ru[i] = '1';
			}
			cur[i] = '0';
		}
	}
	recurseget(l,mid-1,ru);
	recurseget(mid,r,lu);

}

vector<int> restore_permutation(int n, int w, int r) {
	N = n;
	for(int i = 0;i < n;i++)xd += "0";
   	recurseadd(0,n-1);
   	ans.resize(N);
    compile_set();
    recurseget(0,n-1,xd);
    vector<int> pos(n);
    for(int i = 0;i < ans.size();i++)pos[ans[i]] = i;
   	return pos;
}

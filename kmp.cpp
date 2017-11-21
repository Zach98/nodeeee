#include<stdio.h>
#include<string.h>

int next[20];
char S[50], T[40];

int index_kmp(int ls, int lt){
	int i = 0;
	int j = 0;
	while(i < ls && j < lt){
		if(j == 0 || S[i] == T[j]){
			++i;
			++j;
		}
		else j = next[j - 1];
	}
	if(j >= lt) return i - lt;
	else return 0;
}

void get_next(int lt){//abaabcac acabaabaabcacaabc
	int i = 0;
	next[1] = 0;
	int j = 0;
	while(i < lt){
		if(j == 0 || T[i] == T[j]){
			++i;
			++j;
			if(T[i] != T[j]) next[i] = j;
			else next[i] = next[j];
		}
		else j = next[j];
	}
}

int main()
{
	int LengthOfS, LengthOfL;
	
	scanf("%s%s", S, T);
	LengthOfL = strlen(T);
	LengthOfS = strlen(S);
	//get_next(LengthOfL);
	int ans;
	ans = index_kmp(LengthOfS, LengthOfL);
	if(ans == 0) printf("error!");
	else printf("%d", ans);
}

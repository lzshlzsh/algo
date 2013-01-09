#include <stdio.h>
#define CNUMBER 4
int find(int *a, int n){
	int number = CNUMBER;
	int save[number+1];
	int next[n];
	int least[n];
	int i, j, k;
	for(i=0;i<CNUMBER+1;i++){
		save[i]=-1;
	}
	for(i=0;i<n;i++){
		next[i]=-1;
	}
//	for(i=0;i<n;i++){
		i = 0;
		for(j=0;j<n;j++){
			if(number!=0)
				least[j]=-1;
			if(save[a[j]]==-1){
				save[a[j]]=j;
				number--;
			}
			else{
				next[save[a[j]]]=j;
				save[a[j]]=j;
			}
			while(i<j){
				if(a[i]==a[j]||next[i]!=-1)
					i++;
				else
					break;
			}
			if(number == 0 )
				least[j]=j-i+1;
			
		}
		j=0;
		while(least[j]==-1 &&i<n ){
			
			next[save[a[j]]]=j;
		//	save[a[j]]=j;

			while(i<n){
				if(a[i]==a[j]||(next[i]>i||next[i]<j)&&next[i]!=-1)
					i++;
				else
					break;
			}


			least[j]=j+n-i+1;
			
			j++;

		}

//	}
	for(i=0;i<n;i++)
		printf("%d ", least[i]);
	printf("\n");


}

int main(){
	int n;
	int a[100];
	scanf("%d", &n);
	int i;
	for(i=0;i<n;i++)
		scanf("%d", &a[i]);
	find(a, n);
}

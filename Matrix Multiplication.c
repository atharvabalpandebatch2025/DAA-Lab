#include<stdio.h>
int main(void){
	int m,n;
	scanf("%d %d", &m, &n);
	int mx1[m][n];
	for(int i = 0; i< m; i++)
		{
			for(int j=0; j < n;j++)
				{
					scanf("%d", &mx1[i][j]);
				}
		}
	int o,p;
	scanf("%d %d", &o, &p);
	if(n != o)
	{
		printf("Invalid input");
			return 0;
	}
	int mx2[o][p];
	for(int i = 0; i < o; i++){
		for(int j = 0; j < p; j++){
			scanf("%d", &mx2[i][j]);
		}
	}
	int mx[m][p];

	for( int i = 0; i < m; i++){
		for(int j = 0; j < p; j++){
			mx[i][j] = 0;
			for(int k = 0; k < n; k++){
				mx[i][j] += mx1[i][k] * mx2[k][j];
			}
		}
	}
	for(int i = 0; i < m; i++){
		for(int j = 0; j < p; j++){
			printf("%d ", mx[i][j]);
		}
		printf("\n");
	}
}



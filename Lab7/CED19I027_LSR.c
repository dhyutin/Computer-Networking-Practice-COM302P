#include<stdio.h>
#include<limits.h>

// Main 
int main()
{
	int n, i, j, k;
	
	printf("Enter the number of routers: ");
	scanf("%d",&n);
	
	int arr[n][n];
	
	printf("Enter the distances between the routers:\n");
	printf("\n(-1 if the routers are not connected.)\n\n");
	
	for(i=0;i<n;i++)
	{
		arr[i][i] = 0; //distance from itself is 0.
		for(j=i+1;j<n;j++)
		{
			printf("Enter between router %d and %d : ",i+1,j+1);
			scanf("%d",&arr[i][j]);
			arr[j][i] = arr[i][j];
		}
	}
	
	int min = INT_MAX,idx;
	int arr2[n];
	
	for(j=1;j<n;j++)
	{
		arr2[j] = arr[0][j];		
	}
	
	printf("------------------------------\n\nRouter - 1 is root node.\n\n");
	
	for(i=1;i<n;i++)
	{
		printf("\n\n");
		min = INT_MAX;
		for(j=1;j<n;j++)
		{
			if(arr2[j]<=min &&arr2[j]!=-1 &&arr2[j]!=-2)
			{
				min = arr2[j];
				idx = j;
			}
		}
		printf("Distance to router - %d = %d\n",idx+1,min);
		arr2[idx] = -2;
		
		for(j=1;j<n;j++)
		{
			if(arr2[j]!=-2 && arr[idx][j]!=-1)
			if((min + arr[idx][j] < arr2[j] && arr2[j]!=-1) || arr2[j] == -1)
		    {
				arr2[j] = min + arr[idx][j];
			}
		}
	}
    
    return 0;
}

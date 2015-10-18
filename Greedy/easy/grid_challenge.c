/*Sort each row according to alphabetical order. Start comparing adjacent vertical characters. If it fails at one case then print 'NO' else
print 'YES'.*/
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
int compfunc(const void *a, const void *b)
{
	return (*(char *)a-*(char *)b);
}

int main()
{
	int t=0, n=0, i=0, j=0, lexic=TRUE;
	char m[100][100];
	scanf("%d", &t);
	while(t--)
	{
		lexic=TRUE;
		scanf("%d", &n);		
		if(n!=1)
		{
			for(i=0; i<n; ++i)
			{
				scanf("%s", m[i]);
				qsort(m[i], n, sizeof(char), compfunc);
			}
			for(i=0; i<n; ++i)
			{
				for(j=1; j<n; ++j)
				{					
					if(m[j][i]<m[j-1][i])
					{						
						lexic=FALSE;
						break;
					}
				}
				if(lexic==FALSE)
					break;
			}
		}
		else
			scanf("%s", m[0]);
		if(lexic)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
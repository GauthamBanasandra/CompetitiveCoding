/*Have to variables 'five' and 'three'. Initialize 'five' to the number given as input. Decrement 'five' and increment 'three' as long as
the number isn't divisible by both 'five' and 'three'.*/
#include <stdio.h>
int main()
{
	int t=0, five=0, three=0, i=0;
	scanf("%d", &t);

	while(t--)
	{
		five=three=0;
		scanf("%d", &five);
		
		while(five!=-1)
		{
			if(!(five%3) && !(three%5))
				break;
			--five;
			++three;
		}
		//printf("five=%d\tthree=%d\t", five, three);
		if(five==-1)
			printf("-1");
		else
		{
			for(i=0; i<five; ++i)
				printf("5");
			for(i=0; i<three; ++i)
				printf("3");
		}
		printf("\n");
	}
	return 0;
}

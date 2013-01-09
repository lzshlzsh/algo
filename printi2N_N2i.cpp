#include <stdio.h>

/*
 *	give a function interface int func(int i, int N) where i <= N,
 *	print i, i+1, ..., N, N, N-1, ..., i.
 *	can just use one statement, and can not use statements such as
 *	if, for, do, while, ? :
 */

int func(int i, int N)
{
	return !((i < N) && printf("%d\n", i) && func(i + 1, N)
		|| printf("%d\n", i));
}

int func2(int i, int N)
{
	return (i == N) && printf("%d\n", i) 
		|| printf("%d\n", i) && func2(i + 1, N) && printf("%d\n", i);
}
 
int main()
{
	func(1, 5);
	printf("*************\n");
	func2(1, 5);
	printf("*************\n");
	return 0;
}




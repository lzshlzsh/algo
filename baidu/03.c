/*
 * a balls, n floors, want to find the minimum number of floor
 * where a ball drops will be broken. output the minimum number
 * of drops
 * METHOD: dynamic programming
 * assum the answer is b, that is the number of drops
 * f(a, b): the maximum number of floors, when a balls and b drops
 * f(a, b) = 1 + f(a, b - 1) + f(a - 1, b - 1)
 * obviously, f(a, 1) = 1; f(1, b) = b
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define DEBUG
#define MAX_B 64
#define MAX_A 16
#define f(a, b) ff[a - 1][b - 1]

static unsigned int a, n;
static unsigned long long ff[MAX_A][MAX_B];


static void init()
{
	int i;

	memset(ff, 0, sizeof(ff));

	/*f(a, 1) = 1*/
	for (i = 1; i <= MAX_A; i++){
		f(i, 1) = 1;
	}
	/*f(1, b) = b + 1*/
	for (i = 1; i <= MAX_B; i++){
		f(1, i) = i;
	}
}


static unsigned long long do_find_min_drops(int i, int j)
{
	if (f(i, j))
		return f(i, j);
	f(i, j) = do_find_min_drops(i - 1, j - 1) + 
		do_find_min_drops(i, j - 1) + 1;
	return f(i, j);
}

static void do_print_drops(int i, int j, unsigned long long min, 
		unsigned long long max)
{
	if (min > max)
		return;
	if (1 == i){
		assert(j == max - min + 1);
		for (i = min; i <= max; i++){
			printf("%5d", i);
		}
		printf("\n");
		printf("*************\n");
		return;
	}
	if (1 == j){
		assert(min == max);
		printf("%5lld\n", max);
		printf("*************\n");
		return;
	}
	printf("%5lld", min + f(i - 1, j - 1));
	do_print_drops(i - 1, j - 1, min, min + f(i - 1, j - 1) - 1);
	do_print_drops(i, j - 1, min + f(i - 1, j - 1) + 1, max);
}

static void print_drops(int ans)
{
	do_print_drops(a, ans, 2, n);/*[2..n]*/	
}
static void find_min_drops()
{
	/*NOTE: number of floors are [1, n]*/
	int i, j, m;		
	int ans;
#if 0//def DEBUG
	for (i = 2; i <= MAX_A; i++){
		for (j = 2; j <= MAX_B; j++){
			printf("f(%d, %d) = %lld\n", i, j, do_find_min_drops(i, j));
		}
		printf("****************\n");
	}
#endif

	i = 1; 
	j = MAX_B;
	while (i <= j){
		m = (i + j) / 2;
		if (do_find_min_drops(a, m) + 1 < n)
		/*
		 * why +1? because the 1st floor need not to test
		 */
			i = m + 1;
		else
			j = m - 1;
	}
	ans = i;
	if (ans > MAX_B){
		printf("the number of the maximum drops(MAX_B = %d) is too small\n", MAX_B);
		printf("maximum floors " 
				"can be tested is f(%d, %d) + 1 = %lld + 1. STOP\n", a, MAX_B, f(a, MAX_B));
		exit(0);
	}
	printf("the minimum drops: %d\n", ans);
	print_drops(ans);
#ifdef DEBUG
	for (i = 1; i <= a; i++){
		for (j = 1; j <= ans; j++){
			printf("f(%d, %d) = %lld\n", i, j, f(i, j));
		}
		printf("****************\n");
	}
#endif
}
int main(int argc, char **argv)
{
	if (3 != argc){
		fprintf(stderr, "usage: %s a n\n", argv[0]);
		exit(-1);
	}
	
	a = atoi(argv[1]);
	n = atoi(argv[2]);

	printf("a = %d\tn = %d\n", a, n);
	assert(a > 0 && a < MAX_A && n > 0);

	init();

	find_min_drops(); /*drops: 1*/

	return 0;
}




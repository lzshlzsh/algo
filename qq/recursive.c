/*
 * f(m, n) = m + n + 1  if m*n = 0
 * f(m, n) = f(m - 1, f(m, n - 1))
 */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <setjmp.h>

#define MAX (1 << 15)
static jmp_buf jbuf;

#define DEBUG


static int getf(int m, int n)
{
	if (n > 1024){
		printf("m or n is too large, getf return directly\n");
		longjmp(jbuf, 1);
	}
	if (!(m * n))
		return m + n + 1;

	return getf(m - 1, getf(m, n - 1));
}

int main()
{
	int STACK[MAX];
	int top;
	int f;
	int m, n;

	printf("input m and n: ");
	scanf("%d%d", &m, &n);

	if (setjmp(jbuf) == 0){
		printf("f = %d\n", getf(m, n));
	}

	top = 0;
	do {
		if (m*n > 0){
			assert(top < MAX); /*only for correctness check*/
			STACK[top++] = m - 1;
			n--;
		}else{
			f = m + n + 1;
			if (top > 0){
				m = STACK[top - 1];
			}
			top--;
			n = f;
		}
#ifdef DEBUG		
		{
			int i;
			printf("(m, n) = (%d, %d), top = %d :", m, n, top);
			for (i = top - 1; i >= 0; i--){
				printf("%3d", STACK[i]);
			}
			printf("\n");
		}
#endif
	}while (!(-1 == top));
	printf("f = %d\n", f);
	return 0;
}

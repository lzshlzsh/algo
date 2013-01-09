#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>


int main()
{
	int i;
	for (i = 0; i < 5; i++){
		fork();
		printf("%d\n", getpid());
		fflush(stdout);
	}
	return 0;
}

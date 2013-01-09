#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

//#define DEBUG

#define MAX_N 100
#define MAX_M 10
#define MAX_VALID_STATES_NUM 60
#define TRUE 1
#define FALSE 0



typedef struct{
	int state;
	int art_nb;
}State;

static State valid_states[MAX_VALID_STATES_NUM]; /*set S*/
static int valid_states_num = 0;
/*
 * F[i][j][k] is the maximum artilleries such that:
 * line k -- state i
 * line k-1 -- state j
 * line k-2
 * 
 * F[i][j][k] = (number of artilleries of state i) +
 * max {F[j][l][k-1], l is the valid state of line k-2}
 */
static int F[MAX_VALID_STATES_NUM][MAX_VALID_STATES_NUM][MAX_N] = {{{0,}}}; 


static inline int HAS_ART(int s, int i)
{
	return (s & (1 << i));
}
static inline int HAS_ART_CHECK(int s, int i, const int M)
{
	return (i >= 0  && i < M && HAS_ART(s, i));
}
static int ART_VALID_CHECK(int s, int M, const char *line)
{
	int i;
	for (i = 0; i < M; i++){
		/*cannot deploy artillery on high moutain*/
		if (HAS_ART(s, i) && 'H' == line[M - 1 - i]){
			return FALSE;
		}
	}
	return TRUE;
}

static void get_valid_states(const int M)
{
	int s, i;
	int flag, art_nb;
	for (s = 0; s < (1 << M); s++){
		flag = TRUE;
		art_nb = 0;
		for (i = 0; i < M; i++){
			if (HAS_ART(s, i)){ 
				art_nb++;
				if (HAS_ART_CHECK(s, i - 2, M) || HAS_ART_CHECK(s, i - 1, M) ||
						HAS_ART_CHECK(s, i + 1, M) || HAS_ART_CHECK(s, i + 2, M)){
					flag = FALSE;
					break;	
				}
			}
		}
		if (flag){
			valid_states[valid_states_num].state = s;
			valid_states[valid_states_num].art_nb = art_nb;
			valid_states_num++;
#ifdef DEBUG
			printf("%d: 0x%x\n", art_nb, s);
#endif
		}
	}
	printf("valid_states_num %d\n", valid_states_num);	
}

/*down-top process*/
static int func(int i, int j, int k, int M, const char **Map)
{
	int l;
#ifdef DEBUG
	int max_l;
#endif
	if (F[i][j][k])
		return F[i][j][k];

	if (1 == k){
		F[i][j][1] = valid_states[i].art_nb + valid_states[j].art_nb;
#ifdef DEBUG
		printf("F[%d][%d][%d] = %d: 0x%x, 0x%x\n", i, j, k, F[i][j][k], 
				valid_states[i].state, valid_states[j].state);
#endif
		return F[i][j][1];
	}

	/*line k - 2, state l*/
	for (l = 0; l < valid_states_num; l++){
		if (!(valid_states[i].state & valid_states[l].state) &&
					!(valid_states[j].state & valid_states[l].state) && 
				ART_VALID_CHECK(valid_states[l].state, M, Map[k - 2])){
#if 0//def DEBUG
				printf("%d, %d, %d ", i, j, l);
				printf("%d, %d, %d\n", valid_states[i].state, 
						valid_states[j].state, valid_states[l].state); 			
#endif
				int f = func(j, l, k - 1, M, Map);
				if (F[i][j][k] < f){
					F[i][j][k] = f;
#ifdef DEBUG
					max_l = l;
#endif					
				}
		}
	}
	F[i][j][k] += valid_states[i].art_nb;
#ifdef DEBUG
		printf("F[%d][%d][%d] = %d: 0x%x, 0x%x, l = %d\n", i, j, k, F[i][j][k], 
				valid_states[i].state, valid_states[j].state, max_l);
#endif
	return F[i][j][k];
}

static void max_artillery(const int N, const int M, 
		const char **Map)
{
	int max_arts = 0;
	int i, j;

	get_valid_states(M);
	
	for (i = 0; i < valid_states_num; i++){
		if (ART_VALID_CHECK(valid_states[i].state, M, Map[N - 1])){
			for (j = 0; j < valid_states_num; j++){
				if (!(valid_states[i].state & valid_states[j].state) && 
						ART_VALID_CHECK(valid_states[j].state, M, Map[N - 2])){
#if 0//def DEBUG
					printf("%d, %d\n", i, j);			
#endif
					int f = func(i, j, N - 1, M, Map);
					if (max_arts < f){
						max_arts = f;
					}
				}
			}
		}
	}
	printf("maximum artillery: %d\n", max_arts);
}

int main()
{
	int n, m;
	char **Map;
	FILE *file;
	int i;

	file = fopen("artilleryInput", "r");
	if (!file){
		perror("cannot open file artilleryInput");
		exit(1);
	}
	
	fscanf(file, "%d", &n);
	fscanf(file, "%d", &m);
#if 1//def DEBUG
	printf("N = %d, M = %d\n", n, m);
#endif	
	assert(n > 0 && n <= MAX_N);
	assert(m > 0 && m <= MAX_M);
	Map = (char **)malloc(sizeof(char *) * n);
	if (!Map){
		perror("malloc");
		exit(1);
	}
	for (i = 0; i < n; i++){
		Map[i] = (char *)malloc(sizeof(char) * (m + 1));
		if (!Map[i]){
			perror("malloc");
			exit(1);
		}
		fscanf(file, "%s", Map[i]);
#if 1//def DEBUG
		printf("%s\n", Map[i]);
#endif
	}

	max_artillery(n, m, (const char **)Map);

	for (i = 0; i < n; i++){
		free(Map[i]);
	}
	free(Map);
	fclose(file);
	return 0;
}




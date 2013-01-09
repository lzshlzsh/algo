#include <stdio.h>
#include <string.h>

//#define DEBUG

typedef struct{
	unsigned int c2 : 2;
	unsigned int c1 : 2;
	unsigned int c0 : 2;
	unsigned int dummy : 2;
}ClockLine;
typedef ClockLine Clock[3];


static Clock clock;
static Clock move[9] = 
{
	{{1, 1, 0}, {1, 1, 0}, {0, 0, 0}},
	{{1, 1, 1}, {0, 0, 0}, {0, 0, 0}},
	{{0, 1, 1}, {0, 1, 1}, {0, 0, 0}},
	{{1, 0, 0}, {1, 0, 0}, {1, 0, 0}},
	{{0, 1, 0}, {1, 1, 1}, {0, 1, 0}},
	{{0, 0, 1}, {0, 0, 1}, {0, 0, 1}},
	{{0, 0, 0}, {1, 1, 0}, {1, 1, 0}},
	{{0, 0, 0}, {0, 0, 0}, {1, 1, 1}},
	{{0, 0, 0}, {0, 1, 1}, {0, 1, 1}},
};
static int solution[27], min_solution[27];
static int idx = 0, min_seq = 28;

static inline int is_answer()
{
	return (!*(char*)(&clock[0]) && !*(char *)(&clock[1])
			&& !*(char *)(&clock[2]));
}


static void move_plus(int i)
{
	int j;
	for (j = 0; j < 3; j++){
		clock[j].c0 += move[i][j].c0;
		clock[j].c1 += move[i][j].c1;
		clock[j].c2 += move[i][j].c2;
	}
	solution[idx++] = i + 1;
}

static void move_sub(int i)
{
	int j;
	for (j = 0; j < 3; j++){
		clock[j].c0 -= move[i][j].c0;
		clock[j].c1 -= move[i][j].c1;
		clock[j].c2 -= move[i][j].c2;
	}
	idx--;
}

static void pku1166(int line)
{
	if (idx > min_seq)
		return; /*cut off leaf*/
	if (line >= 9){
		if (is_answer()){
			if (min_seq > idx){
				min_seq = idx;
				memcpy(min_solution, solution, sizeof(int) * min_seq);
			}
		}
	}else{
		move_plus(line);
		pku1166(line + 1); /*1*/

		move_plus(line);
		pku1166(line + 1); /*2*/
		
		move_plus(line);
		pku1166(line + 1); /*2*/

		move_sub(line);
		move_sub(line);
		move_sub(line);
		pku1166(line + 1); /*3*/
	}
}


#ifdef DEBUG
static void print_clock()
{
	int i;
	for (i = 0; i < 3; i++){
		printf("%5d", clock[i].c2);
		printf("%5d", clock[i].c1);
		printf("%5d", clock[i].c0);
		printf("\n");
	}
}


static void print_move()
{
	int i;
	for (i = 0; i < 9; i++){
		printf("%d: ", i + 1);
		if (move[i][0].c2){
			printf("A");
		}
		if (move[i][0].c1){
			printf("B");
		}
		if (move[i][0].c0){
			printf("C");
		}
		if (move[i][1].c2){
			printf("D");
		}
		if (move[i][1].c1){
			printf("E");
		}
		if (move[i][1].c0){
			printf("F");
		}
		if (move[i][2].c2){
			printf("G");
		}
		if (move[i][2].c1){
			printf("H");
		}
		if (move[i][2].c0){
			printf("I");
		}
		printf("\n");
	}
}
#endif

int main()
{
	int i, tmp;
#ifdef DEBUG
	printf("enter 9 digits\n");
#endif

	for (i = 0; i < 3; i++){
		scanf("%d", &tmp);
		clock[i].c2 = tmp; 
		scanf("%d", &tmp);
		clock[i].c1 = tmp; 
		scanf("%d", &tmp);
		clock[i].c0 = tmp;
	}

#ifdef DEBUG
	print_clock();
	print_move();
#endif
	pku1166(0);
#ifdef DEBUG
	printf("min_seq = %d\n", min_seq);
#endif
	for (i = 0; i < min_seq; i++){
		printf("%d ", min_solution[i]);
	}
	printf("\n");
	return 0;
}

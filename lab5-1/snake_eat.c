#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define HEAD 'H'
#define BODY 'X'
#define BLANK ' '
#define FOOD '$'
#define WALL '*'

#define REP(i, a, b) for (i = (a); i <= (b); ++i)
#define DWN(i, a, b) for (i = (a); i >= (b); --i)

const int N = 12; // 图边长 
const int MAX_LEN = 20; // 蛇最大总长 

char map[13][13]; // 图 
int dx[5] = {0, 0, 0, -1, 1}; 
int dy[5] = {0, -1, 1, 0, 0}; // 分别表示A，D，W，S 
int x_snake[22], y_snake[22]; // 蛇每个部分的位置 
int len_snake; //当前蛇长 

void pre_build(); // 预建 

void snake_Move(int move_typ); // move_typ ：移动类型 
void creat_new_food(); // 随机产生新食物 
void show(); // 打印图 
void gameover(); // 打印游戏结束 
int gameover_check(); //判断游戏是否结束 

int main()
{
	srand(time(NULL)); //设置初始随机种子 
    pre_build();
    show();
    while (!gameover_check()) //游戏是否继续进行 
    {
        char ch = getchar(); // 读入命令 
        switch (ch)
        {
	        case 'A': snake_Move(1); break ;
   	    	case 'D': snake_Move(2); break ;
        	case 'W': snake_Move(3); break ;
        	case 'S': snake_Move(4); break ;
        }
        system("cls"); // 清屏 
        show();
    }
	gameover(); //游戏结束 
    return 0;
}

void pre_build()
{
	int i; 
    REP(i, 1, N) 
        map[1][i] = map[N][i] = WALL,
        map[i][1] = map[i][N] = WALL,
        map[i][N+1] = '\n';
    //设置初始图 
        
    REP(i, 6, 7) map[5][i] = map[7][i] = map[9][i] = '$';
    REP(i, 5, 8) map[6][i] = map[8][i] = '$';
    //设置初始食物阵 
    
    len_snake = 5; 
    REP(i, 1, len_snake) 
        x_snake[i] = 2,
        y_snake[i] = 6-i+1,
    //设置初始蛇的位置 
    
    map[x_snake[1]][y_snake[1]] = HEAD;
    REP(i, 2, len_snake)
        map[x_snake[i]][y_snake[i]] = BODY;
    //在图上把蛇显示出来 
}

void show() // 打印当前图 
{
	int i, j; 
    REP(i, 1, N)
        REP(j, 1, N+1)
            printf("%c", map[i][j]);
}

void creat_new_food()
{
	int tx, ty;
	do
	{
		tx = rand()%10+1;
		ty = rand()%10+1;
	}while(map[tx+1][ty+1] != BLANK); // 保证把食物生成在空处 
	map[tx+1][ty+1] = FOOD;
}

void snake_Move(int move_typ) 
{
	int i;
	int t_x = x_snake[1] + dx[move_typ];
	int t_y = y_snake[1] + dy[move_typ];
	//t_x和t_y：蛇头移动后的位置 
	
	// 更新蛇的图上信息 
	if (map[t_x][t_y] != FOOD && len_snake < MAX_LEN) 
		map[x_snake[len_snake]][y_snake[len_snake]] = BLANK; // 蛇尾设为空 
	map[x_snake[1]][y_snake[1]] = BODY; //蛇头变成蛇身 
	if (map[t_x][t_y] == FOOD && len_snake < MAX_LEN) //头吃到食物，蛇长一节 
	{
		len_snake ++; //蛇变长 
		creat_new_food(); //生成新的食物 
	}
	map[t_x][t_y] = HEAD; // 设置新蛇头 
	
	    
    // 更新蛇的位置信息 
    DWN(i, len_snake, 2) //蛇身的位置等于它前一部分的位置 
    {
        x_snake[i] = x_snake[i-1];
        y_snake[i] = y_snake[i-1];
    }
    x_snake[1] += dx[move_typ];
    y_snake[1] += dy[move_typ];
}

int gameover_check() // 检查当前游戏状态 
{
	int i, j;
    REP(i, 2, len_snake)
        REP(j, 1, i-1)
            if (x_snake[i] == x_snake[j]
             && y_snake[i] == y_snake[j]) // 头撞到身体 
                return 1;
	REP(i, 1, len_snake)
		if (x_snake[i] <= 1 || y_snake[i] <= 1
		 || x_snake[i] >= 12  || y_snake[i] >= 12) //头撞到边界 
			return 1;
    return 0;
}

void gameover() //游戏结束 
{ 
    system("cls");
    puts("Game Over!!!!"); 
}


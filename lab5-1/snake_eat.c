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

const int N = 12; // ͼ�߳� 
const int MAX_LEN = 20; // ������ܳ� 

char map[13][13]; // ͼ 
int dx[5] = {0, 0, 0, -1, 1}; 
int dy[5] = {0, -1, 1, 0, 0}; // �ֱ��ʾA��D��W��S 
int x_snake[22], y_snake[22]; // ��ÿ�����ֵ�λ�� 
int len_snake; //��ǰ�߳� 

void pre_build(); // Ԥ�� 

void snake_Move(int move_typ); // move_typ ���ƶ����� 
void creat_new_food(); // ���������ʳ�� 
void show(); // ��ӡͼ 
void gameover(); // ��ӡ��Ϸ���� 
int gameover_check(); //�ж���Ϸ�Ƿ���� 

int main()
{
	srand(time(NULL)); //���ó�ʼ������� 
    pre_build();
    show();
    while (!gameover_check()) //��Ϸ�Ƿ�������� 
    {
        char ch = getchar(); // �������� 
        switch (ch)
        {
	        case 'A': snake_Move(1); break ;
   	    	case 'D': snake_Move(2); break ;
        	case 'W': snake_Move(3); break ;
        	case 'S': snake_Move(4); break ;
        }
        system("cls"); // ���� 
        show();
    }
	gameover(); //��Ϸ���� 
    return 0;
}

void pre_build()
{
	int i; 
    REP(i, 1, N) 
        map[1][i] = map[N][i] = WALL,
        map[i][1] = map[i][N] = WALL,
        map[i][N+1] = '\n';
    //���ó�ʼͼ 
        
    REP(i, 6, 7) map[5][i] = map[7][i] = map[9][i] = '$';
    REP(i, 5, 8) map[6][i] = map[8][i] = '$';
    //���ó�ʼʳ���� 
    
    len_snake = 5; 
    REP(i, 1, len_snake) 
        x_snake[i] = 2,
        y_snake[i] = 6-i+1,
    //���ó�ʼ�ߵ�λ�� 
    
    map[x_snake[1]][y_snake[1]] = HEAD;
    REP(i, 2, len_snake)
        map[x_snake[i]][y_snake[i]] = BODY;
    //��ͼ�ϰ�����ʾ���� 
}

void show() // ��ӡ��ǰͼ 
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
	}while(map[tx+1][ty+1] != BLANK); // ��֤��ʳ�������ڿմ� 
	map[tx+1][ty+1] = FOOD;
}

void snake_Move(int move_typ) 
{
	int i;
	int t_x = x_snake[1] + dx[move_typ];
	int t_y = y_snake[1] + dy[move_typ];
	//t_x��t_y����ͷ�ƶ����λ�� 
	
	// �����ߵ�ͼ����Ϣ 
	if (map[t_x][t_y] != FOOD && len_snake < MAX_LEN) 
		map[x_snake[len_snake]][y_snake[len_snake]] = BLANK; // ��β��Ϊ�� 
	map[x_snake[1]][y_snake[1]] = BODY; //��ͷ������� 
	if (map[t_x][t_y] == FOOD && len_snake < MAX_LEN) //ͷ�Ե�ʳ��߳�һ�� 
	{
		len_snake ++; //�߱䳤 
		creat_new_food(); //�����µ�ʳ�� 
	}
	map[t_x][t_y] = HEAD; // ��������ͷ 
	
	    
    // �����ߵ�λ����Ϣ 
    DWN(i, len_snake, 2) //�����λ�õ�����ǰһ���ֵ�λ�� 
    {
        x_snake[i] = x_snake[i-1];
        y_snake[i] = y_snake[i-1];
    }
    x_snake[1] += dx[move_typ];
    y_snake[1] += dy[move_typ];
}

int gameover_check() // ��鵱ǰ��Ϸ״̬ 
{
	int i, j;
    REP(i, 2, len_snake)
        REP(j, 1, i-1)
            if (x_snake[i] == x_snake[j]
             && y_snake[i] == y_snake[j]) // ͷײ������ 
                return 1;
	REP(i, 1, len_snake)
		if (x_snake[i] <= 1 || y_snake[i] <= 1
		 || x_snake[i] >= 12  || y_snake[i] >= 12) //ͷײ���߽� 
			return 1;
    return 0;
}

void gameover() //��Ϸ���� 
{ 
    system("cls");
    puts("Game Over!!!!"); 
}


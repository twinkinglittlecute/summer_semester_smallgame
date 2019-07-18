#include <Windows.h>
#include "LinkList.h"

// 蛇的状态
#define SNAKE_MOVED			0
#define SNAKE_DEAD			1
#define SNAKE_COMPLETE		2
#define SNAKE_EATEN_FOOD	3
#define SNAKE_GROWUP		4
#define SNAKE_ERROR			5

// 蛇的方向
typedef enum _dirction
{
	SNAKE_UP,
	SNAKE_DOWN,
	SNAKE_LEFT,
	SNAKE_RIGHT,
}dirction;//方向，是一个枚举类型，用很多常量代表游戏的不同数据       zbjk

// 游戏坐标
typedef struct _GAME_COORD
{
	short x;
	short y;
}GAME_COORD, *PGAME_COORD;

// 函数声明

/// snake_and_food.c中的接口函数

// 设置边界坐标
void SetBoundary(int x, int y);

// 获得边界坐标
PGAME_COORD GetBoundary();

// 生成新的食物。
int CreateFood();

// 分别获得食物的坐标。
PGAME_COORD GetFood1();
PGAME_COORD GetFood2();
//生成新的毒药。
int CreateDrug();
//分别获得毒药的坐标。
PGAME_COORD GetDrug1();
PGAME_COORD GetDrug2();
PGAME_COORD GetDrug3();
PGAME_COORD GetDrug4();
PGAME_COORD GetDrug5();
PGAME_COORD GetDrug6();
PGAME_COORD GetDrug7();
PGAME_COORD GetDrug8();
PGAME_COORD GetDrug9();
PGAME_COORD GetDrug10();
PGAME_COORD GetDrug11();
PGAME_COORD GetDrug12();
PGAME_COORD GetDrug13();
PGAME_COORD GetDrug14();
PGAME_COORD GetDrug15();
PGAME_COORD GetDrug16();
PGAME_COORD GetDrug17();
PGAME_COORD GetDrug18();



// 创建蛇
void CreateSnake(dirction dir, int head_x, int head_y, int init_len);

// 销毁蛇，释放内存资源。
void DistroySnake();

// 用来移动一步，
// 移动以后，如果吃到了食物，则生长。
// 如果碰到了墙或者自己，则死亡，并返回是否死亡的状态。
int SnakeMove();

// 蛇生长
int SnakeGorwup();

// 获得蛇的长度
int GetSnakeSize();

// 获得蛇的第一个节点的坐标
PGAME_COORD GetSnakeHead();

// 获得蛇的最后一个节点的坐标
PGAME_COORD GetSnakeTail();

// 按照序号获得蛇的节点的坐标，不能超过蛇的长度，否则返回NULL
PGAME_COORD GetSnakeAt(int n);

// 改变蛇移动的方向
void SetDirction(dirction dir);

// 获得当前蛇的方向
dirction GetDirction();




/// game_opration.c 中的接口函数

int GetScore();//获得分数   zbj
int GetLevel();//获得水平   zbj
void CreateGame(HWND hwnd,
	DWORD dwInitTimerElapse,
	unsigned int one_level_scores,
	DOUBLE level_speedup_ratio,
	int boundary_x, int boundary_y,
	int init_x, int init_y,
	int init_len,
	dirction init_dir);//创建游戏开始   zbj 
void OnTimer(HWND hwnd);//启动计时器    zbj
void OnKeyDown(DWORD vk);//启动键盘     zbj
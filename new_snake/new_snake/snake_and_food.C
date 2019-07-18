/********************************************************************************
* ##########  谈谈封装 ##########
* “封装”是程序不会乱掉的一个重要技能。
* 我们要写出结构化、易于阅读、理解和维护的代码。采用封装是比较容易掌握的方法。
*
* 具体而言：
*
* 1、先考虑好这个程序的逻辑和状态需要多少数据来表示，
* 比如这个贪吃蛇游戏，我们使用这些数据就可以表示全部游戏状态。
* // 食物
* GAME_COORD food;
* // 蛇（链表）
* PLIST snake_list;
* // 蛇移动方向
* dirction snake_dir;
* // 游戏边界（这是右下，左上为0,0）
* GAME_COORD boundary;
*
* 2、写出一系列接口函数来操作这些数据。所谓接口函数，满足一下几个特征：
* (1) 这些数据除了接口函数以外，其他代码都不会直接访问。
* (2) 所有其他代码都只能通过调用这些接口函数来改变程序的状态，而不要直接去访问数据。
* 如本文件的若干函数都是对上述数据的操作。

* 这样实现了：对于上层代码，并不需要知道数据的操作逻辑，也不需要知道数据结构，而只需要调用函数即可。
* 对上次代码而言，逻辑简单了很多。
* 同样，如果数据结构和内部逻辑有了修改，那么可以做到接口函数的原型不变，
* 上层代码不变，而只需要修改接口函数的内部实现过程即可。
*
* 这就称之为“封装”，或者称之为 “数据的封装和接口化”
*
*******************************************************************************/



/************** 头文件 ****************/
#include "snake.h"

/************* 全局变量 ****************/ //游戏所需所有全局变量  
// 食物
PGAME_COORD food[2];
//毒药
PGAME_COORD drug[18];
// 蛇（链表）
PLIST snake_list;
// 蛇移动方向
dirction snake_dir;
// 游戏边界（这是右下，左上为0,0）
GAME_COORD boundary;

/*********** 内部函数申明 **************/
/// 判断两个坐标是否相等。
int CoordEqual(PGAME_COORD one, PGAME_COORD two);
/// 判断蛇是否已死
int IsSnakeDead();

/**************函数定义****************/


// 判断两个坐标 GAME_COORD 是否重合
int CoordEqual(PGAME_COORD one, PGAME_COORD two)
{
	if (one->x == two->x && one->y == two->y)//坐标一号与二号是不是坐标相等，如果相同就相当于蛇咬了自己的尾巴 zbj
		return 1;
	return 0;
}

// 设置边界坐标
void SetBoundary(int x, int y)
{
	boundary.x = x;
	boundary.y = y;
}

// 获得边界坐标
PGAME_COORD GetBoundary()
{
	return &boundary;//以指针传递边界（边界右下角坐标）zbj
}

// 生成新的食物。
int CreateFood()
{
	PGAME_COORD posbody;//定义食物坐标 zbj//设置一个坐标体系 先忽略像素点的影响
	int i,j;//循环计数器 zbj
	int size = ListSize(snake_list);//获取蛇的长度，boundary是最右下角的点
	food[0] = (PGAME_COORD)malloc(sizeof(PGAME_COORD));
	food[1] = (PGAME_COORD)malloc(sizeof(PGAME_COORD));
new_food://有点像python

	// 随机生成食物的坐标。
	food[0]->x = rand() % boundary.x;//是为了保证获取的位置在窗口内部，因为有可能生成的数比窗口范围大 zbj
	food[0]->y= rand() % boundary.y;//%常用在取特定范围的随机数，保证余数是平均分布的 ，%100，则余数的范围是0-99
	food[1]->x = rand() % boundary.x;
	food[1]->y = rand() % boundary.y;

	// 判断是否和蛇重叠了，否则重新生成食物坐标，知道不重叠。

	for (i = 0; i < size; i++)//循环读取蛇链表节点的数据 zbj//取蛇的每个结点的坐标   zbjk
	{
		posbody = (PGAME_COORD)ListGetAt(snake_list, i);//读取的数据结果是这个节点当前的坐标 zbj
		for (j = 0; j < 2; j++) {
			if (CoordEqual(posbody, food[j]))//如果食物的坐标与读取节点的坐标相等，那么就重新生成食物的坐标 zbj
			{
				goto new_food;//非常古老的语法，易影响,后面跟了定义了一个标签（或者说位置），就会跳转回去执行标签，类似循环的功能 zbj
			}//查goto的用法    zbj//只要与蛇身的任意位置重复，就重新生成
		}
	}
	return 1;//93--100是在判断食物是不是在蛇的身上，如果重合就生成一个新的食物位置 zbj

}
//生成新的毒药。

int CreateDrug()
{
	PGAME_COORD posbody;//定义毒药坐标 zbj//设置一个坐标体系 先忽略像素点的影响
	int i, j,k;//循环计数器 zbj
	int size = ListSize(snake_list);//获取蛇的长度，boundary是最右下角的点
	for (i = 0; i < 18; i++)
	{
		drug[i] = (PGAME_COORD)malloc(sizeof(PGAME_COORD));
		
	}
	new_drug://有点像python

		// 随机生成毒药的坐标。
	for (i = 0; i < 18; i++)
	{
		drug[i]->x = rand() % boundary.x;//是为了保证获取的位置在窗口内部，因为有可能生成的数比窗口范围大 zbj
		drug[i]->y = rand() % boundary.y;//%常用在取特定范围的随机数，保证余数是平均分布的 ，%100，则余数的范围是0-99
		
	}
	// 判断是否和蛇重叠了，否则重新生成毒药坐标，知道不重叠。

	for (k = 0; k < 18; k++)//循环读取蛇链表节点的数据 zbj//取蛇的每个结点的坐标   zbjk
	{
		
		for (j = 0; j < 2; j++)
		{
			for (i = 0; i < size; i++)//循环读取蛇链表节点的数据 zbj//取蛇的每个结点的坐标   zbjk
			{
				posbody = (PGAME_COORD)ListGetAt(snake_list, i);//读取的数据结果是这个节点当前的坐标 zbj
				if (CoordEqual(posbody, drug[k]) || CoordEqual(food[j],drug[k]))//如果食物的坐标与读取节点的坐标相等，那么就重新生成食物的坐标 zbj
				{
					goto new_drug;//非常古老的语法，易影响,后面跟了定义了一个标签（或者说位置），就会跳转回去执行标签，类似循环的功能 zbj
				}//查goto的用法    zbj//只要与蛇身的任意位置重复，就重新生成
			}
		}
	}
		return 1;//是在判断毒药是不是在蛇的身上，如果重合就生成一个新的毒药位置 zbj

	}


// 分别获得两个食物的坐标。
PGAME_COORD GetFood1()
{
	return food[0];//返回食物的指针 zbj
}
PGAME_COORD GetFood2()
{
	return food[1];//返回食物的指针 zbj
}
//分别获得两颗毒药的坐标。
PGAME_COORD GetDrug1()
{
	return drug[0];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug2()
{
	return drug[1];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug3()
{
	return drug[2];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug4()
{
	return drug[3];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug5()
{
	return drug[4];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug6()
{
	return drug[5];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug7()
{
	return drug[6];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug8()
{
	return drug[7];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug9()
{
	return drug[8];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug10()
{
	return drug[9];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug11()
{
	return drug[10];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug12()
{
	return drug[11];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug13()
{
	return drug[12];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug14()
{
	return drug[13];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug15()
{
	return drug[14];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug16()
{
	return drug[15];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug17()
{
	return drug[16];//返回毒药的指针 zbj
}

PGAME_COORD GetDrug18()
{
	return drug[17];//返回毒药的指针 zbj
}
// 创建蛇
void CreateSnake(dirction dir, int head_x, int head_y, int init_len)//蛇初始方向，初始位置，初始长度。为什么不传每个节点呢，其实可以算出节点位置，初始化不要撞到墙
{//逐一添加节点
	PGAME_COORD p;//初始化蛇头位置坐标 zbj
	int i;//循环计数器 zbj

	SetDirction(dir);//根据要求设定蛇的初始方向 zbj

	snake_list = ListCreate(NULL);//创建一个新的链表snake_list????? zbj

	p = (PGAME_COORD)malloc(sizeof(GAME_COORD));//给p分配内存 zbj
	// 蛇头部的初始位置；
	p->x = head_x;//将参数头节点的位置传入蛇头的初始位置，做了一个循环 zbj
	p->y = head_y;
	ListPushFront(snake_list, p);//把p放到链表snake_list中   zbjk//实现了蛇的头节点??????的建立，头节点下一个节点的数据域是蛇头部的位置?????  zbj

	for (i = 1; i < init_len; i++)//如果蛇的节点长度大于等于0，就增加蛇的长度，至少设定增长的方向  zbj
	{
		//p = (PGAME_COORD)malloc(sizeof(GAME_COORD));
		SnakeGorwup();//蛇生长的函数
	}
	return;
}

// 判断蛇是否死了。
// 返回0 蛇没有死 else 蛇死了。
int IsSnakeDead()//需要引入边界
{
	PGAME_COORD posBody;//两个位置指针  zbj
	PGAME_COORD posHead;

	int i;
	int size = ListSize(snake_list);//获取蛇链表的长度  zbj

	// 判断是否死亡
	/// 碰到墙不死亡，改坐标
	posHead = (PGAME_COORD)ListGetAt(snake_list, 0);//取蛇链表的头节点的位置指针  zbj
	size = ListSize(snake_list);////获取蛇链表的长度  zbj
	if (posHead->x < 0 || posHead->x > boundary.x ||
		posHead->y < 0 || posHead->y > boundary.y)//是不是头的位置小于0或大于边界  x,y任何超过边界 zbj
	{//要修改全部节点的位置

		if (posHead->x < 0)//从左穿墙，改节点坐标从右穿入
			for (i = 0; i < size; i++)
			{
				posBody = (PGAME_COORD)ListGetAt(snake_list, i);//取蛇链表的第i个节点的位置指针   zbj
				posBody->x = boundary.x - ListSize(snake_list) + 1+i;
			}
			
		if (posHead->x > boundary.x)//从右穿墙，改节点坐标从左穿入
			for (i = 0; i < size; i++)
			{
				posBody = (PGAME_COORD)ListGetAt(snake_list, i);
				posBody->x = ListSize(snake_list) - 1 - i;
			}
			
		if (posHead->y < 0)//从上穿墙，改节点坐标从下穿入
			for (i = 0; i < size; i++)
			{
				posBody = (PGAME_COORD)ListGetAt(snake_list, i);
				posHead->y = boundary.y - ListSize(snake_list) + 1 + i;
			}
		if (posHead->y > boundary.y)//从下穿墙，改节点坐标从上穿入
			for (i = 0; i < size; i++)
			{
				posBody = (PGAME_COORD)ListGetAt(snake_list, i);
				posHead->y = ListSize(snake_list) -1-i;
			}
	}
	
	/// 判断是否碰到自己
	//// 从第二个节点开始，逐一和头节点比较。
	size = ListSize(snake_list);////获取蛇链表的长度  zbj

	for (i = 1; i < size; i++)
	{
		posBody = (PGAME_COORD)ListGetAt(snake_list, i);//取蛇链表的第i个节点的位置指针   zbj
		if (CoordEqual(posHead, posBody))//检测碰撞的函数   //如果任何一个节点与头节点发生碰撞相当于蛇死了自己   zbj
		{
			return SNAKE_DEAD;//返回蛇死   zbj
		}
	}
	//是否吃到毒药
	for (i = 0; i < 18; i++)
	{
		if (CoordEqual(posHead, drug[i]))//蛇头是否与食物发生碰撞      zbj
		{
			return SNAKE_DEAD;//返回蛇死   zbj

		}
	}

	return SNAKE_MOVED;//上述两种情况都没发生，蛇可以正常移动 zbj
}

// 销毁蛇，释放内存资源。
void DistroySnake()
{
	ListDistoryAndFree(snake_list);
	return;
}

// 用来移动一步，
// 移动以后，如果吃到了食物，则生长。
// 如果碰到了墙或者自己，则死亡，并返回是否死亡的状态。
int SnakeMove()
{
	// 头和尾的坐标
	PGAME_COORD posHead;
	PGAME_COORD posTail;

	// 把尾从链表中取出，按照当前方向放置到头的位置。
	posHead = (PGAME_COORD)ListGetAt(snake_list, 0);//获得链表中头节点的位置  zbj
	posTail = (PGAME_COORD)ListPopBack(snake_list);

	// 根据当前方向来设定新的头坐标。
	switch (snake_dir)
	{//
	case SNAKE_UP://如果向上，头节点位置向上     zbj
		posTail->y = posHead->y - 1;
		posTail->x = posHead->x;
		break;
	case SNAKE_DOWN://如果向下，头节点位置向下   zbj
		posTail->y = posHead->y + 1;
		posTail->x = posHead->x;
		break;
	case SNAKE_LEFT://如果向左，头节点位置向左   zbj
		posTail->x = posHead->x - 1;
		posTail->y = posHead->y;
		break;
	case SNAKE_RIGHT://如果向右，头节点位置向右   zbj
		posTail->x = posHead->x + 1;
		posTail->y = posHead->y;
		break;
	}
	ListPushFront(snake_list, posTail);//把蛇链表新的头部节点的data（蛇头位置）加到蛇头   zbj

	// 判断是否吃到了食物
	if (CoordEqual(posHead, food[0])|| CoordEqual(posHead, food[1]))//蛇头是否与食物发生碰撞      zbj
	{
		return SNAKE_EATEN_FOOD;//定义了宏
	}

	// 如果没有吃到食物判断是否撞到障碍，然后返回状态。
	return IsSnakeDead();
}

// 蛇生长
int SnakeGorwup()//在蛇的尾巴追加一个节点
{
	// 给新的节点分配内存
	PGAME_COORD pNewTail;//定义三个指针，这是新节点的指针   
	PGAME_COORD pTail;		// 倒数第一节点  
	PGAME_COORD pLastButOne;	// 倒数第二节点    
	int size = GetSnakeSize();//获取蛇的长度 zbj

	if (size >= boundary.x*boundary.y - 1) //长到最长了，游戏结束！~//蛇的长度超过了边界的最大限度 zbj
		return SNAKE_COMPLETE;//返回游戏完成

	if (size == 0) // 没有头，不知从何生长，返回错误。
		return SNAKE_ERROR;
	//产生新的蛇尾巴

	pNewTail = (PGAME_COORD)malloc(sizeof(GAME_COORD));//分配内存，把内存存到指针
	if (size == 1) // 只有一个节点，按照当前的移动方向生长。
	{

		pTail = (PGAME_COORD)GetSnakeTail();//计算新节点的位置，需要把倒数第一个节点的位置拿到
		switch (snake_dir)
		{
		case SNAKE_LEFT://本身是向左，增长的话是右边 zbj
			pNewTail->x = pTail->x + 1;
			pNewTail->y = pTail->y;
			break;
		case SNAKE_RIGHT://本身是向右，增长的话是左边 zbj
			pNewTail->x = pTail->x - 1;
			pNewTail->y = pTail->y;
			break;
		case SNAKE_UP://本身是向上，增长的话是下边  zbj
			pNewTail->x = pTail->x;
			pNewTail->y = pTail->y + 1;
			break;
		case SNAKE_DOWN://本身是向下，增长的话是上边  zbj
			pNewTail->x = pTail->x;
			pNewTail->y = pTail->y - 1;
			break;
		}

	}
	else // 有两个以上节点，取倒数第一和倒数第二计算生长方向。
	{
		pTail = (PGAME_COORD)GetSnakeTail();//取蛇链表最后一个节点的位置指针  zbj
		pLastButOne = (PGAME_COORD)GetSnakeAt(size - 2);//取蛇链表倒数第二个节点的位置指针  zbj 
		// 沿着倒数第二->倒数第一的方向，添加一个新的节点。
		pNewTail->x = pTail->x + (pTail->x - pLastButOne->x);//方向问题画图可知 zbj
		pNewTail->y = pTail->y + (pTail->y - pLastButOne->y);

	}//前面都是算位置  zbj

	// 新节点放入到蛇尾的位置
	ListPushBack(snake_list, pNewTail);//把数据放入链表尾   zbjk
	return SNAKE_GROWUP;//标志蛇生长成功  zbj

}

// 获得蛇的长度
int GetSnakeSize()
{
	return ListSize(snake_list);//返回蛇链表的长度大小
}

// 获得蛇的第一个节点的坐标
PGAME_COORD GetSnakeHead()
{
	return (PGAME_COORD)ListGetAt(snake_list, 0);
}

// 获得蛇的最后一个节点的坐标
PGAME_COORD GetSnakeTail()
{
	return (PGAME_COORD)ListGetAt(snake_list, GetSnakeSize() - 1);//以指针的形式把蛇链表的最后一个节点返回 zbj
}

// 按照序号获得蛇的节点的坐标，不能超过蛇的长度，否则返回NULL
PGAME_COORD GetSnakeAt(int n)//参数是序号 zbj
{
	if (n < ListSize(snake_list))//当序号不超过蛇的长度时 zbj
		return (PGAME_COORD)ListGetAt(snake_list, n);//以指针的形式返回蛇链表的指定节点
	else
		return NULL;

}

// 改变蛇移动的方向
void SetDirction(dirction dir)
{
	//避免原地掉头（自杀），相当于按了也白按
	switch (snake_dir)//如果键盘对蛇的移动方向是与蛇当前的移动方向相反的，那么就return NULL，不改变蛇的移动方向，如果不是这种情况，就将蛇的方向改为键盘所传递的方向 zbj
	{
	case SNAKE_UP:
		if (dir == SNAKE_DOWN)
			return;
		break;
	case SNAKE_DOWN:
		if (dir == SNAKE_UP)
			return;
		break;
	case SNAKE_LEFT:
		if (dir == SNAKE_RIGHT)
			return;
		break;
	case SNAKE_RIGHT:
		if (dir == SNAKE_LEFT)
			return;
		break;
	}
	snake_dir = dir;//改变全局变量蛇的方向   zbj//赋值给全局变量   zbjk
}


// 获得当前蛇的方向
dirction GetDirction()
{
	return snake_dir;//返回全局变量
}
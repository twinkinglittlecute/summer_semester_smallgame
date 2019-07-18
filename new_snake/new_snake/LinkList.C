/************************************************************************

单链表

FUNCTIONS :
ListCreate			- 创建一个新的链表。
ListInsertAt			- 插入节点到链表。
ListPushFront		- 在链表头部插入节点。
ListPushBack			- 在链表尾部插入节点。
ListPopFront			- 删除链表头部节点。
ListPopBack			- 删除链表尾部节点。
ListGetFront			- 获得第一个节点
ListGetBack			- 获得最后一个节点。
ListGetNodeAt		- 根据序号获得节点。
ListDeleteNodeAt		- 根据序号删除节点。
ListDestroy			- 删除整个链表。
ListDestroyAndFree	- 删除整个链表，并释放数据。
ListClear			- 删除链表中的所有节点。
ListClearAndFree		- 清除链表中的所有节点，并释放数据。
ListGetSize			- 获得当前链表大小（节点数量）。


************************************************************************/
#include <stdlib.h> // 使用到了malloc(), free()等函数。
#include "LinkList.h"


// 创建一个链表节点
PNODE NodeCreate(void* data)//参数是任意类型的数据 zbj
{
	PNODE pnode = (PNODE)malloc(sizeof(NODE));//创建一个新节点指针并分配内存 zbj
	pnode->data = data; //结点指针的数据域是传入的参数 zbj
	pnode->next = 0;//节点指针的next域是NULL zbj
	return pnode;//返回这个节点指针 zbj
}

// 销毁链表节点及其数据。
void NodeDistory(PNODE node)
{
	free(node->data);
	free(node);
}

// 获得链表的大小（节点数量）。
int ListSize(PLIST list)
{
	int  cnt;//设置计数器zbj
	PNODE node = list->first;//定义一个新节点指向表的第一个节点zbj

	cnt = 0;//计数器初始化为0 zbj
	while (node)//当节点不为空时 zbj
	{
		cnt++;//计数器加1zbj
		node = node->next;//指向下一个节点zbj
	}
	return (cnt);//返回节点数zbj
}

// 删除链表中特定位置的节点，并返回数据。
// 返回 -1 表示错误，
// 返回 >= 表示插入的位置。
int ListInsertAt(PLIST list, unsigned int n, void* data)
{
	unsigned int  i;
	PNODE tmp;
	PNODE prev;
	PNODE new_node;

	if (n < 0)
		return -1;
	if (n == 0)
	{
		ListPushFront(list, data);
		return 0;
	}
	i = 1;
	tmp = list->first;
	prev = tmp;
	while (i < n)
	{
		prev = tmp;
		tmp = tmp->next;
		if (!tmp)//说明n越界了
			return -1;
		++i;
	}
	//断链表操作   zbjk
	new_node = NodeCreate(data);
	prev->next = new_node;
	new_node->next = tmp->next;//插入完成
	return i;
}


// 删除链表中特定位置的节点，并返回数据。
void* ListDeleteAt(PLIST list, int n)
{
	int  i;
	PNODE tmp;
	PNODE prev;

	tmp = list->first;
	prev = tmp;
	if (n < 1)
		return (NULL);
	if (n == 0)
	{
		return ListPopFront(list);
	}
	i = 1;

	while (i < n)
	{
		prev = tmp;
		tmp = tmp->next;//寻找要删除的节点   zbj
		if (!tmp)
			return (NULL);
		++i;
	}
	prev->next = tmp->next;//  删除该节点    zbj
	return (tmp->data);//返回该节点的诗句    zbj
}


// 获得指定位置上节点中的数据。
void* ListGetAt(PLIST list, unsigned int n)//参数是一个列表，一个unsighed整数(是指定节点的序号) zbj
{
	unsigned int   i;//循环计数器 zbj
	PNODE node = list->first;//生成一个节点指向列表的头节点 zbj

	if (!node)//如果头节点为空，返回NULL zbj
		return (NULL);

	for (i = 1; i <= n; i++)//如果没有到这个节点序号，就继续寻找下一个节点 zbj
	{
		node = node->next;
		if (!node)//如果还未找到这个节点就为空了，那么返回NULL zbj
			return (NULL);
	}
	return (node->data);//否则就返回这个节点的数据 zbj
}

// 创建链表。
PLIST ListCreate(void* list_data)//创建表示蛇的链表，函数中的参数（链表中的数据域）是任意类型的 zbj
{
	PLIST new_list;//初始化一个新链表 zbj

	new_list = NULL;//设新链表为空 zbj
	new_list = (PLIST)malloc(sizeof(LIST));//给新链表分配内存
	if (new_list != NULL)//!!!!!!
	{
		new_list->list_data = list_data;//通常指向NULL，创建的链表头并没有数据
		new_list->first = NULL;
	}
	return (new_list);//返回新链表
}

// 只释放链表头，而不释放其他。
void ListDistory(PLIST list)
{
	if (list != NULL)
	{
		if (list->list_data != NULL)
			free(list->list_data);
		free(list);
	}
}

// 释放整个链表及其所有节点和数据
void ListDistoryAndFree(PLIST list)
{
	if (list != NULL)//当蛇链表不为空时  zbj
	{
		ListClearAndFree(list);
		if (list->list_data != NULL) //当头节点的指针域不为空时  zbj
			free(list->list_data);//释放指针域 zbj
		free(list);//释放内存  zbj
	}
}

// 获取链表头的数据，并从链表中删除。
void* ListPopFront(PLIST list)
{
	PNODE tmp;
	void*  data = NULL;
	if (list != NULL)
	{
		if (list->first != NULL)//链表节点的删除操作   zbj
		{
			tmp = list->first;
			data = tmp->data;
			list->first = tmp->next;
			free(tmp);
		}
	}
	return (data); //返回头节点的数据   zbj
}

// 获取链表尾的数据，并从链表中删除。
void* ListPopBack(PLIST list)//参数为链表，返回值是任意类型的指针  zbj
{
	PNODE prev;//创建
	PNODE current;//创建
	PNODE node = list->first;//创建节点指向头节点   zbj
	void* data;//任意类型数据(就是用来记录表尾的位置)   zbj

	if (!node)//头节点为空   zbj
		return (NULL);//返回NULL   zbj
	if (!(node)->next)//当头节点的下一个节点为空    zbj
	{
		data = (node)->data;//数据为头节点数据（可能是蛇头位置） ！！！ zbj   
		free(node);//释放头节点空间
		node = NULL;
		return (data);//返回头节点数据（可能是蛇头位置)！！！    zbj
	}
	prev = node;//prev指向当前节点   zbj
	current = (node)->next;//current指向当前节点的下一个节点 zbj
	while (current->next)//current节点的下一个节点不为空，说明current节点不为尾部。循环找尾部   zbj
	{
		prev = current;//循环找尾部  zbj
		current = current->next;
	}
	data = current->data;//尾部节点的数据域（尾节点位置） 循环找尾部
	free(current);//释放尾节点空间 循环找尾部
	prev->next = NULL;//尾节点的上一个节点指向空，相当于删除尾节点   循环找尾部
	return (data);//返回尾部节点的数据域（尾节点位置）
}

// 加入数据到链表尾部。
void ListPushBack(PLIST list, void* data)//参数是相应链表和任意形式的数据（一般是最后一个结点的位置指针） zbj
{
	PNODE tmp;//创建一个节点指针 zbj
	PNODE new_node = NodeCreate(data);//创建一个链表节点并附上数据（位置） zbj 

	if (new_node)//如果节点不为空 zbj
	{
		if (list)//且列表不为空 zbj
		{
			if (list->first)//当头节点不为空时  zbj
			{
				tmp = list->first;//用节点指针指向头节点  zbj
				while (tmp->next)//当头节点的下一个节点不为空时  zbj
					tmp = tmp->next;//继续向下寻找直到找到空节点为止，即temp指向尾节点  zbj
				tmp->next = new_node;//在尾节点处接上新建节点 zbj
			}
			else//当头节点为空时，直接在链表的头节点后面接上新建节点 zbj
				list->first = new_node;
		}
	}
}

// 加入数据到链表头部。
void ListPushFront(PLIST list, void* data)//为什么用头插法?????
{
	PNODE new_node;//初始化一个新节点指针 zbj

	if (list != NULL)//如果新链表不为空 zbj
	{
		new_node = NodeCreate(data);//创建一个链表节点,并把data附进去 zbj
		if (new_node != NULL)//如果新节点指针不为空的话 zbj
		{
			new_node->next = list->first;//采用头插法将他们插入链表中 zbj
			list->first = new_node;
		}
	}
}


// 删除链表所有节点，free数据。
void ListClearAndFree(PLIST list)
{
	PNODE tmp;//初始化两个节点  zbj
	PNODE node;

	if (list != NULL)//当蛇链表不为空时   zbj
	{
		node = list->first;//指向头节点  zbj
		while (node)//当节点不为空    zbj
		{
			tmp = node->next;//创建新指针指向下一个节点  zbj
			NodeDistory(node);//删除该节点
			node = tmp;//以下一个节点为起始
		}
		list->first = 0;//使头节点为空
	}
}
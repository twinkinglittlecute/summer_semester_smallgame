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
ListGetAt			- 根据序号获得节点。
ListDeleteAt			- 根据序号删除节点。
ListClear			- 删除链表中的所有节点。
ListClearAndFree		- 清除链表中的所有节点，并释放数据。
ListDestroy			- 删除整个链表。
ListDestroyAndFree	- 删除整个链表，并链表中的全部释放。
ListSize				- 获得当前链表大小（节点数量）。


************************************************************************/

#ifndef LIST_H
#define LIST_H

typedef struct _NODE//定义链表节点  zbjk
{
	void* data;//实际上真正存储数据的是data,各种各样类型的数据都可以用这个链表来保存，因为void表示任意
	struct _NODE* next;
}NODE, *PNODE;

typedef struct _LIST//定义链表头    zbjk
{
	void* list_data;//额外的用一个指针表示链表头存一个数据，一般情况下是没有数据的，通常输入NULL
	PNODE first;
}LIST, *PLIST;


/***  创建一个新的链表  ***/
PLIST ListCreate(void* list_data);

/***  插入节点到链表   ***/
int ListInsertAt(PLIST list, unsigned int n, void* data);

/***  在链表头部插入节点   ***/
void ListPushFront(PLIST list, void* data);

/***  在链表尾部插入节点   ***/
void ListPushBack(PLIST list, void* data);

/***  删除链表头部节点   ***/
void* ListPopFront(PLIST list);

/***  删除链表尾部节点   ***/
void* ListPopBack(PLIST list);

/***  根据序号获得节点   ***/
void* ListGetAt(PLIST list, unsigned int n);

/***  根据序号删除节点   ***/
void* ListDeleteAt(PLIST list, int n);

/***  删除链表中的所有节点   ***/
void ListClearAndFree(PLIST list);

/***  删除整个链表   ***/
void ListDistory(PLIST list);

/***  删除整个链表，并链表中的全部释放   ***/
void ListDistoryAndFree(PLIST list);

/***  获得当前链表大小（节点数量）   ***/
int ListSize(PLIST list);


#endif
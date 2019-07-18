/************************************************************************

������

FUNCTIONS :
ListCreate			- ����һ���µ�������
ListInsertAt			- ����ڵ㵽������
ListPushFront		- ������ͷ������ڵ㡣
ListPushBack			- ������β������ڵ㡣
ListPopFront			- ɾ������ͷ���ڵ㡣
ListPopBack			- ɾ������β���ڵ㡣
ListGetFront			- ��õ�һ���ڵ�
ListGetBack			- ������һ���ڵ㡣
ListGetNodeAt		- ������Ż�ýڵ㡣
ListDeleteNodeAt		- �������ɾ���ڵ㡣
ListDestroy			- ɾ������������
ListDestroyAndFree	- ɾ���������������ͷ����ݡ�
ListClear			- ɾ�������е����нڵ㡣
ListClearAndFree		- ��������е����нڵ㣬���ͷ����ݡ�
ListGetSize			- ��õ�ǰ������С���ڵ���������


************************************************************************/
#include <stdlib.h> // ʹ�õ���malloc(), free()�Ⱥ�����
#include "LinkList.h"


// ����һ�������ڵ�
PNODE NodeCreate(void* data)//�������������͵����� zbj
{
	PNODE pnode = (PNODE)malloc(sizeof(NODE));//����һ���½ڵ�ָ�벢�����ڴ� zbj
	pnode->data = data; //���ָ����������Ǵ���Ĳ��� zbj
	pnode->next = 0;//�ڵ�ָ���next����NULL zbj
	return pnode;//��������ڵ�ָ�� zbj
}

// ���������ڵ㼰�����ݡ�
void NodeDistory(PNODE node)
{
	free(node->data);
	free(node);
}

// ��������Ĵ�С���ڵ���������
int ListSize(PLIST list)
{
	int  cnt;//���ü�����zbj
	PNODE node = list->first;//����һ���½ڵ�ָ����ĵ�һ���ڵ�zbj

	cnt = 0;//��������ʼ��Ϊ0 zbj
	while (node)//���ڵ㲻Ϊ��ʱ zbj
	{
		cnt++;//��������1zbj
		node = node->next;//ָ����һ���ڵ�zbj
	}
	return (cnt);//���ؽڵ���zbj
}

// ɾ���������ض�λ�õĽڵ㣬���������ݡ�
// ���� -1 ��ʾ����
// ���� >= ��ʾ�����λ�á�
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
		if (!tmp)//˵��nԽ����
			return -1;
		++i;
	}
	//����������   zbjk
	new_node = NodeCreate(data);
	prev->next = new_node;
	new_node->next = tmp->next;//�������
	return i;
}


// ɾ���������ض�λ�õĽڵ㣬���������ݡ�
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
		tmp = tmp->next;//Ѱ��Ҫɾ���Ľڵ�   zbj
		if (!tmp)
			return (NULL);
		++i;
	}
	prev->next = tmp->next;//  ɾ���ýڵ�    zbj
	return (tmp->data);//���ظýڵ��ʫ��    zbj
}


// ���ָ��λ���Ͻڵ��е����ݡ�
void* ListGetAt(PLIST list, unsigned int n)//������һ���б���һ��unsighed����(��ָ���ڵ�����) zbj
{
	unsigned int   i;//ѭ�������� zbj
	PNODE node = list->first;//����һ���ڵ�ָ���б���ͷ�ڵ� zbj

	if (!node)//���ͷ�ڵ�Ϊ�գ�����NULL zbj
		return (NULL);

	for (i = 1; i <= n; i++)//���û�е�����ڵ���ţ��ͼ���Ѱ����һ���ڵ� zbj
	{
		node = node->next;
		if (!node)//�����δ�ҵ�����ڵ��Ϊ���ˣ���ô����NULL zbj
			return (NULL);
	}
	return (node->data);//����ͷ�������ڵ������ zbj
}

// ����������
PLIST ListCreate(void* list_data)//������ʾ�ߵ������������еĲ����������е����������������͵� zbj
{
	PLIST new_list;//��ʼ��һ�������� zbj

	new_list = NULL;//��������Ϊ�� zbj
	new_list = (PLIST)malloc(sizeof(LIST));//�������������ڴ�
	if (new_list != NULL)//!!!!!!
	{
		new_list->list_data = list_data;//ͨ��ָ��NULL������������ͷ��û������
		new_list->first = NULL;
	}
	return (new_list);//����������
}

// ֻ�ͷ�����ͷ�������ͷ�������
void ListDistory(PLIST list)
{
	if (list != NULL)
	{
		if (list->list_data != NULL)
			free(list->list_data);
		free(list);
	}
}

// �ͷ����������������нڵ������
void ListDistoryAndFree(PLIST list)
{
	if (list != NULL)//����������Ϊ��ʱ  zbj
	{
		ListClearAndFree(list);
		if (list->list_data != NULL) //��ͷ�ڵ��ָ����Ϊ��ʱ  zbj
			free(list->list_data);//�ͷ�ָ���� zbj
		free(list);//�ͷ��ڴ�  zbj
	}
}

// ��ȡ����ͷ�����ݣ�����������ɾ����
void* ListPopFront(PLIST list)
{
	PNODE tmp;
	void*  data = NULL;
	if (list != NULL)
	{
		if (list->first != NULL)//�����ڵ��ɾ������   zbj
		{
			tmp = list->first;
			data = tmp->data;
			list->first = tmp->next;
			free(tmp);
		}
	}
	return (data); //����ͷ�ڵ������   zbj
}

// ��ȡ����β�����ݣ�����������ɾ����
void* ListPopBack(PLIST list)//����Ϊ����������ֵ���������͵�ָ��  zbj
{
	PNODE prev;//����
	PNODE current;//����
	PNODE node = list->first;//�����ڵ�ָ��ͷ�ڵ�   zbj
	void* data;//������������(����������¼��β��λ��)   zbj

	if (!node)//ͷ�ڵ�Ϊ��   zbj
		return (NULL);//����NULL   zbj
	if (!(node)->next)//��ͷ�ڵ����һ���ڵ�Ϊ��    zbj
	{
		data = (node)->data;//����Ϊͷ�ڵ����ݣ���������ͷλ�ã� ������ zbj   
		free(node);//�ͷ�ͷ�ڵ�ռ�
		node = NULL;
		return (data);//����ͷ�ڵ����ݣ���������ͷλ��)������    zbj
	}
	prev = node;//prevָ��ǰ�ڵ�   zbj
	current = (node)->next;//currentָ��ǰ�ڵ����һ���ڵ� zbj
	while (current->next)//current�ڵ����һ���ڵ㲻Ϊ�գ�˵��current�ڵ㲻Ϊβ����ѭ����β��   zbj
	{
		prev = current;//ѭ����β��  zbj
		current = current->next;
	}
	data = current->data;//β���ڵ��������β�ڵ�λ�ã� ѭ����β��
	free(current);//�ͷ�β�ڵ�ռ� ѭ����β��
	prev->next = NULL;//β�ڵ����һ���ڵ�ָ��գ��൱��ɾ��β�ڵ�   ѭ����β��
	return (data);//����β���ڵ��������β�ڵ�λ�ã�
}

// �������ݵ�����β����
void ListPushBack(PLIST list, void* data)//��������Ӧ������������ʽ�����ݣ�һ�������һ������λ��ָ�룩 zbj
{
	PNODE tmp;//����һ���ڵ�ָ�� zbj
	PNODE new_node = NodeCreate(data);//����һ�������ڵ㲢�������ݣ�λ�ã� zbj 

	if (new_node)//����ڵ㲻Ϊ�� zbj
	{
		if (list)//���б���Ϊ�� zbj
		{
			if (list->first)//��ͷ�ڵ㲻Ϊ��ʱ  zbj
			{
				tmp = list->first;//�ýڵ�ָ��ָ��ͷ�ڵ�  zbj
				while (tmp->next)//��ͷ�ڵ����һ���ڵ㲻Ϊ��ʱ  zbj
					tmp = tmp->next;//��������Ѱ��ֱ���ҵ��սڵ�Ϊֹ����tempָ��β�ڵ�  zbj
				tmp->next = new_node;//��β�ڵ㴦�����½��ڵ� zbj
			}
			else//��ͷ�ڵ�Ϊ��ʱ��ֱ����������ͷ�ڵ��������½��ڵ� zbj
				list->first = new_node;
		}
	}
}

// �������ݵ�����ͷ����
void ListPushFront(PLIST list, void* data)//Ϊʲô��ͷ�巨?????
{
	PNODE new_node;//��ʼ��һ���½ڵ�ָ�� zbj

	if (list != NULL)//�����������Ϊ�� zbj
	{
		new_node = NodeCreate(data);//����һ�������ڵ�,����data����ȥ zbj
		if (new_node != NULL)//����½ڵ�ָ�벻Ϊ�յĻ� zbj
		{
			new_node->next = list->first;//����ͷ�巨�����ǲ��������� zbj
			list->first = new_node;
		}
	}
}


// ɾ���������нڵ㣬free���ݡ�
void ListClearAndFree(PLIST list)
{
	PNODE tmp;//��ʼ�������ڵ�  zbj
	PNODE node;

	if (list != NULL)//����������Ϊ��ʱ   zbj
	{
		node = list->first;//ָ��ͷ�ڵ�  zbj
		while (node)//���ڵ㲻Ϊ��    zbj
		{
			tmp = node->next;//������ָ��ָ����һ���ڵ�  zbj
			NodeDistory(node);//ɾ���ýڵ�
			node = tmp;//����һ���ڵ�Ϊ��ʼ
		}
		list->first = 0;//ʹͷ�ڵ�Ϊ��
	}
}
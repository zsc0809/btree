#ifndef _Treee_H_
#define _Treee_H_
#include <stdbool.h>

#define MAXITEMS 10
#define LEN 50 


typedef struct item
{
	char petname[LEN];
	char petkind[LEN];
} Item;

typedef struct trnode
{
	Item item;
	struct trnode * left;
	struct trnode * right;
} Trnode;

typedef struct tree
{
	Trnode * root;
	int size;
} Tree;

//����ԭ��

//��ʼ��
void Initializetree(Tree * ptree);    			

//�ж�Ϊ�� 
bool Treeisempty(const Tree * ptree);       			

//�ж�Ϊ�� 
bool Treeisfull(const Tree * ptree);        			

//�ڵ���� 
int Treecount(const Tree * ptree);         			

//��ӽڵ� 
bool Additem(Tree * ptree, const Item * pi);	

//ɾ���ڵ� 
bool Delitem(Tree * ptree, const Item * pi);	

//���ҽڵ� 
bool Intree(const Tree * ptree, const Item * item);

//Ӧ�ú�����ÿһ���ڵ� 
void Traverse(const Tree * ptree, void(*pfun)(Item item));

//ɾ���� 
void Deleteall(Tree * ptree);

#endif 
 










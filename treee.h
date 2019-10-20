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

//函数原型

//初始化
void Initializetree(Tree * ptree);    			

//判断为空 
bool Treeisempty(const Tree * ptree);       			

//判断为满 
bool Treeisfull(const Tree * ptree);        			

//节点计数 
int Treecount(const Tree * ptree);         			

//添加节点 
bool Additem(Tree * ptree, const Item * pi);	

//删除节点 
bool Delitem(Tree * ptree, const Item * pi);	

//查找节点 
bool Intree(const Tree * ptree, const Item * item);

//应用函数于每一个节点 
void Traverse(const Tree * ptree, void(*pfun)(Item item));

//删除树 
void Deleteall(Tree * ptree);

#endif 
 










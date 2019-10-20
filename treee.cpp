#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "treee.h"

typedef struct pair
{
	Trnode * parent;
	Trnode * child;
}Pair;

static Trnode * Makenode(const Item * item);
static bool Toleft(const Item * i, const Item * j);
static bool Toright(const Item * i, const Item * j);
static void Addnode(Trnode * newnode, Trnode * root);
static void Inorder(const Trnode * root, void(*pfun)(Item item));
static Pair Seekitem(const Item * pi, const Tree * ptree);
static void Delnode(Trnode ** ptr);
static void Deleteallnodes(Trnode * root);

//初始化
void Initializetree(Tree * ptree)
{
	ptree->size = 0;
	ptree->root = NULL;
}    			

//判断为空 
bool Treeisempty(const Tree * ptree)
{
	if(ptree->root != NULL)
		return false;
	else 
		return true;
}      			

//判断为满 
bool Treeisfull(const Tree * ptree)
{
	if(ptree->size == MAXITEMS)
		return true;
	else 
		return false;	
}       			

//节点计数 
int Treecount(const Tree * ptree)
{
	return ptree->size;
}        			

//添加节点 
bool Additem(Tree * ptree, const Item * pi)
{
	Trnode * newnode;

	if(Treeisfull(ptree))
	{
		fprintf(stderr, "Tree is full.\n");
		return false;
	}
	if(Seekitem(pi, ptree).child != NULL)
	{
		fprintf(stderr, "Attempted to add duplicate item.\n");
		return false;		
	}
	newnode = Makenode(pi); 
	if(newnode == NULL)
	{
		fprintf(stderr, "Couldn't create node.\n");
		return false;		
	}
	ptree->size++;
	if(ptree->root == NULL)
		ptree->root = newnode;
	else
		Addnode(newnode, ptree->root);
	 
	return true;
}	

//删除节点 
bool Delitem(Tree * ptree, const Item * pi)
{
	Pair look;
	
	look = Seekitem(pi,ptree);
	
	if(look.child == NULL)
		return false;
	if(look.parent == NULL)
		Delnode(&ptree->root);
	else if(look.parent->left == look.child)
		Delnode(&look.parent->left);
	else
		Delnode(&look.parent->right);
	ptree->size--;
	
	return true;
}	

//查找节点 
bool Intree(const Tree * ptree, const Item * item)
{
	return (Seekitem(item, ptree).child == NULL) ? false : true;
}

//应用函数于每一个节点 
void Traverse(const Tree * ptree, void(*pfun)(Item item))
{
	if(ptree != NULL)
		Inorder(ptree->root, pfun);
		
}

//删除树 
void Deleteall(Tree * ptree)
{
	if(ptree != NULL)
		Deleteallnodes(ptree->root);
	ptree->root = NULL;
	ptree->size = 0;
	
}

//
static void Inorder(const Trnode * root, void(*pfun)(Item item))
{
	if(root != NULL)
	{
		Inorder(root->left, pfun);
		(*pfun)(root->item);
		Inorder(root->right, pfun);
	}
	
}

//
static void Deleteallnodes(Trnode * root)
{
	Trnode * pright;
	
	if(root != NULL)
	{
		pright = root->right;
		Deleteallnodes(root->left);
		free(root);
		Deleteallnodes(pright);
	}
	
}

//
static void Addnode(Trnode * newnode, Trnode * root)
{
	if(Toleft(&newnode->item, &root->item))
	{
		if(root->left == NULL)
			root->left = newnode;
		else
			Addnode(newnode, root->left);			
	}
	else if(Toright(&newnode->item, &root->item))
	{
		if(root->right == NULL)
			root->right = newnode;
		else
			Addnode(newnode, root->left);			
	}
	else
	{
		fprintf(stderr, "location error in Addnode()\n");
		exit(1);
	}

}

// 
static bool Toleft(const Item * i, const Item * j)
{
	int comp;
	
	if((comp = strcmp(i->petname, j->petname)) < 0)	
		return true;
	else if(comp == 0 && strcmp(i->petkind, j->petkind) < 0)
		return true;
	else
		return false;
}

// 
static bool Toright(const Item * i, const Item * j)
{
	int comp;
	
	if((comp = strcmp(i->petname, j->petname)) > 0)	
		return true;
	else if(comp == 0 && strcmp(i->petkind, j->petkind) > 0)
		return true;
	else
		return false;
}

//
static Trnode * Makenode(const Item * item)
{
	Trnode * temp;
	
	temp = (Trnode *)malloc(sizeof(Trnode));
	if(temp != NULL)
	{
		temp->item = *item;
		temp->left = NULL;
		temp->right = NULL;		
	}

	return temp;
}

//
static Pair Seekitem(const Item * pi, const Tree * ptree)
{
	Pair look;
	look.parent = NULL;
	look.child = ptree->root;
	
	if(look.child == NULL)
		return look;
	while(look.child != NULL)
	{
		if(Toleft(pi, &(look.child->item)))
		{
			look.parent = look.child;
			look.child = look.child->left;
		}
		else if(Toright(pi, &(look.child->item)))
		{
			look.parent = look.child;
			look.child = look.child->right;
		}
		else       //前两条件不满足即为相等 
			break; //则look.child为目标节点 
	}
	
	return look; 
}

static void Delnode(Trnode ** ptr)
{
	Trnode * temp;
	
	if((*ptr)->left == NULL)
	{
		temp = *ptr;
		*ptr = (*ptr)->right;
		free(temp);
	}
	else if((*ptr)->right == NULL)
	{
		temp = *ptr;
		*ptr = (*ptr)->left;
		free(temp);
	}
	else
	{
		for(temp = (*ptr)->left; temp->right !=NULL; temp = temp->right)
			continue;
		temp->right = (*ptr)->right;
		temp = *ptr;
		*ptr = (*ptr)->left;
		free(temp);
	}
	
}


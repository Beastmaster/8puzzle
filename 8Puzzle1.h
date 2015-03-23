
/*-------------------Data Struct: BFS/DFS----------------------*/
#include <iostream>
#include <stdio.h>
#include <malloc.h>

#include "Conio.h"
#include "stdlib.h"
#include "math.h"


#define SETP_DEPTH 15

//node type
typedef
struct node
{
	int graphx[3][3];
	int position_row,position_col;//row,col
	//turn up
	node * Up_node;
	//turn down
	node * Down_node;
	//turn left
	node * Left_node;
	//turn right
	node * Right_node;
	//step
	//1: up
	//2: down
	//3: left
	//4: right
	char Last_Step;
	char Total_Step;
}
Node;
//int level;
void Creat_Up_Node(Node* cur_node);
void Creat_Down_Node(Node* cur_node);
void Creat_Left_Node(Node* cur_node);
void Creat_Right_Node(Node* cur_node);
void Node_Init(Node* cur_node);
void Display_Node(Node* nodex);
char Test_Valid(Node* nodex);
void Find_Zero(Node*);

//DFS
int Recurr_Deep_First(Node*); 
//BFS
int Recurr_Broad_First(Node*);





/*----------------Data Struct: A star-----------------*/

/* 定义8数码的节点状态 */
typedef struct node_star
{
	int s[3][3]; //当前8数码的状态
	int i_0;   //当前空格所在行号
	int j_0;   //当前空格所在列号
	int f;     //当前代价值
	int d;     //当前节点深度
	int h;     //启发信息，采用数码“不在位”距离和
	struct node_star *father; //指向解路径上该节点的父节点
	struct node_star *next;   //指向所在open或closed表中的下一个元素
}Node_Star;

void Copy_node(struct node_star *p1,struct node_star *p2);
void Calculate_f(int deepth,struct node_star *p);
void Add_to_open(struct node_star *p);
void Add_to_closed(struct node_star *p);
void Remove_p(struct node_star *name,struct node_star *p);
int Test_A_B(struct node_star *p1,struct node_star *p2);
struct node_star * Solution_Astar(struct node_star *p);
void Expand_n(struct node_star *p);
struct node_star * Search_A(struct node_star *name,struct node_star *temp);
void Print_result(struct node_star *p);

int A_Star_Begin(int*);




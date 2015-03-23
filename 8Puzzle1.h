
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

/* ����8����Ľڵ�״̬ */
typedef struct node_star
{
	int s[3][3]; //��ǰ8�����״̬
	int i_0;   //��ǰ�ո������к�
	int j_0;   //��ǰ�ո������к�
	int f;     //��ǰ����ֵ
	int d;     //��ǰ�ڵ����
	int h;     //������Ϣ���������롰����λ�������
	struct node_star *father; //ָ���·���ϸýڵ�ĸ��ڵ�
	struct node_star *next;   //ָ������open��closed���е���һ��Ԫ��
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




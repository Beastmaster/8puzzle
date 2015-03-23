#include "8Puzzle1.h"




struct node_star s_0={{3,8,2,1,0,5,7,6,4},1,1,0,0,0,NULL,NULL}; //定义初始状态

struct node_star s_g={{1,2,3,8,0,4,7,6,5},1,1,0,0,0,NULL,NULL}; //定义目标状态
struct node_star s_g2={{2,3,4,1,0,5,8,7,6},1,1,0,0,0,NULL,NULL}; //定义目标状态
struct node_star s_g3={{3,4,5,2,0,6,1,8,7},1,1,0,0,0,NULL,NULL}; //定义目标状态
struct node_star s_g4={{4,6,6,3,0,7,2,1,8},1,1,0,0,0,NULL,NULL}; //定义目标状态
struct node_star s_g5={{5,6,7,4,0,8,3,2,1},1,1,0,0,0,NULL,NULL}; //定义目标状态
struct node_star s_g6={{6,7,8,5,0,1,4,3,2},1,1,0,0,0,NULL,NULL}; //定义目标状态
struct node_star s_g7={{7,8,1,6,0,2,5,4,3},1,1,0,0,0,NULL,NULL}; //定义目标状态
struct node_star s_g8={{8,1,2,7,0,3,6,4,4},1,1,0,0,0,NULL,NULL}; //定义目标状态

struct node_star *open=NULL;                             //建立open表指针
struct node_star *closed=NULL;                            //建立closed表指针
int sum_node=0;                                     //用于记录扩展节点总数

int A_Star_Begin(int* input)
{
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			s_0.s[i][j] = input[3*i+j];
			if (input[3*i+j] == 0)
			{
				s_0.i_0 = i;
				s_0.j_0 = j;
			}
		}
	}
	struct node_star s,*target;
	Copy_node(&s_0,&s);
	Calculate_f(0,&s);           //拷贝8数码初始状态，初始化代价值
	target=Solution_Astar(&s);    //求解主程序
	if(target) Print_result(target);   //输出解路径
	else printf("问题求解失败！");

	getch();
	return 0;
}
/******************************************/
/*                 A*算法                 */
/******************************************/
struct node_star * Solution_Astar(struct node_star *p)
{
	struct node_star *n,*temp;
	Add_to_open(p);     //将s_0放入open表
	while(open!=NULL)  //只要open表中还有元素，就继续对代价最小的节点进行扩展
	{ 
		n=open;             //n指向open表中当前要扩展的元素
		temp=open->next;
		Add_to_closed(n);
		open=temp;
		if(Test_A_B(n,&s_g)
			||Test_A_B(n,&s_g2)
			||Test_A_B(n,&s_g3)
			||Test_A_B(n,&s_g4)
			||Test_A_B(n,&s_g5)
			||Test_A_B(n,&s_g6)
			||Test_A_B(n,&s_g7)
			||Test_A_B(n,&s_g8))  //当前n指向节点为目标时，跳出程序结束；否则，继续下面的步骤
			return n;      
		Expand_n(n);         //扩展节点n    
	}
	return NULL;
}
/*******************************************************/
/*       生成当前节点n通过走步可以得到的所有状态      */
/*******************************************************/
void Expand_n(struct node_star *p)
{
	struct node_star *temp,*same;
	if(p->j_0>=1)  //空格所在列号不小于1,可左移
	{
		temp=p->father;
		if(temp!=NULL&&temp->i_0==p->i_0&&temp->j_0-1==p->j_0)  //新节点与其祖父节点相同
			;
		else  //新节点与其祖父节点不同，或其父节点为起始节点
		{		  
			temp=(struct node_star *)malloc(sizeof(struct node_star));  //给新节点分配空间
			Copy_node(p,temp);  //拷贝p指向的节点状态
			temp->s[temp->i_0][temp->j_0]=temp->s[temp->i_0][temp->j_0-1];  //空格左移
			temp->s[temp->i_0][temp->j_0-1]=0;
			temp->j_0--;
			temp->d++; 
			Calculate_f(temp->d,temp);       //修改新节点的代价值
			temp->father=p;                //新节点指向其父节点		  
			if(same=Search_A(closed,temp))   //在closed表中找到与新节点状态相同的节点
			{
				if(temp->f<same->f)  //temp指向的节点,其代价比closed表中相同状态节点代价小，加入open表
				{
					Remove_p(closed,same);  //从closed表中删除与temp指向节点状态相同的节点
					Add_to_open(temp);
					sum_node++;
				}
				else;
			}
			else if(same=Search_A(open,temp))  //在open表中找到与新节点状态相同的节点
			{
				if(temp->f<same->f)  //temp指向的节点,其代价比open表中相同状态节点代价小，加入open表
				{
					Remove_p(open,same);  //从open表中删除与temp指向节点状态相同的节点
					Add_to_open(temp);
					sum_node++;
				}
				else ;
			}
			else  //新节点为完全不同的新节点，加入open表
			{
				Add_to_open(temp);
				sum_node++;
			}			  
		}
	}//end左移
	if(p->j_0<=1)  //空格所在列号不大于1,可右移
	{
		temp=p->father;
		if(temp!=NULL&&temp->i_0==p->i_0&&temp->j_0+1==p->j_0)  //新节点与其祖父节点相同
			;
		else  //新节点与其祖父节点不同，或其父节点为起始节点
		{		  
			temp=(struct node_star *)malloc(sizeof(struct node_star));  //给新节点分配空间
			Copy_node(p,temp);  //拷贝p指向的节点状态
			temp->s[temp->i_0][temp->j_0]=temp->s[temp->i_0][temp->j_0+1];  //空格右移
			temp->s[temp->i_0][temp->j_0+1]=0;
			temp->j_0++;
			temp->d++;
			Calculate_f(temp->d,temp);       //修改新节点的代价值
			temp->father=p;                //新节点指向其父节点
			if(same=Search_A(closed,temp))   //在closed表中找到与新节点状态相同的节点
			{
				if(temp->f<same->f)  //temp指向的节点,其代价比closed表中相同状态节点代价小，加入open表
				{
					Remove_p(closed,same);  //从closed表中删除与temp指向节点状态相同的节点
					Add_to_open(temp);
					sum_node++;
				}
				else;
			}
			else if(same=Search_A(open,temp))  //在open表中找到与新节点状态相同的节点
			{
				if(temp->f<same->f)  //temp指向的节点,其代价比open表中相同状态节点代价小，加入open表
				{
					Remove_p(open,same);  //从open表中删除与temp指向节点状态相同的节点
					Add_to_open(temp);
					sum_node++;
				}
				else ;
			}
			else  //新节点为完全不同的新节点，加入open表
			{
				Add_to_open(temp);
				sum_node++;
			}
		}
	}//end右移
	if(p->i_0>=1)  //空格所在列号不小于1,上移
	{
		temp=p->father;
		if(temp!=NULL&&temp->i_0==p->i_0-1&&temp->j_0==p->j_0)  //新节点与其祖父节点相同
			;
		else  //新节点与其祖父节点不同，或其父节点为起始节点
		{		  
			temp=(struct node_star *)malloc(sizeof(struct node_star));  //给新节点分配空间
			Copy_node(p,temp);  //拷贝p指向的节点状态
			temp->s[temp->i_0][temp->j_0]=temp->s[temp->i_0-1][temp->j_0];  //空格上移
			temp->s[temp->i_0-1][temp->j_0]=0;
			temp->i_0--;
			temp->d++;
			Calculate_f(temp->d,temp);       //修改新节点的代价值
			temp->father=p;                //新节点指向其父节点
			if(same=Search_A(closed,temp))   //在closed表中找到与新节点状态相同的节点
			{
				if(temp->f<same->f)  //temp指向的节点,其代价比closed表中相同状态节点代价小，加入open表
				{
					Remove_p(closed,same);  //从closed表中删除与temp指向节点状态相同的节点
					Add_to_open(temp);
					sum_node++;
				}
				else;
			}
			else if(same=Search_A(open,temp))  //在open表中找到与新节点状态相同的节点
			{
				if(temp->f<same->f)  //temp指向的节点,其代价比open表中相同状态节点代价小，加入open表
				{
					Remove_p(open,same);  //从open表中删除与temp指向节点状态相同的节点
					Add_to_open(temp);
					sum_node++;
				}
				else ;
			}
			else  //新节点为完全不同的新节点，加入open表
			{
				Add_to_open(temp);
				sum_node++;
			}
		}
	}//end上移
	if(p->i_0<=1)  //空格所在列号不大于1,下移
	{
		temp=p->father;
		if(temp!=NULL&&temp->i_0==p->i_0+1&&temp->j_0==p->j_0)  //新节点与其祖父节点相同
			;
		else  //新节点与其祖父节点不同，或其父节点为起始节点
		{		  
			temp=(struct node_star *)malloc(sizeof(struct node_star));  //给新节点分配空间
			Copy_node(p,temp);  //拷贝p指向的节点状态
			temp->s[temp->i_0][temp->j_0]=temp->s[temp->i_0+1][temp->j_0];  //空格下移
			temp->s[temp->i_0+1][temp->j_0]=0;
			temp->i_0++;
			temp->d++;
			Calculate_f(temp->d,temp);       //修改新节点的代价值
			temp->father=p;                //新节点指向其父节点
			if(same=Search_A(closed,temp))   //在closed表中找到与新节点状态相同的节点
			{
				if(temp->f<same->f)  //temp指向的节点,其代价比closed表中相同状态节点代价小，加入open表
				{
					Remove_p(closed,same);  //从closed表中删除与temp指向节点状态相同的节点
					Add_to_open(temp);
					sum_node++;
				}
				else;
			}
			else if(same=Search_A(open,temp))  //在open表中找到与新节点状态相同的节点
			{
				if(temp->f<same->f)  //temp指向的节点,其代价比open表中相同状态节点代价小，加入open表
				{
					Remove_p(open,same);  //从open表中删除与temp指向节点状态相同的节点
					Add_to_open(temp);
					sum_node++;
				}
				else ;
			}
			else  //新节点为完全不同的新节点，加入open表
			{
				Add_to_open(temp);
				sum_node++;
			}			  
		}
	}//end下移
}
/*******************************************************/
/*              添加p指向的节点到open表中            */
/*******************************************************/
void Add_to_open(struct node_star *p)
{
	struct node_star *p1,*p2;
	p1=open;              //初始时p1指向open表首部
	p2=NULL;
	if(open==NULL)        //open表为空时，待插入节点即为open表第一个元素，open指向该元素
	{
		p->next=NULL;
		open=p;
	}
	else                   //open表不为空时，添加待插入节点，并保证open表代价递增的排序
	{
		while(p1!=NULL&&p->f>p1->f)
		{
			p2=p1;         //p2始终指向p1指向的前一个元素
			p1=p1->next;
		}
		if(p2==NULL)      //待插入节点为当前open表最小
		{
			p->next=open;
			open=p;
		}
		else if(p1==NULL)  //待插入节点为当前open表最大
		{
			p->next=NULL;
			p2->next=p;
		}
		else               //待插入节点介于p2、p1之间
		{
			p2->next=p;
			p->next=p1;
		}
	}
}
/*******************************************************/
/*             添加p指向的节点到closed表中             */
/*******************************************************/
void Add_to_closed(struct node_star *p)
{
	if(closed==NULL)     //closed表为空时，p指向节点为closed表第一个元素，closed指向该元素
	{
		p->next=NULL;
		closed=p;
	}
	else                 //closed表不为空时，直接放到closed表首部
	{
		p->next=closed;
		closed=p;
	}
}
/**************************************************************/
/*   在open表或closed表中搜索与temp指向节点状态相同的节点，   */
/*                  返回搜索到的节点地址                      */
/**************************************************************/
struct node_star * Search_A(struct node_star *name,struct node_star *temp)
{
	struct node_star *p1;
	p1=name;                  //p1指向open表或closed表
	while(p1!=NULL)
	{
		if(Test_A_B(p1,temp))   //找到相同的节点，返回该节点地址
			return p1;
		else
			p1=p1->next;
	}
	return NULL;
}
/**********************************************************/
/*  判断两个节点A、B状态是否相同，相同则返回1，否则返回0  */
/**********************************************************/
int Test_A_B(struct node_star *p1,struct node_star *p2)
{
	int i,j,flag;
	flag=1;
	for(i=0;i<=2;i++)
		for(j=0;j<=2;j++)
		{ 
			if((p2->s[i][j])!=(p1->s[i][j])) { flag=0; return flag; }
			else ;
		}
		return flag;
}
/*******************************************************/
/*           从open表或closed表删除指定节点            */
/*******************************************************/
void Remove_p(struct node_star *name,struct node_star *p)
{
	struct node_star *p1,*p2;
	p1=NULL;
	p2=NULL;
	if(name==NULL)                           //如果name指向的链表为空，则不需要进行删除
		return;
	else if(Test_A_B(name,p)&&name->f==p->f)    //指定节点为name指向的链表的第一个元素
	{
		open=name->next;
		name->next=NULL;
		return;
	}
	else
	{
		p2=name;
		p1=p2->next;
		while(p1)
		{
			if(Test_A_B(p1,p)&&p1->f==p->f)   //找到指定节点
			{
				p2->next=p1->next;
				return;
			}
			else
			{
				p2=p1;                     //p2始终指向p1指向的前一个元素
				p1=p1->next;
			}
		}
		return;
	}
}
/******************************************/
/*        计算某个节点状态的代价值        */
/******************************************/
void Calculate_f(int deepth,struct node_star *p)
{
	int i,j,temp;
	temp=0;  
	for(i=0;i<=2;i++)     //计算所有“不在位”数码的距离和
	{
		for(j=0;j<=2;j++)
		{
			switch(p->s[i][j])
			{
			case 0: temp+=abs(i-1)+abs(j-1); break;
			case 1: temp+=abs(i-0)+abs(j-0); break;
			case 2: temp+=abs(i-0)+abs(j-1); break;
			case 3: temp+=abs(i-0)+abs(j-2); break;
			case 4: temp+=abs(i-1)+abs(j-2); break;
			case 5: temp+=abs(i-2)+abs(j-2); break;
			case 6: temp+=abs(i-2)+abs(j-1); break;
			case 7: temp+=abs(i-2)+abs(j-0); break;
			case 8: temp+=abs(i-1)+abs(j-0); break;
			}
		}
	}
	p->h=temp;
	p->f=deepth+p->h;
}
/********************************************/
/* 将p1指向的节点状态拷贝到p2指向的节点中 */
/********************************************/
void Copy_node(struct node_star *p1,struct node_star *p2)
{
	int i,j;
	for(i=0;i<=2;i++)
	{
		for(j=0;j<=2;j++)
		{ p2->s[i][j]=p1->s[i][j]; }
	}
	p2->i_0=p1->i_0;
	p2->j_0=p1->j_0;
	p2->f=p1->f;
	p2->d=p1->d;
	p2->h=p1->h;
	p2->next=p1->next;
	p2->father=p1->father;
}
/********************************************/
/*                输出解路径                */
/********************************************/
void Print_result(struct node_star *p)
{
	struct node_star *path[100];
	struct node_star *temp,*temp_father;
	int i,j,k;
	for(i=0;i<=99;i++)                   //初始化路径指针数组
		path[i]=0;
	temp=p;
	printf("总共扩展 %d 个节点\n",sum_node);
	printf("总共扩展 %d 层\n",temp->d);
	printf("*************************************************\n");
	printf("解路径如下：\n");
	for(i=p->d;i>=0;i--)                  //存储解路径上各节点的地址
	{
		path[i]=temp;
		temp=temp->father;
	}
	for(k=0;k<=p->d;k++)                //输出解路径
	{
		temp=path[k];                  //建立节点指点指针
		printf("第%d步 ",temp->d);
		if(k-1>=0)                     //输出移动策略
		{
			temp_father=path[k-1];
			if(temp->i_0<temp_father->i_0) printf("—>上移\n");
			if(temp->i_0>temp_father->i_0) printf("—>下移\n");
			if(temp->j_0<temp_father->j_0) printf("—>左移\n");
			if(temp->j_0>temp_father->j_0) printf("—>右移\n");
		}
		else
			printf("\n");
		printf("当前：f=%d，d=%d，h=%d\n",temp->f,temp->d,temp->h);
		printf("当前节点状态为：\n");
		for(i=0;i<=2;i++)
		{
			for(j=0;j<=2;j++)
			{
				printf("%d  ",temp->s[i][j]);
			}
			printf("\n");
		}	  
		printf("\n");
	}
}





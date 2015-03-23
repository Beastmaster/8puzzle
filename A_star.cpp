#include "8Puzzle1.h"




struct node_star s_0={{3,8,2,1,0,5,7,6,4},1,1,0,0,0,NULL,NULL}; //�����ʼ״̬

struct node_star s_g={{1,2,3,8,0,4,7,6,5},1,1,0,0,0,NULL,NULL}; //����Ŀ��״̬
struct node_star s_g2={{2,3,4,1,0,5,8,7,6},1,1,0,0,0,NULL,NULL}; //����Ŀ��״̬
struct node_star s_g3={{3,4,5,2,0,6,1,8,7},1,1,0,0,0,NULL,NULL}; //����Ŀ��״̬
struct node_star s_g4={{4,6,6,3,0,7,2,1,8},1,1,0,0,0,NULL,NULL}; //����Ŀ��״̬
struct node_star s_g5={{5,6,7,4,0,8,3,2,1},1,1,0,0,0,NULL,NULL}; //����Ŀ��״̬
struct node_star s_g6={{6,7,8,5,0,1,4,3,2},1,1,0,0,0,NULL,NULL}; //����Ŀ��״̬
struct node_star s_g7={{7,8,1,6,0,2,5,4,3},1,1,0,0,0,NULL,NULL}; //����Ŀ��״̬
struct node_star s_g8={{8,1,2,7,0,3,6,4,4},1,1,0,0,0,NULL,NULL}; //����Ŀ��״̬

struct node_star *open=NULL;                             //����open��ָ��
struct node_star *closed=NULL;                            //����closed��ָ��
int sum_node=0;                                     //���ڼ�¼��չ�ڵ�����

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
	Calculate_f(0,&s);           //����8�����ʼ״̬����ʼ������ֵ
	target=Solution_Astar(&s);    //���������
	if(target) Print_result(target);   //�����·��
	else printf("�������ʧ�ܣ�");

	getch();
	return 0;
}
/******************************************/
/*                 A*�㷨                 */
/******************************************/
struct node_star * Solution_Astar(struct node_star *p)
{
	struct node_star *n,*temp;
	Add_to_open(p);     //��s_0����open��
	while(open!=NULL)  //ֻҪopen���л���Ԫ�أ��ͼ����Դ�����С�Ľڵ������չ
	{ 
		n=open;             //nָ��open���е�ǰҪ��չ��Ԫ��
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
			||Test_A_B(n,&s_g8))  //��ǰnָ��ڵ�ΪĿ��ʱ������������������򣬼�������Ĳ���
			return n;      
		Expand_n(n);         //��չ�ڵ�n    
	}
	return NULL;
}
/*******************************************************/
/*       ���ɵ�ǰ�ڵ�nͨ���߲����Եõ�������״̬      */
/*******************************************************/
void Expand_n(struct node_star *p)
{
	struct node_star *temp,*same;
	if(p->j_0>=1)  //�ո������кŲ�С��1,������
	{
		temp=p->father;
		if(temp!=NULL&&temp->i_0==p->i_0&&temp->j_0-1==p->j_0)  //�½ڵ������游�ڵ���ͬ
			;
		else  //�½ڵ������游�ڵ㲻ͬ�����丸�ڵ�Ϊ��ʼ�ڵ�
		{		  
			temp=(struct node_star *)malloc(sizeof(struct node_star));  //���½ڵ����ռ�
			Copy_node(p,temp);  //����pָ��Ľڵ�״̬
			temp->s[temp->i_0][temp->j_0]=temp->s[temp->i_0][temp->j_0-1];  //�ո�����
			temp->s[temp->i_0][temp->j_0-1]=0;
			temp->j_0--;
			temp->d++; 
			Calculate_f(temp->d,temp);       //�޸��½ڵ�Ĵ���ֵ
			temp->father=p;                //�½ڵ�ָ���丸�ڵ�		  
			if(same=Search_A(closed,temp))   //��closed�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
			{
				if(temp->f<same->f)  //tempָ��Ľڵ�,����۱�closed������ͬ״̬�ڵ����С������open��
				{
					Remove_p(closed,same);  //��closed����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
					Add_to_open(temp);
					sum_node++;
				}
				else;
			}
			else if(same=Search_A(open,temp))  //��open�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
			{
				if(temp->f<same->f)  //tempָ��Ľڵ�,����۱�open������ͬ״̬�ڵ����С������open��
				{
					Remove_p(open,same);  //��open����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
					Add_to_open(temp);
					sum_node++;
				}
				else ;
			}
			else  //�½ڵ�Ϊ��ȫ��ͬ���½ڵ㣬����open��
			{
				Add_to_open(temp);
				sum_node++;
			}			  
		}
	}//end����
	if(p->j_0<=1)  //�ո������кŲ�����1,������
	{
		temp=p->father;
		if(temp!=NULL&&temp->i_0==p->i_0&&temp->j_0+1==p->j_0)  //�½ڵ������游�ڵ���ͬ
			;
		else  //�½ڵ������游�ڵ㲻ͬ�����丸�ڵ�Ϊ��ʼ�ڵ�
		{		  
			temp=(struct node_star *)malloc(sizeof(struct node_star));  //���½ڵ����ռ�
			Copy_node(p,temp);  //����pָ��Ľڵ�״̬
			temp->s[temp->i_0][temp->j_0]=temp->s[temp->i_0][temp->j_0+1];  //�ո�����
			temp->s[temp->i_0][temp->j_0+1]=0;
			temp->j_0++;
			temp->d++;
			Calculate_f(temp->d,temp);       //�޸��½ڵ�Ĵ���ֵ
			temp->father=p;                //�½ڵ�ָ���丸�ڵ�
			if(same=Search_A(closed,temp))   //��closed�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
			{
				if(temp->f<same->f)  //tempָ��Ľڵ�,����۱�closed������ͬ״̬�ڵ����С������open��
				{
					Remove_p(closed,same);  //��closed����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
					Add_to_open(temp);
					sum_node++;
				}
				else;
			}
			else if(same=Search_A(open,temp))  //��open�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
			{
				if(temp->f<same->f)  //tempָ��Ľڵ�,����۱�open������ͬ״̬�ڵ����С������open��
				{
					Remove_p(open,same);  //��open����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
					Add_to_open(temp);
					sum_node++;
				}
				else ;
			}
			else  //�½ڵ�Ϊ��ȫ��ͬ���½ڵ㣬����open��
			{
				Add_to_open(temp);
				sum_node++;
			}
		}
	}//end����
	if(p->i_0>=1)  //�ո������кŲ�С��1,����
	{
		temp=p->father;
		if(temp!=NULL&&temp->i_0==p->i_0-1&&temp->j_0==p->j_0)  //�½ڵ������游�ڵ���ͬ
			;
		else  //�½ڵ������游�ڵ㲻ͬ�����丸�ڵ�Ϊ��ʼ�ڵ�
		{		  
			temp=(struct node_star *)malloc(sizeof(struct node_star));  //���½ڵ����ռ�
			Copy_node(p,temp);  //����pָ��Ľڵ�״̬
			temp->s[temp->i_0][temp->j_0]=temp->s[temp->i_0-1][temp->j_0];  //�ո�����
			temp->s[temp->i_0-1][temp->j_0]=0;
			temp->i_0--;
			temp->d++;
			Calculate_f(temp->d,temp);       //�޸��½ڵ�Ĵ���ֵ
			temp->father=p;                //�½ڵ�ָ���丸�ڵ�
			if(same=Search_A(closed,temp))   //��closed�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
			{
				if(temp->f<same->f)  //tempָ��Ľڵ�,����۱�closed������ͬ״̬�ڵ����С������open��
				{
					Remove_p(closed,same);  //��closed����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
					Add_to_open(temp);
					sum_node++;
				}
				else;
			}
			else if(same=Search_A(open,temp))  //��open�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
			{
				if(temp->f<same->f)  //tempָ��Ľڵ�,����۱�open������ͬ״̬�ڵ����С������open��
				{
					Remove_p(open,same);  //��open����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
					Add_to_open(temp);
					sum_node++;
				}
				else ;
			}
			else  //�½ڵ�Ϊ��ȫ��ͬ���½ڵ㣬����open��
			{
				Add_to_open(temp);
				sum_node++;
			}
		}
	}//end����
	if(p->i_0<=1)  //�ո������кŲ�����1,����
	{
		temp=p->father;
		if(temp!=NULL&&temp->i_0==p->i_0+1&&temp->j_0==p->j_0)  //�½ڵ������游�ڵ���ͬ
			;
		else  //�½ڵ������游�ڵ㲻ͬ�����丸�ڵ�Ϊ��ʼ�ڵ�
		{		  
			temp=(struct node_star *)malloc(sizeof(struct node_star));  //���½ڵ����ռ�
			Copy_node(p,temp);  //����pָ��Ľڵ�״̬
			temp->s[temp->i_0][temp->j_0]=temp->s[temp->i_0+1][temp->j_0];  //�ո�����
			temp->s[temp->i_0+1][temp->j_0]=0;
			temp->i_0++;
			temp->d++;
			Calculate_f(temp->d,temp);       //�޸��½ڵ�Ĵ���ֵ
			temp->father=p;                //�½ڵ�ָ���丸�ڵ�
			if(same=Search_A(closed,temp))   //��closed�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
			{
				if(temp->f<same->f)  //tempָ��Ľڵ�,����۱�closed������ͬ״̬�ڵ����С������open��
				{
					Remove_p(closed,same);  //��closed����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
					Add_to_open(temp);
					sum_node++;
				}
				else;
			}
			else if(same=Search_A(open,temp))  //��open�����ҵ����½ڵ�״̬��ͬ�Ľڵ�
			{
				if(temp->f<same->f)  //tempָ��Ľڵ�,����۱�open������ͬ״̬�ڵ����С������open��
				{
					Remove_p(open,same);  //��open����ɾ����tempָ��ڵ�״̬��ͬ�Ľڵ�
					Add_to_open(temp);
					sum_node++;
				}
				else ;
			}
			else  //�½ڵ�Ϊ��ȫ��ͬ���½ڵ㣬����open��
			{
				Add_to_open(temp);
				sum_node++;
			}			  
		}
	}//end����
}
/*******************************************************/
/*              ���pָ��Ľڵ㵽open����            */
/*******************************************************/
void Add_to_open(struct node_star *p)
{
	struct node_star *p1,*p2;
	p1=open;              //��ʼʱp1ָ��open���ײ�
	p2=NULL;
	if(open==NULL)        //open��Ϊ��ʱ��������ڵ㼴Ϊopen���һ��Ԫ�أ�openָ���Ԫ��
	{
		p->next=NULL;
		open=p;
	}
	else                   //open��Ϊ��ʱ����Ӵ�����ڵ㣬����֤open����۵���������
	{
		while(p1!=NULL&&p->f>p1->f)
		{
			p2=p1;         //p2ʼ��ָ��p1ָ���ǰһ��Ԫ��
			p1=p1->next;
		}
		if(p2==NULL)      //������ڵ�Ϊ��ǰopen����С
		{
			p->next=open;
			open=p;
		}
		else if(p1==NULL)  //������ڵ�Ϊ��ǰopen�����
		{
			p->next=NULL;
			p2->next=p;
		}
		else               //������ڵ����p2��p1֮��
		{
			p2->next=p;
			p->next=p1;
		}
	}
}
/*******************************************************/
/*             ���pָ��Ľڵ㵽closed����             */
/*******************************************************/
void Add_to_closed(struct node_star *p)
{
	if(closed==NULL)     //closed��Ϊ��ʱ��pָ��ڵ�Ϊclosed���һ��Ԫ�أ�closedָ���Ԫ��
	{
		p->next=NULL;
		closed=p;
	}
	else                 //closed��Ϊ��ʱ��ֱ�ӷŵ�closed���ײ�
	{
		p->next=closed;
		closed=p;
	}
}
/**************************************************************/
/*   ��open���closed����������tempָ��ڵ�״̬��ͬ�Ľڵ㣬   */
/*                  �����������Ľڵ��ַ                      */
/**************************************************************/
struct node_star * Search_A(struct node_star *name,struct node_star *temp)
{
	struct node_star *p1;
	p1=name;                  //p1ָ��open���closed��
	while(p1!=NULL)
	{
		if(Test_A_B(p1,temp))   //�ҵ���ͬ�Ľڵ㣬���ظýڵ��ַ
			return p1;
		else
			p1=p1->next;
	}
	return NULL;
}
/**********************************************************/
/*  �ж������ڵ�A��B״̬�Ƿ���ͬ����ͬ�򷵻�1�����򷵻�0  */
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
/*           ��open���closed��ɾ��ָ���ڵ�            */
/*******************************************************/
void Remove_p(struct node_star *name,struct node_star *p)
{
	struct node_star *p1,*p2;
	p1=NULL;
	p2=NULL;
	if(name==NULL)                           //���nameָ�������Ϊ�գ�����Ҫ����ɾ��
		return;
	else if(Test_A_B(name,p)&&name->f==p->f)    //ָ���ڵ�Ϊnameָ�������ĵ�һ��Ԫ��
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
			if(Test_A_B(p1,p)&&p1->f==p->f)   //�ҵ�ָ���ڵ�
			{
				p2->next=p1->next;
				return;
			}
			else
			{
				p2=p1;                     //p2ʼ��ָ��p1ָ���ǰһ��Ԫ��
				p1=p1->next;
			}
		}
		return;
	}
}
/******************************************/
/*        ����ĳ���ڵ�״̬�Ĵ���ֵ        */
/******************************************/
void Calculate_f(int deepth,struct node_star *p)
{
	int i,j,temp;
	temp=0;  
	for(i=0;i<=2;i++)     //�������С�����λ������ľ����
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
/* ��p1ָ��Ľڵ�״̬������p2ָ��Ľڵ��� */
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
/*                �����·��                */
/********************************************/
void Print_result(struct node_star *p)
{
	struct node_star *path[100];
	struct node_star *temp,*temp_father;
	int i,j,k;
	for(i=0;i<=99;i++)                   //��ʼ��·��ָ������
		path[i]=0;
	temp=p;
	printf("�ܹ���չ %d ���ڵ�\n",sum_node);
	printf("�ܹ���չ %d ��\n",temp->d);
	printf("*************************************************\n");
	printf("��·�����£�\n");
	for(i=p->d;i>=0;i--)                  //�洢��·���ϸ��ڵ�ĵ�ַ
	{
		path[i]=temp;
		temp=temp->father;
	}
	for(k=0;k<=p->d;k++)                //�����·��
	{
		temp=path[k];                  //�����ڵ�ָ��ָ��
		printf("��%d�� ",temp->d);
		if(k-1>=0)                     //����ƶ�����
		{
			temp_father=path[k-1];
			if(temp->i_0<temp_father->i_0) printf("��>����\n");
			if(temp->i_0>temp_father->i_0) printf("��>����\n");
			if(temp->j_0<temp_father->j_0) printf("��>����\n");
			if(temp->j_0>temp_father->j_0) printf("��>����\n");
		}
		else
			printf("\n");
		printf("��ǰ��f=%d��d=%d��h=%d\n",temp->f,temp->d,temp->h);
		printf("��ǰ�ڵ�״̬Ϊ��\n");
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





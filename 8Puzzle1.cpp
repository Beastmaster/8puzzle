/********************
A implementation of 8 puzzle
Completed algorithm: BFS/DFS/A*

2015.1.20

--QINSHUO
*********************/
#include "8Puzzle1.h"

int main(int argc,char** argv)
{
	int graph_init[] = {8,2,3,1,6,4,7,0,5};//{3,8,2,1,0,5,7,6,4};

	Node* node1 = new Node;
	Node_Init(node1);
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			node1->graphx[i][j] = graph_init[3*i+j];
		}
	}
	Find_Zero(node1);

	node1->position_col =3;
	node1->position_row =2;
	std::cout<<"|-----------Initial Graph--------|"<<std::endl;
	Display_Node(node1);
	std::cout<<"|---------------Begin!-----------|"<<std::endl;

	std::cout<<"select mode: a/b/d or e(exit)"<<std::endl;
	begin_select:
	char select_mode = getchar();
	switch (select_mode)
	{
	case 'd':
		{
			std::cout<<"begin recurring DFS"<<std::endl;
			Recurr_Deep_First(node1);
			goto begin_select;
		}
	case 'b':
		{
			std::cout<<"begin recurring BFS"<<std::endl;
			Recurr_Broad_First(node1);
			goto begin_select;
		}
	case 'a':
		{
			std::cout<<"begin recurring A STAR"<<std::endl;
			A_Star_Begin(graph_init);
			goto begin_select;
		}
	case 'e':
		break;
	default:
		{
			std::cout<<"input error:"<<std::endl<<"select mode: a/b/d"<<std::endl;
			goto begin_select;
		}
	}

	system("pause");
	return 0;
}


void Creat_Up_Node(Node* cur_node)
{
	std::cout<<"creating Up node..."<<std::endl;
	if (cur_node == NULL)
	{
		std::cout<<"an null cur_node"<<std::endl;
		return;
	}
	//test null cur_node
	if (cur_node->graphx[0][0]+
		cur_node->graphx[0][1]+
		cur_node->graphx[0][2]+
		cur_node->graphx[1][0]+
		cur_node->graphx[1][1]+
		cur_node->graphx[1][2]+
		cur_node->graphx[2][0]+
		cur_node->graphx[2][1]+
		cur_node->graphx[2][2] != 36)
	{
		std::cout<<"error: up graph invalid"<<std::endl;
		cur_node->Up_node = NULL;
		return;
	}

	//creat new node
	Node* new_node = new Node;
	Node_Init(new_node);
	new_node->Last_Step = 1;
	new_node->Total_Step = cur_node->Total_Step+1;

	//test position validation first
	if ((cur_node->position_row <= 1)||(cur_node->Last_Step == 2))//down
	{
		std::cout<<"no up node: edge or circle"<<std::endl;
		delete new_node;
		new_node = NULL;
		cur_node->Up_node = NULL;
	}
	else
	{
		//put number into new graph
		for (int i = 0;i<3;i++)
		{
			for (int j = 0;j<3;j++)
			{
				new_node->graphx[i][j] = cur_node->graphx[i][j];
			}
		}
		//change position flag
		new_node->position_row = cur_node->position_row-1;
		new_node->position_col = cur_node->position_col;

		//change position
		new_node->graphx[new_node->position_row-1][new_node->position_col-1] = 
			cur_node->graphx[cur_node->position_row-1][cur_node->position_col-1];
		new_node->graphx[new_node->position_row+1-1][cur_node->position_col-1] =
			cur_node->graphx[cur_node->position_row-1-1][new_node->position_col-1];

		cur_node->Up_node = new_node;
	}
}

void Creat_Down_Node(Node* cur_node)
{
	std::cout<<"creating down node..."<<std::endl;
	if (cur_node == NULL)
	{
		return;
	}
	//test null cur_node
	if (cur_node->graphx[0][0]+
		cur_node->graphx[0][1]+
		cur_node->graphx[0][2]+
		cur_node->graphx[1][0]+
		cur_node->graphx[1][1]+
		cur_node->graphx[1][2]+
		cur_node->graphx[2][0]+
		cur_node->graphx[2][1]+
		cur_node->graphx[2][2] != 36)
	{
		std::cout<<"error: down graph invalid"<<std::endl;
		cur_node->Up_node = NULL;
		return;
	}

	//creat new node
	Node* new_node = new Node;
	Node_Init(new_node);
	new_node->Last_Step = 2;
	new_node->Total_Step = cur_node->Total_Step+1;

	//test position validation first
	if ((cur_node->position_row >= 3)||(cur_node->Last_Step == 1))
	{
		std::cout<<"no down node: edge or circle"<<std::endl;
		delete new_node;
		new_node = NULL;
		cur_node->Up_node = NULL;
	}
	else
	{
		//put number into new graph
		for (int i = 0;i<3;i++)
		{
			for (int j = 0;j<3;j++)
			{
				new_node->graphx[i][j] = cur_node->graphx[i][j];
			}
		}
		//change position flag
		new_node->position_row = cur_node->position_row+1;
		new_node->position_col = cur_node->position_col;

		//change position
		new_node->graphx[new_node->position_row-1][new_node->position_col-1] = 
			cur_node->graphx[cur_node->position_row-1][new_node->position_col-1];
		new_node->graphx[cur_node->position_row-1][cur_node->position_col-1] =
			cur_node->graphx[new_node->position_row-1][new_node->position_col-1];

		cur_node->Down_node = new_node;
	}
}

void Creat_Left_Node(Node* cur_node)
{
	std::cout<<"creating left node ..."<<std::endl;
	if (cur_node == NULL)
	{
		return;
	}
	//test null cur_node
	if (cur_node->graphx[0][0]+
		cur_node->graphx[0][1]+
		cur_node->graphx[0][2]+
		cur_node->graphx[1][0]+
		cur_node->graphx[1][1]+
		cur_node->graphx[1][2]+
		cur_node->graphx[2][0]+
		cur_node->graphx[2][1]+
		cur_node->graphx[2][2] != 36)
	{
		std::cout<<"error: left graph invalid"<<std::endl;
		cur_node->Up_node = NULL;
		return;
	}

	//creat new node
	Node* new_node = new Node;
	Node_Init(new_node);
	new_node->Last_Step = 3;
	new_node->Total_Step = cur_node->Total_Step+1;

	//test position validation first
	if ((cur_node->position_col <= 1)||(cur_node->Last_Step == 4))
	{
		std::cout<<"no left node: edge or circle"<<std::endl;
		delete new_node;
		new_node = NULL;
		cur_node->Up_node = NULL;
	}
	else
	{
		//put number into new graph
		for (int i = 0;i<3;i++)
		{
			for (int j = 0;j<3;j++)
			{
				new_node->graphx[i][j] = cur_node->graphx[i][j];
			}
		}
		//change position flag
		new_node->position_row = cur_node->position_row;
		new_node->position_col = cur_node->position_col-1;

		//change position
		new_node->graphx[new_node->position_row-1][new_node->position_col-1] = 
			cur_node->graphx[cur_node->position_row-1][cur_node->position_col-1];
		new_node->graphx[cur_node->position_row-1][new_node->position_col+1-1] =
			cur_node->graphx[new_node->position_row-1][new_node->position_col-1];

		cur_node->Left_node = new_node;
	}
}

void Creat_Right_Node(Node* cur_node)
{
	std::cout<<"creating right node ..."<<std::endl;
	//test null cur_node
	if (cur_node == NULL)
	{
		return;
	}
	if (cur_node->graphx[0][0]+
		cur_node->graphx[0][1]+
		cur_node->graphx[0][2]+
		cur_node->graphx[1][0]+
		cur_node->graphx[1][1]+
		cur_node->graphx[1][2]+
		cur_node->graphx[2][0]+
		cur_node->graphx[2][1]+
		cur_node->graphx[2][2] != 36)
	{
		std::cout<<"error: right graph invalid"<<std::endl;
		cur_node->Right_node = NULL;
		return;
	}

	//creat new node
	Node* new_node = new Node;
	Node_Init(new_node);
	new_node->Last_Step = 4;
	new_node->Total_Step = cur_node->Total_Step+1;

	//test position validation first
	if ((cur_node->position_col >= 3)||(cur_node->Last_Step == 3))
	{
		std::cout<<"no right node: edge or circle"<<std::endl;
		delete new_node;
		new_node = NULL;
		cur_node->Up_node = NULL;
	}
	else
	{
		//put number into new graph
		for (int i = 0;i<3;i++)
		{
			for (int j = 0;j<3;j++)
			{
				new_node->graphx[i][j] = cur_node->graphx[i][j];
			}
		}
		//change position flag
		new_node->position_row = cur_node->position_row;
		new_node->position_col = cur_node->position_col+1;

		//change position
		new_node->graphx[new_node->position_row-1][cur_node->position_col-1] = 
			cur_node->graphx[new_node->position_row-1][cur_node->position_col+1-1];
		new_node->graphx[new_node->position_row-1][new_node->position_col-1] =
			cur_node->graphx[cur_node->position_row-1][cur_node->position_col-1];

		cur_node->Right_node = new_node;
	}
}



char Test_Valid(Node* nodex)
{
	//if invalid return 0
	//if valid return 1
	if (nodex == NULL)
	{
		std::cout<<"solution invalid--graph null"<<std::endl;
		return 0;
	}

	int arr[16] = {0};
	// put into order
	for(int i=0;i<3;i++)
	{
		arr[i]=nodex->graphx[0][i];
	}
	arr[3]=nodex->graphx[1][2];
	arr[7]=nodex->graphx[1][0];
	
	for(int i=2;i>=0;i--)
	{
		arr[6-i]=nodex->graphx[2][i];
	}
	//sort
	int pos = 0;
	for(int i=0;i<8;i++)
	{
		if (arr[i]==1)
		{
			pos = i;
			break;
		}
	}
	if (arr==NULL)
	{
		std::cout<<"re allocate memeory failed";
		return 1;
	}
	for(int i=0;i<pos;i++)
	{
		arr[i+8] = arr[i];
	}
	for(int i=pos;i<pos+7;i++)
	{
		if(arr[i] >= arr[i+1])
		{
			std::cout<<"solution invalid"<<std::endl;
			return 0;
		}
	}
	std::cout<<"solution valid"<<std::endl;
	return 1;
}

int Recurr_Deep_First(Node* last_node)
{
	//test null of last_node
	if ((last_node == NULL)||(last_node->Total_Step>SETP_DEPTH))
	{
		std::cout<<"recurr: last node null"<<std::endl;
		return 0;
	}
	//test validation of node
	if(Test_Valid(last_node))
	{
		std::cout<<"|---------------successful!!-------------|"<<std::endl;
		Display_Node(last_node);
		std::cout<<"total steps:"<<(int)last_node->Total_Step<<std::endl;
		std::cout<<"|---------------successful!!-------------|"<<std::endl;
		system("pause");
		return 1;
	}
	else
	{
		Display_Node(last_node);
	}
	//move down
	Creat_Down_Node(last_node);
	Recurr_Deep_First(last_node->Down_node);
	if (last_node->Down_node != NULL)
	{
		delete last_node->Down_node;
		last_node->Down_node = NULL;
	}
	//move up
	Creat_Up_Node(last_node);
	Recurr_Deep_First(last_node->Up_node);
	if (last_node->Up_node != NULL)
	{
		delete last_node->Up_node;
		last_node->Up_node = NULL;
	}
	//move left
	Creat_Left_Node(last_node);
	Recurr_Deep_First(last_node->Left_node);
	if (last_node->Left_node != NULL)
	{
		delete last_node->Left_node;
		last_node->Left_node = NULL;
	}
	//move right
	Creat_Right_Node(last_node);
	Recurr_Deep_First(last_node->Right_node);
	if (last_node->Right_node != NULL)
	{
		delete last_node->Right_node;
		last_node->Right_node = NULL;
	}
}



int Recurr_Broad_First(Node* last_node)
{
	//test null of last_node
	if ((last_node == NULL)||(last_node->Total_Step>SETP_DEPTH))
	{
		std::cout<<"recurr: last node null"<<std::endl;
		return 0;
	}

	//creat new node first
	//move down
	Creat_Down_Node(last_node);
	//move up
	Creat_Up_Node(last_node);
	//move left
	Creat_Left_Node(last_node);	
	//move right
	Creat_Right_Node(last_node);

	//test validation of node
	if(Test_Valid(last_node))
	{
		std::cout<<"|---------------successful!!-------------|"<<std::endl;
		Display_Node(last_node);
		std::cout<<"total steps:"<<(int)last_node->Total_Step<<std::endl;
		std::cout<<"|---------------successful!!-------------|"<<std::endl;
		return 0;
	}
	else if (Test_Valid(last_node->Up_node))
	{
		std::cout<<"|---------------successful!!-------------|"<<std::endl;
		Display_Node(last_node->Up_node);
		std::cout<<"total steps:"<<(int)last_node->Up_node->Total_Step<<std::endl;
		std::cout<<"|---------------successful!!-------------|"<<std::endl;
		return 0;
	}
	else if (Test_Valid(last_node->Down_node))
	{
		std::cout<<"|---------------successful!!-------------|"<<std::endl;
		Display_Node(last_node->Down_node);
		std::cout<<"total steps:"<<(int)last_node->Down_node->Total_Step<<std::endl;
		std::cout<<"|---------------successful!!-------------|"<<std::endl;
		return 0;
	}
	else if (Test_Valid(last_node->Right_node))
	{
		std::cout<<"|---------------successful!!-------------|"<<std::endl;
		Display_Node(last_node->Right_node);
		std::cout<<"total steps:"<<(int)last_node->Right_node->Total_Step<<std::endl;
		std::cout<<"|---------------successful!!-------------|"<<std::endl;
		return 0;
	}
	else if (Test_Valid(last_node->Left_node))
	{
		std::cout<<"|---------------successful!!-------------|"<<std::endl;
		Display_Node(last_node->Left_node);
		std::cout<<"total steps:"<<(int)last_node->Left_node->Total_Step<<std::endl;
		std::cout<<"|---------------successful!!-------------|"<<std::endl;
		return 0;
	}
	else
	{
		Display_Node(last_node);
	}


	Recurr_Deep_First(last_node->Down_node);
	if (last_node->Down_node != NULL)
	{
		delete last_node->Down_node;
		last_node->Down_node = NULL;
	}

	Recurr_Deep_First(last_node->Up_node);
	if (last_node->Up_node != NULL)
	{
		delete last_node->Up_node;
		last_node->Up_node = NULL;
	}

	Recurr_Deep_First(last_node->Left_node);
	if (last_node->Left_node != NULL)
	{
		delete last_node->Left_node;
		last_node->Left_node = NULL;
	}

	Recurr_Deep_First(last_node->Right_node);
	if (last_node->Right_node != NULL)
	{
		delete last_node->Right_node;
		last_node->Right_node = NULL;
	}
}


void Node_Init(Node* cur_node)
{
	//0 position: row,col
	cur_node->position_row=0;
	cur_node->position_col = 0;

	//turn up
	cur_node->Up_node = NULL;
	//turn down
	cur_node->Down_node = NULL;
	//turn left
	cur_node->Left_node = NULL;
	//turn right
	cur_node->Right_node = NULL;
	
	//
	cur_node->Last_Step  = 0;
	cur_node->Total_Step = 0;
}

void Find_Zero(Node* nodex)
{
	if (nodex == NULL)
	{
		return;
	}
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			if (nodex->graphx[i][j] == 0)
			{
				nodex->position_row = i+1;
				nodex->position_col = j+1;
				std::cout<<"0 position:"<<nodex->position_row<<","<<nodex->position_col<<std::endl;
				break;
			}
		}
	}
}

void Display_Node(Node* nodex)
{
	if (nodex == NULL)
	{
		std::cout<<"error: node NULL"<<std::endl;
		return;
	}
	else
	{
		for (int i = 0;i<3;i++)
		{
			for (int j = 0;j<3;j++)
			{
				std::cout<<nodex->graphx[i][j]<<"\t";
			}
			std::cout<<std::endl;
		}
	}
	std::cout<<std::endl;
}

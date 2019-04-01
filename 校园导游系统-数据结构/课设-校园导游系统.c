#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define Max 30
#define Infinity 32767

typedef struct{
	int num;					//������ţ� 
	char name[30];				//�������ƣ� 
	char star[6];				//���㻷������ָ���� 
	char information[30];		//�������飻 
}Data;

typedef struct{
	int arcs[Max][Max];			//��(��)����Ϣ�� 
	Data vex[Max];				//������Ϣ���������͸���ʵ��������ж��壻 
	int vexnum;					//������Ŀ�� 
	int arcnum;					//��(��)����Ŀ�� 
}AdjMatrix;						//�ڽӾ���

struct{
		int adjvex;
		int lowcost;
}closedge[Max];

AdjMatrix *G;
int m = 1,min = Infinity; 
int path[20] = {0}; 
int tag;


/*��������*/
void Welcome();						//��ӭ���棻 
void Menuout();						//�˳����棻 
void Boundary_layer();				//���˵����棻 
void Readfile();					//���ļ��� 
void Savefile(int flag);			//�����ļ��� 
void Map();							//���ʵ�ͼ��
void Search();						//��ѯ������Ϣ�� 
void Top();							//�����Ƽ���						
void Information();					//�������飻
void SearchAllRoute();				//��ѯ����������֮������м�·���� 
void DFS(int start,int ending,int stack[],int visited[]);		//DFS��ȱ�������·����
void Minsimpleroute();				//��ѯ����������̼�·������ת�������٣���
void Shortcut();					//��ѯ�����������·������Ȩ���·�����ȣ��� 
void Floyd(int start,int end);		//�����·����Floyd�㷨����
void AddNewRoute();					//�����·�ߣ�
void AddNewSence();					//����¾��㣻 
void DeleteOldRoute();				//������·�ߣ� 
void DeleteOldSence();				//�����ɾ��㣻 
void BestRoute();					//У԰�����о������Ѳ���������
void Prim(int start);				//��Ѳ���������Prim�㷨����С����������
void Satisfied();					//�û�����ȵ��飻 

void main()
{	
	G=(AdjMatrix *)malloc(sizeof(AdjMatrix));
	Welcome();						//��ӭ����; 
	Boundary_layer();				//���˵�����; 	
}

//�������ܣ���ӭ���溯���� 
void  Welcome()
{
	system("color E3"); //���ú���system("color xx") x:������ɫ x:ǰ����ɫ �����������,E=����ɫ,3=����ɫ��5=��ɫ;
	printf("\n\n\n\n"); 
	printf("\t\t\t\t\t*****************************\n");
	printf("\t\t\t\t\t*                           *\n");
	printf("\t\t\t\t\t*       ---��ӭ����---      *\n"); 
	printf("\t\t\t\t\t*      �����ʵ��ѧ��ͼ��   *\n");
	printf("\t\t\t\t\t*                           *\n");
	printf("\t\t\t\t\t*****************************\n");
	printf("\n\t\t\t\t\t\t�밴���������>>>");
	getch();//getch()��������������������ַ���������Ļ�ϣ����������������˵�ѡ�� 
	system("cls"); 
	
} 

//�������ܣ��˳����溯���� 
void Menuout() 
{            
	system("cls");                     
	printf("\n\n");
	printf("\n\n\t\t\t\t*��������|  ллʹ�������ʵ��ѧУ԰����ϵͳ  | �������� *\n");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t\t\t��������˳�>>>\n");
	getch();
	exit(0); 
}  

//�������ܣ����˵����棻 
void Boundary_layer()
{
	char identify[10],secret[6];			//��¼����ݣ� 
	int num=13699,num1;						//numΪ����Աͳһ���� ������Ա����ͳһ��Ϊ12596;
	int choice,f=1,i;						//choiceΪ��������ѡ������룬f�����ж�ѭ���Ƿ���У� 
	while(f){
		printf("\t\t����������������������������������������������������������������������������������������\n");
		printf("\n\t\t\t\t\t\t\t��¼\n\n");
		printf("\t\t\t��ѡ�����Ա��¼�����룺manager�������û���¼�����룺other��\n\t\t\t");
		scanf("%s",identify);
		if(strcmp(identify,"manager")==0){
			printf("\n\t\t\t�������˺ţ�\n\t\t\t");
			scanf("%d",&num1);
			getchar();
			printf("\n\t\t\t����������\n\t\t\t");
			for(i=0;i<5;i++)
			{
				secret[i]=getch();
				if(secret[i]=='\b')
				{
					printf("\b \b");
					i=i-2;
				}
				else 
					printf("*");
			}
			getch(); 
		}
		printf("\n\n\t\t����������������������������������������������������������������������������������������\n");
		getch();
		if( (strcmp(identify,"manager")==0) && (num1==num) && (strcmp(secret,"12596")==0))
		do{
			f=0;
			system("cls");
			printf("\t\t\t������������������������������������������������������������\n");
			printf("\n\t\t\t�������������У԰����ϵͳ�������������\n\n");
			printf("\t\t\t                        1����ѯУ԰ȫ��ͼ\n\n");
			printf("\t\t\t                        2����ѯ������Ϣ\n\n");
			printf("\t\t\t                        3�������·��\n\n");
			printf("\t\t\t                        4������¾���\n\n");
			printf("\t\t\t                        5��������·��\n\n");
			printf("\t\t\t                        6�������ɾ���\n\n");
			printf("\t\t\t                        7����ѯ�����������м�·��\n\n");
			printf("\t\t\t                        8����ѯ����������̼�·��\n\n");
			printf("\t\t\t                        9����ѯ���������ѷ���·��\n\n");
			printf("\t\t\t                        10��У԰���о������Ѳ�������\n\n");
			printf("\t\t\t                        0���˳�ϵͳ\n\n");
			printf("\t\t\t                           ��ѡ��0-10��:\n\n");
			printf("\t\t\t������������������������������������������������������������\n\t\t\t");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:Map(); break;
					case 2:Search(); break;
						case 3:AddNewRoute(); break; 
							case 4:AddNewSence(); break;
								case 5:DeleteOldRoute(); break;
									case 6:DeleteOldSence(); break;
										case 7:SearchAllRoute(); break;
											case 8:Minsimpleroute(); break;
												case 9:Shortcut(); break;
													case 10:BestRoute(); break; 
														case 0:Menuout(); break;
			}
		}while(choice!=0);
		else if(strcmp(identify,"other")==0)
		do{
			f=0;
			system("cls");
			printf("\t\t\t������������������������������������������������������������\n");
			printf("\n\t\t\t�������������У԰����ϵͳ�������������\n\n");
			printf("\t\t\t                        1����ѯУ԰ȫ��ͼ\n\n");
			printf("\t\t\t                        2����ѯ������Ϣ\n\n");
			printf("\t\t\t                        3����ѯ�����������м�·��\n\n");
			printf("\t\t\t                        4����ѯ����������̼�·��\n\n");
			printf("\t\t\t                        5����ѯ���������ѷ���·��\n\n");
			printf("\t\t\t                        6����д�û������\n\n");
			printf("\t\t\t                        0���˳�ϵͳ\n\n");
			printf("\t\t\t                           ��ѡ��0-6��:\n\n");
			printf("\t\t\t������������������������������������������������������������\n\t\t\t");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:Map(); break;
					case 2:Search(); break;
						case 3:SearchAllRoute(); break;
							case 4:Minsimpleroute(); break;
								case 5:Shortcut(); break;
									case 6:Satisfied(); break;
										case 0:Menuout(); break;
			}
		}while(choice!=0);
		else{
			printf("\n\t\t\t������������������(��������˻�)!\n"); 
			getch();
			system("cls");
		}	
	}
}

//�������ܣ����Ҹ����ھ����е�λ�ã� 
int LocateVex(char *v)
{
	int i;
	for(i=1;i<=G->vexnum;i++)
		if(strcmp(G->vex[i].name,v)==0)
			return i;
	return 0;
}

//�������ܣ����ļ��� 
void Readfile()
{
	FILE *fp1,*fp2;
	int i,j,m,n,len;
	char filename1[30]={"У԰������Ϣ.txt"},filename2[30]={"У԰����·��.txt"};
	char start[30],end[30];
	fp1=fopen(filename1,"rt");
	fp2=fopen(filename2,"rt");
	if(!fp1 || !fp2)
	{
		printf("���ļ�������������˳�!\n");
		getch();
		exit(1);	
	}
	else{ 
		fscanf(fp1,"%d %d\n",&G->vexnum,&G->arcnum);
		for(i=1;i<=G->vexnum;i++)
			for(j=1;j<=G->vexnum;j++)
				G->arcs[i][j]=Infinity;
		for(i=1;i<=G->vexnum;i++)
		{
			fscanf(fp1,"%d %s %s %s\n",&G->vex[i].num,G->vex[i].name,G->vex[i].star,G->vex[i].information);
		}
		for(i=1;i<=G->arcnum;i++)
		{
			fscanf(fp2,"%s %s %d\n",start,end,&len);
			m=LocateVex(start);
			n=LocateVex(end);
			G->arcs[m][n]=len;
			G->arcs[n][m]=len;
		}
	}
}

//�������ܣ������ļ��� 
void Savefile(int flag)
{
	FILE *fp;
	int i,j,k;
	char filename1[30]={"У԰������Ϣ.txt"},filename2[30]={"У԰����·��.txt"};
	if(flag==1)
	{
		fp=fopen(filename1,"wt");
		if(!fp)
		{
			printf("���ļ�������������˳�!\n");
			getch();
			exit(1);	
		}
		fprintf(fp,"%d %d\n",G->vexnum,G->arcnum);
		for(i=1;i<=G->vexnum;i++)
		{
			fprintf(fp,"%d %s %s %s\n",G->vex[i].num,G->vex[i].name,G->vex[i].star,G->vex[i].information);
		}
		fclose(fp);
	}
	if(flag==2) 
	{
		fp=fopen(filename2,"wt");
		if(!fp)
		{
			printf("���ļ�������������˳�!\n");
			getch();
			exit(1);	
		}
   		for(j=1;j<=G->vexnum;j++)
			for(i=1;i<=j;i++)
			{
				if(G->arcs[i][j]!=Infinity || G->arcs[j][i]!=Infinity)
				{
					fprintf(fp,"%s %s %d\n",G->vex[i].name,G->vex[j].name,G->arcs[i][j]);
				}
			}
		fclose(fp);
	}
}

//�������ܣ����ʵ�ͼ�� 
void Map()
{ 
	system("cls");
    printf("\t����������������������������������������������������������������������������������������������\n");   
	printf("\t�����������������������������������������������行\n");
    printf("\t��                                 �����ʵ��ѧƽ��ͼ                                       ��\n");
    printf("\t�����������������������������������������������行\n");
	printf("\t��               ����                       ��    ��                                   ���� ��\n");     
	printf("\t��              ��170                       ��    ��            230              �����ٳ�   ��\n");
	printf("\t��              ��������������¥            ��    ��    �������Ũ�����������         50 ��  ��\n"); 
	printf("\t��              ��                          ��    ��                      ��     �ݷ��ѧ¥ ��\n");     
	printf("\t��      ����������                          �� �� ��                      ����������������  ��\n"); 
	printf("\t��  230 ��      ��                          ��    ��                  530 ��            ��  ��\n");     
	printf("\t��      ��      ��300                       ��    ��                      ��  	   100  ��  ��\n");    
	printf("\t��     ��ѧ¥   ��                          ��    ��                      ��      ��������¥��\n");    
	printf("\t��      ��      ��������   ��ѧ�������   �� �� ��                      ��            ��  ��\n");    
	printf("\t��      ��80    ��100                       ��    ��              ����������      210   ��  ��\n");    
	printf("\t��      ��      ��        100               ��    ��          ����Է                        ��\n");
	printf("\t��      ��        ͼ��ݨ�������            ��    ��             ��                         ��\n");    
	printf("\t��      ʵ��¥                              ��    ��         150 ��                 �������è�\n");     
	printf("\t��      ��         ������������������������������������������������                    ��   ��\n");     
	printf("\t��  100 ��         ��                          ����            ����                    ��   ��\n");
	printf("\t��      ��   С�ٳ�������������������������������������������������                    ��   ��\n");
	printf("\t��     ��          ��200     ����    ��ٳ� ��    ����������                           ��   ��\n");    
	printf("\t��     ��80        ��      70��             ��    ��      ��   ��ѧ������  ������������   ��\n");
	printf("\t��     ��          ��        ��             ��    ��      ��                           ��   ��\n");
	printf("\t��     �� ����     ������������   ������    ��    ��   100��                           ��   ��\n");     
	printf("\t��    ԡ��         ��100                    �� �� ��      ��                                ��\n");    
	printf("\t��                 ��                       ��    ��      ��                                ��\n");    
	printf("\t��                  ����Է                  ��    ��      ����������������������¥          ��\n");     
	printf("\t��               70��                       ��    ��                                        ��\n");
    printf("\t��                 ��                       ��    ��                                        ��\n");
	printf("\t��     ������  ��ѧ������  ������           ��    ��                                        ��\n");      
	printf("\t��   60��                      ��60         ��    ��                                        ��\n");     
	printf("\t��     ��                      ��           �� �� ��                                        ��\n");     
	printf("\t��              ����¥                      ��    ��                                        ��\n");     
	printf("\t����������������������������������������������������������������������������������������������\n");
	getch();
}

//�������ܣ���������Ƽ�
void Top()
{	
	system("cls");
	Readfile();
	int i,j,k,m,len[G->vexnum][2];
	for(i=1;i<=G->vexnum;i++)					//���㾰���Ǽ�ָ���� 
	{
		len[i][0]=strlen(G->vex[i].star);
		len[i][1]=i;
	}
	for(i=1;i<=G->vexnum-1;i++)					//�����㰴���Ǽ��ָߵ������� 
	{
		k=i;
		for(j=i+1;j<=G->vexnum;j++)
			if(len[k][0]<len[j][0])		k=j;
		if(k!=j)
		{
			m=len[i][0];
			len[i][0]=len[k][0];
			len[k][0]=m;
			m=len[i][1];
			len[i][1]=len[k][1];
			len[k][1]=m;
		}
	}
	printf("\n\t\t\t\t������������������������\n\n");
	printf("\t\t\t\t                   �������ָ��               \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\t\tNO.%-6d %-20s%s\n\n",i,G->vex[len[i][1]].name,G->vex[len[i][1]].star);
	 } 
	printf("\n\t\t\t\t������������������������\n\n");
	getch();
} 

//�������ܣ���ѯ�������飻
void Information()
{
	int i,j,choice;
	Readfile();
	system("cls");
	printf("\n\t\t\t\t���������������������������������\n\n");
	printf("\t\t\t\t                            �����ѯ                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-10s",i,G->vex[i].name);
		if(i%2==0)	printf("\n\n"); 
	 }  
	printf("\n\t\t\t\t������ϣ����ѯ�ص�ǰ����ţ�1-%d����",G->vexnum); 
	printf("\n\t\t\t\t���������������������������������\n\n\t\t\t\t");
	scanf("%d",&choice);
	if(choice<=G->vexnum)
	{
		printf("\n\t\t\t\t��%s\t�Ǽ���%s\n\n",G->vex[choice].name,G->vex[choice].star);
		printf("\t\t\t\t��������ܣ� %s",G->vex[choice].information);
 	}
 	else printf("\n\t\t\t\t������Ϣ����");
 	getchar();
	getch();
}

//�������ܣ���ѯ������Ϣ�� 
void Search()
{
	int choice,i;
	system("cls");
	printf("\n\n\n\n"); 
	printf("\t\t\t\t\t*************************************\n");
	printf("\t\t\t\t\t*                                   *\n");
	printf("\t\t\t\t\t*       1��Top�����Ƽ�              *\n"); 
	printf("\t\t\t\t\t*                                   *\n");
	printf("\t\t\t\t\t*       2����ѯĳ����������         *\n");
	printf("\t\t\t\t\t*                                   *\n");
	printf("\t\t\t\t\t*             �����루1/2����       *\n");
	printf("\t\t\t\t\t*************************************\n\t\t\t\t\t");
	scanf("%d",&choice); 
	switch(choice)
	{
		case 1:Top();break;
			case 2:Information();break;
				default:printf("\n\t\t\t\t������Ϣ����");
	}
	getchar();
	getch();
} 

//�������ܣ�������������֮������м�·���� 
void SearchAllRoute() 
{        
	Readfile();
	int i,start,end;        
	int stack[100]={0};    
	int visited[50]={0}; 
	system("cls");
	printf("\n\t\t\t\t�������������������������������\n\n");
	printf("\t\t\t\t                          У԰����                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-17s",i,G->vex[i].name);
		if(i%2==0)	printf("\n"); 
	 }  
	printf("\n\t\t\t\t�������������������������������\n\n\t\t\t\t");
	printf("\n\t\t\t\t�����������ţ�1-%d����",G->vexnum);
	scanf("%d",&start);        
	printf("\n\t\t\t\t�������յ���ţ�1-%d����",G->vexnum);   
	scanf("%d",&end);
	if(start<=G->vexnum && end<=G->vexnum)
	{ 
		stack[0]=start;               
		visited[start]=1;  
		tag=1;     
		DFS(start,end,stack,visited); 
		printf("\n\t\t\t\t�����Ǵ� %s----->%s �����п���·��!\n",G->vex[start].name,G->vex[end].name);
	}
	else printf("\n\t\t\t\t������Ϣ����");
	getchar();
	getch();
}   

//�������ܣ�DFS��ȱ�������·���� 
void DFS(int start,int ending,int stack[],int visited[])
{    
	Readfile();   
	int i, j;      
	for(i=1; i<=G->vexnum; i++) 
	{         
		if(G->arcs[start][i] != Infinity && visited[i]==0)
		{             
			if(i == ending){						//������ѵ����յ㣬������ղž�����·��                
				if(tag==1){ 						// tag�����ж�������·����������·��,tag=1ʱ������·���� 
					printf("\n\t\t\t\t");         
					for(j=0; j<m; j++)      
						printf("%s-->", G->vex[stack[j]].name);    
					printf("%s\n", G->vex[ending].name);  
					getch();  
				}   
				else   								//������·��ʱ��¼�������ٵ�·��  
					if(m<=min){        
						min=m;       
						for(j=0;j<m;j++)       
							path[j]=stack[j];      
					}            
			}              
			else{									//����õ㲻���յ�                           
				visited[i]=1;                 
				stack[m] = i;						//���õ������              
				m++;                
				DFS(i,ending,stack,visited);		//��������        
				visited[i]=0;              
				m--;             
			}        
		}  
	} 
} 

//�������ܣ�������������֮�����̼�·������ת�������٣�DFS�㷨���� 
void Minsimpleroute() 
{
	char name[20];   
	int i;     
	int start,end;    
	int stack[100]={0};     
	int visited[50]={0}; 
	Readfile();      
	system("cls");
	printf("\n\t\t\t\t�������������������������������\n\n");
	printf("\t\t\t\t                          У԰����                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-17s",i,G->vex[i].name);
		if(i%2==0)	printf("\n"); 
	 }  
	printf("\n\t\t\t\t�������������������������������\n\n\t\t\t\t");
	printf("\n\t\t\t\t�����������ţ�1-%d����",G->vexnum);
	scanf("%d",&start);        
	printf("\n\t\t\t\t�������յ���ţ�1-%d����",G->vexnum);   
	scanf("%d",&end);
	if(start<=G->vexnum && end<=G->vexnum)
	{
		visited[start]=1; 
		stack[0]=start;   
		tag=0;      
		DFS(start,end,stack,visited);   
		printf("\n\t\t\t\t��ת�������ٵ�·��Ϊ��\n\t\t\t\t");       
		for(i=0;i<min;i++)          
		printf("%s-->",G->vex[path[i]].name);    
		printf("%s\n", G->vex[end].name);
	}
	else printf("\n\t\t\t\t������Ϣ����");
	getchar();
	getch();
} 

//�������ܣ�����������֮�����ѷ���·�ߣ���Ȩ���·�����ȣ��� 
void Shortcut()
{     
	char name[20];   
	int start,end;     
	int i;     
	int dist[Max]; 				//dist�������ڼ�¼Դ�㵽������������̾���ֵ�� 
	Readfile();   
	system("cls");
	printf("\n\t\t\t\t�������������������������������\n\n");
	printf("\t\t\t\t                          У԰����                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-17s",i,G->vex[i].name);
		if(i%2==0)	printf("\n"); 
	 }  
	printf("\n\t\t\t\t�������������������������������\n\n\t\t\t\t");
	printf("\n\t\t\t\t�����������ţ�1-%d����",G->vexnum);
	scanf("%d",&start);        
	printf("\n\t\t\t\t�������յ���ţ�1-%d����",G->vexnum);   
	scanf("%d",&end);
	if(start<=G->vexnum && end<=G->vexnum)
	{
		if(start<end)
			Floyd(end,start);
		else 
			Floyd(start,end);
	}
	else printf("\n\t\t\t\t������Ϣ����");
	getchar();
	getch();
}   

//�������ܣ������·����Floyd�㷨���� 
void Floyd(int start,int end)
{
	int F[Max][Max];
	int path[Max][Max];
	int i,j,k,m,temp;
	for(i=1;i<=G->vexnum;i++)
		for(j=1;j<=G->vexnum;j++)
			F[i][j]=Infinity;
	for(i=1;i<=G->vexnum;i++)
		for(j=1;j<=G->vexnum;j++)
		{
			if(G->arcs[i][j]!=Infinity)
			{
				F[i][j]=G->arcs[i][j];
			}
			if(G->arcs[j][i]!=Infinity)
			{
				F[i][j]=G->arcs[j][i];
			}
			if(i!=j)
			path[i][j]=j;
			else path[i][j]=0;
		}	
	for(k=1;k<=G->vexnum;k++)
	{
		for(j=1;j<=i;j++)
		{
			for(i=1;i<=G->vexnum;i++)
				if(F[i][j]>F[i][k]+F[k][j])
				{
					F[i][j]=F[i][k]+F[k][j];
					F[j][i]=F[i][k]+F[k][j];
					path[i][j]=path[i][k];
				}
		}
	}
	printf("\n\t\t\t\t��%s��%s�����·��Ϊ��\n\n\t\t\t\t��%s",G->vex[start].name,G->vex[end].name,G->vex[start].name);
	temp=path[start][end];
	while(1){
		printf("----->%s",G->vex[temp].name);
		if(temp == end)	break;
		temp=path[temp][end];
	}
	printf("\n\t\t\t\t����%dkm",F[start][end]); 
	getch();
} 

//�������ܣ���д�û�����ȣ�
void Satisfied()
{
	char s[6];
	int choice,i;
	Readfile();
	system("cls");
	printf("\n\t\t\t\t�������������������������������\n\n");
	printf("\t\t\t\t                          У԰����                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-17s",i,G->vex[i].name);
		if(i%2==0)	printf("\n"); 
	 }  
	printf("\t\t\t\t�������㱦�������ɣ�\n");
	printf("\t\t\t\t��ѡ������۾���(1-%d)��\n\t\t\t\t",G->vexnum);
	scanf("%d",&choice);
	printf("\t\t\t\t�����������,�Ǽ���1-5(����*)��\n\t\t\t\t");
	scanf("%s",s);
	if(choice<=G->vexnum && strlen(s)<=5 && strlen(s)>0)
	{
		for(i=1;i<=G->vexnum;i++)							//�����������ȣ� 
			if(i==choice)
			{
				if(strlen(s)>strlen(G->vex[i].star))
				strcpy(G->vex[i].star,s);
				break;
			}
			Savefile(1);
		printf("��л�������ۡ�\n");
	}
	else printf("\n\t\t\t\t������Ϣ����"); 
	getchar();
	getch();
}
 
//�������ܣ������·�ߣ� 
void AddNewRoute()
{
	int start,end,weight,i;
	FILE *fp;
	char filename[30]={"У԰����·��.txt"};
	Readfile(); 
	system("cls");
	printf("\n\t\t\t\t�������������������������������\n\n");
	printf("\t\t\t\t                          У԰����                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-17s",i,G->vex[i].name);
		if(i%2==0)	printf("\n"); 
	 }  
	printf("\n\t\t\t\t�������������������������������\n\n\t\t\t\t");
	printf("\n\t\t\t\t����������·�ߵ������ţ�1-%d����",G->vexnum);
	scanf("%d",&start);        
	printf("\n\t\t\t\t����������·�ߵ��յ���ţ�1-%d����",G->vexnum);   
	scanf("%d",&end);
	printf("\n\t\t\t\t��������Ҫ��ӵ�·�����ȣ�");
	scanf("%d",&weight);
	if(start<=G->vexnum && end<=G->vexnum && weight>0)
	{
		G->arcs[start][end]=weight;
		G->arcs[end][start]=weight;
		G->arcnum++; 
		Savefile(1);
		fp=fopen(filename,"a");
		if(fp==NULL)
		{
			printf("д�ļ�������������˳���");
			getch();
			exit(1);
		}
		fprintf(fp,"%s %s %d\n",G->vex[start].name,G->vex[end].name,weight); 
		fclose(fp);
		printf("\n���·�߳ɹ���");
	}
	else printf("\n\t\t\t\t������Ϣ����");
	getchar();
	getch();
}

//�������ܣ�����¾��㣻 
void AddNewSence()
{
	Readfile();
	FILE *fp;
	char sence[30];
	char filename[30]={"У԰������Ϣ.txt"};
	G->vexnum++; 
	system("cls");
	printf("\n\t\t\t\t�������������������������������\n\n");
	printf("\n\t\t\t\t����������·�ӵľ������ƣ�\n\t\t\t\t");
	scanf("%s",G->vex[G->vexnum].name);
	printf("\n\t\t\t\t�����뾰���Ǽ���\n\t\t\t\t");
	scanf("%s",G->vex[G->vexnum].star);
	printf("\n\t\t\t\t�����뾰�����飺\n\t\t\t\t");
	scanf("%s",G->vex[G->vexnum].information);
	fp=fopen(filename,"a");
	if(fp==NULL)
	{
		printf("д�ļ�������������˳���");
		getch();
		exit(1);
	}
	fprintf(fp,"%d %s %s %s\n",G->vexnum,G->vex[G->vexnum].name,G->vex[G->vexnum].star,G->vex[G->vexnum].information); 
	fclose(fp);
	Savefile(1);
	printf("%d\n",G->vexnum);
	printf("��ӳɹ���");
	getch(); 
}

//�������ܣ�������·�ߣ� 
void DeleteOldRoute()
{
	int start,end,i;
	FILE *fp;
	char filename[30]={"У԰����·��.txt"};
	Readfile(); 
	system("cls");
	printf("\n\t\t\t\t�������������������������������\n\n");
	printf("\t\t\t\t                          У԰����                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-17s",i,G->vex[i].name);
		if(i%2==0)	printf("\n"); 
	 }  
	printf("\n\t\t\t\t�������������������������������\n\n\t\t\t\t");
	printf("\n\t\t\t\t�����볷����·�ߵ������ţ�1-%d����",G->vexnum);
	scanf("%d",&start);        
	printf("\n\t\t\t\t�����볷����·�ߵ��յ���ţ�1-%d����",G->vexnum);   
	scanf("%d",&end);
	if(start<=G->vexnum && end<=G->vexnum)
	{
		G->arcnum--;
		G->arcs[start][end]=Infinity;
		G->arcs[end][start]=Infinity; 
		Savefile(1);
		Savefile(2);
		printf("\t\t\t\tɾ��·�߳ɹ���\n");
	}
	else printf("\n\t\t\t\t������Ϣ����");
	getchar();
	getch();
}

//�������ܣ������ɾ��㣻
void DeleteOldSence()
{
	int number,i,j; 
	Readfile(); 
	system("cls");
	printf("\n\t\t\t\t�������������������������������\n\n");
	printf("\t\t\t\t                          У԰����                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-17s",i,G->vex[i].name);
		if(i%2==0)	printf("\n"); 
	 }  
	printf("\n\t\t\t\t�������������������������������\n\n\t\t\t\t");
	printf("\n\t\t\t\t��������Ҫ�����ɾ������ţ�1-%d����",G->vexnum);
	scanf("%d",&number); 
	   	for(i=1;i<=G->vexnum;i++)									//ɾ����ɾ�����ص�·��; 
	   	{
	   		if(G->arcs[i][number]!=Infinity || G->arcs[number][i]!=Infinity)
	   		{
				G->arcs[i][number]=Infinity;
				G->arcs[number][i]=Infinity;
				G->arcnum--;   			
			}
	   	}
	   	for(i=number;i<G->vexnum;i++)
		{   for(j=1;j<=G->vexnum;j++)
			   	G->arcs[i][j]=G->arcs[i+1][j];
		} 
		for(j=number;j<G->vexnum;j++)
		{  for(i=1;i<=G->vexnum;i++)  
			 G->arcs[i][j]=G->arcs[i][j+1]; 
		}   	
		   for(i=number;i<G->vexnum;i++)								//ɾ���ɾ��㣻 
		{
			strcpy(G->vex[i].name,G->vex[i+1].name);
			strcpy(G->vex[i].star,G->vex[i+1].star);
			strcpy(G->vex[i].information,G->vex[i+1].information);
	   }     
	   	G->vexnum--;
	   	Savefile(1);
	   	Savefile(2);
	   printf("\n\t\t\t\t��������ɹ���");
	getch();
} 

//�������ܣ�У԰�����о������Ѳ���������
void BestRoute()
{
	int start;
	printf("\t\t\t\t��������ʼ�㣺\n\t\t\t\t");
	scanf("%d",&start);
	printf("\n\n\t\t\t\t��Ѳ���·��Ϊ��\n\t\t\t\t"); 
	Prim(start);
	getch();
}

//�������ܣ���Ѳ���������Prim�㷨����С���������� 
void Prim(int start)
{
	Readfile();
	int i,e,k,m,min,j=1,sum=0;
	int s[Max];
	s[0]=start;
	closedge[start].lowcost=0;
	for(i=1;i<=G->vexnum;i++)
		if(i!=start)
		{
			closedge[i].adjvex=start;
			closedge[i].lowcost=G->arcs[start][i];
		}
	for(e=1;e<=G->vexnum-1;e++)
	{
		min=Infinity;
		for(k=1;k<=G->vexnum;k++)
		{
			if(closedge[k].lowcost!=0 && closedge[k].lowcost<min)
			{
				m=k;
				min=closedge[k].lowcost;
			}
		}
		sum+=closedge[m].lowcost;
		closedge[m].lowcost=0;
		s[j++]=m;
		for(i=1;i<=G->vexnum;i++)
			if(i!=m && G->arcs[m][i]<closedge[i].lowcost)
			{
				closedge[i].lowcost=G->arcs[m][i];
				closedge[i].adjvex=m;
			}
	}
	printf("·�����ȣ�%dkm\n\n",sum);	
	for(i=0;i<G->vexnum-1;i++)
	{
		printf("%s----->",G->vex[s[i]].name);
	}
	printf("%s",G->vex[s[i]].name);
	getch();
}

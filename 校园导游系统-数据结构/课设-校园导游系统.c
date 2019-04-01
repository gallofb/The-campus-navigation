#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define Max 30
#define Infinity 32767

typedef struct{
	int num;					//景点序号； 
	char name[30];				//景点名称； 
	char star[6];				//景点环境优美指数； 
	char information[30];		//景点详情； 
}Data;

typedef struct{
	int arcs[Max][Max];			//边(或弧)的信息； 
	Data vex[Max];				//顶点信息，顶点类型根据实际情况自行定义； 
	int vexnum;					//顶点数目； 
	int arcnum;					//边(或弧)的数目； 
}AdjMatrix;						//邻接矩阵；

struct{
		int adjvex;
		int lowcost;
}closedge[Max];

AdjMatrix *G;
int m = 1,min = Infinity; 
int path[20] = {0}; 
int tag;


/*函数声明*/
void Welcome();						//欢迎界面； 
void Menuout();						//退出界面； 
void Boundary_layer();				//主菜单界面； 
void Readfile();					//读文件； 
void Savefile(int flag);			//保存文件； 
void Map();							//西邮地图；
void Search();						//查询景点信息； 
void Top();							//景点推荐；						
void Information();					//景点详情；
void SearchAllRoute();				//查询任意两景点之间的所有简单路径； 
void DFS(int start,int ending,int stack[],int visited[]);		//DFS深度遍历查找路径；
void Minsimpleroute();				//查询两景点间的最短简单路径（中转次数最少）；
void Shortcut();					//查询两景点间的最短路径（带权最短路径长度）； 
void Floyd(int start,int end);		//求最短路径（Floyd算法）；
void AddNewRoute();					//添加新路线；
void AddNewSence();					//添加新景点； 
void DeleteOldRoute();				//撤销旧路线； 
void DeleteOldSence();				//撤销旧景点； 
void BestRoute();					//校园中所有景点的最佳布网方案；
void Prim(int start);				//最佳布网方案（Prim算法求最小生成树）；
void Satisfied();					//用户满意度调查； 

void main()
{	
	G=(AdjMatrix *)malloc(sizeof(AdjMatrix));
	Welcome();						//欢迎界面; 
	Boundary_layer();				//主菜单界面; 	
}

//函数功能：欢迎界面函数； 
void  Welcome()
{
	system("color E3"); //调用函数system("color xx") x:背景颜色 x:前景颜色 可以随意组合,E=淡黄色,3=湖蓝色，5=紫色;
	printf("\n\n\n\n"); 
	printf("\t\t\t\t\t*****************************\n");
	printf("\t\t\t\t\t*                           *\n");
	printf("\t\t\t\t\t*       ---欢迎来到---      *\n"); 
	printf("\t\t\t\t\t*      西安邮电大学地图网   *\n");
	printf("\t\t\t\t\t*                           *\n");
	printf("\t\t\t\t\t*****************************\n");
	printf("\n\t\t\t\t\t\t请按任意键继续>>>");
	getch();//getch()函数不将键盘上输入的字符回显在屏幕上，常用于密码输入或菜单选择 
	system("cls"); 
	
} 

//函数功能：退出界面函数； 
void Menuout() 
{            
	system("cls");                     
	printf("\n\n");
	printf("\n\n\t\t\t\t*★★★★★★★|  谢谢使用西安邮电大学校园导游系统  | ★★★★★★★ *\n");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t\t\t按任意键退出>>>\n");
	getch();
	exit(0); 
}  

//函数功能：主菜单界面； 
void Boundary_layer()
{
	char identify[10],secret[6];			//登录者身份； 
	int num=13699,num1;						//num为管理员统一工号 ，管理员密码统一设为12596;
	int choice,f=1,i;						//choice为函数功能选项的输入，f用于判断循环是否进行； 
	while(f){
		printf("\t\t▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼\n");
		printf("\n\t\t\t\t\t\t\t登录\n\n");
		printf("\t\t\t请选择管理员登录（输入：manager）或者用户登录（输入：other）\n\t\t\t");
		scanf("%s",identify);
		if(strcmp(identify,"manager")==0){
			printf("\n\t\t\t请输入账号：\n\t\t\t");
			scanf("%d",&num1);
			getchar();
			printf("\n\t\t\t请输入密码\n\t\t\t");
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
		printf("\n\n\t\t▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼\n");
		getch();
		if( (strcmp(identify,"manager")==0) && (num1==num) && (strcmp(secret,"12596")==0))
		do{
			f=0;
			system("cls");
			printf("\t\t\t▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼\n");
			printf("\n\t\t\t★★★★★★★★★★★★校园导游系统★★★★★★★★★★★★\n\n");
			printf("\t\t\t                        1、查询校园全景图\n\n");
			printf("\t\t\t                        2、查询景点信息\n\n");
			printf("\t\t\t                        3、添加新路线\n\n");
			printf("\t\t\t                        4、添加新景点\n\n");
			printf("\t\t\t                        5、撤销旧路线\n\n");
			printf("\t\t\t                        6、撤销旧景点\n\n");
			printf("\t\t\t                        7、查询两景点间的所有简单路径\n\n");
			printf("\t\t\t                        8、查询两景点间的最短简单路径\n\n");
			printf("\t\t\t                        9、查询两景点间最佳访问路线\n\n");
			printf("\t\t\t                        10、校园所有景点的最佳布网方案\n\n");
			printf("\t\t\t                        0、退出系统\n\n");
			printf("\t\t\t                           请选择（0-10）:\n\n");
			printf("\t\t\t▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼\n\t\t\t");
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
			printf("\t\t\t▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼\n");
			printf("\n\t\t\t★★★★★★★★★★★★校园导游系统★★★★★★★★★★★★\n\n");
			printf("\t\t\t                        1、查询校园全景图\n\n");
			printf("\t\t\t                        2、查询景点信息\n\n");
			printf("\t\t\t                        3、查询两景点间的所有简单路径\n\n");
			printf("\t\t\t                        4、查询两景点间的最短简单路径\n\n");
			printf("\t\t\t                        5、查询两景点间最佳访问路线\n\n");
			printf("\t\t\t                        6、填写用户满意度\n\n");
			printf("\t\t\t                        0、退出系统\n\n");
			printf("\t\t\t                           请选择（0-6）:\n\n");
			printf("\t\t\t▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼▲▼\n\t\t\t");
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
			printf("\n\t\t\t输入有误，请重新输入(按任意键退回)!\n"); 
			getch();
			system("cls");
		}	
	}
}

//函数功能：查找各点在矩阵中的位置； 
int LocateVex(char *v)
{
	int i;
	for(i=1;i<=G->vexnum;i++)
		if(strcmp(G->vex[i].name,v)==0)
			return i;
	return 0;
}

//函数功能：读文件； 
void Readfile()
{
	FILE *fp1,*fp2;
	int i,j,m,n,len;
	char filename1[30]={"校园景点信息.txt"},filename2[30]={"校园景点路径.txt"};
	char start[30],end[30];
	fp1=fopen(filename1,"rt");
	fp2=fopen(filename2,"rt");
	if(!fp1 || !fp2)
	{
		printf("读文件出错，按任意键退出!\n");
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

//函数功能：保存文件； 
void Savefile(int flag)
{
	FILE *fp;
	int i,j,k;
	char filename1[30]={"校园景点信息.txt"},filename2[30]={"校园景点路径.txt"};
	if(flag==1)
	{
		fp=fopen(filename1,"wt");
		if(!fp)
		{
			printf("读文件出错，按任意键退出!\n");
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
			printf("读文件出错，按任意键退出!\n");
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

//函数功能：西邮地图； 
void Map()
{ 
	system("cls");
    printf("\t▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n");   
	printf("\t▓★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★▓\n");
    printf("\t▓                                 西安邮电大学平面图                                       ▓\n");
    printf("\t▓★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★▓\n");
	printf("\t▓               北门                       ▓    ▓                                   ↑北 ▓\n");     
	printf("\t▓              ▓170                       ▓    ▓            230              东区操场   ▓\n");
	printf("\t▓              ▓▓▓▓▓行政楼            ▓    ▓    东区正门▓▓▓▓▓▓         50 ▓  ▓\n"); 
	printf("\t▓              ▓                          ▓    ▓                      ▓     逸夫教学楼 ▓\n");     
	printf("\t▓      ▓▓▓▓▓                          ▓ 子 ▓                      ▓▓▓▓▓▓▓▓  ▓\n"); 
	printf("\t▓  230 ▓      ▓                          ▓    ▓                  530 ▓            ▓  ▓\n");     
	printf("\t▓      ▓      ▓300                       ▓    ▓                      ▓  	   100  ▓  ▓\n");    
	printf("\t▓     教学楼   ▓                          ▓    ▓                      ▓      东区宿舍楼▓\n");    
	printf("\t▓      ▓      ▓▓▓▓   大学生活动中心   ▓ 午 ▓                      ▓            ▓  ▓\n");    
	printf("\t▓      ▓80    ▓100                       ▓    ▓              ▓▓▓▓▓      210   ▓  ▓\n");    
	printf("\t▓      ▓      ▓        100               ▓    ▓          东升苑                        ▓\n");
	printf("\t▓      ▓        图书馆▓▓▓▓            ▓    ▓             ▓                         ▓\n");    
	printf("\t▓      实验楼                              ▓    ▓         150 ▓                 东区澡堂▓\n");     
	printf("\t▓      ▓         ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓                    ▓   ▓\n");     
	printf("\t▓  100 ▓         ▓                          天桥            ▓▓                    ▓   ▓\n");
	printf("\t▓      ▓   小操场▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓                    ▓   ▓\n");
	printf("\t▓     ▓          ▓200     ▓▓    大操场 ▓    ▓▓▓▓▓                           ▓   ▓\n");    
	printf("\t▓     ▓80        ▓      70▓             ▓    ▓      ▓   大学生服务部  ▓▓▓▓▓▓   ▓\n");
	printf("\t▓     ▓          ▓        ▓             ▓    ▓      ▓                           ▓   ▓\n");
	printf("\t▓     ▓ 美广     ▓▓▓▓▓▓   体育馆    ▓    ▓   100▓                           ▓   ▓\n");     
	printf("\t▓    浴室         ▓100                    ▓ 大 ▓      ▓                                ▓\n");    
	printf("\t▓                 ▓                       ▓    ▓      ▓                                ▓\n");    
	printf("\t▓                  旭日苑                  ▓    ▓      ▓▓▓▓▓▓▓▓▓家属楼          ▓\n");     
	printf("\t▓               70▓                       ▓    ▓                                        ▓\n");
    printf("\t▓                 ▓                       ▓    ▓                                        ▓\n");
	printf("\t▓     ▓▓▓  大学生超市  ▓▓▓           ▓    ▓                                        ▓\n");      
	printf("\t▓   60▓                      ▓60         ▓    ▓                                        ▓\n");     
	printf("\t▓     ▓                      ▓           ▓ 道 ▓                                        ▓\n");     
	printf("\t▓              宿舍楼                      ▓    ▓                                        ▓\n");     
	printf("\t▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n");
	getch();
}

//函数功能：景点好评推荐
void Top()
{	
	system("cls");
	Readfile();
	int i,j,k,m,len[G->vexnum][2];
	for(i=1;i<=G->vexnum;i++)					//计算景点星级指数； 
	{
		len[i][0]=strlen(G->vex[i].star);
		len[i][1]=i;
	}
	for(i=1;i<=G->vexnum-1;i++)					//将景点按照星级又高到底排序； 
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
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★\n\n");
	printf("\t\t\t\t                   景点好评指数               \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\t\tNO.%-6d %-20s%s\n\n",i,G->vex[len[i][1]].name,G->vex[len[i][1]].star);
	 } 
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★\n\n");
	getch();
} 

//函数功能：查询景点详情；
void Information()
{
	int i,j,choice;
	Readfile();
	system("cls");
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");
	printf("\t\t\t\t                            景点查询                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-10s",i,G->vex[i].name);
		if(i%2==0)	printf("\n\n"); 
	 }  
	printf("\n\t\t\t\t请输入希望查询地点前的序号（1-%d）：",G->vexnum); 
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n\t\t\t\t");
	scanf("%d",&choice);
	if(choice<=G->vexnum)
	{
		printf("\n\t\t\t\t●%s\t星级：%s\n\n",G->vex[choice].name,G->vex[choice].star);
		printf("\t\t\t\t◆详情介绍： %s",G->vex[choice].information);
 	}
 	else printf("\n\t\t\t\t输入信息错误！");
 	getchar();
	getch();
}

//函数功能：查询景点信息； 
void Search()
{
	int choice,i;
	system("cls");
	printf("\n\n\n\n"); 
	printf("\t\t\t\t\t*************************************\n");
	printf("\t\t\t\t\t*                                   *\n");
	printf("\t\t\t\t\t*       1、Top景点推荐              *\n"); 
	printf("\t\t\t\t\t*                                   *\n");
	printf("\t\t\t\t\t*       2、查询某个景点详情         *\n");
	printf("\t\t\t\t\t*                                   *\n");
	printf("\t\t\t\t\t*             请输入（1/2）：       *\n");
	printf("\t\t\t\t\t*************************************\n\t\t\t\t\t");
	scanf("%d",&choice); 
	switch(choice)
	{
		case 1:Top();break;
			case 2:Information();break;
				default:printf("\n\t\t\t\t输入信息错误！");
	}
	getchar();
	getch();
} 

//函数功能：求任意两景点之间的所有简单路径； 
void SearchAllRoute() 
{        
	Readfile();
	int i,start,end;        
	int stack[100]={0};    
	int visited[50]={0}; 
	system("cls");
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");
	printf("\t\t\t\t                          校园景点                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-17s",i,G->vex[i].name);
		if(i%2==0)	printf("\n"); 
	 }  
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n\t\t\t\t");
	printf("\n\t\t\t\t请输入起点序号（1-%d）：",G->vexnum);
	scanf("%d",&start);        
	printf("\n\t\t\t\t请输入终点序号（1-%d）：",G->vexnum);   
	scanf("%d",&end);
	if(start<=G->vexnum && end<=G->vexnum)
	{ 
		stack[0]=start;               
		visited[start]=1;  
		tag=1;     
		DFS(start,end,stack,visited); 
		printf("\n\t\t\t\t以上是从 %s----->%s 的所有可行路径!\n",G->vex[start].name,G->vex[end].name);
	}
	else printf("\n\t\t\t\t输入信息错误！");
	getchar();
	getch();
}   

//函数功能：DFS深度遍历查找路径； 
void DFS(int start,int ending,int stack[],int visited[])
{    
	Readfile();   
	int i, j;      
	for(i=1; i<=G->vexnum; i++) 
	{         
		if(G->arcs[start][i] != Infinity && visited[i]==0)
		{             
			if(i == ending){						//如果深搜到了终点，就输出刚才经过的路径                
				if(tag==1){ 						// tag用于判断找最优路径还是所有路径,tag=1时找所有路径； 
					printf("\n\t\t\t\t");         
					for(j=0; j<m; j++)      
						printf("%s-->", G->vex[stack[j]].name);    
					printf("%s\n", G->vex[ending].name);  
					getch();  
				}   
				else   								//找最优路径时记录次数最少的路径  
					if(m<=min){        
						min=m;       
						for(j=0;j<m;j++)       
							path[j]=stack[j];      
					}            
			}              
			else{									//如果该点不是终点                           
				visited[i]=1;                 
				stack[m] = i;						//将该点存起来              
				m++;                
				DFS(i,ending,stack,visited);		//接着深搜        
				visited[i]=0;              
				m--;             
			}        
		}  
	} 
} 

//函数功能：求任意两景点之间的最短简单路径（中转次数最少，DFS算法）； 
void Minsimpleroute() 
{
	char name[20];   
	int i;     
	int start,end;    
	int stack[100]={0};     
	int visited[50]={0}; 
	Readfile();      
	system("cls");
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");
	printf("\t\t\t\t                          校园景点                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-17s",i,G->vex[i].name);
		if(i%2==0)	printf("\n"); 
	 }  
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n\t\t\t\t");
	printf("\n\t\t\t\t请输入起点序号（1-%d）：",G->vexnum);
	scanf("%d",&start);        
	printf("\n\t\t\t\t请输入终点序号（1-%d）：",G->vexnum);   
	scanf("%d",&end);
	if(start<=G->vexnum && end<=G->vexnum)
	{
		visited[start]=1; 
		stack[0]=start;   
		tag=0;      
		DFS(start,end,stack,visited);   
		printf("\n\t\t\t\t中转次数最少的路径为：\n\t\t\t\t");       
		for(i=0;i<min;i++)          
		printf("%s-->",G->vex[path[i]].name);    
		printf("%s\n", G->vex[end].name);
	}
	else printf("\n\t\t\t\t输入信息错误！");
	getchar();
	getch();
} 

//函数功能：任意两景点之间的最佳访问路线（带权最短路径长度）； 
void Shortcut()
{     
	char name[20];   
	int start,end;     
	int i;     
	int dist[Max]; 				//dist数组用于记录源点到其余各顶点的最短距离值； 
	Readfile();   
	system("cls");
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");
	printf("\t\t\t\t                          校园景点                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-17s",i,G->vex[i].name);
		if(i%2==0)	printf("\n"); 
	 }  
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n\t\t\t\t");
	printf("\n\t\t\t\t请输入起点序号（1-%d）：",G->vexnum);
	scanf("%d",&start);        
	printf("\n\t\t\t\t请输入终点序号（1-%d）：",G->vexnum);   
	scanf("%d",&end);
	if(start<=G->vexnum && end<=G->vexnum)
	{
		if(start<end)
			Floyd(end,start);
		else 
			Floyd(start,end);
	}
	else printf("\n\t\t\t\t输入信息错误！");
	getchar();
	getch();
}   

//函数功能：求最短路径（Floyd算法）； 
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
	printf("\n\t\t\t\t从%s到%s的最短路径为：\n\n\t\t\t\t从%s",G->vex[start].name,G->vex[end].name,G->vex[start].name);
	temp=path[start][end];
	while(1){
		printf("----->%s",G->vex[temp].name);
		if(temp == end)	break;
		temp=path[temp][end];
	}
	printf("\n\t\t\t\t距离%dkm",F[start][end]); 
	getch();
} 

//函数功能：填写用户满意度；
void Satisfied()
{
	char s[6];
	int choice,i;
	Readfile();
	system("cls");
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");
	printf("\t\t\t\t                          校园景点                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-17s",i,G->vex[i].name);
		if(i%2==0)	printf("\n"); 
	 }  
	printf("\t\t\t\t请留下你宝贵的意见吧！\n");
	printf("\t\t\t\t请选择待评价景点(1-%d)：\n\t\t\t\t",G->vexnum);
	scanf("%d",&choice);
	printf("\t\t\t\t请输入满意度,星级从1-5(输入*)：\n\t\t\t\t");
	scanf("%s",s);
	if(choice<=G->vexnum && strlen(s)<=5 && strlen(s)>0)
	{
		for(i=1;i<=G->vexnum;i++)							//保留最高满意度； 
			if(i==choice)
			{
				if(strlen(s)>strlen(G->vex[i].star))
				strcpy(G->vex[i].star,s);
				break;
			}
			Savefile(1);
		printf("感谢您的评价。\n");
	}
	else printf("\n\t\t\t\t输入信息错误！"); 
	getchar();
	getch();
}
 
//函数功能：添加新路线； 
void AddNewRoute()
{
	int start,end,weight,i;
	FILE *fp;
	char filename[30]={"校园景点路径.txt"};
	Readfile(); 
	system("cls");
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");
	printf("\t\t\t\t                          校园景点                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-17s",i,G->vex[i].name);
		if(i%2==0)	printf("\n"); 
	 }  
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n\t\t\t\t");
	printf("\n\t\t\t\t请输入新添路线的起点序号（1-%d）：",G->vexnum);
	scanf("%d",&start);        
	printf("\n\t\t\t\t请输入新添路线的终点序号（1-%d）：",G->vexnum);   
	scanf("%d",&end);
	printf("\n\t\t\t\t请输入所要添加的路径长度：");
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
			printf("写文件出错，按任意键退出！");
			getch();
			exit(1);
		}
		fprintf(fp,"%s %s %d\n",G->vex[start].name,G->vex[end].name,weight); 
		fclose(fp);
		printf("\n添加路线成功！");
	}
	else printf("\n\t\t\t\t输入信息错误！");
	getchar();
	getch();
}

//函数功能：添加新景点； 
void AddNewSence()
{
	Readfile();
	FILE *fp;
	char sence[30];
	char filename[30]={"校园景点信息.txt"};
	G->vexnum++; 
	system("cls");
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");
	printf("\n\t\t\t\t请输入新添路加的景点名称：\n\t\t\t\t");
	scanf("%s",G->vex[G->vexnum].name);
	printf("\n\t\t\t\t请输入景点星级：\n\t\t\t\t");
	scanf("%s",G->vex[G->vexnum].star);
	printf("\n\t\t\t\t请输入景点详情：\n\t\t\t\t");
	scanf("%s",G->vex[G->vexnum].information);
	fp=fopen(filename,"a");
	if(fp==NULL)
	{
		printf("写文件出错，按任意键退出！");
		getch();
		exit(1);
	}
	fprintf(fp,"%d %s %s %s\n",G->vexnum,G->vex[G->vexnum].name,G->vex[G->vexnum].star,G->vex[G->vexnum].information); 
	fclose(fp);
	Savefile(1);
	printf("%d\n",G->vexnum);
	printf("添加成功！");
	getch(); 
}

//函数功能：撤销旧路线； 
void DeleteOldRoute()
{
	int start,end,i;
	FILE *fp;
	char filename[30]={"校园景点路径.txt"};
	Readfile(); 
	system("cls");
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");
	printf("\t\t\t\t                          校园景点                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-17s",i,G->vex[i].name);
		if(i%2==0)	printf("\n"); 
	 }  
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n\t\t\t\t");
	printf("\n\t\t\t\t请输入撤销旧路线的起点序号（1-%d）：",G->vexnum);
	scanf("%d",&start);        
	printf("\n\t\t\t\t请输入撤销旧路线的终点序号（1-%d）：",G->vexnum);   
	scanf("%d",&end);
	if(start<=G->vexnum && end<=G->vexnum)
	{
		G->arcnum--;
		G->arcs[start][end]=Infinity;
		G->arcs[end][start]=Infinity; 
		Savefile(1);
		Savefile(2);
		printf("\t\t\t\t删除路线成功！\n");
	}
	else printf("\n\t\t\t\t输入信息错误！");
	getchar();
	getch();
}

//函数功能：撤销旧景点；
void DeleteOldSence()
{
	int number,i,j; 
	Readfile(); 
	system("cls");
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");
	printf("\t\t\t\t                          校园景点                       \n\n");
	for(i=1;i<=G->vexnum;i++)
	{
		printf("\t\t\t\tNO.%-2d %-17s",i,G->vex[i].name);
		if(i%2==0)	printf("\n"); 
	 }  
	printf("\n\t\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n\t\t\t\t");
	printf("\n\t\t\t\t请输入所要撤销旧景点的序号（1-%d）：",G->vexnum);
	scanf("%d",&number); 
	   	for(i=1;i<=G->vexnum;i++)									//删除与旧景点相关的路线; 
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
		   for(i=number;i<G->vexnum;i++)								//删除旧景点； 
		{
			strcpy(G->vex[i].name,G->vex[i+1].name);
			strcpy(G->vex[i].star,G->vex[i+1].star);
			strcpy(G->vex[i].information,G->vex[i+1].information);
	   }     
	   	G->vexnum--;
	   	Savefile(1);
	   	Savefile(2);
	   printf("\n\t\t\t\t撤销景点成功！");
	getch();
} 

//函数功能：校园中所有景点的最佳布网方案；
void BestRoute()
{
	int start;
	printf("\t\t\t\t请输入起始点：\n\t\t\t\t");
	scanf("%d",&start);
	printf("\n\n\t\t\t\t最佳布网路线为：\n\t\t\t\t"); 
	Prim(start);
	getch();
}

//函数功能：最佳布网方案（Prim算法求最小生成树）； 
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
	printf("路径长度：%dkm\n\n",sum);	
	for(i=0;i<G->vexnum-1;i++)
	{
		printf("%s----->",G->vex[s[i]].name);
	}
	printf("%s",G->vex[s[i]].name);
	getch();
}

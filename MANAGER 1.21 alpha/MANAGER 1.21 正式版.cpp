// MANAGER 1.21 正式版.cpp : Defines the entry point for the console application.

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "Windows.h"
#include "conio.h"

#define TOTAL 100//定义能储存的书本数目的最大值
#define NULL 0//定义NULL为0
#define EOF -1//定义EOF为-1

static int re=0;//定义重新返回登陆界面的全局变量
static char stname[TOTAL];//记录学生ID的全局变量
static int stpower;//记录学生权限的全局变量
static int stnum;//记录学生权限的全局变量

enum//枚举对应键的ascii码
{
	UP=72,
	DOWN=80,
	ENTER=13,
};

char *caidan[]=
{
	"↑☆  ●[1]图书信息录入   ☆↓  ",
	"↑☆  ●[2]图书信息查询   ☆↓  ",
	"↑☆  ●[3]图书信息删除   ☆↓  ",
	"↑☆  ●[4]图书信息修改   ☆↓  ",
	"↑☆  ●[5]全部图书信息   ☆↓  ",
	"↑☆  ●[6]学生账户管理   ☆↓  ",
	"↑☆  ●[7]退出系统       ☆↓  ",
};

char *xcaidan[]=
{
	"↑☆  ●[1]借阅图书   ☆↓  ",
	"↑☆  ●[2]借阅查询   ☆↓  ",
	"↑☆  ●[3]归还图书   ☆↓  ",
	"↑☆  ●[4]续借图书   ☆↓  ",
	"↑☆  ●[5]修改密码   ☆↓  ",
	"↑☆  ●[6]退出系统   ☆↓  ",
};

struct book//定义书本结构体
{
	char name[TOTAL];//书名
	char author[TOTAL];//作者
	char press[TOTAL];//出版社
	char number[TOTAL];//编号
	int jie;//是否借阅
	struct book * next;
};

struct lendtime//定义借阅时间结构体
{
	char name[TOTAL];
	int year;//借阅年份
	int month;//借阅月份
	int day;//借阅日期
	int hour;//借阅小时
	int minute;//借阅分钟
	int second;//借阅秒
	char man[TOTAL];//借阅人名字
	struct lendtime * next;
};

struct student//定义学生账户信息
{
	char ac[TOTAL];
	char pw[TOTAL];
	int power;//借阅月份上限
	int num;//借阅书目上限
	int use;//账户是否可以使用
	struct student * next;
};

struct book * Create();
struct lendtime * Create2();
struct student * Create3();

int ldmin(int a,int b,int c);
int ldmax(int a,int b);
double ld(char str1[],char str2[]);

void scan(struct book * head);
void tscan(struct lendtime * head2);
void gscan(struct student * head3);

void menu(struct book * head,struct student * head3);
void xmenu(struct book * head,struct lendtime * head2,struct student * head3);

void save(struct book * head);
void tsave(struct lendtime * head2);
void gsave(struct student * head3);

void add(struct book * head);
void find(struct book * head);
void dele(struct book * head);
void editor(struct book * head);
void print(struct book * head);
void manage(struct student * head3);

void xlend(struct book * head,struct lendtime * head2);
void xfind(struct book * head,struct lendtime * head2);
void xreturn(struct book * head,struct lendtime * head2);
void xrelet(struct book * head,struct lendtime * head2);
void xfix(struct student * head3);

void exit();

int login(int x,struct student * head3);
void enroll(struct student * head3);

struct book * Create()//建立book链表
{
	struct book * head;
	head=(struct book *)malloc(sizeof(struct book));//分配头节点空间
	head->next=NULL;//头节点指针域初始化，定为空
	scan(head);
	return head;
}

struct lendtime * Create2()//建立lendtime链表
{
	struct lendtime * head2;
	head2=(struct lendtime *)malloc(sizeof(struct lendtime));//分配头节点空间
	head2->next=NULL;//头节点指针域初始化，定为空
	tscan(head2);
	return head2;
}

struct student * Create3()//建立student链表
{
	struct student * head3;
	head3=(struct student *)malloc(sizeof(struct student));//分配头节点空间
	head3->next=NULL;//头节点指针域初始化，定为空
	gscan(head3);
	return head3;
}

int ldmin(int a,int b,int c)//LD算法中矩阵最小值算法
{
	int min=a;
	if(min>b)
		min=b;
	if(min>c)
		min=c;
	return min;
}

int ldmax(int a,int b)//LD算法中比较哪个字符串更长的算法
{
	int max=a;
	if(max<b)
		max=b;
	return max;
}

double ld(char str1[],char str2[])//计算模糊搜索相关度的LD算法
{
	int len1,len2;
	double xg;
	int i,j;
	char ch1,ch2;
	int temp;
	len1=strlen(str1);//
	len2=strlen(str2);//计算字符串长度
	double c,e;
	int d[100][100];//定义矩阵
	if(len1==0)
	{
		return len2;
	}
	if(len2==0)
	{
		return len1;
	}
	for(j=0;j<=len2;j++)
	{
		d[0][j]=j;
	}
	for(i=0;i<=len1;i++)
	{
		d[i][0]=i;
	}
	for(i=1;i<=len1;i++)
	{
		ch1=str1[i-1];
		for(j=1;j<=len2; j++)
		{
			ch2=str2[j-1];
			if(ch1==ch2)//若两字符相等则该元素位置左上的位置计算时不加1，反之加1
			{
				temp=0;
			}
			else
			{
				temp=1;
			}
			d[i][j]=ldmin(d[i-1][j]+1,d[i][j-1]+1,d[i-1][j-1]+temp);//该位置元素值为其左、上、左上的值经过一定换算后其中的最小值
		}
	}
	c=d[len1][len2];//取矩阵最右下角的元素值
	e=ldmax(len1,len2);//取两个字符串更长的那个的长度
	xg=1-(c/e);//相关度计算公式
	return xg;
}

void sleep(int s)//停止一段时间的算法
{
	time_t tmp1=time(NULL);
	time_t tmp2=tmp1;
	while(difftime(tmp2,tmp1)<s)
	{
		tmp2=time(NULL);
	}
}

int main(struct book * head,struct lendtime * head2,struct student * head3)//主函数
{
	char wu;
	int num,a=0;
	HANDLE ohandle = GetStdHandle(STD_OUTPUT_HANDLE);//获取句柄
	SetConsoleTextAttribute(ohandle,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//设置字体颜色
	while(!kbhit())
	{
		time_t timet;
		struct tm *t;
		time (&timet);
		t=gmtime(&timet);
		printf("欢迎您使用图书管理系统1.21正式版！\n\n作者：游晔晟，冯金，马续智\n\n小组：苟富贵蛤相忘\n\n\n");
		printf("        实时时钟：        \n");
		printf(" →→→→→→→→→→→→   \n");
		printf("↑                      ↓  \n");
		printf("↑     %2d : %2d : %2d     ↓  \n",8+t->tm_hour,t->tm_min,t->tm_sec);
		printf("↑                      ↓  \n");
		printf(" ←←←←←←←←←←←←   \n");
		printf("\n\n按任意键继续！");
		sleep(1);
		system("cls");
	}
	wu=getch();
	head=Create();
	head2=Create2();
	head3=Create3();
loop:system("cls");//清屏//非法访问返回地址
	printf("图书管理系统1.21正式版\n\n");
	num=login(a,head3);//登陆系统
	system("cls");//清屏
	switch (num)//对login函数返回值（登陆系统）进行判断
	{
	case 0://非法访问返回为0
		{
			printf("【非法访问，请重新尝试！】\n");
			system("pause");//点任意键继续
			system("cls");//清屏
			goto loop;
		}
	case 1://管理员访问返回为1
		{
			printf("★欢迎您管理员！★\n");
			system("pause");//点任意键继续
			menu(head,head3);//进入管理员菜单
			break;
		}
	case 2://用户访问返回为2
		{
			printf("★欢迎您使用图书馆借阅系统！★\n");
			system("pause");//点任意键继续
			xmenu(head,head2,head3);
			break;
		}
	case 3://注册返回为3
		{
			printf("【注册成功！】\n");
			system("pause");//点任意键继续
			system("cls");//清屏
			goto loop;
		}
	case 4://账户被管理员冻结返回为4
		{
			printf("【账户被管理员冻结，请联系管理员！】\n");
			system("pause");//点任意键继续
			system("cls");//清屏
			goto loop;
		}
	}
	if(re==1)//如果re为1则返回loop处
	{
		re=0;
		system("cls");//清屏
		goto loop;
	}
	save(head);
	tsave(head2);
	gsave(head3);
	system("pause");
	return 0;
}

void scan(struct book * head)//读取之前添加的内容至链表
{
	struct book *s,*p;//定义结构体指针变量 s指向开辟的新结点首地址 p为中间变量
	p=head;//将p指针对准头结点
	FILE *fp;
	fp=fopen("book.txt","a+");//以读写方式新建并打开book.txt文件
	while(p->next!= NULL)
	{
		p=p->next;//修改p指向下一个节点
	}
	if(fgetc(fp)==EOF)//抓取文件第一个字符
	{
		head=NULL;//若txt内没有内容则将头结点改为空
	}
	else
	{
		while(!feof(fp))//逐行读取文件直至结束
		{
			s=(struct book *)malloc(sizeof(struct book));//分配s节点空间
			fscanf(fp,"%s %s %s %s %d \n",&s->name,&s->author,&s->press,&s->number,&s->jie);//按对应格式读取内容至s节点
			p->next=s;//将新增加的节点添加进链表
			p=s;//p指向尾节点，向后移
			s->next=NULL;//修改s下一个节点为空
		}
	}
	fclose(fp);
}

void tscan(struct lendtime * head2)//读取之前添加的内容至链表
{
	struct lendtime *s,*p;//定义结构体指针变量 s指向开辟的新结点首地址 p为中间变量
	p=head2;//将p指针对准头结点
	FILE *fp;
	fp=fopen("time.txt","a+");//以读写方式新建并打开time.txt文件
	while(p->next!= NULL)
	{
		p=p->next;//修改p指向下一个节点
	}
	if(fgetc(fp)==EOF)//抓取文件第一个字符
	{
		head2=NULL;//若txt内没有内容则将头结点改为空
	}
	else
	{
		while(!feof(fp))//逐行读取文件直至结束
		{
			s=(struct lendtime *)malloc(sizeof(struct lendtime));//分配s节点空间
			fscanf(fp,"%s %d %d %d %d %d %d %s \n",&s->name,&s->year,&s->month,&s->day,&s->hour,&s->minute,&s->second,&s->man);//按对应格式读取内容至s节点
			p->next=s;//将新增加的节点添加进链表
			p=s;//p指向尾节点，向后移
			s->next=NULL;//修改s下一个节点为空
		}
	}
	fclose(fp);
}

void gscan(struct student * head3)//读取之前添加的内容至链表
{
	struct student *s,*p;//定义结构体指针变量 s指向开辟的新结点首地址 p为中间变量
	p=head3;//将p指针对准头结点
	FILE *fp;
	fp=fopen("student.txt","a+");//以读写方式新建并打开time.txt文件
	while(p->next!= NULL)
	{
		p=p->next;//修改p指向下一个节点
	}
	if(fgetc(fp)==EOF)//抓取文件第一个字符
	{
		head3=NULL;//若txt内没有内容则将头结点改为空
	}
	else
	{
		while(!feof(fp))//逐行读取文件直至结束
		{
			s=(struct student *)malloc(sizeof(struct student));//分配s节点空间
			fscanf(fp,"%s %s %d %d %d \n",&s->ac,&s->pw,&s->power,&s->num,&s->use);//按对应格式读取内容至s节点
			p->next=s;//将新增加的节点添加进链表
			p=s;//p指向尾节点，向后移
			s->next=NULL;//修改s下一个节点为空
		}
	}
	fclose(fp);
}

void menu(struct book * head,struct student * head3)//管理员菜单
{
loop:char key=0;
	int i,select=0;
	HANDLE ohandle = GetStdHandle(STD_OUTPUT_HANDLE);//获取句柄
	SetConsoleTextAttribute(ohandle,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//设置字体颜色
	for (;;)
	{
		system("cls");//清屏
		time_t timet;//调用数据库中time函数
		struct tm *t;//创建tm结构体用于保存时间
		time (&timet);//得到电脑的时间
		t=gmtime(&timet);//读取标准时区（UTC）时间
		printf("现在时间为%d年%d月%d日%d时%d分%d秒。\n",1900+t->tm_year,1+t->tm_mon,t->tm_mday,8+t->tm_hour,t->tm_min,t->tm_sec);
		printf("\n");
		printf(" →→→→→→→→→→→→→→ \n");
		printf("↑☆☆☆☆☆☆☆☆☆☆☆☆☆↓\n");
		printf("↑☆☆ §图书管理系统§ ☆☆↓\n");
		printf("↑☆☆☆☆☆☆☆☆☆☆☆☆☆↓\n");
		for(i=0;i<7;i++)//这里共7个选项
		{
			if(i==select)//设置焦点高亮
				SetConsoleTextAttribute(ohandle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
			else if(i==select+1)//恢复设置
				SetConsoleTextAttribute(ohandle,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
			puts(caidan[i]);
		}
		SetConsoleTextAttribute(ohandle,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//恢复原来字体
		printf("↑☆☆☆☆☆☆☆☆☆☆☆☆☆↓\n");	
		printf(" ←←←←←←←←←←←←←← \n");
		key=getch();//读取键盘输入按键
		if(key==0xd)//Enter键
		{
			break;
		}
		if(key<0)//非ascii码键2个字节
		{
			key=getch();//读取按键第二字节的内容
			switch(MapVirtualKey(key,1))//对按键ascii码switch
			{
			case VK_UP://↑键
				{
				select = (select+6)%7;//焦点上移，减一，滚动选择，共7个选项
				break;
				}
			case VK_DOWN://↓键
				{
				select = (select+1)%7;//焦点下移，加一
				break;
				}
			}
		}
	}
	system("cls");//清屏
	switch (select+1)
	{
	case 1:add(head);break;
	case 2:find(head);break;
	case 3:dele(head);break;
	case 4:editor(head);break;
	case 5:print(head);break;
	case 6:manage(head3);break;
	case 7:exit();break;
	}
	if(select!=6)
	{
		goto loop;
	}
}

void save(struct book * head)//保存数据至文件
{
	struct book *p;//定义结构体指针变量 p指向开辟的新结点首地址
	FILE *fp;
	p=head;//将p指针对准头结点
	fp=fopen("book.txt","w+");//以读写方式新建book.txt文件
	while(p->next!=NULL)
	{
		p=p->next;//修改p指向下一个节点
		fprintf(fp,"\n%s %s %s %s %d ",p->name,p->author,p->press,p->number,p->jie);
	}
	fclose(fp);
	printf("已将图书数据保存到book.txt文件\n");
}

void tsave(struct lendtime * head2)
{
	struct lendtime *p;//定义结构体指针变量 p指向开辟的新结点首地址
	FILE *fp;
	p=head2;//将p指针对准头结点
	fp=fopen("time.txt","w+");//以读写方式新建time.txt文件
	while(p->next!=NULL)
	{
		p=p->next;//修改p指向下一个节点
		fprintf(fp,"\n%s %d %d %d %d %d %d %s ",p->name,p->year,p->month,p->day,p->hour,p->minute,p->second,p->man);
	}
	fclose(fp);
	printf("已将借阅时间数据保存到time.txt文件\n");
}

void gsave(struct student * head3)
{
	struct student *p;//定义结构体指针变量 p指向开辟的新结点首地址
	FILE *fp;
	p=head3;//将p指针对准头结点
	fp=fopen("student.txt","w+");//以读写方式新建student.txt文件
	while(p->next!=NULL)
	{
		p=p->next;//修改p指向下一个节点
		fprintf(fp,"\n%s %s %d %d %d ",p->ac,p->pw,p->power,p->num,p->use);
	}
	fclose(fp);
	printf("已将学生账户数据保存到student.txt文件\n");
}

void add(struct book * head)//添加书本
{
	struct book *s,*p;//定义结构体指针变量 s指向开辟的新结点首地址 p为中间变量
	char again='Y';//定义变量,选择是否重复输入
	p=head;
	while(p->next!= NULL)
	{
		p=p->next;//修改p指向下一个节点
	}  
	while(again=='Y'||again=='y')//开辟新空间,存入数据,添加进链表
	{
		s=(struct book *)malloc(sizeof(struct book));//分配s节点空间
		printf("→请输入图书书名:\n");
		fflush(stdin);//清空输入缓冲区
		scanf("%s",&s->name);
		printf("→请输入图书作者名:\n");
		fflush(stdin);//清空输入缓冲区
		scanf("%s",&s->author);
		printf("→请输入图书出版社:\n");
		fflush(stdin);//清空输入缓冲区
		scanf("%s",&s->press);
		printf("→请输入图书ISBN编号:\n");
		fflush(stdin);//清空输入缓冲区
		scanf("%s",&s->number);
		s->jie=0;//输入图书初始借阅情况为未借出
		p->next=s;//将新增加的节点添加进链表
		p=s;//p指向尾节点，向后移
		s->next=NULL;//修改s下一个节点为空
		printf("添加成功！\n");
		printf("继续添加？(Y/N):\n");
		fflush(stdin);//清空输入缓冲区
		scanf("%c",&again);
	}
	system("pause");//点任意键继续
	system("cls");//清屏
} 

void find(struct book * head)//查找书本
{
	struct book *p;//定义结构体指针变量 p为中间变量
	int i=0;//判断是否查找到的变量
	int way;//定义查找方式
	char sure[TOTAL];//存储内容的中间变量
	char search[TOTAL];//存储输入内容
	p=head;
	if(head==NULL||head->next==NULL)//判断数据库是否为空
	{
		printf("图书库为空！\n");
	}
	else
	{
jump:printf("请选择查找方式：\n1：书名查找\n2：作者查找\n3：出版社查找\n4：ISBN编号查找\n查找方式：");//若way值非法的返回地址
		fflush(stdin);//清空输入缓冲区
		scanf("%d",&way);
		if(way==1||way==2||way==3||way==4)
		{
			printf("请输入您要查找的内容:");
			fflush(stdin);//清空输入缓冲区
			scanf("%s",&search);
		}
		while(p->next!=NULL)//指针从头节点开始移动，遍历至尾结点，查找书目信息
		{
			p=p->next;//修改p指向下一个节点
			switch (way)
			{
			case 1:strcpy(sure,p->name);break;
			case 2:strcpy(sure,p->author);break;
			case 3:strcpy(sure,p->press);break;
			case 4:strcpy(sure,p->number);break;
			default:
				{
					printf("查找方式不合法！请重新选择！\n\n");
					system("pause");//按任意键继续
					system("cls");//清屏
					goto jump;
				}
			}
			if(strcmp(sure,search)==0)
			{
				i=1;//判断变量返回为真
				printf("\n已找到图书！\n");
				printf("    书名: %s\t\n",p->name);
				printf("  作者名: %s\t\n",p->author);
				printf("  出版社: %s\t\n",p->press);
				printf("ISBN编号: %s\t\n",p->number);
				if(p->jie!=0)
				{
					printf("已借出%d月\t\n",p->jie);
				}
				else
				{
					printf("未借出\t\n");
				}
				break;
			}
		}
		if(i==0)
		{
			printf("图书不存在！\n");//判断变量为假时报错
		}
	}
	system("pause");//按任意键继续
	system("cls");//清屏
}

void dele(struct book * head)//删除书本
{
	struct book *s,*p;//s为中间变量，p为遍历时使用的指针
	char name[TOTAL];
	int i=0;//判断是否查找到的变量
	p=head;
	s=head;
	printf("请输入您要删除的书名:\n");
	scanf("%s",&name);
	while(p!=NULL)//遍历到尾结点
	{
		if(strcmp(p->name,name)==0)
		{
			i=1;
			break;
		}
		p=p->next;//修改p指向下一个节点
	}
	if(i==1)
	{
		for(;s->next!=p;)//找到所需删除卡号结点的上一个结点
		{
			s=s->next;//修改s指向下一个节点
		}
		s->next=p->next;//将后一节点地址赋值给前一节点的指针域
		free(p);//释放p节点内存
		printf("删除成功！\n");
	}
	else//未找到书目
	{
		printf("图书不存在！\n");
	}
	system("pause");//按任意键继续
	system("cls");//清屏
}

void editor(struct book * head)//编辑书本
{
	struct book *s,*p;//s为中间变量，p为遍历时使用的指针
	char name[TOTAL];
	int i=0;//判断是否查找到的变量
	p=head;
	s=head;
	printf("请输入您要编辑的书名:\n");
	scanf("%s",&name);
	while(p!=NULL)//遍历到尾结点
	{
		if(strcmp(p->name,name)==0)
		{
			i++;
			break;
		}
		p=p->next;//修改p指向下一个节点
	}
	if(i==1)
	{
		for(;s->next!=p;)//找到所需删除卡号结点的上一个结点
		{
			s=s->next;//修改s指向下一个节点
		}
		s->next=p->next;//将后一节点地址赋值给前一节点的指针域
		free(p);//释放p节点内存
		struct book *s,*p;//定义结构体指针变量 s指向开辟的新结点首地址 p为中间变量
		p=head;
		while(p->next!= NULL)
		{
			p=p->next;//修改p指向下一个节点
		}
		s=(struct book *)malloc(sizeof(struct book));//分配s节点空间
		printf("请输入图书书名:\n");
		fflush(stdin);//清空输入缓冲区
		scanf("%s",&s->name);
		printf("请输入图书作者名:\n");
		fflush(stdin);//清空输入缓冲区
		scanf("%s",&s->author);
		printf("请输入图书出版社:\n");
		fflush(stdin);//清空输入缓冲区
		scanf("%s",&s->press);
		printf("请输入图书ISBN编号:\n");
		fflush(stdin);//清空输入缓冲区
		scanf("%s",&s->number);
		s->jie=0;
		p->next=s;//将新增加的节点添加进链表
		p=s;//p指向尾节点，向后移
		s->next=NULL;//修改s下一个节点为空
	}
	else//未找到书目
	{
		printf("图书不存在！\n");
	}
	system("pause");//按任意键继续
	system("cls");//清屏
}

 
void print(struct book * head)//浏览全部书库
{
	struct book *p;
	int num=0;//定义计算书目数量的变量
	if(head==NULL||head->next==NULL)//判断数据库是否为空
	{
		printf("没有图书记录！\n");
	}
	else
	{
		p=head;
		while(p->next!= NULL)//指针从头节点开始移动，遍历至尾结点，依次输出图书信息
		{
			num++;
			p=p->next;//修改p指向下一个节点
			printf("第%d本图书：\n",num);
			printf("    书名: %s\t\n",p->name);
			printf("  作者名: %s\t\n",p->author);
			printf("  出版社: %s\t\n",p->press);
			printf("ISBN编号: %s\t\n",p->number);
			if(p->jie!=0)
			{
				printf("已借出%d月\t\n",p->jie);
			}
			else
			{
				printf("未借出\t\n");
			}
			printf("\n");
		}
	}
	system("pause");//按任意键继续
	system("cls");//清屏
}

void manage(struct student * head3)
{
	struct student *p,*s;
	p=head3;
	s=head3;
	char mag[TOTAL];
	int i=0;
	int choose;
	printf("请输入要管理的学生账户：\n");
	scanf("%s",&mag);
	while(p->next!=NULL)
	{
		p=p->next;
		if(strcmp(p->ac,mag)==0)
		{
			i=1;
			break;
		}
	}
	if(i==1)
	{
		system("cls");//清屏
		while(i==1)
		{
			printf("账户：%s\n请选择管理功能：\n1：查看密码\n2：修改最大借阅月份\n3：修改最大借阅书目\n4：冻结账户\n5：解冻账户\n6：注销账户\n7：退出\n管理功能：",p->ac);
			scanf("%d",&choose);
			printf("\n");
			switch (choose)
			{
			case 1:
				{
					printf("密码是：%s\n",p->pw);
					break;
				}
			case 2:
				{
					printf("原最大借阅月份为%d月，更改为：",p->power);
					scanf("%d",&p->power);
					printf("\n更改成功为%d月！\n",p->power);
					break;
				}
			case 3:
				{
					printf("原最大借阅书目为%d本，更改为：",p->num);
					scanf("%d",&p->num);
					printf("\n更改成功为%d本！\n",p->num);
					break;
				}
			case 4:
				{
					p->use=0;
					printf("冻结成功！\n");
					break;
				}
			case 5:
				{
					p->use=1;
					printf("解冻成功！\n");
					break;
				}
			case 6:
				{
					for(;s->next!=p;)//找到所需删除卡号结点的上一个结点
					{
						s=s->next;//修改s指向下一个节点
					}
					s->next=p->next;//将后一节点地址赋值给前一节点的指针域
					free(p);//释放p节点内存
					printf("删除成功！\n");
					i=2;
					break;
				}
			case 7:
				{
					i=2;
					break;
				}
			default:
				{
					printf("输入不合法，请重新输入！\n");
					break;
				}
			}
			system("pause");//按任意键继续
			system("cls");//清屏
		}
	}
	else
	{
		printf("账户不存在！\n");
		system("pause");//按任意键继续
		system("cls");//清屏
	}
}

void exit()//退出
{
	char again;
	system("cls");//清屏
	printf("感谢使用图书管理系统！\n\n");
	printf("是否需要回退至登陆界面？（Y/N）\n");
	scanf("%s",&again);
	if(again=='Y'||again=='y')
	{
		re=1;
	}
}

void xmenu(struct book * head,struct lendtime * head2,struct student * head3)
{
loop:char key=0;
	int i,select=0;
	HANDLE ohandle = GetStdHandle(STD_OUTPUT_HANDLE);//获取句柄
	SetConsoleTextAttribute(ohandle,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//设置字体颜色
	for (;;)
	{
		system("cls");//清屏
		time_t timet;//调用数据库中time函数
		struct tm *t;//创建tm结构体用于保存时间
		time (&timet);//得到电脑的时间
		t=gmtime(&timet);//读取标准时区（UTC）时间
		printf("现在时间为%d年%d月%d日%d时%d分%d秒。\n",1900+t->tm_year,1+t->tm_mon,t->tm_mday,8+t->tm_hour,t->tm_min,t->tm_sec);
		printf("账户：%s\n最大借阅月份：%d\n最大借阅数量：%d\n",stname,stpower,stnum);
		printf("\n");
		printf(" →→→→→→→→→→→→ \n");
		printf("↑☆☆☆☆☆☆☆☆☆☆☆↓\n");
		printf("↑☆ §图书借阅系统§ ☆↓\n");
		printf("↑☆☆☆☆☆☆☆☆☆☆☆↓\n");
		for(i=0;i<6;i++)//这里共6个选项
		{
			if(i==select)//设置焦点高亮
				SetConsoleTextAttribute(ohandle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
			else if(i==select+1)//恢复设置
				SetConsoleTextAttribute(ohandle,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
			puts(xcaidan[i]);
		}
		SetConsoleTextAttribute(ohandle,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//恢复原来字体
		printf("↑☆☆☆☆☆☆☆☆☆☆☆↓\n");	
		printf(" ←←←←←←←←←←←← \n");
		key=getch();//读取键盘输入按键
		if(key==0xd)//Enter键
		{
			break;
		}
		if(key<0)//非ascii码键2个字节
		{
			key=getch();//读取按键第二字节的内容
			switch(MapVirtualKey(key,1))//对按键ascii码switch
			{
			case VK_UP://↑键
				{
				select = (select+5)%6;//焦点上移，减一，滚动选择，共6个选项
				break;
				}
			case VK_DOWN://↓键
				{
				select = (select+1)%6;//焦点下移，加一
				break;
				}
			}
		}
	}
	system("cls");//清屏
	switch (select+1)
	{
	case 1:xlend(head,head2);break;
	case 2:xfind(head,head2);break;
	case 3:xreturn(head,head2);break;
	case 4:xrelet(head,head2);break;
	case 5:xfix(head3);break;
	case 6:exit();break;
	}
	if(select!=5)
	{
		goto loop;
	}
}

void xlend(struct book * head,struct lendtime * head2)
{
	struct book *p;//p为遍历时使用的指针
	struct lendtime *s,*q;//s指向开辟的新结点首地址 q为中间变量
	int enough=0;//判断借阅数目的变量
	int i=0,k=0;//判断是否查找到的变量
	int way;//定义查找方式
	char sure[TOTAL];//存储内容的中间变量
	char search[TOTAL];//存储输入内容
	char fuzzy;//是否模糊查找
	char j;//模糊搜索时确认书目的变量
	double flag;//存储模糊搜索时对应书目的相关度的变量
	int chnum;//计算对应书目有效长度的中间变量
	double character,dao;//存储对应书目有效长度（中文与数字字母全部计算为1个）（按strlen中文会计算为2个）并取倒数的变量
	p=head;
	q=head2;
	while(q->next!= NULL)
	{
		q=q->next;
		if(strcmp(q->man,stname)==0)
		{
			enough++;
		}
	}
	q=head2;
	if(enough<stnum)//最多借阅X本
	{
		while(q->next!= NULL)
		{
			q=q->next;//修改q指向下一个节点
		}
		if(head==NULL||head->next==NULL)//判断数据库是否为空
		{
			printf("图书库为空！\n");
		}
		else
		{
			printf("是否使用模糊查找（Y/N）：");
			fflush(stdin);//清空输入缓冲区
			scanf("%c",&fuzzy);
jump:printf("请选择查找方式：\n1：书名查找\n2：作者查找\n3：出版社查找\n4：ISBN编号查找\n查找方式：");//若way值非法返回的地址
			fflush(stdin);//清空输入缓冲区
			scanf("%d",&way);
			if(way==1||way==2||way==3||way==4)
			{
				printf("请输入您要查找的内容:");
				fflush(stdin);//清空输入缓冲区
				scanf("%s",&search);
			}
			while(p->next!=NULL)//指针从头节点开始移动，遍历至尾结点，查找书目信息
			{
				p=p->next;//修改p指向下一个节点
				switch (way)
				{
				case 1:strcpy(sure,p->name);break;
				case 2:strcpy(sure,p->author);break;
				case 3:strcpy(sure,p->press);break;
				case 4:strcpy(sure,p->number);break;
				default:
					{
						printf("查找方式不合法！请重新选择！\n\n");
						system("pause");//按任意键继续
						system("cls");//清屏
						goto jump;
					}
				}
				chnum=strlen(sure);
				character=0.0000;
				for(chnum=0;sure[chnum];)//遍历计算字符串的有效长度
				{
					if(sure[chnum]<0)
					{
						chnum+=2;
					}
					else
					{
						chnum++;
					}
					character+=1.0000;
				}
				dao=(1.0000/character)-0.0000001;//取有效长度倒数并减一个微小值，确保与相关度相同时能有效识别
				if(fuzzy=='Y'||fuzzy=='y')
				{
					flag=0.000+ld(sure,search);//相关度
					if(flag!=0&&flag>=dao)//相关度不等于0（两个字符串至少有字符相同）且相关度大于等于有效长度的倒数（确保有中文时能识别至少2个，增加搜索引擎的准确率）
					{
						k++;
						printf("\n");
						printf("第%d本书：\t\n",k);
						printf("    书名: %s\t\n",p->name);
						printf("  作者名: %s\t\n",p->author);
						printf("  出版社: %s\t\n",p->press);
						printf("ISBN编号: %s\t\n",p->number);
						printf("该书相关度为：%.4f",flag);
						printf("\n确定是这一本吗？(Y/N)\n");
						scanf("%s",&j);
						if(j=='Y'||j=='y')
						{
							i=1;//判断变量返回为真
							if(p->jie==0)
							{
								p->jie=1;
								s=(struct lendtime *)malloc(sizeof(struct lendtime));//分配s节点空间
								time_t timet;//调用数据库中time函数
								struct tm *t;//创建tm结构体用于保存时间
								time (&timet);//得到电脑的时间
								t=gmtime(&timet);//读取标准时区（UTC）时间
								strcpy(s->name,p->name);
								s->year=1900+t->tm_year;
								s->month=1+t->tm_mon;
								s->day=t->tm_mday;
								s->hour=8+t->tm_hour;
								s->minute=t->tm_min;
								s->second=t->tm_sec;
								strcpy(s->man,stname);
								q->next=s;//将新增加的节点添加进链表
								q=s;//p指向尾节点，向后移
								s->next=NULL;//修改s下一个节点为空
								printf("\n借阅成功！\n");
								printf("    书名: %s\t\n",p->name);
								printf("  作者名: %s\t\n",p->author);
								printf("  出版社: %s\t\n",p->press);
								printf("ISBN编号: %s\t\n",p->number);
								printf("借阅时间为%d年%d月%d日%d时%d分%d秒。\n",1900+t->tm_year,1+t->tm_mon,t->tm_mday,8+t->tm_hour,t->tm_min,t->tm_sec);
								printf("借阅账户为%s\t\n",stname);
							}
							else
							{
								printf("该书已被借阅！\n");
							}
							break;
						}
					}
				}
				else
				{
					if(strcmp(search,sure)==0)
					{
						i=1;//判断变量返回为真
						if(p->jie==0)
						{
							p->jie=1;
							s=(struct lendtime *)malloc(sizeof(struct lendtime));//分配s节点空间
							time_t timet;//调用数据库中time函数
							struct tm *t;//创建tm结构体用于保存时间
							time (&timet);//得到电脑的时间
							t=gmtime(&timet);//读取标准时区（UTC）时间
							strcpy(s->name,p->name);
							s->year=1900+t->tm_year;
							s->month=1+t->tm_mon;
							s->day=t->tm_mday;
							s->hour=8+t->tm_hour;
							s->minute=t->tm_min;
							s->second=t->tm_sec;
							strcpy(s->man,stname);
							q->next=s;//将新增加的节点添加进链表
							q=s;//p指向尾节点，向后移
							s->next=NULL;//修改s下一个节点为空
							printf("\n借阅成功！\n");
							printf("    书名: %s\t\n",p->name);
							printf("  作者名: %s\t\n",p->author);
							printf("  出版社: %s\t\n",p->press);
							printf("ISBN编号: %s\t\n",p->number);
							printf("借阅时间为%d年%d月%d日%d时%d分%d秒。\n",1900+t->tm_year,1+t->tm_mon,t->tm_mday,8+t->tm_hour,t->tm_min,t->tm_sec);
							printf("借阅账户为%s\t\n",stname);
						}
						else
						{
							printf("该书已被借阅！\n");
						}
						break;
					}
				}
			}
			if(i==0)
			{
				printf("图书不存在！\n");
			}
		}
	}
	else
	{
		printf("借阅书目数量已达上限！\n");
	}
	system("pause");//按任意键继续
	system("cls");//清屏
}

void xfind(struct book * head,struct lendtime * head2)
{
	struct book *p;//p为遍历时使用的指针
	struct lendtime *q;//q为遍历时使用的指针
	int num=0;
	p=head;
	q=head2;
	printf("账户%s: \n\n",stname);
	if(head==NULL||head->next==NULL)//判断数据库是否为空
	{
		printf("图书库为空！\n");
	}
	else
	{
		while(p->next!=NULL)//指针从头节点开始移动，遍历至尾结点，查找书目信息
		{
			p=p->next;//修改p指向下一个节点
			if(p->jie!=0)
			{
				while(q->next!=NULL)//指针从头节点开始移动，遍历至尾结点，查找时间信息;
				{
					q=q->next;
					if(strcmp(q->name,p->name)==0)
					{
						break;
					}
				}
				if(strcmp(q->man,stname)==0)
				{
					num++;
					printf("借阅图书%d: \n",num);
					printf("      书名: %s\t\n",p->name);
					printf("    作者名: %s\t\n",p->author);
					printf("    出版社: %s\t\n",p->press);
					printf("  ISBN编号: %s\t\n",p->number);
					printf("已借阅时间: %d月\t\n",p->jie);
					printf("借阅时间为%d年%d月%d日%d时%d分%d秒。\n",q->year,q->month,q->day,q->hour,q->minute,q->second);
				}
				q=head2;
			}
		}
	}
	if(num==0)
	{
		printf("无借阅书目！\n");
	}
	system("pause");//按任意键继续
	system("cls");//清屏
}

void xreturn(struct book * head,struct lendtime * head2)
{
	struct book *p;//p为遍历时使用的指针
	struct lendtime *q,*s;////s为中间变量，q为遍历时使用的指针
	int i=0;//判断是否查找到的变量
	char name[TOTAL];
	p=head;
	q=head2;
	s=head2;
	if(head==NULL||head->next==NULL)//判断数据库是否为空
	{
		printf("图书库为空！\n");
	}
	else
	{
		printf("请输入您要归还的书名:");
		fflush(stdin);//清空输入缓冲区
		scanf("%s",&name);
		while(p->next!=NULL)//指针从头节点开始移动，遍历至尾结点，查找书目信息
		{
			p=p->next;//修改p指向下一个节点
			if(strcmp(p->name,name)==0)
			{
				i=1;//判断变量返回为真
				if(p->jie!=0)
				{
					while(q->next!=NULL)//指针从头节点开始移动，遍历至尾结点，查找时间信息;
					{
						q=q->next;
						if(strcmp(q->name,p->name)==0)
						{
							if(strcmp(q->man,stname)==0)
							{
								p->jie=0;
								printf("归还成功！\n");
								printf("    书名: %s\t\n",p->name);
								printf("  作者名: %s\t\n",p->author);
								printf("  出版社: %s\t\n",p->press);
								printf("ISBN编号: %s\t\n",p->number);
								printf("借阅时间为%d年%d月%d日%d时%d分%d秒。\n",q->year,q->month,q->day,q->hour,q->minute,q->second);
								printf("借阅账户为%s\t\n",stname);
								for(;s->next!=q;)//找到所需删除卡号结点的上一个结点
								{
									s=s->next;//修改s指向下一个节点
								}
								s->next=q->next;//将后一节点地址赋值给前一节点的指针域
								free(q);//释放p节点内存
							}
							else
							{
								printf("该书被其他人借阅！\n");
							}
							break;
						}
					}	
				}
				else
				{
					printf("该书未借阅！\n");
				}
				break;
			}
		}
		if(i==0)
		{
			printf("图书不存在！\n");
		}
	}
	system("pause");//按任意键继续
	system("cls");//清屏
}

void xrelet(struct book * head,struct lendtime * head2)
{
	struct book *p;//p为遍历时使用的指针
	struct lendtime *q;//q为遍历时使用的指针
	int i=0;//判断是否查找到的变量
	char name[TOTAL];
	p=head;
	q=head2;
	if(head==NULL||head->next==NULL)//判断数据库是否为空
	{
		printf("图书库为空！\n");
	}
	else
	{
		printf("请输入您要续借的书名:");
		fflush(stdin);//清空输入缓冲区
		scanf("%s",&name);
		while(p->next!=NULL)//指针从头节点开始移动，遍历至尾结点，查找书目信息
		{
			p=p->next;//修改p指向下一个节点
			if(strcmp(p->name,name)==0)
			{
				i=1;//判断变量返回为真
				if(p->jie!=0)
				{
					while(q->next!=NULL)//指针从头节点开始移动，遍历至尾结点，查找时间信息;
					{
						q=q->next;
						if(strcmp(q->name,p->name)==0)
						{
							if(strcmp(q->man,stname)==0)
							{
								if((p->jie!=stpower)&&(p->jie<stpower))//最多续借X次
								{
									p->jie++;
									printf("续借成功！现在该书借阅时间为%d月！\t\n",p->jie);
									printf("    书名: %s\t\n",p->name);
									printf("  作者名: %s\t\n",p->author);
									printf("  出版社: %s\t\n",p->press);
									printf("ISBN编号: %s\t\n",p->number);
									printf("借阅时间为%d年%d月%d日%d时%d分%d秒。\n",q->year,q->month,q->day,q->hour,q->minute,q->second);
									printf("借阅账户为%s\t\n",stname);
								}
								else
								{
									printf("该书已达到借阅上限！\n");
								}
							}
							else
							{
								printf("该书被其他人借阅！\n");
							}
							break;
						}
					}
				}
				else
				{
					printf("该书未借阅！\n");
				}
				break;
			}
		}
		if(i==0)
		{
			printf("图书不存在！\n");
		}
	}
	system("pause");//按任意键继续
	system("cls");//清屏
}

void xfix(struct student * head3)
{
	struct student *p;
	p=head3;
	for(;;)
	{
		p=p->next;
		if(strcmp(p->ac,stname)==0)
		{
			break;
		}
	}
	printf("请修改密码：\n");
	scanf("%s",&p->pw);
	printf("密码修改成功！\n");
	system("pause");//按任意键继续
	system("cls");//清屏
}

int login(int y,struct student * head3)//登陆系统
{
	struct student *p;
	p=head3;
	int i;
	char mima[TOTAL];
	int x=0;
	char ac[TOTAL],pw[TOTAL];
	char res;
	printf("是否需要注册？(Y/N)\n");
	scanf("%s",&res);
	if (res=='Y'||res=='y')
	{
		x=3;
		enroll(head3);
	}
	else
	{
		printf("请输入账号：\n");
		scanf("%s",&ac);
		printf("请输入密码：\n");
		for(i=0;i<=TOTAL;i++)
		{
			mima[i]=getch();
			if(mima[i]=='\r')
			{
				break;
			}
			else if(mima[i]=='\b')
			{
				if(i==0)
				{
					mima[i]='\0';
					printf("\b");
					printf(" ");
					i--;
				}
				else
				{
					mima[i]='\0';
					printf("\b");
					printf(" ");
					printf("\b");
					i-=2;
				}
			}
			else
			{
			printf("*");
			}
		}
		mima[i]='\0';
		strcpy(pw,mima);
		if((strcmp(ac,"administrator")==0)&&(strcmp(pw,"goufugui")==0))//账号密码均为真
		{
			x=1;
		}
		else
		{
			while(p->next!=NULL)
			{
				p=p->next;
				if((strcmp(ac,p->ac)==0)&&(strcmp(pw,p->pw)==0))//账号密码均为真
				{
					if(p->use==1)
					{
						strcpy(stname,ac);
						stpower=p->power;
						stnum=p->num;
						x=2;
						break;
					}
					else
					{
						x=4;
						break;
					}
				}
			}
		}	
	}
	return x;
}

void enroll(struct student * head3)//注册系统
{
	int i;
	char mima[TOTAL];
	struct student *p,*s,*q;
loop:system("cls");//清屏//IMPORTANT：下面判断名字重合后返回此处
	p=head3;
	q=head3;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	s=(struct student *)malloc(sizeof(struct student));//给s指针分配内存空间
	printf("请注册账号：\n");
	scanf("%s",&s->ac);
	while(q->next!=NULL)
	{
		q=q->next;
		if(strcmp(q->ac,s->ac)==0)//重复账户名则报错
		{
			printf("已存在该账户！请重新输入！\n");
			free(s);
			system("pause");
			goto loop;
		}
	}
	printf("请输入密码：\n");
	for(i=0;i<=TOTAL;i++)
	{
		mima[i]=getch();
		if(mima[i]=='\r')
		{
			break;
		}
		else if(mima[i]=='\b')
		{
			if(i==0)
			{
				mima[i]='\0';
				printf("\b");
				printf(" ");
				i--;
			}
			else
			{
				mima[i]='\0';
				printf("\b");
				printf(" ");
				printf("\b");
				i-=2;
			}
		}
		else
		{
		printf("*");
		}
	}
	mima[i]='\0';
	strcpy(s->pw,mima);
	s->power=3;
	s->num=6;
	s->use=1;
	p->next=s;//将新增加的节点添加进链表
	p=s;//p指向尾节点，向后移
	s->next=NULL;//修改s下一个节点为空
}

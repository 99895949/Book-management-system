// MANAGER 1.21 ��ʽ��.cpp : Defines the entry point for the console application.

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "Windows.h"
#include "conio.h"

#define TOTAL 100//�����ܴ�����鱾��Ŀ�����ֵ
#define NULL 0//����NULLΪ0
#define EOF -1//����EOFΪ-1

static int re=0;//�������·��ص�½�����ȫ�ֱ���
static char stname[TOTAL];//��¼ѧ��ID��ȫ�ֱ���
static int stpower;//��¼ѧ��Ȩ�޵�ȫ�ֱ���
static int stnum;//��¼ѧ��Ȩ�޵�ȫ�ֱ���

enum//ö�ٶ�Ӧ����ascii��
{
	UP=72,
	DOWN=80,
	ENTER=13,
};

char *caidan[]=
{
	"����  ��[1]ͼ����Ϣ¼��   ���  ",
	"����  ��[2]ͼ����Ϣ��ѯ   ���  ",
	"����  ��[3]ͼ����Ϣɾ��   ���  ",
	"����  ��[4]ͼ����Ϣ�޸�   ���  ",
	"����  ��[5]ȫ��ͼ����Ϣ   ���  ",
	"����  ��[6]ѧ���˻�����   ���  ",
	"����  ��[7]�˳�ϵͳ       ���  ",
};

char *xcaidan[]=
{
	"����  ��[1]����ͼ��   ���  ",
	"����  ��[2]���Ĳ�ѯ   ���  ",
	"����  ��[3]�黹ͼ��   ���  ",
	"����  ��[4]����ͼ��   ���  ",
	"����  ��[5]�޸�����   ���  ",
	"����  ��[6]�˳�ϵͳ   ���  ",
};

struct book//�����鱾�ṹ��
{
	char name[TOTAL];//����
	char author[TOTAL];//����
	char press[TOTAL];//������
	char number[TOTAL];//���
	int jie;//�Ƿ����
	struct book * next;
};

struct lendtime//�������ʱ��ṹ��
{
	char name[TOTAL];
	int year;//�������
	int month;//�����·�
	int day;//��������
	int hour;//����Сʱ
	int minute;//���ķ���
	int second;//������
	char man[TOTAL];//����������
	struct lendtime * next;
};

struct student//����ѧ���˻���Ϣ
{
	char ac[TOTAL];
	char pw[TOTAL];
	int power;//�����·�����
	int num;//������Ŀ����
	int use;//�˻��Ƿ����ʹ��
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

struct book * Create()//����book����
{
	struct book * head;
	head=(struct book *)malloc(sizeof(struct book));//����ͷ�ڵ�ռ�
	head->next=NULL;//ͷ�ڵ�ָ�����ʼ������Ϊ��
	scan(head);
	return head;
}

struct lendtime * Create2()//����lendtime����
{
	struct lendtime * head2;
	head2=(struct lendtime *)malloc(sizeof(struct lendtime));//����ͷ�ڵ�ռ�
	head2->next=NULL;//ͷ�ڵ�ָ�����ʼ������Ϊ��
	tscan(head2);
	return head2;
}

struct student * Create3()//����student����
{
	struct student * head3;
	head3=(struct student *)malloc(sizeof(struct student));//����ͷ�ڵ�ռ�
	head3->next=NULL;//ͷ�ڵ�ָ�����ʼ������Ϊ��
	gscan(head3);
	return head3;
}

int ldmin(int a,int b,int c)//LD�㷨�о�����Сֵ�㷨
{
	int min=a;
	if(min>b)
		min=b;
	if(min>c)
		min=c;
	return min;
}

int ldmax(int a,int b)//LD�㷨�бȽ��ĸ��ַ����������㷨
{
	int max=a;
	if(max<b)
		max=b;
	return max;
}

double ld(char str1[],char str2[])//����ģ��������ضȵ�LD�㷨
{
	int len1,len2;
	double xg;
	int i,j;
	char ch1,ch2;
	int temp;
	len1=strlen(str1);//
	len2=strlen(str2);//�����ַ�������
	double c,e;
	int d[100][100];//�������
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
			if(ch1==ch2)//�����ַ�������Ԫ��λ�����ϵ�λ�ü���ʱ����1����֮��1
			{
				temp=0;
			}
			else
			{
				temp=1;
			}
			d[i][j]=ldmin(d[i-1][j]+1,d[i][j-1]+1,d[i-1][j-1]+temp);//��λ��Ԫ��ֵΪ�����ϡ����ϵ�ֵ����һ����������е���Сֵ
		}
	}
	c=d[len1][len2];//ȡ���������½ǵ�Ԫ��ֵ
	e=ldmax(len1,len2);//ȡ�����ַ����������Ǹ��ĳ���
	xg=1-(c/e);//��ضȼ��㹫ʽ
	return xg;
}

void sleep(int s)//ֹͣһ��ʱ����㷨
{
	time_t tmp1=time(NULL);
	time_t tmp2=tmp1;
	while(difftime(tmp2,tmp1)<s)
	{
		tmp2=time(NULL);
	}
}

int main(struct book * head,struct lendtime * head2,struct student * head3)//������
{
	char wu;
	int num,a=0;
	HANDLE ohandle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ���
	SetConsoleTextAttribute(ohandle,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//����������ɫ
	while(!kbhit())
	{
		time_t timet;
		struct tm *t;
		time (&timet);
		t=gmtime(&timet);
		printf("��ӭ��ʹ��ͼ�����ϵͳ1.21��ʽ�棡\n\n���ߣ������ɣ����������\n\nС�飺�����������\n\n\n");
		printf("        ʵʱʱ�ӣ�        \n");
		printf(" ������������������������   \n");
		printf("��                      ��  \n");
		printf("��     %2d : %2d : %2d     ��  \n",8+t->tm_hour,t->tm_min,t->tm_sec);
		printf("��                      ��  \n");
		printf(" ������������������������   \n");
		printf("\n\n�������������");
		sleep(1);
		system("cls");
	}
	wu=getch();
	head=Create();
	head2=Create2();
	head3=Create3();
loop:system("cls");//����//�Ƿ����ʷ��ص�ַ
	printf("ͼ�����ϵͳ1.21��ʽ��\n\n");
	num=login(a,head3);//��½ϵͳ
	system("cls");//����
	switch (num)//��login��������ֵ����½ϵͳ�������ж�
	{
	case 0://�Ƿ����ʷ���Ϊ0
		{
			printf("���Ƿ����ʣ������³��ԣ���\n");
			system("pause");//�����������
			system("cls");//����
			goto loop;
		}
	case 1://����Ա���ʷ���Ϊ1
		{
			printf("�ﻶӭ������Ա����\n");
			system("pause");//�����������
			menu(head,head3);//�������Ա�˵�
			break;
		}
	case 2://�û����ʷ���Ϊ2
		{
			printf("�ﻶӭ��ʹ��ͼ��ݽ���ϵͳ����\n");
			system("pause");//�����������
			xmenu(head,head2,head3);
			break;
		}
	case 3://ע�᷵��Ϊ3
		{
			printf("��ע��ɹ�����\n");
			system("pause");//�����������
			system("cls");//����
			goto loop;
		}
	case 4://�˻�������Ա���᷵��Ϊ4
		{
			printf("���˻�������Ա���ᣬ����ϵ����Ա����\n");
			system("pause");//�����������
			system("cls");//����
			goto loop;
		}
	}
	if(re==1)//���reΪ1�򷵻�loop��
	{
		re=0;
		system("cls");//����
		goto loop;
	}
	save(head);
	tsave(head2);
	gsave(head3);
	system("pause");
	return 0;
}

void scan(struct book * head)//��ȡ֮ǰ��ӵ�����������
{
	struct book *s,*p;//����ṹ��ָ����� sָ�򿪱ٵ��½���׵�ַ pΪ�м����
	p=head;//��pָ���׼ͷ���
	FILE *fp;
	fp=fopen("book.txt","a+");//�Զ�д��ʽ�½�����book.txt�ļ�
	while(p->next!= NULL)
	{
		p=p->next;//�޸�pָ����һ���ڵ�
	}
	if(fgetc(fp)==EOF)//ץȡ�ļ���һ���ַ�
	{
		head=NULL;//��txt��û��������ͷ����Ϊ��
	}
	else
	{
		while(!feof(fp))//���ж�ȡ�ļ�ֱ������
		{
			s=(struct book *)malloc(sizeof(struct book));//����s�ڵ�ռ�
			fscanf(fp,"%s %s %s %s %d \n",&s->name,&s->author,&s->press,&s->number,&s->jie);//����Ӧ��ʽ��ȡ������s�ڵ�
			p->next=s;//�������ӵĽڵ���ӽ�����
			p=s;//pָ��β�ڵ㣬�����
			s->next=NULL;//�޸�s��һ���ڵ�Ϊ��
		}
	}
	fclose(fp);
}

void tscan(struct lendtime * head2)//��ȡ֮ǰ��ӵ�����������
{
	struct lendtime *s,*p;//����ṹ��ָ����� sָ�򿪱ٵ��½���׵�ַ pΪ�м����
	p=head2;//��pָ���׼ͷ���
	FILE *fp;
	fp=fopen("time.txt","a+");//�Զ�д��ʽ�½�����time.txt�ļ�
	while(p->next!= NULL)
	{
		p=p->next;//�޸�pָ����һ���ڵ�
	}
	if(fgetc(fp)==EOF)//ץȡ�ļ���һ���ַ�
	{
		head2=NULL;//��txt��û��������ͷ����Ϊ��
	}
	else
	{
		while(!feof(fp))//���ж�ȡ�ļ�ֱ������
		{
			s=(struct lendtime *)malloc(sizeof(struct lendtime));//����s�ڵ�ռ�
			fscanf(fp,"%s %d %d %d %d %d %d %s \n",&s->name,&s->year,&s->month,&s->day,&s->hour,&s->minute,&s->second,&s->man);//����Ӧ��ʽ��ȡ������s�ڵ�
			p->next=s;//�������ӵĽڵ���ӽ�����
			p=s;//pָ��β�ڵ㣬�����
			s->next=NULL;//�޸�s��һ���ڵ�Ϊ��
		}
	}
	fclose(fp);
}

void gscan(struct student * head3)//��ȡ֮ǰ��ӵ�����������
{
	struct student *s,*p;//����ṹ��ָ����� sָ�򿪱ٵ��½���׵�ַ pΪ�м����
	p=head3;//��pָ���׼ͷ���
	FILE *fp;
	fp=fopen("student.txt","a+");//�Զ�д��ʽ�½�����time.txt�ļ�
	while(p->next!= NULL)
	{
		p=p->next;//�޸�pָ����һ���ڵ�
	}
	if(fgetc(fp)==EOF)//ץȡ�ļ���һ���ַ�
	{
		head3=NULL;//��txt��û��������ͷ����Ϊ��
	}
	else
	{
		while(!feof(fp))//���ж�ȡ�ļ�ֱ������
		{
			s=(struct student *)malloc(sizeof(struct student));//����s�ڵ�ռ�
			fscanf(fp,"%s %s %d %d %d \n",&s->ac,&s->pw,&s->power,&s->num,&s->use);//����Ӧ��ʽ��ȡ������s�ڵ�
			p->next=s;//�������ӵĽڵ���ӽ�����
			p=s;//pָ��β�ڵ㣬�����
			s->next=NULL;//�޸�s��һ���ڵ�Ϊ��
		}
	}
	fclose(fp);
}

void menu(struct book * head,struct student * head3)//����Ա�˵�
{
loop:char key=0;
	int i,select=0;
	HANDLE ohandle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ���
	SetConsoleTextAttribute(ohandle,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//����������ɫ
	for (;;)
	{
		system("cls");//����
		time_t timet;//�������ݿ���time����
		struct tm *t;//����tm�ṹ�����ڱ���ʱ��
		time (&timet);//�õ����Ե�ʱ��
		t=gmtime(&timet);//��ȡ��׼ʱ����UTC��ʱ��
		printf("����ʱ��Ϊ%d��%d��%d��%dʱ%d��%d�롣\n",1900+t->tm_year,1+t->tm_mon,t->tm_mday,8+t->tm_hour,t->tm_min,t->tm_sec);
		printf("\n");
		printf(" ���������������������������� \n");
		printf("�����������������\n");
		printf("����� ��ͼ�����ϵͳ�� ����\n");
		printf("�����������������\n");
		for(i=0;i<7;i++)//���ﹲ7��ѡ��
		{
			if(i==select)//���ý������
				SetConsoleTextAttribute(ohandle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
			else if(i==select+1)//�ָ�����
				SetConsoleTextAttribute(ohandle,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
			puts(caidan[i]);
		}
		SetConsoleTextAttribute(ohandle,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//�ָ�ԭ������
		printf("�����������������\n");	
		printf(" ���������������������������� \n");
		key=getch();//��ȡ�������밴��
		if(key==0xd)//Enter��
		{
			break;
		}
		if(key<0)//��ascii���2���ֽ�
		{
			key=getch();//��ȡ�����ڶ��ֽڵ�����
			switch(MapVirtualKey(key,1))//�԰���ascii��switch
			{
			case VK_UP://����
				{
				select = (select+6)%7;//�������ƣ���һ������ѡ�񣬹�7��ѡ��
				break;
				}
			case VK_DOWN://����
				{
				select = (select+1)%7;//�������ƣ���һ
				break;
				}
			}
		}
	}
	system("cls");//����
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

void save(struct book * head)//�����������ļ�
{
	struct book *p;//����ṹ��ָ����� pָ�򿪱ٵ��½���׵�ַ
	FILE *fp;
	p=head;//��pָ���׼ͷ���
	fp=fopen("book.txt","w+");//�Զ�д��ʽ�½�book.txt�ļ�
	while(p->next!=NULL)
	{
		p=p->next;//�޸�pָ����һ���ڵ�
		fprintf(fp,"\n%s %s %s %s %d ",p->name,p->author,p->press,p->number,p->jie);
	}
	fclose(fp);
	printf("�ѽ�ͼ�����ݱ��浽book.txt�ļ�\n");
}

void tsave(struct lendtime * head2)
{
	struct lendtime *p;//����ṹ��ָ����� pָ�򿪱ٵ��½���׵�ַ
	FILE *fp;
	p=head2;//��pָ���׼ͷ���
	fp=fopen("time.txt","w+");//�Զ�д��ʽ�½�time.txt�ļ�
	while(p->next!=NULL)
	{
		p=p->next;//�޸�pָ����һ���ڵ�
		fprintf(fp,"\n%s %d %d %d %d %d %d %s ",p->name,p->year,p->month,p->day,p->hour,p->minute,p->second,p->man);
	}
	fclose(fp);
	printf("�ѽ�����ʱ�����ݱ��浽time.txt�ļ�\n");
}

void gsave(struct student * head3)
{
	struct student *p;//����ṹ��ָ����� pָ�򿪱ٵ��½���׵�ַ
	FILE *fp;
	p=head3;//��pָ���׼ͷ���
	fp=fopen("student.txt","w+");//�Զ�д��ʽ�½�student.txt�ļ�
	while(p->next!=NULL)
	{
		p=p->next;//�޸�pָ����һ���ڵ�
		fprintf(fp,"\n%s %s %d %d %d ",p->ac,p->pw,p->power,p->num,p->use);
	}
	fclose(fp);
	printf("�ѽ�ѧ���˻����ݱ��浽student.txt�ļ�\n");
}

void add(struct book * head)//����鱾
{
	struct book *s,*p;//����ṹ��ָ����� sָ�򿪱ٵ��½���׵�ַ pΪ�м����
	char again='Y';//�������,ѡ���Ƿ��ظ�����
	p=head;
	while(p->next!= NULL)
	{
		p=p->next;//�޸�pָ����һ���ڵ�
	}  
	while(again=='Y'||again=='y')//�����¿ռ�,��������,��ӽ�����
	{
		s=(struct book *)malloc(sizeof(struct book));//����s�ڵ�ռ�
		printf("��������ͼ������:\n");
		fflush(stdin);//������뻺����
		scanf("%s",&s->name);
		printf("��������ͼ��������:\n");
		fflush(stdin);//������뻺����
		scanf("%s",&s->author);
		printf("��������ͼ�������:\n");
		fflush(stdin);//������뻺����
		scanf("%s",&s->press);
		printf("��������ͼ��ISBN���:\n");
		fflush(stdin);//������뻺����
		scanf("%s",&s->number);
		s->jie=0;//����ͼ���ʼ�������Ϊδ���
		p->next=s;//�������ӵĽڵ���ӽ�����
		p=s;//pָ��β�ڵ㣬�����
		s->next=NULL;//�޸�s��һ���ڵ�Ϊ��
		printf("��ӳɹ���\n");
		printf("������ӣ�(Y/N):\n");
		fflush(stdin);//������뻺����
		scanf("%c",&again);
	}
	system("pause");//�����������
	system("cls");//����
} 

void find(struct book * head)//�����鱾
{
	struct book *p;//����ṹ��ָ����� pΪ�м����
	int i=0;//�ж��Ƿ���ҵ��ı���
	int way;//������ҷ�ʽ
	char sure[TOTAL];//�洢���ݵ��м����
	char search[TOTAL];//�洢��������
	p=head;
	if(head==NULL||head->next==NULL)//�ж����ݿ��Ƿ�Ϊ��
	{
		printf("ͼ���Ϊ�գ�\n");
	}
	else
	{
jump:printf("��ѡ����ҷ�ʽ��\n1����������\n2�����߲���\n3�����������\n4��ISBN��Ų���\n���ҷ�ʽ��");//��wayֵ�Ƿ��ķ��ص�ַ
		fflush(stdin);//������뻺����
		scanf("%d",&way);
		if(way==1||way==2||way==3||way==4)
		{
			printf("��������Ҫ���ҵ�����:");
			fflush(stdin);//������뻺����
			scanf("%s",&search);
		}
		while(p->next!=NULL)//ָ���ͷ�ڵ㿪ʼ�ƶ���������β��㣬������Ŀ��Ϣ
		{
			p=p->next;//�޸�pָ����һ���ڵ�
			switch (way)
			{
			case 1:strcpy(sure,p->name);break;
			case 2:strcpy(sure,p->author);break;
			case 3:strcpy(sure,p->press);break;
			case 4:strcpy(sure,p->number);break;
			default:
				{
					printf("���ҷ�ʽ���Ϸ���������ѡ��\n\n");
					system("pause");//�����������
					system("cls");//����
					goto jump;
				}
			}
			if(strcmp(sure,search)==0)
			{
				i=1;//�жϱ�������Ϊ��
				printf("\n���ҵ�ͼ�飡\n");
				printf("    ����: %s\t\n",p->name);
				printf("  ������: %s\t\n",p->author);
				printf("  ������: %s\t\n",p->press);
				printf("ISBN���: %s\t\n",p->number);
				if(p->jie!=0)
				{
					printf("�ѽ��%d��\t\n",p->jie);
				}
				else
				{
					printf("δ���\t\n");
				}
				break;
			}
		}
		if(i==0)
		{
			printf("ͼ�鲻���ڣ�\n");//�жϱ���Ϊ��ʱ����
		}
	}
	system("pause");//�����������
	system("cls");//����
}

void dele(struct book * head)//ɾ���鱾
{
	struct book *s,*p;//sΪ�м������pΪ����ʱʹ�õ�ָ��
	char name[TOTAL];
	int i=0;//�ж��Ƿ���ҵ��ı���
	p=head;
	s=head;
	printf("��������Ҫɾ��������:\n");
	scanf("%s",&name);
	while(p!=NULL)//������β���
	{
		if(strcmp(p->name,name)==0)
		{
			i=1;
			break;
		}
		p=p->next;//�޸�pָ����һ���ڵ�
	}
	if(i==1)
	{
		for(;s->next!=p;)//�ҵ�����ɾ�����Ž�����һ�����
		{
			s=s->next;//�޸�sָ����һ���ڵ�
		}
		s->next=p->next;//����һ�ڵ��ַ��ֵ��ǰһ�ڵ��ָ����
		free(p);//�ͷ�p�ڵ��ڴ�
		printf("ɾ���ɹ���\n");
	}
	else//δ�ҵ���Ŀ
	{
		printf("ͼ�鲻���ڣ�\n");
	}
	system("pause");//�����������
	system("cls");//����
}

void editor(struct book * head)//�༭�鱾
{
	struct book *s,*p;//sΪ�м������pΪ����ʱʹ�õ�ָ��
	char name[TOTAL];
	int i=0;//�ж��Ƿ���ҵ��ı���
	p=head;
	s=head;
	printf("��������Ҫ�༭������:\n");
	scanf("%s",&name);
	while(p!=NULL)//������β���
	{
		if(strcmp(p->name,name)==0)
		{
			i++;
			break;
		}
		p=p->next;//�޸�pָ����һ���ڵ�
	}
	if(i==1)
	{
		for(;s->next!=p;)//�ҵ�����ɾ�����Ž�����һ�����
		{
			s=s->next;//�޸�sָ����һ���ڵ�
		}
		s->next=p->next;//����һ�ڵ��ַ��ֵ��ǰһ�ڵ��ָ����
		free(p);//�ͷ�p�ڵ��ڴ�
		struct book *s,*p;//����ṹ��ָ����� sָ�򿪱ٵ��½���׵�ַ pΪ�м����
		p=head;
		while(p->next!= NULL)
		{
			p=p->next;//�޸�pָ����һ���ڵ�
		}
		s=(struct book *)malloc(sizeof(struct book));//����s�ڵ�ռ�
		printf("������ͼ������:\n");
		fflush(stdin);//������뻺����
		scanf("%s",&s->name);
		printf("������ͼ��������:\n");
		fflush(stdin);//������뻺����
		scanf("%s",&s->author);
		printf("������ͼ�������:\n");
		fflush(stdin);//������뻺����
		scanf("%s",&s->press);
		printf("������ͼ��ISBN���:\n");
		fflush(stdin);//������뻺����
		scanf("%s",&s->number);
		s->jie=0;
		p->next=s;//�������ӵĽڵ���ӽ�����
		p=s;//pָ��β�ڵ㣬�����
		s->next=NULL;//�޸�s��һ���ڵ�Ϊ��
	}
	else//δ�ҵ���Ŀ
	{
		printf("ͼ�鲻���ڣ�\n");
	}
	system("pause");//�����������
	system("cls");//����
}

 
void print(struct book * head)//���ȫ�����
{
	struct book *p;
	int num=0;//���������Ŀ�����ı���
	if(head==NULL||head->next==NULL)//�ж����ݿ��Ƿ�Ϊ��
	{
		printf("û��ͼ���¼��\n");
	}
	else
	{
		p=head;
		while(p->next!= NULL)//ָ���ͷ�ڵ㿪ʼ�ƶ���������β��㣬�������ͼ����Ϣ
		{
			num++;
			p=p->next;//�޸�pָ����һ���ڵ�
			printf("��%d��ͼ�飺\n",num);
			printf("    ����: %s\t\n",p->name);
			printf("  ������: %s\t\n",p->author);
			printf("  ������: %s\t\n",p->press);
			printf("ISBN���: %s\t\n",p->number);
			if(p->jie!=0)
			{
				printf("�ѽ��%d��\t\n",p->jie);
			}
			else
			{
				printf("δ���\t\n");
			}
			printf("\n");
		}
	}
	system("pause");//�����������
	system("cls");//����
}

void manage(struct student * head3)
{
	struct student *p,*s;
	p=head3;
	s=head3;
	char mag[TOTAL];
	int i=0;
	int choose;
	printf("������Ҫ�����ѧ���˻���\n");
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
		system("cls");//����
		while(i==1)
		{
			printf("�˻���%s\n��ѡ������ܣ�\n1���鿴����\n2���޸��������·�\n3���޸���������Ŀ\n4�������˻�\n5���ⶳ�˻�\n6��ע���˻�\n7���˳�\n�����ܣ�",p->ac);
			scanf("%d",&choose);
			printf("\n");
			switch (choose)
			{
			case 1:
				{
					printf("�����ǣ�%s\n",p->pw);
					break;
				}
			case 2:
				{
					printf("ԭ�������·�Ϊ%d�£�����Ϊ��",p->power);
					scanf("%d",&p->power);
					printf("\n���ĳɹ�Ϊ%d�£�\n",p->power);
					break;
				}
			case 3:
				{
					printf("ԭ��������ĿΪ%d��������Ϊ��",p->num);
					scanf("%d",&p->num);
					printf("\n���ĳɹ�Ϊ%d����\n",p->num);
					break;
				}
			case 4:
				{
					p->use=0;
					printf("����ɹ���\n");
					break;
				}
			case 5:
				{
					p->use=1;
					printf("�ⶳ�ɹ���\n");
					break;
				}
			case 6:
				{
					for(;s->next!=p;)//�ҵ�����ɾ�����Ž�����һ�����
					{
						s=s->next;//�޸�sָ����һ���ڵ�
					}
					s->next=p->next;//����һ�ڵ��ַ��ֵ��ǰһ�ڵ��ָ����
					free(p);//�ͷ�p�ڵ��ڴ�
					printf("ɾ���ɹ���\n");
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
					printf("���벻�Ϸ������������룡\n");
					break;
				}
			}
			system("pause");//�����������
			system("cls");//����
		}
	}
	else
	{
		printf("�˻������ڣ�\n");
		system("pause");//�����������
		system("cls");//����
	}
}

void exit()//�˳�
{
	char again;
	system("cls");//����
	printf("��лʹ��ͼ�����ϵͳ��\n\n");
	printf("�Ƿ���Ҫ��������½���棿��Y/N��\n");
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
	HANDLE ohandle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ���
	SetConsoleTextAttribute(ohandle,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//����������ɫ
	for (;;)
	{
		system("cls");//����
		time_t timet;//�������ݿ���time����
		struct tm *t;//����tm�ṹ�����ڱ���ʱ��
		time (&timet);//�õ����Ե�ʱ��
		t=gmtime(&timet);//��ȡ��׼ʱ����UTC��ʱ��
		printf("����ʱ��Ϊ%d��%d��%d��%dʱ%d��%d�롣\n",1900+t->tm_year,1+t->tm_mon,t->tm_mday,8+t->tm_hour,t->tm_min,t->tm_sec);
		printf("�˻���%s\n�������·ݣ�%d\n������������%d\n",stname,stpower,stnum);
		printf("\n");
		printf(" ������������������������ \n");
		printf("���������������\n");
		printf("���� ��ͼ�����ϵͳ�� ���\n");
		printf("���������������\n");
		for(i=0;i<6;i++)//���ﹲ6��ѡ��
		{
			if(i==select)//���ý������
				SetConsoleTextAttribute(ohandle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
			else if(i==select+1)//�ָ�����
				SetConsoleTextAttribute(ohandle,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
			puts(xcaidan[i]);
		}
		SetConsoleTextAttribute(ohandle,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//�ָ�ԭ������
		printf("���������������\n");	
		printf(" ������������������������ \n");
		key=getch();//��ȡ�������밴��
		if(key==0xd)//Enter��
		{
			break;
		}
		if(key<0)//��ascii���2���ֽ�
		{
			key=getch();//��ȡ�����ڶ��ֽڵ�����
			switch(MapVirtualKey(key,1))//�԰���ascii��switch
			{
			case VK_UP://����
				{
				select = (select+5)%6;//�������ƣ���һ������ѡ�񣬹�6��ѡ��
				break;
				}
			case VK_DOWN://����
				{
				select = (select+1)%6;//�������ƣ���һ
				break;
				}
			}
		}
	}
	system("cls");//����
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
	struct book *p;//pΪ����ʱʹ�õ�ָ��
	struct lendtime *s,*q;//sָ�򿪱ٵ��½���׵�ַ qΪ�м����
	int enough=0;//�жϽ�����Ŀ�ı���
	int i=0,k=0;//�ж��Ƿ���ҵ��ı���
	int way;//������ҷ�ʽ
	char sure[TOTAL];//�洢���ݵ��м����
	char search[TOTAL];//�洢��������
	char fuzzy;//�Ƿ�ģ������
	char j;//ģ������ʱȷ����Ŀ�ı���
	double flag;//�洢ģ������ʱ��Ӧ��Ŀ����ضȵı���
	int chnum;//�����Ӧ��Ŀ��Ч���ȵ��м����
	double character,dao;//�洢��Ӧ��Ŀ��Ч���ȣ�������������ĸȫ������Ϊ1��������strlen���Ļ����Ϊ2������ȡ�����ı���
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
	if(enough<stnum)//������X��
	{
		while(q->next!= NULL)
		{
			q=q->next;//�޸�qָ����һ���ڵ�
		}
		if(head==NULL||head->next==NULL)//�ж����ݿ��Ƿ�Ϊ��
		{
			printf("ͼ���Ϊ�գ�\n");
		}
		else
		{
			printf("�Ƿ�ʹ��ģ�����ң�Y/N����");
			fflush(stdin);//������뻺����
			scanf("%c",&fuzzy);
jump:printf("��ѡ����ҷ�ʽ��\n1����������\n2�����߲���\n3�����������\n4��ISBN��Ų���\n���ҷ�ʽ��");//��wayֵ�Ƿ����صĵ�ַ
			fflush(stdin);//������뻺����
			scanf("%d",&way);
			if(way==1||way==2||way==3||way==4)
			{
				printf("��������Ҫ���ҵ�����:");
				fflush(stdin);//������뻺����
				scanf("%s",&search);
			}
			while(p->next!=NULL)//ָ���ͷ�ڵ㿪ʼ�ƶ���������β��㣬������Ŀ��Ϣ
			{
				p=p->next;//�޸�pָ����һ���ڵ�
				switch (way)
				{
				case 1:strcpy(sure,p->name);break;
				case 2:strcpy(sure,p->author);break;
				case 3:strcpy(sure,p->press);break;
				case 4:strcpy(sure,p->number);break;
				default:
					{
						printf("���ҷ�ʽ���Ϸ���������ѡ��\n\n");
						system("pause");//�����������
						system("cls");//����
						goto jump;
					}
				}
				chnum=strlen(sure);
				character=0.0000;
				for(chnum=0;sure[chnum];)//���������ַ�������Ч����
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
				dao=(1.0000/character)-0.0000001;//ȡ��Ч���ȵ�������һ��΢Сֵ��ȷ������ض���ͬʱ����Чʶ��
				if(fuzzy=='Y'||fuzzy=='y')
				{
					flag=0.000+ld(sure,search);//��ض�
					if(flag!=0&&flag>=dao)//��ضȲ�����0�������ַ����������ַ���ͬ������ضȴ��ڵ�����Ч���ȵĵ�����ȷ��������ʱ��ʶ������2�����������������׼ȷ�ʣ�
					{
						k++;
						printf("\n");
						printf("��%d���飺\t\n",k);
						printf("    ����: %s\t\n",p->name);
						printf("  ������: %s\t\n",p->author);
						printf("  ������: %s\t\n",p->press);
						printf("ISBN���: %s\t\n",p->number);
						printf("������ض�Ϊ��%.4f",flag);
						printf("\nȷ������һ����(Y/N)\n");
						scanf("%s",&j);
						if(j=='Y'||j=='y')
						{
							i=1;//�жϱ�������Ϊ��
							if(p->jie==0)
							{
								p->jie=1;
								s=(struct lendtime *)malloc(sizeof(struct lendtime));//����s�ڵ�ռ�
								time_t timet;//�������ݿ���time����
								struct tm *t;//����tm�ṹ�����ڱ���ʱ��
								time (&timet);//�õ����Ե�ʱ��
								t=gmtime(&timet);//��ȡ��׼ʱ����UTC��ʱ��
								strcpy(s->name,p->name);
								s->year=1900+t->tm_year;
								s->month=1+t->tm_mon;
								s->day=t->tm_mday;
								s->hour=8+t->tm_hour;
								s->minute=t->tm_min;
								s->second=t->tm_sec;
								strcpy(s->man,stname);
								q->next=s;//�������ӵĽڵ���ӽ�����
								q=s;//pָ��β�ڵ㣬�����
								s->next=NULL;//�޸�s��һ���ڵ�Ϊ��
								printf("\n���ĳɹ���\n");
								printf("    ����: %s\t\n",p->name);
								printf("  ������: %s\t\n",p->author);
								printf("  ������: %s\t\n",p->press);
								printf("ISBN���: %s\t\n",p->number);
								printf("����ʱ��Ϊ%d��%d��%d��%dʱ%d��%d�롣\n",1900+t->tm_year,1+t->tm_mon,t->tm_mday,8+t->tm_hour,t->tm_min,t->tm_sec);
								printf("�����˻�Ϊ%s\t\n",stname);
							}
							else
							{
								printf("�����ѱ����ģ�\n");
							}
							break;
						}
					}
				}
				else
				{
					if(strcmp(search,sure)==0)
					{
						i=1;//�жϱ�������Ϊ��
						if(p->jie==0)
						{
							p->jie=1;
							s=(struct lendtime *)malloc(sizeof(struct lendtime));//����s�ڵ�ռ�
							time_t timet;//�������ݿ���time����
							struct tm *t;//����tm�ṹ�����ڱ���ʱ��
							time (&timet);//�õ����Ե�ʱ��
							t=gmtime(&timet);//��ȡ��׼ʱ����UTC��ʱ��
							strcpy(s->name,p->name);
							s->year=1900+t->tm_year;
							s->month=1+t->tm_mon;
							s->day=t->tm_mday;
							s->hour=8+t->tm_hour;
							s->minute=t->tm_min;
							s->second=t->tm_sec;
							strcpy(s->man,stname);
							q->next=s;//�������ӵĽڵ���ӽ�����
							q=s;//pָ��β�ڵ㣬�����
							s->next=NULL;//�޸�s��һ���ڵ�Ϊ��
							printf("\n���ĳɹ���\n");
							printf("    ����: %s\t\n",p->name);
							printf("  ������: %s\t\n",p->author);
							printf("  ������: %s\t\n",p->press);
							printf("ISBN���: %s\t\n",p->number);
							printf("����ʱ��Ϊ%d��%d��%d��%dʱ%d��%d�롣\n",1900+t->tm_year,1+t->tm_mon,t->tm_mday,8+t->tm_hour,t->tm_min,t->tm_sec);
							printf("�����˻�Ϊ%s\t\n",stname);
						}
						else
						{
							printf("�����ѱ����ģ�\n");
						}
						break;
					}
				}
			}
			if(i==0)
			{
				printf("ͼ�鲻���ڣ�\n");
			}
		}
	}
	else
	{
		printf("������Ŀ�����Ѵ����ޣ�\n");
	}
	system("pause");//�����������
	system("cls");//����
}

void xfind(struct book * head,struct lendtime * head2)
{
	struct book *p;//pΪ����ʱʹ�õ�ָ��
	struct lendtime *q;//qΪ����ʱʹ�õ�ָ��
	int num=0;
	p=head;
	q=head2;
	printf("�˻�%s: \n\n",stname);
	if(head==NULL||head->next==NULL)//�ж����ݿ��Ƿ�Ϊ��
	{
		printf("ͼ���Ϊ�գ�\n");
	}
	else
	{
		while(p->next!=NULL)//ָ���ͷ�ڵ㿪ʼ�ƶ���������β��㣬������Ŀ��Ϣ
		{
			p=p->next;//�޸�pָ����һ���ڵ�
			if(p->jie!=0)
			{
				while(q->next!=NULL)//ָ���ͷ�ڵ㿪ʼ�ƶ���������β��㣬����ʱ����Ϣ;
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
					printf("����ͼ��%d: \n",num);
					printf("      ����: %s\t\n",p->name);
					printf("    ������: %s\t\n",p->author);
					printf("    ������: %s\t\n",p->press);
					printf("  ISBN���: %s\t\n",p->number);
					printf("�ѽ���ʱ��: %d��\t\n",p->jie);
					printf("����ʱ��Ϊ%d��%d��%d��%dʱ%d��%d�롣\n",q->year,q->month,q->day,q->hour,q->minute,q->second);
				}
				q=head2;
			}
		}
	}
	if(num==0)
	{
		printf("�޽�����Ŀ��\n");
	}
	system("pause");//�����������
	system("cls");//����
}

void xreturn(struct book * head,struct lendtime * head2)
{
	struct book *p;//pΪ����ʱʹ�õ�ָ��
	struct lendtime *q,*s;////sΪ�м������qΪ����ʱʹ�õ�ָ��
	int i=0;//�ж��Ƿ���ҵ��ı���
	char name[TOTAL];
	p=head;
	q=head2;
	s=head2;
	if(head==NULL||head->next==NULL)//�ж����ݿ��Ƿ�Ϊ��
	{
		printf("ͼ���Ϊ�գ�\n");
	}
	else
	{
		printf("��������Ҫ�黹������:");
		fflush(stdin);//������뻺����
		scanf("%s",&name);
		while(p->next!=NULL)//ָ���ͷ�ڵ㿪ʼ�ƶ���������β��㣬������Ŀ��Ϣ
		{
			p=p->next;//�޸�pָ����һ���ڵ�
			if(strcmp(p->name,name)==0)
			{
				i=1;//�жϱ�������Ϊ��
				if(p->jie!=0)
				{
					while(q->next!=NULL)//ָ���ͷ�ڵ㿪ʼ�ƶ���������β��㣬����ʱ����Ϣ;
					{
						q=q->next;
						if(strcmp(q->name,p->name)==0)
						{
							if(strcmp(q->man,stname)==0)
							{
								p->jie=0;
								printf("�黹�ɹ���\n");
								printf("    ����: %s\t\n",p->name);
								printf("  ������: %s\t\n",p->author);
								printf("  ������: %s\t\n",p->press);
								printf("ISBN���: %s\t\n",p->number);
								printf("����ʱ��Ϊ%d��%d��%d��%dʱ%d��%d�롣\n",q->year,q->month,q->day,q->hour,q->minute,q->second);
								printf("�����˻�Ϊ%s\t\n",stname);
								for(;s->next!=q;)//�ҵ�����ɾ�����Ž�����һ�����
								{
									s=s->next;//�޸�sָ����һ���ڵ�
								}
								s->next=q->next;//����һ�ڵ��ַ��ֵ��ǰһ�ڵ��ָ����
								free(q);//�ͷ�p�ڵ��ڴ�
							}
							else
							{
								printf("���鱻�����˽��ģ�\n");
							}
							break;
						}
					}	
				}
				else
				{
					printf("����δ���ģ�\n");
				}
				break;
			}
		}
		if(i==0)
		{
			printf("ͼ�鲻���ڣ�\n");
		}
	}
	system("pause");//�����������
	system("cls");//����
}

void xrelet(struct book * head,struct lendtime * head2)
{
	struct book *p;//pΪ����ʱʹ�õ�ָ��
	struct lendtime *q;//qΪ����ʱʹ�õ�ָ��
	int i=0;//�ж��Ƿ���ҵ��ı���
	char name[TOTAL];
	p=head;
	q=head2;
	if(head==NULL||head->next==NULL)//�ж����ݿ��Ƿ�Ϊ��
	{
		printf("ͼ���Ϊ�գ�\n");
	}
	else
	{
		printf("��������Ҫ���������:");
		fflush(stdin);//������뻺����
		scanf("%s",&name);
		while(p->next!=NULL)//ָ���ͷ�ڵ㿪ʼ�ƶ���������β��㣬������Ŀ��Ϣ
		{
			p=p->next;//�޸�pָ����һ���ڵ�
			if(strcmp(p->name,name)==0)
			{
				i=1;//�жϱ�������Ϊ��
				if(p->jie!=0)
				{
					while(q->next!=NULL)//ָ���ͷ�ڵ㿪ʼ�ƶ���������β��㣬����ʱ����Ϣ;
					{
						q=q->next;
						if(strcmp(q->name,p->name)==0)
						{
							if(strcmp(q->man,stname)==0)
							{
								if((p->jie!=stpower)&&(p->jie<stpower))//�������X��
								{
									p->jie++;
									printf("����ɹ������ڸ������ʱ��Ϊ%d�£�\t\n",p->jie);
									printf("    ����: %s\t\n",p->name);
									printf("  ������: %s\t\n",p->author);
									printf("  ������: %s\t\n",p->press);
									printf("ISBN���: %s\t\n",p->number);
									printf("����ʱ��Ϊ%d��%d��%d��%dʱ%d��%d�롣\n",q->year,q->month,q->day,q->hour,q->minute,q->second);
									printf("�����˻�Ϊ%s\t\n",stname);
								}
								else
								{
									printf("�����Ѵﵽ�������ޣ�\n");
								}
							}
							else
							{
								printf("���鱻�����˽��ģ�\n");
							}
							break;
						}
					}
				}
				else
				{
					printf("����δ���ģ�\n");
				}
				break;
			}
		}
		if(i==0)
		{
			printf("ͼ�鲻���ڣ�\n");
		}
	}
	system("pause");//�����������
	system("cls");//����
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
	printf("���޸����룺\n");
	scanf("%s",&p->pw);
	printf("�����޸ĳɹ���\n");
	system("pause");//�����������
	system("cls");//����
}

int login(int y,struct student * head3)//��½ϵͳ
{
	struct student *p;
	p=head3;
	int i;
	char mima[TOTAL];
	int x=0;
	char ac[TOTAL],pw[TOTAL];
	char res;
	printf("�Ƿ���Ҫע�᣿(Y/N)\n");
	scanf("%s",&res);
	if (res=='Y'||res=='y')
	{
		x=3;
		enroll(head3);
	}
	else
	{
		printf("�������˺ţ�\n");
		scanf("%s",&ac);
		printf("���������룺\n");
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
		if((strcmp(ac,"administrator")==0)&&(strcmp(pw,"goufugui")==0))//�˺������Ϊ��
		{
			x=1;
		}
		else
		{
			while(p->next!=NULL)
			{
				p=p->next;
				if((strcmp(ac,p->ac)==0)&&(strcmp(pw,p->pw)==0))//�˺������Ϊ��
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

void enroll(struct student * head3)//ע��ϵͳ
{
	int i;
	char mima[TOTAL];
	struct student *p,*s,*q;
loop:system("cls");//����//IMPORTANT�������ж������غϺ󷵻ش˴�
	p=head3;
	q=head3;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	s=(struct student *)malloc(sizeof(struct student));//��sָ������ڴ�ռ�
	printf("��ע���˺ţ�\n");
	scanf("%s",&s->ac);
	while(q->next!=NULL)
	{
		q=q->next;
		if(strcmp(q->ac,s->ac)==0)//�ظ��˻����򱨴�
		{
			printf("�Ѵ��ڸ��˻������������룡\n");
			free(s);
			system("pause");
			goto loop;
		}
	}
	printf("���������룺\n");
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
	p->next=s;//�������ӵĽڵ���ӽ�����
	p=s;//pָ��β�ڵ㣬�����
	s->next=NULL;//�޸�s��һ���ڵ�Ϊ��
}

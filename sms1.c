
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

void show1();//画面1 
void show2();//画面2
struct student *input();//输入 
void output(struct student *pHead);//输出 
void increase(struct student *pHead);//增加 
void strike_out(struct student *);//删除
void chang(struct student *pHead);//修改 
void inquiry(struct student *pHead);//查询  
void sore(struct student *pHead); //排序 



struct student
{
	char name[20];//姓名 
	char num[20];//学号 
	char classes[20];//班级 
	double score[3];//分数 
	double aver;//平均分
	struct student *next;//指针域 
}; 

int iCound; 
void show1()
{  
	char cipher[20]={"123456"},a[20],t;
	int i,j;
	printf("欢迎进入学生信息管理系统\n");
	for(i=0;i<3;i++)
	{
		printf("请输入管理员密码：");	
		for(j=0;a[j-1]!=13;j++)
		{
			a[j]=getch();
			if(a[j]==8&&j>0)
			{
				printf("\b \b");
				j-=2;
			}		
			else if(j>=0)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
		a[j-1]='\0';	
		if(strcmp(cipher,a)==0)
	 		return;
	}
	printf("三次输入错误！！！退出系统\n");
	Sleep(150);
	exit(1);
}
void show2()
{
	printf("         ******************学生信息管理系统*************************\n");
	printf("         1.输入学生信息                 2.输出所有学生信息\n");
	printf("         3.增加新的学生信息             4.删除学生信息\n");
	printf("         5.修改学生信息                 6.查询学生信息\n");
	printf("         7.根据平均分排序输出           0.退出\n");
	printf("         请输入相应的数字\n"); 
	printf("         ***********************************************************\n");
}
void input_1(struct student *pNew)//输入节点的值 
{
	fflush(stdin);
	printf("请输入姓名：");
	gets(pNew->name);
	if(pNew->name[0]=='#')
		return; 
	printf("请输入学号：");
	gets(pNew->num);
	printf("请输入班级：");
	gets(pNew->classes);
	printf("请输入三门课的成绩：");	
	scanf("%lf%lf%lf",&pNew->score[0],&pNew->score[1],&pNew->score[2]);
	pNew->aver=(pNew->score[0]+pNew->score[1]+pNew->score[2])/3.0;	
	printf("\n");
}
struct student *input()//创建链表 
{
	struct student *pHead=NULL,*pEnd,*pNew;
	iCound=0;
	pEnd=pHead=(struct student *)malloc(sizeof(struct student));
	pNew=(struct student *)malloc(sizeof(struct student));
	printf("姓名输入#时，停止输入\n");
	input_1(pNew);
	while(pNew->name[0]!='#')
	{
		iCound++;
		pEnd->next=pNew;
		pNew->next=NULL;
		pEnd=pNew;
		pNew=(struct student *)malloc(sizeof(struct student)); 
		input_1(pNew);
	} 
	free(pNew);
	return pHead; 	
}
void output(struct student *pHead)//输出 
{
	
	int i=0;
	pHead=pHead->next;
	printf("名单内一共有%d个学生\n",iCound);
	printf("编号/排名\t姓名\t学号\t班级\t科目一\t科目二\t科目三\t平均分\n");
	while(pHead!=NULL)
	{
		printf("No.%d\t\t",++i);
		printf("%s\t%s\t%s\t",pHead->name,pHead->num,pHead->classes);
		printf("%.1lf\t%.1lf\t%.1lf\t",pHead->score[0],pHead->score[1],pHead->score[2]);
		printf("%.1lf\n",pHead->aver);
		pHead=pHead->next;
	}
}
void increase(struct student *pHead)//增加 
{
	char a[20];
	struct student *pNew;
	int flag=1;
	printf("请输入你想插入学生后(学号)\n");
	scanf("%s",a);
	while(pHead->next&&strcmp(pHead->num,a)!=0)
		pHead=pHead->next;
	if(pHead->next==NULL&&strcmp(pHead->num,a)!=0)
	{
		printf("未找到此人，如果要插入尾部请输入1\n");
		flag=0;
		scanf("%d",&flag); 
	}	
	if(flag==1)
	{
		pNew=(struct student *)malloc(sizeof(struct student)); 
		input_1(pNew);
		pNew->next=pHead->next;
		pHead->next=pNew;
		iCound++;
	}		 
}
void strike_out(struct student *pHead)//删除
{
	char a[20];
	struct student *pHead_1=pHead;
	printf("请输入你想删除学生的学号\n");
	scanf("%s",a);
	while(pHead&&strcmp(pHead->num,a))
	{
		pHead_1=pHead;
		pHead=pHead->next;
	}	
	if(pHead==NULL)
		printf("查无此人！\n");
	else
	{
		pHead_1->next=pHead->next;
		free(pHead);
		iCound--;
		printf("已删除！\n");
	}

}

void chang(struct student *pHead)//修改 
{
	char a[20];
	printf("请输入你想修改学生的学号\n");
	scanf("%s",a);
	while(pHead&&strcmp(pHead->num,a))
		pHead=pHead->next;
	if(pHead==NULL)
		printf("未找到此人\n");	
	else 
		input_1(pHead);	
}
void inquiry(struct student *pHead) //查询 
{
	char a[20];
	printf("请输入你想查询学生的学号\n");
	scanf("%s",a);
	while(pHead&&strcmp(pHead->num,a))
		pHead=pHead->next;
	if(pHead==NULL)
		printf("未找到此人\n");	 
	else 
	{
		printf("姓名\t学号\t班级\t科目一\t科目二\t科目三\t平均分\n");
		printf("%s\t%s\t%s\t",pHead->name,pHead->num,pHead->classes);
		printf("%.1lf\t%.1lf\t%.1lf\t",pHead->score[0],pHead->score[1],pHead->score[2]);
		printf("%.1lf\n",pHead->aver);
	}		
}
void sore(struct student *pHead) //排序 
{
	int i,j,flag;
	struct student *pj_1,*pj,*pj_h,*pt;
	for(i=0;i<iCound-1;i++)
		for(j=0,pj=pHead,flag==0;j<iCound-i;j++) 
		{
			if(flag==0)
			{
				pj_1=pj;
				pj=pj->next;
				pj_h=pj->next;
			}
			if(flag==1)
			{
				pj_1=pj_1->next;
				pj_h=pj->next;
			}	
			flag=0;
			if((pj->aver)<(pj_h->aver))
			{
				pt=pj->next;
				pj->next=pj_h->next;
				pj_h->next=pt;
				
				pt=pj_1->next;
				pj_1->next=pj_h->next;
				pj_h->next=pt;
				flag=1;	
			}	
		}
			
} 
int main(void)
{
	int a;
	struct student *pHead;
	show1(); 
	while(1)
	{
		system("cls");
		show2();
		fflush(stdin);
		scanf("%d",&a);
		switch(a)
		{
			case 1:pHead=input();break;//输入 
			case 2:output(pHead);break;//输出 
			case 3:increase(pHead);break;//增加 
			case 4:strike_out(pHead);break;//删除
			case 5:chang(pHead);break;//修改 
			case 6:inquiry(pHead);break;//查询 
			case 7:sore(pHead);break;//排序 
			case 0:exit(0);break;
			default :printf("输入有误请重新输入\n");break; 
		}
		printf("按任意键进行下一步操作\n");
		getch();
	}
}
#include<stdio.h>

#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#define size 2

struct building{          //房屋信息 
	int state; 	  //状态：出售，出租，已出售或已出租
	long money; 	  //价格
	char owner[30];   //姓名 
	char address[50]; //地址
	int nums;	  //编号
}buildings[size]; 

struct custom{         //客户信息 
	char name[30]; //姓名 
	char ps[50];   //备注 
	long price;    //目标价位 
	int state;     //状态：想买房，想租房，已买房或已租房
	int num;       //编号
}customs[size];

FILE *fpb;   //文件指针
FILE *fpc;
int menu_select();    //界面函数
void inputbuilding(); //输入房屋信息
void inputcustom();   //输入客户信息
void listbuilding();  //按照金额从大到小排列房屋信息
void listcustom();    //按照金额从大到小排列客户信息
void search();

main(){
	for( ; ;){
		switch(menu_select()){
		case 0:inputbuilding();
			break;
		case 1:inputcustom();
			break;
		case 2:listbuilding();
			break;
		case 3:listcustom();
			break;
		case 4:search();
			break;
		case 5:exit(0);
		}
	}
}

int menu_select(){
	int i; char s[3];
	printf("\n 欢迎使用，请按任意键继续......\n\n ");
	getch();
	printf("           *房屋租赁管理系统*                 \n\n");
	printf("  0.添加房屋信息 \n");
	printf("  1.添加客户信息 \n");
	printf("  2.按金额排序列出所有房屋信息 \n");
	printf("  3.按金额排序列出所有客户信息 \n");
	printf("  4.查询合同信息 \n");
	printf("  5.退出 \n");
	do{
		printf("\n 请选择(0~5):");
		scanf("%s",&s);
		i=atoi(s);
	}
	while(i<0||i>5);
	return(i);
}

void swapc(struct custom *a,struct custom *b){
	int ii;long ll;char aa[30];char bb[50];
	ii=(*a).state;(*a).state=(*b).state;(*b).state=ii;
	ii=(*a).num;(*a).num=(*b).num;(*b).num=ii;
	ll=(*a).price;(*a).price=(*b).price;(*b).price=ll;
	strcpy(aa,(*a).name);strcpy((*a).name,(*b).name);strcpy((*b).name,aa);
	strcpy(bb,(*a).ps);strcpy((*a).ps,(*b).ps);strcpy((*b).ps,bb);
}

void searchb(){
	int i,b;
	fpb=fopen("build.c","r"); //从文件中取出文件信息放到buildings数组里
	for(i=0;i<size;i++)
	fread(&buildings[i],sizeof(struct building),1,fpb);
	fclose(fpb);
	printf(" 请输入合同号：");
	scanf("%d",&b);
	for(i=0;i<size;i++){
		if(buildings[i].nums==b) {
			printf(" 合同编号：%d",buildings[i].nums);
			printf(" 金额:%ld ",buildings[i].money);
			printf(" 所有人: ");puts(buildings[i].owner);
			printf(" 地址店面等其他信息: ");puts(buildings[i].address);
			if(buildings[i].state==1) printf(" 状态: 出售\n");
			if(buildings[i].state==2) printf(" 状态: 出租\n");
			if(buildings[i].state==3) printf(" 状态: 已售\n");
			if(buildings[i].state==4) printf(" 状态: 已出租\n");
		}
	}
}

void searchc(){
	int i,b;
	fpc=fopen("custom.c","r");
	for(i=0;i<size;i++)
	fread(&customs[i],sizeof(struct custom),1,fpb);
	fclose(fpc);
	printf(" 请输入合同号：");
	scanf("%d",&b);
	for(i=0;i<size;i++){
		if(buildings[i].nums==b){
			printf(" 合同编号：%d",customs[i].num);
			printf(" 金额:%ld ",customs[i].price);
			printf(" 姓名: \n");puts(customs[i].name);
			printf(" 客户其他信息: ");puts(customs[i].ps);
			if(customs[i].state==1) printf(" 状态: 希望购房\n");
			if(customs[i].state==2) printf(" 状态: 希望租房\n");
			if(buildings[i].state==3) printf(" 状态: 已购房\n");
			if(buildings[i].state==4) printf(" 状态: 已租房\n");
		}
	}
}

void search(){
	int a;
	printf("\n1 房屋合同查询\n2客户合同查询\n请选择：");
	scanf("%d",&a);
	if(a==1) searchb();
	if(a==2) searchc();
}

void inputbuilding(){
	int i;int a;long d;
	printf("\n 请输入房屋信息\n");
	for(i=0;i<size;i++){
		printf("\n 请输入第 %d 个房屋信息\n",i+1);
		printf("\n 1 出售\n 2 出租\n 3 已售\n 4 已出租\n\n 请输入房屋状态:");
		scanf("%d",&a);
		buildings[i].state=a;
		
		printf("\n 请输入房屋的所有人姓名：");
		scanf("%s",&buildings[i].owner);
		printf("\n 请输入房屋的地址：");
		scanf("%s",&buildings[i].address);
		printf("\n 请输入房屋的合同编号：");
		scanf("%d",&buildings[i].nums);
		printf("\n 请输入价格：");
		
		scanf("%ld",&d);
		buildings[i].money=d;
	}
	fpb=fopen("build.c","w"); //输入到文件
	for(i=0;i<size;i++)
	fwrite(&buildings[i],sizeof(struct building),1,fpb);
	fclose(fpb); //输入到文件
}

void listbuilding(){
	int i,j;long mon[size];
	int ii;long ll;char aa[30];char bb[50];
	struct building *p1;struct building *p2;
	fpb=fopen("build.c","r"); //从文件中取出文件信息放到buildings 数组里 
	for(i=0;i<size;i++)
	fread(&buildings[i],sizeof(struct building),1,fpb);
	fclose(fpb); //从文件中取出文件信息放到buildings 数组里
	
	for(i=0;i<size;i++)
	for(j=0;j<size-i;j++)
	if(buildings[j].money<buildings[j+1].money){
		ii=buildings[j].state;buildings[j].state=buildings[j+1].state;buildings[j+1].state=ii;
		ii=buildings[j].nums;buildings[j].nums=buildings[j+1].nums;buildings[j+1].nums=ii;
		ll=buildings[j].money;buildings[j].money=buildings[j+1].money;buildings[j+1].money=ll;
		strcpy(aa,buildings[j].owner);strcpy(buildings[j].owner,buildings[j+1].owner);strcpy(buildings[j+1].owner,aa);
		strcpy(bb,buildings[j].address);strcpy(buildings[j].address,buildings[j+1].address);strcpy(buildings[j+1].address,bb);
	}
	
	for(j=0;j<size;j++){
		printf(" 合同编号：%d",buildings[j].nums);
		printf(" 金额:%ld ",buildings[j].money);
		printf(" 所有人: ");puts(buildings[j].owner);
		printf(" 地址店面等其他信息: ");puts(buildings[j].address);
		if(buildings[j].state==1) printf(" 状态: 卖房\n\n");
		if(buildings[j].state==2) printf(" 状态: 出租房\n\n");
		if(buildings[j].state==3) printf(" 状态: 已卖\n\n");
		if(buildings[j].state==4) printf(" 状态: 已出租\n\n");
	}
}

void inputcustom(){
	int i;int a;long d;
	printf("\n 请输入客户信息\n");
	for(i=0;i<size;i++){
		printf("\n 请输入第 %d 个客户\n",i+1);
		printf("\n 1 希望购房\n 2 希望租房\n 3已经完成购房\n 4已经完成租房\n\n 请输入客户状态:");
		scanf("%d",&a);
		customs[i].state=a;
		printf("\n 请输入客户姓名:");
		scanf("%s",&customs[i].name);
		printf("\n 请输入客户业务合同编号:");
		scanf("%d",&customs[i].num);
		printf("\n 请输入备注:");
		scanf("%s",&customs[i].ps);
		printf("\n 请输入价格:");
		scanf("%ld",&d);
		customs[i].price=d;
	}
	fpc=fopen("custom.c","w");
	for(i=0;i<size;i++)
	fwrite(&customs[i],sizeof(struct custom),1,fpc);
	fclose(fpc);
}

void listcustom(){
	int i,j;long mon[size];long mid; 
	int ii;long ll;char aa[30];char bb[50];
	struct custom p1;struct custom p2;
	fpc=fopen("custom.c","r");
	for(i=0;i<size;i++)
	fread(&customs[i],sizeof(struct custom),1,fpb);
	fclose(fpc);
	for(i=0;i<size;i++)
	for(j=0;j<size-i;j++)
	if(customs[j].price<customs[j+1].price){
		ii=customs[j].state;customs[j].state=customs[j+1].state;customs[j+1].state=ii;
		ii=customs[j].num;customs[j].num=customs[j+1].num;customs[j+1].num=ii;
		ll=customs[j].price;customs[j].price=customs[j+1].price;customs[j+1].price=ll;
		strcpy(aa,customs[j].name);strcpy(customs[j].name,customs[j+1].name); strcpy(customs[j+1].name,aa);
		strcpy(bb,customs[j].ps);strcpy(customs[j].ps,customs[j+1].ps);strcpy(customs[j+1].ps,bb);
	}
	for(j=0;j<size;j++){
		printf(" 合同编号：%d",customs[j].num);
		printf(" 金额:%ld ",customs[j].price);
		printf(" 姓名: \n");puts(customs[j].name);
		printf(" 备注: ");puts(customs[j].ps);
		if(customs[j].state==1) printf(" 状态: 希望购房 \n");
		if(customs[j].state==2) printf(" 状态: 希望租房 \n");
		if(buildings[j].state==3) printf(" 状态: 已购房 \n");
		if(buildings[j].state==4) printf(" 状态: 已租房 \n");
	}
}

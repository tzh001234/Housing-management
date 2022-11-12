#define size 3//密码1234
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>


struct building
{int state; /*楼房的状态：出售，


出租，已出售或已出租 */
long money; /*出售的金额或者出租的金额 */
char owner[30]; /* 拥有者名字 */
char address[50]; /*楼房的地址及其他信息 */
int nums;/*编号*/
}buildings[size];


struct custom
{
char name[30]; /*客户的名字*/
char ps[50]; /*其他的资料 */
long price; /*需要租楼房的租金，或者是需要买楼房的价格 */
int state; /*客户的状态：想买房，想租房，已经买了房或租了房 */
int num; /*编号*/
}customs[size];


FILE *fpb; /*文件指针 */
FILE *fpc;
/*函数声明 */
int menu_select(); /*界面函数 */
void inputbuilding(); /*输入楼房信息 */
void inputcustom(); /*输入客户信息*/
void listbuilding(); /*按照金额从大到小排列房屋信息 */
void listcustom(); /*按照金额从大到小排列客户信息 */
void caculate(); /*计算收入，按照交易金额的十分之一收取*/
void caculatec(); /*计算收入 ，按照交易金额的十分之一收取*/
void code(); /*加密函数 */
void search();


main(){
code();
for( ; ;)
{switch(menu_select())
{
case 0:inputbuilding();
break;

case 1:inputcustom();
break;

case 2:listbuilding();
break;

case 3:listcustom();
break;

case 4:caculate();
break;

case 5:caculatec();
break;
case 6:search();
break;
case 7:exit(0);
}
}
}

int menu_select(){
int i; char s[3];
printf("\n\t请按任意键继续......\n");
printf("\n\n******************************欢迎您的使用*******************************\n\n\n");
getch();
printf(" ********************************菜单**********************************\n");
printf(" * 欢迎使用亮宇租售有限公司房地产管理软件 *\n");
printf(" * *\n");
printf(" * 0.请输入需要出售或转让或已经出售转让的房屋信息 *\n");
printf(" * 1.请输入需要租赁或购买或应经租赁和购买房屋的客户信息 *\n");
printf(" * 2.列出所有房屋业务信息（按金额排序） *\n");
printf(" * 3.列出所有客户业务信息（按金额排序） *\n");
printf(" * 4.统计从房屋业务中获得的收入 *\n");
printf(" * 5.统计从客户业务中获得的收入 *\n");
printf(" * 6.具体查询合同信息 *\n");
printf(" *7.退出 *\n");
printf("********************************欢迎************************************\n\n");
do{
printf("\n 请选择(0~7):");
scanf("%s",&s);
i=atoi(s);
}
while(i<0||i>7);
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

void code(){
long a;
long b;
a=1234;
for(;;)
{
printf("请您输入密码：\n");
scanf("%ld",&b);
if(abs(a-b)<=1) break;
else {printf("密码错误，请重新输入\n");getch();}
}
}

void searchb(){
int i,b;
fpb=fopen("build.c","r"); /*从文件中取出文件信息放到buildings 数组里 */
for(i=0;i<size;i++)
fread(&buildings[i],sizeof(struct building),1,fpb);
fclose(fpb);
printf("请输入合同号：");
scanf("%d",&b);
for(i=0;i<size;i++)
{if(buildings[i].nums==b) {
printf("合同编号：%d",buildings[i].nums);
printf("金额:%ld ",buildings[i].money);
printf("所有人: ");puts(buildings[i].owner);
printf("地址店面等其他信息: ");puts(buildings[i].address);
if(buildings[i].state==1) printf("状态: 卖房\n");
if(buildings[i].state==2) printf("状态: 出租房\n");
if(buildings[i].state==3) printf("状态: 已卖\n");
if(buildings[i].state==4) printf("状态: 已出租\n");
}
}
}

void searchc(){
int i,b;
fpc=fopen("custom.c","r");
for(i=0;i<size;i++)
fread(&customs[i],sizeof(struct custom),1,fpb);
fclose(fpc);
printf("请输入合同号：");
scanf("%d",&b);
for(i=0;i<size;i++)
{if(buildings[i].nums==b) {
printf("合同编号：%d",customs[i].num);
printf("金额:%ld ",customs[i].price);
printf("姓名: \n");puts(customs[i].name);
printf("客户其他信息: ");puts(customs[i].ps);
if(customs[i].state==1) printf("状态: 希望购房\n");
if(customs[i].state==2) printf("状态: 希望租房\n");
if(buildings[i].state==3) printf("状态: 已购房\n");
if(buildings[i].state==4) printf("状态: 已租房\n");
}
}
}

void search(){
int a;
printf("\n请选择：\n1 房屋合同查询\n2客户合同查询");
scanf("%d",&a);
if(a==1) searchb();
if(a==2) searchc();
}

void inputbuilding(){
int i;int a;long d;
printf("请输入房屋信息\n");
for(i=0;i<size;i++)
{
printf("请输入第 %d 个信息\n",i+1);
printf("请输入房屋状态:\n1 出售\n2 出租\n3 已出售\n4 已出租\n");
scanf("%d",&a);
buildings[i].state=a;

printf("\n请输入房屋的所有人姓名\n");
scanf("%s",&buildings[i].owner);
printf("\n请输入房屋的地址等其他信息\n");
scanf("%s",&buildings[i].address);
printf("\n请输入房屋的合同编号\n");
scanf("%d",&buildings[i].nums);
printf("请输入对应的金额（出售价或出租价）\n");



scanf("%ld",&d);
buildings[i].money=d;
}
fpb=fopen("build.c","w"); /*输入到文件中 */
for(i=0;i<size;i++)
fwrite(&buildings[i],sizeof(struct building),1,fpb);
fclose(fpb); /*输入到文件中 */
}

void listbuilding(){
int i,j;long mon[size];
int ii;long ll;char aa[30];char bb[50];
struct building *p1;struct building *p2;
fpb=fopen("build.c","r"); /*从文件中取出文件信息放到buildings 数组里 */
for(i=0;i<size;i++)
fread(&buildings[i],sizeof(struct building),1,fpb);
fclose(fpb); /*从文件中取出文件信息放到buildings 数组里 */

for(i=0;i<size;i++)
for(j=0;j<size-i;j++)
if(buildings[j].money<buildings[j+1].money) {
ii=buildings[j].state;buildings[j].state=buildings[j+1].state;buildings[j+1].state=ii;
ii=buildings[j].nums;buildings[j].nums=buildings[j+1].nums;buildings[j+1].nums=ii;


ll=buildings[j].money;buildings[j].money=buildings[j+1].money;buildings[j+1].money=ll;
strcpy(aa,buildings[j].owner);strcpy(buildings[j].owner,buildings[j+1].owner);strcpy(buildings[j+1].owner,aa);
strcpy(bb,buildings[j].address);strcpy(buildings[j].address,buildings[j+1].address);strcpy(buildings[j+1].address,bb);
}

for(j=0;j<size;j++)
{
printf("合同编号：%d",buildings[j].nums);
printf("金额:%ld ",buildings[j].money);
printf("所有人: ");puts(buildings[j].owner);
printf("地址店面等其他信息: ");puts(buildings[j].address);
if(buildings[j].state==1) printf("状态: 卖房\n\n");
if(buildings[j].state==2) printf("状态: 出租房\n\n");
if(buildings[j].state==3) printf("状态: 已卖\n\n");
if(buildings[j].state==4) printf("状态: 已出租\n\n");}

}

void inputcustom(){
int i;int a;long d;
printf("请输入客户信息\n");
for(i=0;i<size;i++)
{
printf("请输入第 %d 个客户\n",i+1);
printf("请输入客户状态:\n1 希望购房\n2 希望租房\n3已经在本公司完成购房\n4已经在本公司完成租房\n");
scanf("%d",&a);
customs[i].state=a;

printf("\n请输入客户姓名\n");
scanf("%s",&customs[i].name);
printf("\n请输入客户业务合同编号\n");
scanf("%d",&customs[i].num);

printf("\n请输入客户的其他要求或其他信息\n");
scanf("%s",&customs[i].ps);

printf("请输入对应的金额（购房或租房价格）\n");
scanf("%ld",&d);
customs[i].price=d;
}
fpc=fopen("custom.c","w");
for(


i=0;i<size;i++)
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
if(customs[j].price<customs[j+1].price)
{
ii=customs[j].state;customs[j].state=customs[j+1].state;customs[j+1].state=ii;
ii=customs[j].num;customs[j].num=customs[j+1].num;customs[j+1].num=ii;


ll=customs[j].price;customs[j].price=customs[j+1].price;customs[j+1].price=ll;
strcpy(aa,customs[j].name);strcpy(customs[j].name,customs[j+1].name); strcpy(customs[j+1].name,aa);
strcpy(bb,customs[j].ps);strcpy(customs[j].ps,customs[j+1].ps);strcpy(customs[j+1].ps,bb);}

for(j=0;j<size;j++)
{
printf("合同编号：%d",customs[j].num);
printf("金额:%ld ",customs[j].price);
printf("姓名: \n");puts(customs[j].name);
printf("客户其他信息: ");puts(customs[j].ps);

if(customs[j].state==1) printf("状态: 希望购房\n");
if(customs[j].state==2) printf("状态: 希望租房\n");
if(buildings[j].state==3) printf("状态: 已购房\n");
if(buildings[j].state==4) printf("状态: 已租房\n");
}

}

void caculatesold(){
int i;double sum;
fpb=fopen("build.c","r");
for(i=0;i<size;i++)
fread(&buildings[i],sizeof(struct building),1,fpb);
fclose(fpb);
sum=0;
for(i=0;i<size;i++)
if(buildings[i].state==3) sum+=buildings[i].money*0.01;
printf("卖房中介收益为%f",sum);

}

void caculaterent(){
int i;double sum;
fpb=fopen("build.c","r");
for(i=0;i<size;i++)
fread(&buildings[i],sizeof(struct building),1,fpb);
fclose(fpb);
sum=0;
for(i=0;i<size;i++)
if(buildings[i].state==4) sum+=buildings[i].money*0.1;
printf("出租房中介收益为%f",sum);
}

void caculatecsold(){
int i;double sum;
fpc=fopen("custom.c","r");
for(i=0;i<size;i++)
fread(&customs[i],sizeof(struct custom),1,fpc);
fclose(fpc);
sum=0;
for(i=0;i<size;i++)
if(customs[i].state==3) sum+=customs[i].price*0.1;
printf("买房中介收益为%f",sum);
}

void caculatecrent(){
int i;double sum;
fpc=fopen("custom.c","r");
for(i=0;i<size;i++)
fread(&customs[i],sizeof(struct custom),1,fpc);
fclose(fpc);
sum=0;
for(i=0;i<size;i++)
if(customs[i].state==4)
sum+=customs[i].price*0.1;
printf("求租房中介收益为%f",sum);
};

void caculate(){
int a;
printf("\n请选择：\n1 从卖房中获得的中介收益\n2 从出租房中获得的中介收益\n");
scanf("%d",&a);
if(a==1) caculatesold();
if(a==2) caculaterent();
}

void caculatec(){
int a;
printf("\n请选择：\n 1 从买房者获得的中介收益\n2 从租房者中获得的中介收益\n");
scanf("%d",&a);
if(a==1) caculatecsold();
if(a==2) caculatecrent();
} 


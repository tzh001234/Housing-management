#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#define size 2

struct building{      //������Ϣ 
	int state; 		  //״̬�����ۣ����⣬�ѳ��ۻ��ѳ���
	long money; 	  //�۸�
	char owner[30];   //���� 
	char address[50]; //��ַ
	int nums;	      //���
}buildings[size]; 

struct custom{     //�ͻ���Ϣ 
	char name[30]; //���� 
	char ps[50];   //��ע 
	long price;    //Ŀ���λ 
	int state;     //״̬�����򷿣����ⷿ�����򷿻����ⷿ
	int num;       //���
}customs[size];

FILE *fpb;   //�ļ�ָ��
FILE *fpc;
int menu_select();    //���溯��
void inputbuilding(); //���뷿����Ϣ
void inputcustom();   //����ͻ���Ϣ
void listbuilding();  //���ս��Ӵ�С���з�����Ϣ
void listcustom();    //���ս��Ӵ�С���пͻ���Ϣ
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
	printf("\n ��ӭʹ�ã��밴���������......\n\n ");
	getch();
	printf("           * �������޹���ϵͳ*                 \n\n");
	printf("  0.��ӷ�����Ϣ \n");
	printf("  1.��ӿͻ���Ϣ \n");
	printf("  2.����������г����з�����Ϣ \n");
	printf("  3.����������г����пͻ���Ϣ \n");
	printf("  4.�����ѯ��ͬ��Ϣ \n");
	printf("  5.�˳� \n");
	do{
		printf("\n ��ѡ��(0~5):");
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
	fpb=fopen("build.c","r"); /*���ļ���ȡ���ļ���Ϣ�ŵ�buildings ������ */
	for(i=0;i<size;i++)
	fread(&buildings[i],sizeof(struct building),1,fpb);
	fclose(fpb);
	printf(" �������ͬ�ţ�");
	scanf("%d",&b);
	for(i=0;i<size;i++){
		if(buildings[i].nums==b) {
			printf(" ��ͬ��ţ�%d",buildings[i].nums);
			printf(" ���:%ld ",buildings[i].money);
			printf(" ������: ");puts(buildings[i].owner);
			printf(" ��ַ�����������Ϣ: ");puts(buildings[i].address);
			if(buildings[i].state==1) printf(" ״̬: ����\n");
			if(buildings[i].state==2) printf(" ״̬: ���ⷿ\n");
			if(buildings[i].state==3) printf(" ״̬: ����\n");
			if(buildings[i].state==4) printf(" ״̬: �ѳ���\n");
		}
	}
}

void searchc(){
	int i,b;
	fpc=fopen("custom.c","r");
	for(i=0;i<size;i++)
	fread(&customs[i],sizeof(struct custom),1,fpb);
	fclose(fpc);
	printf(" �������ͬ�ţ�");
	scanf("%d",&b);
	for(i=0;i<size;i++){
		if(buildings[i].nums==b){
			printf(" ��ͬ��ţ�%d",customs[i].num);
			printf(" ���:%ld ",customs[i].price);
			printf(" ����: \n");puts(customs[i].name);
			printf(" �ͻ�������Ϣ: ");puts(customs[i].ps);
			if(customs[i].state==1) printf(" ״̬: ϣ������\n");
			if(customs[i].state==2) printf(" ״̬: ϣ���ⷿ\n");
			if(buildings[i].state==3) printf(" ״̬: �ѹ���\n");
			if(buildings[i].state==4) printf(" ״̬: ���ⷿ\n");
		}
	}
}

void search(){
	int a;
	printf("\n1 ���ݺ�ͬ��ѯ\n2�ͻ���ͬ��ѯ\n��ѡ��");
	scanf("%d",&a);
	if(a==1) searchb();
	if(a==2) searchc();
}

void inputbuilding(){
	int i;int a;long d;
	printf("\n �����뷿����Ϣ\n");
	for(i=0;i<size;i++){
		printf("\n ������� %d ��������Ϣ\n",i+1);
		printf("\n 1 ����\n 2 ����\n 3 �ѳ���\n 4 �ѳ���\n\n �����뷿��״̬:");
		scanf("%d",&a);
		buildings[i].state=a;
		
		printf("\n �����뷿�ݵ�������������");
		scanf("%s",&buildings[i].owner);
		printf("\n �����뷿�ݵĵ�ַ��");
		scanf("%s",&buildings[i].address);
		printf("\n �����뷿�ݵĺ�ͬ��ţ�");
		scanf("%d",&buildings[i].nums);
		printf("\n �������Ӧ�Ľ����ۼۻ����ۣ���");
		
		scanf("%ld",&d);
		buildings[i].money=d;
	}
	fpb=fopen("build.c","w"); //���뵽�ļ�
	for(i=0;i<size;i++)
	fwrite(&buildings[i],sizeof(struct building),1,fpb);
	fclose(fpb); //���뵽�ļ�
}

void listbuilding(){
	int i,j;long mon[size];
	int ii;long ll;char aa[30];char bb[50];
	struct building *p1;struct building *p2;
	fpb=fopen("build.c","r"); /*���ļ���ȡ���ļ���Ϣ�ŵ�buildings ������ */
	for(i=0;i<size;i++)
	fread(&buildings[i],sizeof(struct building),1,fpb);
	fclose(fpb); /*���ļ���ȡ���ļ���Ϣ�ŵ�buildings ������ */
	
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
		printf(" ��ͬ��ţ�%d",buildings[j].nums);
		printf(" ���:%ld ",buildings[j].money);
		printf(" ������: ");puts(buildings[j].owner);
		printf(" ��ַ�����������Ϣ: ");puts(buildings[j].address);
		if(buildings[j].state==1) printf(" ״̬: ����\n\n");
		if(buildings[j].state==2) printf(" ״̬: ���ⷿ\n\n");
		if(buildings[j].state==3) printf(" ״̬: ����\n\n");
		if(buildings[j].state==4) printf(" ״̬: �ѳ���\n\n");
	}
}

void inputcustom(){
	int i;int a;long d;
	printf("\n ������ͻ���Ϣ\n");
	for(i=0;i<size;i++){
		printf("\n ������� %d ���ͻ�\n",i+1);
		printf("\n 1 ϣ������\n 2 ϣ���ⷿ\n 3�Ѿ���ɹ���\n 4�Ѿ�����ⷿ\n\n ������ͻ�״̬:");
		scanf("%d",&a);
		customs[i].state=a;
		printf("\n ������ͻ�����:");
		scanf("%s",&customs[i].name);
		printf("\n ������ͻ�ҵ���ͬ���:");
		scanf("%d",&customs[i].num);
		printf("\n �����뱸ע:");
		scanf("%s",&customs[i].ps);
		printf("\n �������Ӧ�Ľ��������ⷿ�۸�:");
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
		printf(" ��ͬ��ţ�%d",customs[j].num);
		printf(" ���:%ld ",customs[j].price);
		printf(" ����: \n");puts(customs[j].name);
		printf(" ��ע: ");puts(customs[j].ps);
		if(customs[j].state==1) printf(" ״̬: ϣ������\n");
		if(customs[j].state==2) printf(" ״̬: ϣ���ⷿ\n");
		if(buildings[j].state==3) printf(" ״̬: �ѹ���\n");
		if(buildings[j].state==4) printf(" ״̬: ���ⷿ\n");
	}
}

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SIZE 100
int gap = 0;
//�������� 
typedef struct {
    int key;   
}SLNode;
typedef struct {
    SLNode r[SIZE+1];
    int length;
    float comp;//�Ƚϴ��� 
    float move;//�ƶ����� 
}SqList;

void CreateSqList(SqList * L){
	//����һ��L 
	srand( (unsigned int)time(NULL)+gap++);//���� 
    for(int i=1; i<=SIZE; ++i)
    	L->r[i].key=rand()%100+1;
	    L->length=SIZE;	L->comp=0;L->move=0;
}
void CopyList(SqList * L,SqList * cl){
	//����L��cl 
	for(int i=1; i<=L->length; ++i)
    	cl->r[i].key=L->r[i].key;
	    cl->length=L->length;
		cl->comp=L->comp;cl->move=L->move;	
}
void ShowList(SqList * L){
	//��ʾL������ 
	for (int i=1; i<=L->length; i++) 
    printf("%d ",L->r[i].key);
	if(L->comp||L->move)  printf("\n�Ƚϴ���Ϊ%.0f���ƶ�����Ϊ%.0f",L->comp,L->move); 
    printf("\n");
}

/******************************** 
��������
�������ܣ�ð���������� 
�����������������L,�Ƿ���ʾ�������step��1��ʾ��0����ʾ��ȱʡֵΪ0�� 
��������ֵ����  
**********************************/
void BubbleSort(SqList * L,int step=0){
	int flag;//�ж��Ƿ�����ı��� 
	for (int i=1; i<=L->length-1; i++){//n-1��ð��
	   flag=1; 
	   for(int j=1;j<=L->length-i;j++){	   	
   		if(L->r[j].key>L->r[j+1].key){
		   //����˳�� 
		L->r[0].key=L->r[j].key;
		L->r[j].key=L->r[j+1].key;
		L->r[j+1].key=L->r[0].key;
		L->move+=3; flag=0; 
		   }
		   L->comp++;
   	}
   	if(flag)break;//����������ѭ�� 
   	if(step){printf("��%d��ð��������Ϊ��",i);ShowList(L);}//�Ƿ���ʾ���� 
	}
	 
}
/******************************** 
��������InsertSort
�������ܣ�ֱ�Ӳ�������(����) 
�����������������L,�Ƿ���ʾ�������step��1��ʾ��0����ʾ
��������ֵ����  
**********************************/
void InsertSort(SqList * L,int step=0){
	for (int i=2; i<=L->length; i++){//n-1�˲���
		if (L->r[i].key<L->r[i-1].key) {//��r[i]��ǰ��������������ֵС������λ���� 
            int j;
            L->r[0]=L->r[i];//��r[0]��¼Ҫ�����ֵ 
            L->move++;
            for (j=i-1; j>0 && (L->r[0].key<L->r[j].key); j--){
            	//��λ���� 
            	L->r[j+1]=L->r[j];
            	L->move++;L->comp++;//
            }
            if(j>0) L->comp++;   
            //���뵽�Ƴ����Ŀռ� 
            L->r[j+1]=L->r[0];L->move++;
            L->comp++;
		}     
        else  L->comp++;
        if(step){printf("��%d��ֱ�Ӳ���������Ϊ��",i-1);ShowList(L);}//�Ƿ���ʾ���� 
	}
}



int SelectMinKey(SqList *L,int i){
	//��L�ĵ�i��Ԫ�ؿ�ʼ���ҵ���С��Ԫ���±�min 
	int min=i;
	for(int j=i+1;j<=L->length;j++){
		if(L->r[j].key<L->r[min].key) min=j;
		L->comp++;
	}	
	return min;
}
/******************************** 
��������SelectSort
�������ܣ���ѡ������ ������
�����������������L,�Ƿ���ʾ�������step��1��ʾ��0����ʾ
��������ֵ����  
**********************************/
void SelectSort(SqList * L,int step=0){
	//��ѡ�������㷨����L��n-1��ѡ����� 
	for (int i=1; i<L->length; i++) {
        int j=SelectMinKey(L,i);
        if (i!=j) { //λ��i��ֵ������С������λ�� 
            L->r[0]=L->r[i];
            L->r[i]=L->r[j];
            L->r[j]=L->r[0];
            L->move+=3;
        }
        if(step){printf("��%d�˼�ѡ��������Ϊ��",i);ShowList(L);}//�Ƿ���ʾ���� 
    }
} 
void 	ShellInsert(SqList * L,int dk,int step){
    //dk Ϊλ����������L���dk��һ�˲��������㷨
    for (int i=dk+1; i<=L->length; i++){     
        if (L->r[i].key<L->r[i-dk].key) {//��r[i]��ǰ��������������ֵС������λ���� 
            int j;
            L->r[0]=L->r[i];//��r[0]��¼Ҫ�����ֵ 
            L->move++;
            //��λ���� 
            for (j=i-dk; j>0 && (L->r[0].key<L->r[j].key); j-=dk){
            	L->r[j+dk]=L->r[j];
            	L->move++;L->comp++;//
            }
            if(j>0) L->comp++;   
            //���뵽�Ƴ����Ŀռ� 
            L->r[j+dk]=L->r[0];L->move++;
            L->comp++;
        }
        else  L->comp++;
        if(step){printf("ϣ���������Ϊ��");ShowList(L);}//�Ƿ���ʾ���� 
    }
}
/******************************** 
��������ShellSort
�������ܣ�ϣ���������� 
�����������������L �ض���ز���,�Ƿ���ʾ�������step��1��ʾ��0����ʾ
��������ֵ����  
**********************************/
void ShellSort(SqList * L,int dlta[],int t,int step=0){
	//��λ����������dlta[1...t-1] ��L��ϣ������ 
    for (int k=0; k<t; k++){
    	ShellInsert(L, dlta[k],step);
    	//if(step){printf("��%d������������ϣ��������Ϊ��",k+1);ShowList(L);}//�Ƿ���ʾ���� 
    } 
           
}
void HeapAdjust(SqList * L,int index,int length,int step=0){
	//�󶥶ѵ��� ����L��ǰlength��Ԫ���еĵ�index���ڵ������ʹ����ϴ󶥶�˳��
	int lchild = 2 * index ;
	int rchild = 2 * index + 1;
	int max = index;
	if (lchild<=length&&L->r[lchild].key>L->r[max].key)	
		max = lchild;L->comp++;	
	if (rchild<=length&&L->r[rchild].key>L->r[max].key)	
		max = rchild;L->comp++;	
	if (max != index)//�����ں��ӽڵ㣬����˳�� 
	{
		//L->r[0].key����ʱ����temp������ 
		L->r[0].key=L->r[max].key;
		L->r[max].key=L->r[index].key;
		L->r[index].key=L->r[0].key;
		L->move+=3;//�ؼ��ֽ�����Ϊ3���ƶ�
		HeapAdjust(L, max, length,step);
		 if(step){printf("���������Ϊ��");ShowList(L);}//�Ƿ���ʾ���� 
	}
}  
/******************************** 
��������HeapSort
�������ܣ����������� 
�����������������L,�Ƿ���ʾ�������step��1��ʾ��0����ʾ
��������ֵ����  
**********************************/
void HeapSort(SqList * L,int step=0){
	//������ 
	//��ÿ����Ҷ�ӽ�㵹����д󶥶ѵ�������ʼ����
	int length=L->length; 
	for (int i = length / 2 ; i > 0; i--)
		HeapAdjust(L, i, length,step);
	//���Ѷ�ֵ�ŵ�����β������ʣ��Ԫ�ؽ��д�Ѷ�����
	for (int i = length ; i >1; i--)
	{//L->r[0].key����ʱ����temp������ 
		L->r[0].key=L->r[1].key;
		L->r[1].key=L->r[i].key;
		L->r[i].key=L->r[0].key;
		L->move+=3; 
		HeapAdjust(L, 1, i-1,step);//�Ը��ڵ���һ�δ�Ѷ��������õ����ֵ 
	}
	 if(step){printf("��������Ϊ��");ShowList(L);}//�Ƿ���ʾ����  
} 
void Merge(SqList * L,int start,int mid,int end,int step=0){
	//�������ӱ�ϳɵ������ӱ� 
	int i,j,k;k=start;SqList *List=new SqList();
	for(i=start,j=mid+1;i<=mid&&j<=end;k++){//ǰ��������һ�ȽϺ�ӵ�list�� 
		if(L->r[i].key<L->r[j].key) 
	     List->r[k].key=L->r[i++].key;
     	else List->r[k].key=L->r[j++].key;
		 L->comp++;L->move++;	
	}
	while(i<=mid)List->r[k++].key=L->r[i++].key;L->move++;//��ʣ���ֵ�ӵ�list���� 
	while(j<=end)List->r[k++].key=L->r[j++].key;L->move++;
	for (int t  = start; t <=k-1; t++){//���źõĽ������ԭʼ��L 
		L->r[t].key=List->r[t].key;L->move++;
	}
	 if(step){printf("�鲢�������Ϊ��");ShowList(L);}//�Ƿ���ʾ����    
}
/******************************** 
��������MergeSort 
�������ܣ��鲢�������� 
�����������������L��������Ԫ���������п�ʼ��ĩβ��λ�� ,�Ƿ���ʾ�������step
��������ֵ����  
**********************************/
void  MergeSort(SqList * L,int start,int end,int step=0){
	if(start<end){
		int mid=(start+end)/2;
		MergeSort(L,start,mid,step);//�������
		MergeSort(L,mid+1,end,step);//�ұ�����
		Merge(L,start,mid,end,step);//�ϲ�����
	}
}
void QSort(SqList * L,int low ,int high,int step=0){
	if(low>=high)return;
	int begin=low,end=high;
	L->r[0].key=L->r[low].key;L->move++;//��L->r[0]��¼����L->r[low]��ֵ 
	while(low<high){
		while(low<high&&L->r[high].key>=L->r[0].key){//high����̽ѰС�������ֵ 
			high--;L->comp++;
		}
		if(L->r[high].key<L->r[0].key){L->r[low].key=L->r[high].key;L->move++;L->comp++;} 		
		while(low<high&&L->r[low].key<=L->r[0].key){//low����̽Ѱ�����������ֵ 
			low++;L->comp++;
		}
		if(L->r[low].key>L->r[0].key){L->r[high].key=L->r[low].key;L->move++;L->comp++;} 		
	}
	L->r[low].key=L->r[0].key;L->move++;//�����ֵ��λ 
	QSort(L,begin,low-1,step);//low��Ϊ�µ����Ὣ�ӱ��Ϊ�����ֵݹ����� 
	QSort(L,low+1,end,step); 
	 if(step){printf("�����������Ϊ��");ShowList(L);}//�Ƿ���ʾ���� 
} 
/******************************** 
��������QuickSort 
�������ܣ�������������
�����������������L,�Ƿ���ʾ�������step��1��ʾ��0����ʾ
��������ֵ����  
**********************************/
void QuickSort(SqList * L,int step=0){
	QSort(L,1,L->length,step);
}  
/******************************** 
��������Menu_main 
�������ܣ���ʾ���˵� 
��������������� 
��������ֵ����  
**********************************/
void Menu_main(){
	system("cls"); //�����Ļ����ʾ����Ϣ
	printf("        ��------------------------------------------------------------------------ ��\n");
    printf("        ��                            �����˵�                                     ��\n"); 
	printf("        ��------------------------------------------------------------------------ ��\n");
	printf("        ��            1.�������һ��α���������ʾ�����㷨������                 ��\n");
	printf("        ��            2.ѡ��һ���㷨�����ӻ��㷨����                               ��\n");	
	printf("        ��            3.��������������ݱȽϷ�������ʾƽ��������ܺ���������   ��\n");
	printf("        ��-------------------------------------------------------------------------��\n");
	printf("        ��            4.���˵�                                                     ��\n");
	printf("        ��            0.�˳�����                                                   ��\n");			
	printf("        ��------------------------------------------------------------------------ ��\n\n");
    printf("          �밴����Ӧ���ּ����س���ѡ�����\n");
}
/******************************** 
��������Menu_opr2
�������ܣ���ʾ����2���㷨ѡ��˵� 
��������������� 
��������ֵ����  
**********************************/
void Menu_opr2(){
	system("cls"); //�����Ļ����ʾ����Ϣ
	printf("        ������������������������������������������������������������������������\n");
	printf("        ��           �����㷨ѡ��˵�       ��\n"); 
	printf("        ������������������������������������������������������������������������\n");
	printf("        ��            1.ð������            ��\n");
	printf("        ��            2.ֱ�Ӳ�������        ��\n");	
	printf("        ��            3.��ѡ������        ��\n");
	printf("        ��            4.ϣ������            ��\n");
	printf("        ��            5.������              ��\n"); 
	printf("        ��            6.�鲢����            ��\n");
	printf("        ��            7.��������            ��\n");
	printf("        ������������������������������������������������������������������������\n");
	printf("        ��            8.�����㷨ѡ��˵�    ��\n");
	printf("        ��            9.���˵�              ��\n");
	printf("        ��            0.�˳�����            ��\n");			
	printf("        ������������������������������������������������������������������������\n\n");
	printf("          �밴����Ӧ���ּ����س���ѡ�������㷨\n");
}
/******************************** 
��������Operation_1
�������ܣ�����1��ʵ��
**********************************/
void Operation_1(){
	srand( (unsigned int)time(NULL) );
	SqList *L=new SqList();SqList *List=new SqList();			
		 CreateSqList(L);CopyList(L,List);
		 printf("###############################################################\n");
	     printf("�������һ��α���������ʾ�����㷨���\n");
         printf("###############################################################\n");
		 printf("α�����Ϊ��");ShowList(List);printf("\n");
		 BubbleSort(List);printf("ð��������Ϊ��");ShowList(List);CopyList(L,List);printf("\n");
		 InsertSort(List);printf("ֱ�Ӳ���������Ϊ��");ShowList(List);CopyList(L,List);printf("\n");		 
		 SelectSort(List);printf("��ѡ��������Ϊ��");ShowList(List);CopyList(L,List);printf("\n");
		 int dlta[4]={7,5,3,1};        
         ShellSort(List, dlta, 4);printf("ϣ��������Ϊ��");ShowList(List);CopyList(L,List);printf("\n");
         HeapSort(List); printf("��������Ϊ��");ShowList(List);CopyList(L,List);printf("\n");         
         MergeSort(List,1,List->length); printf("�鲢����Ϊ��");ShowList(List);CopyList(L,List);printf("\n"); 
         QuickSort(List); printf("��������Ϊ��");ShowList(List);CopyList(L,List);printf("\n"); 
	
	
}
/******************************** 
��������Operation_2 
�������ܣ�����2��ʵ��
**********************************/
void Operation_2(){
	Menu_opr2();int dlta[4]={7,5,3,1};
	int c;c=getchar();
	SqList *L=new SqList();
	 while(c!=EOF){
	 	if(c-'0'>=1&&c-'0'<=7){
	 		CreateSqList(L);
 		printf("###############################################################\n");
	 	printf("�µ�α�����Ϊ��");ShowList(L);
	 	printf("###############################################################\n");
	 	}	 		
 		switch(c){
	 	 case '1':BubbleSort(L,1);break;//ð������			
		 case '2':InsertSort(L,1);break;//ֱ�Ӳ�������
		 case '3':SelectSort(L,1);break;//��ѡ������
		 case '4':ShellSort(L, dlta, 4,1); break;//ϣ������
		 case '5':HeapSort(L,1);break;//������ 
		 case '6':MergeSort(L,1,L->length,1);break;//�鲢����     
		 case '7':QuickSort(L,1);break;//��������
		 case '8':Menu_opr2();break;//�㷨ѡ��˵�
		 case '9':system("cls");Menu_main();return;break;//���˵�
		 case '0':exit(0);break;//�˳�����
		 case '\n':break;
		 default:printf("������������������:\n");
       }       
	   c=getchar();
 	}
}
/******************************** 
��������Operation_3 
�������ܣ�����3��ʵ��
**********************************/	  
void Operation_3(){
	srand( (unsigned int)time(NULL) );
    int n=rand()%10+10;//���������������
    float count[n+2][21]; float sum;
	SqList *L=new SqList();SqList *List=new SqList();
	printf("###############################################################\n");
	printf("��������������ݽ��бȽϷ���������ƽ��������ܺ��������ܡ�\n");
	printf("###############################################################\n");
	for(int m=0;m<=377;m++)//���� 
         printf("*"); printf("\n"); 
	for(int i=1;i<=n;i++){//��¼�ȽϺ��ƶ�����	
	     int j=0;	
		 CreateSqList(L);CopyList(L,List);
		 printf("��%d��α�����Ϊ��",i);ShowList(List);
		 BubbleSort(List);
		 count[i-1][j]=List->comp;count[i-1][j+1]=List->move;count[i-1][j+2]= List->comp+List->move;j+=3;		        
         CopyList(L,List);InsertSort(List);
         count[i-1][j]=List->comp;count[i-1][j+1]=List->move;count[i-1][j+2]= List->comp+List->move;j+=3;
		 CopyList(L,List);SelectSort(List);
		 count[i-1][j]=List->comp;count[i-1][j+1]=List->move;count[i-1][j+2]= List->comp+List->move;j+=3;
         CopyList(L,List);int dlta[4]={7,5,3,1};ShellSort(List, dlta, 4);        
         count[i-1][j]=List->comp;count[i-1][j+1]=List->move;count[i-1][j+2]= List->comp+List->move;j+=3;
		 CopyList(L,List);HeapSort(List);
		 count[i-1][j]=List->comp;count[i-1][j+1]=List->move;count[i-1][j+2]= List->comp+List->move;j+=3;
		 CopyList(L,List); MergeSort(List,1,List->length);
		 count[i-1][j]=List->comp;count[i-1][j+1]=List->move;count[i-1][j+2]= List->comp+List->move;j+=3;
		 CopyList(L,List);QuickSort(List);
		 count[i-1][j]=List->comp;count[i-1][j+1]=List->move;count[i-1][j+2]= List->comp+List->move;j+=3;
	}
		for(int j=0;j<21;j++){//��ƽ��������ܺ��������� 
		sum=0;float max;max=count[0][j];
		for(int i=0;i<n;i++){
			sum+=count[i][j];
			if(count[i][j]>max)max=count[i][j];
		}		
		count[n][j]=sum/n;
		count[n+1][j]=max;	 
	}
	     for(int m=0;m<=377;m++)//���� 
         printf("*"); printf("\n"); 
	printf("		ð������		ֱ�Ӳ�������		��ѡ������		ϣ������\
		������			�鲢����		��������\n");
	printf("����		�Ƚ�	�ƶ�	��	�Ƚ�	�ƶ�	��	�Ƚ�	�ƶ�	��\
	�Ƚ�	�ƶ�	��	�Ƚ�	�ƶ�	��	�Ƚ�	�ƶ�	��	�Ƚ�	�ƶ�	��\n");
	for(int i=0;i<n+2;i++){//���� 
		if(i<n) 
		printf("��%d��α�����	",i+1);
		else if(i==n) printf("ƽ��������� 	");		
		else if(i==n+1) printf("��������	");
		for(int j=0;j<21;j++){
			printf("%.0f	",count[i][j]);
		}
		printf("\n");
		for(int m=0;m<=188;m++)//���� 
         printf("-"); printf("\n");
	}
}
void Demo(){
	Menu_main();
	 int c;c=getchar();
	 while(c!=EOF){
 		switch(c){
	 	 case '1':Operation_1();break;//����1			
		 case '2':Operation_2();break;//����2
		 case '3':Operation_3();break;//����3
		 case '4':Menu_main();break;//���˵� 
		 case '0':exit(0);break;//�˳� 
		 case '\n':break;//������ 
		 default:printf("������������������:\n");
       }       
	   c=getchar();
 	}		
}	 
int main() {
	Demo();
    return 0;  
}
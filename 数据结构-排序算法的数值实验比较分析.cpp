#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SIZE 100
int gap = 0;
//数据类型 
typedef struct {
    int key;   
}SLNode;
typedef struct {
    SLNode r[SIZE+1];
    int length;
    float comp;//比较次数 
    float move;//移动次数 
}SqList;

void CreateSqList(SqList * L){
	//建立一个L 
	srand( (unsigned int)time(NULL)+gap++);//种子 
    for(int i=1; i<=SIZE; ++i)
    	L->r[i].key=rand()%100+1;
	    L->length=SIZE;	L->comp=0;L->move=0;
}
void CopyList(SqList * L,SqList * cl){
	//复制L到cl 
	for(int i=1; i<=L->length; ++i)
    	cl->r[i].key=L->r[i].key;
	    cl->length=L->length;
		cl->comp=L->comp;cl->move=L->move;	
}
void ShowList(SqList * L){
	//显示L的内容 
	for (int i=1; i<=L->length; i++) 
    printf("%d ",L->r[i].key);
	if(L->comp||L->move)  printf("\n比较次数为%.0f，移动次数为%.0f",L->comp,L->move); 
    printf("\n");
}

/******************************** 
函数名：
函数功能：冒泡排序（升序） 
函数输入参数：数组L,是否显示步骤变量step，1显示，0不显示（缺省值为0） 
函数返回值：无  
**********************************/
void BubbleSort(SqList * L,int step=0){
	int flag;//判断是否有序的变量 
	for (int i=1; i<=L->length-1; i++){//n-1趟冒泡
	   flag=1; 
	   for(int j=1;j<=L->length-i;j++){	   	
   		if(L->r[j].key>L->r[j+1].key){
		   //交换顺序 
		L->r[0].key=L->r[j].key;
		L->r[j].key=L->r[j+1].key;
		L->r[j+1].key=L->r[0].key;
		L->move+=3; flag=0; 
		   }
		   L->comp++;
   	}
   	if(flag)break;//若有序，跳出循环 
   	if(step){printf("第%d趟冒泡排序结果为：",i);ShowList(L);}//是否显示步骤 
	}
	 
}
/******************************** 
函数名：InsertSort
函数功能：直接插入排序(升序) 
函数输入参数：数组L,是否显示步骤变量step，1显示，0不显示
函数返回值：无  
**********************************/
void InsertSort(SqList * L,int step=0){
	for (int i=2; i<=L->length; i++){//n-1趟插入
		if (L->r[i].key<L->r[i-1].key) {//若r[i]比前面有序序列最大的值小，做移位操作 
            int j;
            L->r[0]=L->r[i];//用r[0]记录要插入的值 
            L->move++;
            for (j=i-1; j>0 && (L->r[0].key<L->r[j].key); j--){
            	//移位操作 
            	L->r[j+1]=L->r[j];
            	L->move++;L->comp++;//
            }
            if(j>0) L->comp++;   
            //插入到移出来的空间 
            L->r[j+1]=L->r[0];L->move++;
            L->comp++;
		}     
        else  L->comp++;
        if(step){printf("第%d趟直接插入排序结果为：",i-1);ShowList(L);}//是否显示步骤 
	}
}



int SelectMinKey(SqList *L,int i){
	//从L的第i个元素开始，找到最小的元素下标min 
	int min=i;
	for(int j=i+1;j<=L->length;j++){
		if(L->r[j].key<L->r[min].key) min=j;
		L->comp++;
	}	
	return min;
}
/******************************** 
函数名：SelectSort
函数功能：简单选择排序 （升序）
函数输入参数：数组L,是否显示步骤变量step，1显示，0不显示
函数返回值：无  
**********************************/
void SelectSort(SqList * L,int step=0){
	//简单选择排序算法，对L做n-1趟选择操作 
	for (int i=1; i<L->length; i++) {
        int j=SelectMinKey(L,i);
        if (i!=j) { //位置i的值不是最小，交换位置 
            L->r[0]=L->r[i];
            L->r[i]=L->r[j];
            L->r[j]=L->r[0];
            L->move+=3;
        }
        if(step){printf("第%d趟简单选择排序结果为：",i);ShowList(L);}//是否显示步骤 
    }
} 
void 	ShellInsert(SqList * L,int dk,int step){
    //dk 为位置增量，对L间隔dk做一趟插入排序算法
    for (int i=dk+1; i<=L->length; i++){     
        if (L->r[i].key<L->r[i-dk].key) {//若r[i]比前面有序序列最大的值小，做移位操作 
            int j;
            L->r[0]=L->r[i];//用r[0]记录要插入的值 
            L->move++;
            //移位操作 
            for (j=i-dk; j>0 && (L->r[0].key<L->r[j].key); j-=dk){
            	L->r[j+dk]=L->r[j];
            	L->move++;L->comp++;//
            }
            if(j>0) L->comp++;   
            //插入到移出来的空间 
            L->r[j+dk]=L->r[0];L->move++;
            L->comp++;
        }
        else  L->comp++;
        if(step){printf("希尔排序过程为：");ShowList(L);}//是否显示步骤 
    }
}
/******************************** 
函数名：ShellSort
函数功能：希尔排序（升序） 
函数输入参数：数组L 特定相关参数,是否显示步骤变量step，1显示，0不显示
函数返回值：无  
**********************************/
void ShellSort(SqList * L,int dlta[],int t,int step=0){
	//按位置增量序列dlta[1...t-1] 对L做希尔排序 
    for (int k=0; k<t; k++){
    	ShellInsert(L, dlta[k],step);
    	//if(step){printf("第%d个增量序列下希尔排序结果为：",k+1);ShowList(L);}//是否显示步骤 
    } 
           
}
void HeapAdjust(SqList * L,int index,int length,int step=0){
	//大顶堆调整 ，对L的前length个元素中的第index个节点调整，使其符合大顶堆顺序
	int lchild = 2 * index ;
	int rchild = 2 * index + 1;
	int max = index;
	if (lchild<=length&&L->r[lchild].key>L->r[max].key)	
		max = lchild;L->comp++;	
	if (rchild<=length&&L->r[rchild].key>L->r[max].key)	
		max = rchild;L->comp++;	
	if (max != index)//若大于孩子节点，交换顺序 
	{
		//L->r[0].key起到临时变量temp的作用 
		L->r[0].key=L->r[max].key;
		L->r[max].key=L->r[index].key;
		L->r[index].key=L->r[0].key;
		L->move+=3;//关键字交换计为3次移动
		HeapAdjust(L, max, length,step);
		 if(step){printf("堆排序过程为：");ShowList(L);}//是否显示步骤 
	}
}  
/******************************** 
函数名：HeapSort
函数功能：堆排序（升序） 
函数输入参数：数组L,是否显示步骤变量step，1显示，0不显示
函数返回值：无  
**********************************/
void HeapSort(SqList * L,int step=0){
	//堆排序 
	//对每个非叶子结点倒叙进行大顶堆调整，初始化堆
	int length=L->length; 
	for (int i = length / 2 ; i > 0; i--)
		HeapAdjust(L, i, length,step);
	//将堆顶值放到数组尾部，对剩余元素进行大堆顶调整
	for (int i = length ; i >1; i--)
	{//L->r[0].key起到临时变量temp的作用 
		L->r[0].key=L->r[1].key;
		L->r[1].key=L->r[i].key;
		L->r[i].key=L->r[0].key;
		L->move+=3; 
		HeapAdjust(L, 1, i-1,step);//对根节点做一次大堆顶调整，得到最大值 
	}
	 if(step){printf("堆排序结果为：");ShowList(L);}//是否显示步骤  
} 
void Merge(SqList * L,int start,int mid,int end,int step=0){
	//将两段子表合成到有序子表 
	int i,j,k;k=start;SqList *List=new SqList();
	for(i=start,j=mid+1;i<=mid&&j<=end;k++){//前后两段逐一比较后加到list中 
		if(L->r[i].key<L->r[j].key) 
	     List->r[k].key=L->r[i++].key;
     	else List->r[k].key=L->r[j++].key;
		 L->comp++;L->move++;	
	}
	while(i<=mid)List->r[k++].key=L->r[i++].key;L->move++;//将剩余的值加到list后面 
	while(j<=end)List->r[k++].key=L->r[j++].key;L->move++;
	for (int t  = start; t <=k-1; t++){//将排好的结果赋给原始的L 
		L->r[t].key=List->r[t].key;L->move++;
	}
	 if(step){printf("归并排序过程为：");ShowList(L);}//是否显示步骤    
}
/******************************** 
函数名：MergeSort 
函数功能：归并排序（升序） 
函数输入参数：数组L，待排序元素在数组中开始、末尾的位置 ,是否显示步骤变量step
函数返回值：无  
**********************************/
void  MergeSort(SqList * L,int start,int end,int step=0){
	if(start<end){
		int mid=(start+end)/2;
		MergeSort(L,start,mid,step);//左边有序
		MergeSort(L,mid+1,end,step);//右边有序
		Merge(L,start,mid,end,step);//合并左右
	}
}
void QSort(SqList * L,int low ,int high,int step=0){
	if(low>=high)return;
	int begin=low,end=high;
	L->r[0].key=L->r[low].key;L->move++;//用L->r[0]记录枢轴L->r[low]的值 
	while(low<high){
		while(low<high&&L->r[high].key>=L->r[0].key){//high向左探寻小于枢轴的值 
			high--;L->comp++;
		}
		if(L->r[high].key<L->r[0].key){L->r[low].key=L->r[high].key;L->move++;L->comp++;} 		
		while(low<high&&L->r[low].key<=L->r[0].key){//low向右探寻大于于枢轴的值 
			low++;L->comp++;
		}
		if(L->r[low].key>L->r[0].key){L->r[high].key=L->r[low].key;L->move++;L->comp++;} 		
	}
	L->r[low].key=L->r[0].key;L->move++;//枢轴的值归位 
	QSort(L,begin,low-1,step);//low作为新的枢轴将子表分为两部分递归整理 
	QSort(L,low+1,end,step); 
	 if(step){printf("快速排序过程为：");ShowList(L);}//是否显示步骤 
} 
/******************************** 
函数名：QuickSort 
函数功能：快速排序（升序）
函数输入参数：数组L,是否显示步骤变量step，1显示，0不显示
函数返回值：无  
**********************************/
void QuickSort(SqList * L,int step=0){
	QSort(L,1,L->length,step);
}  
/******************************** 
函数名：Menu_main 
函数功能：显示主菜单 
函数输入参数：无 
函数返回值：无  
**********************************/
void Menu_main(){
	system("cls"); //清除屏幕上显示的信息
	printf("        ┏------------------------------------------------------------------------ ┓\n");
    printf("        ┃                            操作菜单                                     ┃\n"); 
	printf("        ┃------------------------------------------------------------------------ ┃\n");
	printf("        ┃            1.随机产生一组伪随机数，显示各个算法排序结果                 ┃\n");
	printf("        ┃            2.选择一个算法，可视化算法步骤                               ┃\n");	
	printf("        ┃            3.随机产生多组数据比较分析，显示平均情况性能和最坏情况性能   ┃\n");
	printf("        ┃-------------------------------------------------------------------------┃\n");
	printf("        ┃            4.主菜单                                                     ┃\n");
	printf("        ┃            0.退出程序                                                   ┃\n");			
	printf("        ┗------------------------------------------------------------------------ ┛\n\n");
    printf("          请按下相应数字键并回车来选择操作\n");
}
/******************************** 
函数名：Menu_opr2
函数功能：显示操作2的算法选择菜单 
函数输入参数：无 
函数返回值：无  
**********************************/
void Menu_opr2(){
	system("cls"); //清除屏幕上显示的信息
	printf("        ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("        ┃           排序算法选择菜单       ┃\n"); 
	printf("        ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
	printf("        ┃            1.冒泡排序            ┃\n");
	printf("        ┃            2.直接插入排序        ┃\n");	
	printf("        ┃            3.简单选择排序        ┃\n");
	printf("        ┃            4.希尔排序            ┃\n");
	printf("        ┃            5.堆排序              ┃\n"); 
	printf("        ┃            6.归并排序            ┃\n");
	printf("        ┃            7.快速排序            ┃\n");
	printf("        ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
	printf("        ┃            8.排序算法选择菜单    ┃\n");
	printf("        ┃            9.主菜单              ┃\n");
	printf("        ┃            0.退出程序            ┃\n");			
	printf("        ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n");
	printf("          请按下相应数字键并回车来选择排序算法\n");
}
/******************************** 
函数名：Operation_1
函数功能：操作1的实现
**********************************/
void Operation_1(){
	srand( (unsigned int)time(NULL) );
	SqList *L=new SqList();SqList *List=new SqList();			
		 CreateSqList(L);CopyList(L,List);
		 printf("###############################################################\n");
	     printf("随机产生一组伪随机数，显示各个算法结果\n");
         printf("###############################################################\n");
		 printf("伪随机数为：");ShowList(List);printf("\n");
		 BubbleSort(List);printf("冒泡排序结果为：");ShowList(List);CopyList(L,List);printf("\n");
		 InsertSort(List);printf("直接插入排序结果为：");ShowList(List);CopyList(L,List);printf("\n");		 
		 SelectSort(List);printf("简单选择排序结果为：");ShowList(List);CopyList(L,List);printf("\n");
		 int dlta[4]={7,5,3,1};        
         ShellSort(List, dlta, 4);printf("希尔排序结果为：");ShowList(List);CopyList(L,List);printf("\n");
         HeapSort(List); printf("堆排序结果为：");ShowList(List);CopyList(L,List);printf("\n");         
         MergeSort(List,1,List->length); printf("归并序结果为：");ShowList(List);CopyList(L,List);printf("\n"); 
         QuickSort(List); printf("快速序结果为：");ShowList(List);CopyList(L,List);printf("\n"); 
	
	
}
/******************************** 
函数名：Operation_2 
函数功能：操作2的实现
**********************************/
void Operation_2(){
	Menu_opr2();int dlta[4]={7,5,3,1};
	int c;c=getchar();
	SqList *L=new SqList();
	 while(c!=EOF){
	 	if(c-'0'>=1&&c-'0'<=7){
	 		CreateSqList(L);
 		printf("###############################################################\n");
	 	printf("新的伪随机数为：");ShowList(L);
	 	printf("###############################################################\n");
	 	}	 		
 		switch(c){
	 	 case '1':BubbleSort(L,1);break;//冒泡排序			
		 case '2':InsertSort(L,1);break;//直接插入排序
		 case '3':SelectSort(L,1);break;//简单选择排序
		 case '4':ShellSort(L, dlta, 4,1); break;//希尔排序
		 case '5':HeapSort(L,1);break;//堆排序 
		 case '6':MergeSort(L,1,L->length,1);break;//归并排序     
		 case '7':QuickSort(L,1);break;//快速排序
		 case '8':Menu_opr2();break;//算法选择菜单
		 case '9':system("cls");Menu_main();return;break;//主菜单
		 case '0':exit(0);break;//退出程序
		 case '\n':break;
		 default:printf("您的输入有误！请重试:\n");
       }       
	   c=getchar();
 	}
}
/******************************** 
函数名：Operation_3 
函数功能：操作3的实现
**********************************/	  
void Operation_3(){
	srand( (unsigned int)time(NULL) );
    int n=rand()%10+10;//随机产生多组数据
    float count[n+2][21]; float sum;
	SqList *L=new SqList();SqList *List=new SqList();
	printf("###############################################################\n");
	printf("随机产生多组数据进行比较分析，给出平均情况性能和最坏情况性能。\n");
	printf("###############################################################\n");
	for(int m=0;m<=377;m++)//划线 
         printf("*"); printf("\n"); 
	for(int i=1;i<=n;i++){//记录比较和移动次数	
	     int j=0;	
		 CreateSqList(L);CopyList(L,List);
		 printf("第%d组伪随机数为：",i);ShowList(List);
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
		for(int j=0;j<21;j++){//求平均情况性能和最坏情况性能 
		sum=0;float max;max=count[0][j];
		for(int i=0;i<n;i++){
			sum+=count[i][j];
			if(count[i][j]>max)max=count[i][j];
		}		
		count[n][j]=sum/n;
		count[n+1][j]=max;	 
	}
	     for(int m=0;m<=377;m++)//划线 
         printf("*"); printf("\n"); 
	printf("		冒泡排序		直接插入排序		简单选择排序		希尔排序\
		堆排序			归并排序		快速排序\n");
	printf("次数		比较	移动	总	比较	移动	总	比较	移动	总\
	比较	移动	总	比较	移动	总	比较	移动	总	比较	移动	总\n");
	for(int i=0;i<n+2;i++){//画表 
		if(i<n) 
		printf("第%d组伪随机数	",i+1);
		else if(i==n) printf("平均情况性能 	");		
		else if(i==n+1) printf("最坏情况性能	");
		for(int j=0;j<21;j++){
			printf("%.0f	",count[i][j]);
		}
		printf("\n");
		for(int m=0;m<=188;m++)//划线 
         printf("-"); printf("\n");
	}
}
void Demo(){
	Menu_main();
	 int c;c=getchar();
	 while(c!=EOF){
 		switch(c){
	 	 case '1':Operation_1();break;//操作1			
		 case '2':Operation_2();break;//操作2
		 case '3':Operation_3();break;//操作3
		 case '4':Menu_main();break;//主菜单 
		 case '0':exit(0);break;//退出 
		 case '\n':break;//处理换行 
		 default:printf("您的输入有误！请重试:\n");
       }       
	   c=getchar();
 	}		
}	 
int main() {
	Demo();
    return 0;  
}
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
  int i,j,a1,b1,c1,d1,k,ii,jj,pd,m,n,p,q;
  //n代表雷数， 
  int a[11][11],b[11][11],c[11][11];
  int award(int a[11][11],int b[11][11],int c[11][11],int i1,int j1);//声明递归函数 
  printf("******************************W E L C O M E******************************\n");
  printf("游戏操作：每一回合两个简单操作：选择位置+判断（输入0代表安全，输入1代表有雷）\n"); 
  printf("每一回合结束后，若踩到雷则游戏结束（雷用*表示），若成功拆除地雷用#表示\n");
  printf("关联位置用数字表示（代表这个数字的局部九宫格含有的总地雷数）,待判断位置用？表示\n");
  printf("如果所有雷拆除成功，则获胜！\n");
  printf("******************************游 戏 开 始********************************\n");
  printf("\n"); 
  printf("请输入一个小于81的正整数表示雷数："); 
  scanf("%d",&n);
  q=n; //游戏成功输出时需要用到 
  for (i=0;i<=10;i++)  
     for (j=0;j<=10;j++) 
	   {
	    	a[i][j]=0;b[i][j]=0;c[i][j]=0;
	   }//三个11*11二维数组（矩阵）全部初始化为0 
  for (i=0;i<=10;i++) 
  {
  	b[i][0]=100;
  	b[0][i]=100;
  	b[10][i]=100;
  	b[i][10]=100;// 11*11二维数组b的四条边缘全部初始化为100
  }
  srand(time(NULL)); //生成随机数 
  a1=1;
  //printf("以下为雷的坐标:\n");
  while (a1<=n) //从a==1开始，依次将n个雷随机分布到9*9的矩阵上 
  {
	c1=1+rand()%9;
	b1=1+rand()%9;//坐标值在1-9之间 
   	if (a[c1][b1]!=9)
	{
	   a[c1][b1]=9; //将雷（用9代表）赋值给这个位置 
	   a1++;
	} 	
   }
  printf("\n");
  //从48到99属于游戏开挂程序，仅仅用在检验程序时使用，当游戏正式交付玩家时，该部分省去 
  printf("雷初始化分布如下：\n");
  printf("\n");
 	for (i=1;i<=9;i++)  
 	{
  	 for (j=1;j<=9;j++) 
    	  if (a[i][j]==9) 
	    	  printf("  *");
		  else 
		      printf("%3d",a[i][j]);
	printf("\n");
	}
 //进行统计 
 for (i=1;i<=9;i++)  
 {
 	for (j=1;j<=9;j++) 
	 {
 		if (a[i-1][j-1]>=9) a[i][j]++;
 		if (a[i-1][j]>=9) a[i][j]++;
 		if (a[i-1][j+1]>=9) a[i][j]++;
 		if (a[i][j-1]>=9) a[i][j]++;
 		if (a[i][j+1]>=9) a[i][j]++;
 		if (a[i+1][j-1]>=9) a[i][j]++;
 		if (a[i+1][j]>=9) a[i][j]++;
 		if (a[i+1][j+1]>=9) a[i][j]++; 
		 //总共8个if，统计每一个a[i][j]局部九宫格的雷数，如果含有雷，则该位置+1 
		 //注意：理解好为什么要用>=9而不是==9，（范围变宽了，则意味着会涵盖更多情况）
		 //因为开始我们是用9代表雷，如果再遍历过程中遇到雷本身，且它的局部九宫格中也含有雷，则该位置+1,大于9了
		 //以后这个位置的雷以局部九宫格形式再出现时，代表这个雷的数字不是9，而是比9更大的数了，但我们仍然需要把它记录
		 //到中心位置，故条件判断不是==9,+1，而应该是>=9,+1 
		 //经过统计，a矩阵分布着数字，其中>=9则为有雷，<9则作为关联位置，==0则代表奖励位置 
 	 }
 } 
printf("\n");	printf("统计后雷数分布如下：\n");	printf("\n");
 for (i=1;i<=9;i++)
 {
 	for (j=1;j<=9;j++)
	 {
	 	if (a[i][j]>=9) //同理上面的分析 
	 	{
	 		printf("  *");
	 	}
	 	else 
	 	{
	 	printf("%3d",a[i][j]); //该位置不是雷，作为关联位置出现 
	 	} 
	 } 	
		printf("\n");
 }
 k=0;
 while(k==0) /////////////////////////////////////////////////////////////////////游戏开始
             //选择+判断，直到满足条件 
{
	printf("\n");
 	printf("请在？区域选择任意一个位置：\n");
 	printf("请输入一个横坐标："); 
	scanf("%d",&ii);
	printf("请输入一个纵坐标："); 
	scanf("%d",&jj);
	printf("请判断该位置：用0表示安全，用1表示有雷："); 
	scanf("%d",&pd);
	printf("\n");
/**/if((a[ii][jj]>=9)&&(pd==0)) //如果该位置有雷，但是输入的是0，则失败 
	{
	    b[ii][jj]=1; //好像可以删掉 
		printf("GAME OVER :( GAME OVER :( GAME OVER :( GAME OVER :( \n");
		printf("\n");
		 
		for (i=1;i<=9;i++)
		{
 			for (j=1;j<=9;j++) 
 			{
 				if (b[i][j]<2&&a[i][j]<9) //此位置无雷，作为关联位置出现 
					printf("%3d",a[i][j]);
				else if (b[i][j]==2&&a[i][j]>=9) //成功的仍然记录下来 
					printf("  #");
				else if (b[i][j]<2&&a[i][j]>=9) 
					printf("  *");
			} 	 
			printf("\n");
		}
		k=1;
	}
/**/else if((a[ii][jj]>=9)&&(pd==1)) //如果该位置有雷，且输入的是1，则成功 
	{   
	    b[ii][jj]=2; //作为成功标记 
		printf("(%d,%d)位置的雷拆除成功！\n",ii,jj);
		printf("\n"); 
		n--;//每拆除一个雷则n-- 
		if (n==0) //每成功拆掉一个雷则进行一次判断 
		{
		   for (i=1;i<=9;i++)
	    	{
 			  for (j=1;j<=9;j++) 
 				{
 					if (b[i][j]==2) printf("  #");//该位置是雷且拆除成功，则输出# 
					else if((b[i][j]<2)&&(a[i][j]<9)) printf("%3d",a[i][j]); //该地无雷， 
				}
			 printf("\n");
		   	 k=1;
			} 
	    	printf("Congratulations!!! Congratulations!!! Congratulations!!!\n");
	    	printf("\n");
	    	printf("%d个雷已全部成功拆除：）\n",q);
			break; //跳出while循环 
		}
		//不执行if，则输出剩余地雷数 
		printf("当前还剩余%d个雷，请继续：）\n",n);
		printf("\n"); 
		for (i=1;i<=9;i++)
		{
 			for (j=1;j<=9;j++) 
 			{
 				if (b[i][j]==2) printf("  #"); //位置是雷且拆除成功，则输出# 
	 			else if (b[i][j]==1) printf("%3d",a[i][j]);
	 			else if (b[i][j]==0) printf("  ?");
			} 
			printf("\n");
		} 
	}
/**/else if((a[ii][jj]<9)&&(pd==1)) //该位置无雷，但判断有雷 
	{
		printf("该位置没有雷，请重新判断:）\n"); 
	}
/**/else if((a[ii][jj]<9)&&(a[ii][jj]>0)&&(pd==0))//成功打开关联位置
	{
		b[ii][jj]=1;//成功打开关联位置做好标记 
		for (i=1;i<=9;i++)
		{
 			for (j=1;j<=9;j++) 
   				 if (b[i][j]==2) printf("  #");
	 			else if (b[i][j]==1) printf("%3d",a[i][j]);//b[ii][jj]=1;成功打开关联位置后做的标记 
	 			else if (b[i][j]==0) printf("  ?"); //打开关联位置后，其他位置仍然用？表示 
			printf("\n");
		}
		printf("当前还剩余%d个雷，请继续：）\n",n);
		printf("\n");
	}
/**/else if((a[ii][jj]==0)&&(pd==0)) //扫雷游戏中的递归打开，作为一种奖励机制 
	{
	    p=award(a,b,c,ii,jj); //调用奖励函数，递归打开全部0位置，注意把初始奖励坐标ii,jj传给函数 
	    for (i=1;i<=9;i++)
		{
 			for (j=1;j<=9;j++) 
   				 if (b[i][j]==2) printf("  #");
	 			else if (b[i][j]==1) printf("%3d",a[i][j]);
	 			else if (b[i][j]==0) printf("  ?");
			printf("\n");
		}
		printf("当前还剩余%d个雷，请继续：）\n",n);	 
		printf("\n"); 	
	}
	for(i=0;i<50;i++)
	{
		printf("~");////////////////////////////////////////////////////////////////分界线 
	} 
}//while的大括号 
return  0;
}//main()主函数的大括号 

int award(int a[11][11],int b[11][11],int c[11][11],int i1,int j1) 
//定义递归函数，用于连续打开0位置（游戏中的一种奖励机制） 
{
	b[i1][j1]=1;
	if (b[i1-1][j1-1]!=100) b[i1-1][j1-1]=1;
	if (b[i1-1][j1]!=100) b[i1-1][j1]=1;
	if (b[i1-1][j1+1]!=100) b[i1-1][j1+1]=1;
	if (b[i1][j1-1]!=100) b[i1][j1-1]=1;
	if (b[i1][j1+1]!=100) b[i1][j1+1]=1;
	if (b[i1+1][j1-1]!=100) b[i1+1][j1-1]=1;
	if (b[i1+1][j1]!=100) b[i1+1][j1]=1;
	if (b[i1+1][j1+1]!=100) b[i1+1][j1+1]=1; 
	//总共八个if，把b[i1][j1]这个数的局部九宫格穷尽,只要该位置是一般位置（9*9），则该九宫格全部赋值为1 
	c[i1][j1]=1; 
	//作为标记元素，已经打开过的就不再进行下面的判断了 
	
	if ((a[i1-1][j1-1]==0)&&(b[i1-1][j1-1]!=100)&&(c[i1-1][j1-1]==0)) award(a,b,c,i1-1,j1-1);
	if ((a[i1-1][j1]==0)&&(b[i1-1][j1]!=100)&&(c[i1-1][j1]==0)) award(a,b,c,i1-1,j1);
	if ((a[i1-1][j1+1]==0)&&(b[i1-1][j1+1]!=100)&&(c[i1-1][j1+1]==0)) award(a,b,c,i1-1,j1+1);
	if ((a[i1][j1-1]==0)&&(b[i1][j1-1]!=100)&&(c[i1][j1-1]==0)) award(a,b,c,i1,j1-1);
	if ((a[i1][j1+1]==0)&&(b[i1][j1+1]!=100)&&(c[i1][j1+1]==0)) award(a,b,c,i1,j1+1);
	if ((a[i1+1][j1-1]==0)&&(b[i1+1][j1-1]!=100)&&(c[i1+1][j1-1]==0)) award(a,b,c,i1+1,j1-1);
	if ((a[i1+1][j1]==0)&&(b[i1+1][j1]!=100)&&(c[i1+1][j1]==0)) award(a,b,c,i1+1,j1);
	if ((a[i1+1][j1+1]==0)&&(b[i1+1][j1+1]!=100)&&(c[i1+1][j1+1]==0)) award(a,b,c,i1+1,j1+1);
	//注意if里面第一个条件：a[][]==0,而不是a[][]>=0&&a[][]<9，只有a[][]为0位置时 
	//对于相应的b[][]来说，局部九宫格全部赋值为1，再在b[][]==1时打开a[][]，这样不会把雷所代表的>=9位置打开 
	//只要b[][]!=100,且c[][]为0，则调用递归函数，使b[][],c[][]为1
	//再不断以当前坐标为出发点，步步为营，依次探索周围的局部九宫格 
	//最终结果：当a[][]为0位置，则对应b[][]为1，c[][]为1，递归打开所有0位置
	//即使a[][]不是0位置，且不是雷（193行），仍然把b[][]标记为1，递归打开时作为关联位置出现 
	//总共八个if，把n[i1][j1],n[i1][j1],n[i1][j1]这个数的局部九宫格穷尽,注意坐标的一一对应 
	return 0;
}

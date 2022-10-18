#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
struct node
{
	float x;
	int y;
}a[10000],b[10000];
int t,cnt1,cnt2,f,f1,f2;
char s1[100000];
int main()
{
	cnt1=0;
	f1=0;
	f2=0;
	while(scanf("%s",s1)&&strcmp(s1,"-")&&strcmp(s1,"+"))
	{
		cnt1++;
		a[cnt1].x=atof(s1);
		scanf("%d",&a[cnt1].y);
		if (a[cnt1].x!=0&&a[cnt1].y==0)f2=1;
	} 
	if (!strcmp(s1,"-"))f=1;
	else f=0;
	for (int j=1;j<=cnt1;j++){
		for (int i=1;i<cnt1;i++)
		{
			if (a[i].y<a[i+1].y)
			{
				t=a[i].y;
				a[i].y=a[i+1].y;
				a[i+1].y=t;
				t=a[i].x;
				a[i].x=a[i+1].x;
				a[i+1].x=t;
			}
		}
	}
	a[cnt1+1].y=-1;
	cnt2=1;
	while (scanf("%lf",&b[cnt2].x)!=EOF)
	{
		scanf("%d",&b[cnt2].y);
		if (b[cnt2].x!=0&&b[cnt2].y==0)f2=1;
		cnt2++;
	}
	cnt2--;
    for (int j=1;j<=cnt2;j++)
	{
		for (int i=1;i<cnt2;i++)
		{
			if (b[i].y<b[i+1].y)
			{
				t=b[i].y;
				b[i].y=b[i+1].y;
				b[i+1].y=t;
				t=b[i].x;
				b[i].x=b[i+1].x;
				b[i+1].x=t;
			}
		}
	} 
	b[cnt2+1].y=-1;
	for (int i=1;i<=cnt1;i++)
	{
		for (int j=1;j<=cnt2;j++)
		{
			if (f==0)
			{
				if (a[i].x==b[j].x*(-1)&&a[i].y==b[j].y)f1=1;
			}
			else 
			{
				if (a[i].x==b[j].x&&a[i].y==b[j].y)f1=1;
			}
		}
	} 
	int i=1;
	int j=1;
	while (1)
	{
		if (f1==1&&a[i].y<0&&b[j].y<0&&f2==0)printf("0 0"); 
		if (i>cnt1&&j>cnt2)break;
		if (i>cnt1)
		{
			if (b[j].x==0&&b[j].y==0)
			{
				j++;
				continue;
			}
			if (f==0){
				printf("%g ",b[j].x);
				printf("%d ",b[j].y);
			}
			else {
				printf("%g ",(-1)*b[j].x);
				printf("%d ",b[j].y);
			}
			j++;
			continue;
		}
		if (j>cnt2)
		{
			if (a[i].x==0&&a[i].y==0){
				i++;
				continue;
			}
			printf("%g ",a[i].x);
			printf("%d ",a[i].y);
			i++;
			continue;
		}
		if (a[i].y==b[j].y)
		{
			if (f==1)
			{
				if (a[i].x!=b[j].x)
				{
					printf("%g ",a[i].x-b[j].x);
					printf("%d ",a[i].y);
				}
			}
			else if (a[i].x!=(-1)*b[j].x)
			{
				printf("%g ",a[i].x+b[j].x);
				printf("%d ",a[i].y);
			}
			i++;
			j++;
		}
		if (a[i].y>b[j].y)
		{
			if (a[i].x==0&&a[i].y==0)
			{
				i++;
				continue;
			}
			printf("%g ",a[i].x);
			printf("%d ",a[i].y);
			i++;
		}
		if (a[i].y<b[j].y)
		{
			if (b[j].x==0&&b[j].y==0)
			{
				j++;
				continue;
			}
			if (f==0)
			{
				printf("%g ",b[j].x);
				printf("%d ",b[j].y);
			}
			else 
			{
				printf("%g ",(-1)*b[j].x);
				printf("%d ",b[j].y);
			}
			j++;
		}
	}
	return 0;
}


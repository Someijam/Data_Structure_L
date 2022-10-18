#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
	double x;
	double y;
} b[100000], a[100000], c[100000];
int cnt, f2, f3;
char op;
void deal()
{
	int i, f, nowi;
	double num, power;
	char c;
	char s[1000];
	char s1[1000];
	i=0;
	while (1)
	{
		scanf("%c", &c);
		s[i]=c;
		if (s[i]==')')break;
		i++;
	}
	i=0;
	f=0;
	num=0;
	power=0;
	f2=0;
	while (1)
	{
		c=s[i];
		if ((c=='+'||c=='-'||c==')')&&f==1&&s[i-1]!='('&&s[i-1]!='^')
		{
			f=0;
			for (int j=nowi; j<i; j++)s1[j-nowi]=s[j];
			if (num!=0)
			{
				power=atof(s1);
				cnt++;
				b[cnt].x=num;
				b[cnt].y=power;
				num=0;
				power=0;
			}
			else
			{
				num=atof(s1);
				cnt++;
				b[cnt].x=num;
				b[cnt].y=0;
				num=0;
				power=0;
			}
			for (int j=nowi; j<i; j++)s1[j-nowi]=0;
		}
		if (f==1&&c=='x')
		{
			f=0;
			for (int j=nowi; j<i; j++)s1[j-nowi]=0;
			for (int j=nowi; j<i; j++)s1[j-nowi]=s[j];
			if (s[i-1]=='('||s[i-1]=='+'||s[i-1]=='-')
			{
				if (s[i-1]=='('||s[i-1]=='+')num=1;
				else num=-1;
			}
			else num=atof(s1);
			for (int j=nowi; j<i; j++)s1[j-nowi]=0;
			if (s[i+1]!='^')
			{
				power=1;
				cnt++;
				b[cnt].x=num;
				b[cnt].y=power;
				num=0;
				power=0;
			}
		}
		if ((c=='('||c=='+'||c=='-')&&f==0)
		{
			f=1;
			if (c=='-')nowi=i;
			else nowi=i+1;
		}
		if (c=='^')
		{
			f=1;
			nowi=i+1;
		}
		i++;
		if (c==')')return;
	}
}
int cnt1, cnt2;
int main()
{
	cnt=0;
	deal();
	for (int i=1; i<=cnt; i++)
	{
		a[i].x=b[i].x;
		a[i].y=b[i].y;
		b[i].x=0;
		b[i].y=0;
	}
	cnt1=cnt;
	cnt=0;
	scanf("%c", &op);
	deal();
	cnt2=cnt;
	if (op=='+')f2=0;
	else f2=1;
	for (int i=1; i<=cnt1; i++)
	{
		for (int j=1; j<cnt1; j++)
		{
			if (a[j].y<a[j+1].y)
			{
				double t=a[j].y;
				a[j].y=a[j+1].y;
				a[j+1].y=t;
				t=a[j].x;
				a[j].x=a[j+1].x;
				a[j+1].x=t;
			}
		}
	}
	for (int i=1; i<=cnt1; i++)
	{
		while (a[i].y==a[i+1].y&&(i+1<=cnt1))
		{
			a[i].x += a[i+1].x;
			for (int j=i+1; j<=cnt1; j++)
			{
				a[j].x=a[j+1].x;
				a[j].y=a[j+1].y;
			}
			cnt1--;
		}
	}
	for (int i=1; i<=cnt2; i++)
	{
		for (int j=1; j<cnt2; j++)
		{
			if (b[j].y<b[j+1].y)
			{
				double t=b[j].y;
				b[j].y=b[j+1].y;
				b[j+1].y=t;
				t=b[j].x;
				b[j].x=b[j+1].x;
				b[j+1].x=t;
			}
		}
	}
	for (int i=1; i<=cnt1; i++)
	{
		while (b[i].y==b[i+1].y&&(i+1<=cnt1))
		{
			b[i].x += b[i+1].x;
			for (int j=i+1; j<=cnt1; j++)
			{
				b[j].x=b[j+1].x;
				b[j].y=b[j+1].y;
			}
			cnt1--;
		}
	}
	int i=1;
	int j=1;
	cnt=0;
	while (1)
	{
		if (i>cnt1&&j>cnt2)break;
		if (i>cnt1)
		{
			cnt++;
			if (f2==0)c[cnt].x=b[j].x;
			else c[cnt].x=(-1) * b[j].x;
			c[cnt].y=b[j].y;
			j++;
			continue;
		}
		if (j>cnt2)
		{
			cnt++;
			c[cnt].x=a[i].x;
			c[cnt].y=a[i].y;
			i++;
			continue;
		}
		if (a[i].y==b[j].y)
		{
			if (f2==0)
			{
				cnt++;
				c[cnt].x=a[i].x+b[j].x;
				c[cnt].y=a[i].y;
			}
			else
			{
				cnt++;
				c[cnt].x=a[i].x-b[j].x;
				c[cnt].y=a[i].y;
			}
			i++;
			j++;
		}
		if (a[i].y>b[j].y)
		{
			cnt++;
			c[cnt].x=a[i].x;
			c[cnt].y=a[i].y;
			i++;
		}
		if (a[i].y<b[j].y)
		{
			cnt++;
			if (f2==0)c[cnt].x=b[j].x;
			else c[cnt].x=(-1) * b[j].x;
			c[cnt].y=b[j].y;
			j++;
		}
	}
	f3=0;
	for (int i=1; i<=cnt; i++)
	{
		if (c[i].x>0&&f3==1)printf("+");
		if ((c[i].x==1||c[i].x==-1)&&c[i].y!=0)
		{
			if (c[i].y!=1)
			{
				if (c[i].x==1)printf("x^%g", c[i].y);
				else printf("-x^%g", c[i].y);
			}
			else
			{
				if (c[i].x==1)printf("x");
				else printf("-x");
			}
			f3=1;
			continue;
		}
		if (c[i].x==0)continue;
		if (c[i].y==0)
		{
			printf("%g", c[i].x);
			f3=1;
			continue;
		}
		if (c[i].x<0)
		{
			printf("-");
			c[i].x=(-1) * c[i].x;
			printf("%gx^%g", c[i].x, c[i].y);
			f3=1;
			continue;
		}
		if (c[i].y!=1)printf("%gx^%g", c[i].x, c[i].y);
		else printf("%gx", c[i].x);
		f3=1;
	}
	if (f3==0)printf("0");
	return 0;
}

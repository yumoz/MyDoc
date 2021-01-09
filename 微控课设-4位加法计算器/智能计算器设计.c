#include<reg52.h>			
typedef unsigned char uint8;
typedef unsigned int uint16;

sbit rw=P2^5;
sbit rs=P2^6;
sbit e=P2^7;
sbit led=P3^7;

uint8 key,num,ei,eii,p;
uint8 fuhao;//定义具体的那个符号，是加减还是乘除。
uint8 flag;	//定义有没有按下符号键，这个是统称
long a,b,c,d;	//定义运算数据的第一个和第二个及等于的数变量
uint8 k; //定义小数点后面显示的位数

uint8 dat1[]={1,2,3,0x2b-0x30, 4,5,6,0x2d-0x30, 7,8,9,0x2a-0x30,
									0,0x01-0x30,0x3d-0x30,0x2b-0x30 };//保存显示的数据
uint8 dat2[]="9999 revo rewsna";
uint8 dat3[]="Hi welcome into";
uint8 dat4[]="counter by yumo";
void delay(uint16 i)
{
	while(i--);
}
void lcdwrc(uint8 c)//写入命令
{
	delay(1000);
	rs=0;//选择发送命令
	rw=0;//选择写入
	e=0;//使能
	
	P0=c;//放入命令
	e=1;//写时序
	delay(1000);//保持时间
	e=0;
}
void lcdwrd(uint8 dat)//写入数据
{
	delay(1000);
	rs=1;//选择输入数据
	rw=0;//选择写入
	e=0;
	
	P0=dat;//写入数据
	e=1;//写入时序
	delay(1000);
	e=0;
	rs=0;
}

void lcdinit()//LCD初始化
{
	delay(1500);
	lcdwrc(0x38);
	delay(500);
	lcdwrc(0x38);
	delay(500);
	lcdwrc(0x38);
	delay(500);
	lcdwrc(0x38);
	lcdwrc(0x08);
	lcdwrc(0x01);
	lcdwrc(0x06);
	lcdwrc(0x0c);
	key=0;
	num=0;
	flag=0;
	fuhao=0;
	a=0;
	b=0;
	c=0;
	d=0;
	led=0;
}

show()
{
	for(eii=0;eii<15;eii++)
	{
		
		lcdwrd(dat3[eii]);
	}	
	lcdwrc(0xc0);//写命令函数使其到第二行第一个字符
	for(p=0;p<15;p++)
	{
		
		lcdwrd(dat4[p]);
	}	
	return 1;
}
void keyscan()
{
	P1=0xfe;   //令第一行为0，然后判断是哪一列按下
	if(P1!=0xfe)
	{
		delay(1000);
		if(P1!=0xfe)
		{
			key=P1&0xf0;
			switch(key)
			{
				case 0xe0: num=0;break;	  //1
				case 0xd0: num=1;break;	  //2
				case 0xb0: num=2;break;	  //3
				case 0x70: num=3;break;	  //加
			}
		}
		while(P1!=0xfe);
		if(num==0||num==1||num==2)	 //确认第一行的数1,2,3
		{
			if(flag==0)	 //没有按下符号键
			{
				led=1;
				a=a*10+dat1[num];	
			}
			else
			{
				led=1;
				delay(1000);
				led=0;
				delay(1000);
				led=1;
				b=b*10+dat1[num];
			}		
		}
		if(num==3)
		{
			led=0;
			flag=1;
			fuhao=1;//加号+	
		}
		lcdwrd(0x30+dat1[num]);
	}

	P1=0xfd;				//令第二行为0，判断是哪一列按下
	if(P1!=0xfd)
	{
		delay(1000);
		if(P1!=0xfd)
		{
			key=P1&0xf0;
			switch(key)
			{
				case 0xe0: num=4;break;	  //4
				case 0xd0: num=5;break;	  //5
				case 0xb0: num=6;break;	  //6
				case 0x70: num=7;break;	  //减—
			}	
		}
		while(P1!=0xfd);
		if(num==4||num==5||num==6)
		{
			if(flag==0)	 //没有按下符号键
			{
				led=1;
				a=a*10+dat1[num];	
			}
			else
			{
				led=1;
				b=b*10+dat1[num];
			}			
		}
		else
		{
			led=0;
			flag=1;
			fuhao=2;//带表减号
		}
		lcdwrd(0x30+dat1[num]);
	}

	P1=0xfb;		 //令第三行为0，判断哪一列按下
	if(P1!=0xfb)
	{
		delay(1000);
		if(P1!=0xfb)
		{
			key=P1&0xf0;
			switch(key)
			{
				case 0xe0: num=8;break;	  //7
				case 0xd0: num=9;break;	  //8
				case 0xb0: num=10;break;  //9
				case 0x70: num=11;break;  //乘*
			}	
		}
		while(P1!=0xfb);
		if(num==8||num==9||num==10)
		{
			if(flag==0)	 //没有按下符号键
			{
				led=1;
				a=a*10+dat1[num];	
			}
			else
			{
				led=1;
				b=b*10+dat1[num];
			}			
		}
		else
		{
			led=0;
			flag=1;
			fuhao=3;//带表乘号*
		}
		lcdwrd(0x30+dat1[num]);
	}

	P1=0xf7;		 //令第四行为0，判断哪一列按下
	if(P1!=0xf7)
	{
		delay(1000);
		if(P1!=0xf7)
		{
			key=P1&0xf0;
			switch(key)
			{
				case 0xe0: num=12;break;  //0
				case 0xd0: num=13;break;  //清除rst
				case 0xb0: num=14;break;  //等号=
				case 0x70: num=15;break;  //除/
			}	
		}
		while(P1!=0xf7);
		switch(num)
		{
			case 12: 
					if(flag==0)	 //没有按下符号键
					{
						led=1;
						a=a*10+dat1[num];
						lcdwrd(0x30);	
					}
					else
					{
						led=1;
						b=b*10+dat1[num];
						lcdwrd(0x30);
					}
					break;			
			case 13: 
					lcdwrc(0x01);	//清屏指令			
					a=0;
					b=0;
			    c=0;
					flag=0;
					fuhao=0;
					break;
			case 15:
				
					led=0;
					flag=1;
					fuhao=4;
					lcdwrd(0x2f);//除号/
					break;					
			case 14: 					//如果是等于号
					if(fuhao==1)//加
					{
						lcdwrc(0x4f+0x80);
						lcdwrc(0x04);//设置光标左移，屏幕不移动
						c=a+b;
						
						if(c==0)
						{
							lcdwrc(0x4f+0x80);
							lcdwrc(0x04);
							lcdwrd(0x30);
						}
						while((c!=0)&&(c<=9999))	 //一位一位显示
						{
							
							lcdwrd(0x30+c%10);//显示结果的最后一位在0x4f的位置
							c=c/10;//取前面的结果数据	
						}						
						if(c>9999)
						{
							for(ei=0;ei<=16;ei++)
							{
								lcdwrd(dat2[ei]);			
							}			
						}						
						lcdwrd(0x3d); //显示等于号=
						a=0;
						b=0;
						c=0;
						flag=0;
						fuhao=0;//全部清除为0
					}					
					if(fuhao==2)   //减
					{
						lcdwrc(0x4f+0x80);
						lcdwrc(0x04);//设置光标左移，屏幕不移动
						if(a>b)
							c=a-b;
						else
							c=b-a;
						
						if((c==0))//此语句位置影响显示
						{
							lcdwrc(0x4f+0x80);
							lcdwrc(0x04);
							lcdwrd(0x30);
						}
						while((c!=0)&&(c<=9999))	 //一位一位显示
						{
							lcdwrd(0x30+c%10);//显示结果的最后一位在0x4f的位置
							c=c/10;//取前面的结果数据	
						}
						if(c>9999) 
						{
							for(ei=0;ei<=16;ei++)
							{
								lcdwrd(dat2[ei]);			
							}								
						}					
						if(a<b)	lcdwrd(0x2d); //显示-号
						lcdwrd(0x3d); //显示等于号=
						a=0;
						b=0;
						flag=0;
						fuhao=0;//全部清除为0
					}					
					if(fuhao==3)//乘法		
					{
						lcdwrc(0x4f+0x80);
						lcdwrc(0x04);//设置光标左移，屏幕不移动
						c=a*b;
						while((c!=0)&(c<=9999))	 //一位一位显示
						{
							lcdwrd(0x30+c%10);//显示结果的最后一位在0x4f的位置
							c=c/10;//取前面的结果数据	
						}
						if (c>9999) 
						{
							for(ei=0;ei<=16;ei++)
							{
								lcdwrd(dat2[ei]);			
							}					
						}
						if(a==0||b==0)
						{
							lcdwrd(0x30);
						}
						lcdwrd(0x3d); //显示等于号=
						a=0;
						b=0;
						flag=0;
						fuhao=0;//全部清除为0	
					}				
					if(fuhao==4)//除法
					{
						k=0;
						lcdwrc(0x4f+0x80);
						lcdwrc(0x04);//设置光标左移，屏幕不移动
						c=(long)(((float)a/b)*10000);//强制转换为long。
						while((c!=0)&&(c<=99990000))	 //一位一位显示
						{
							k++;
							lcdwrd(0x30+c%10);//显示结果的最后一位在0x4f的位置
							c=c/10;//取前面的结果数据
							if(k==4)//结果保留四位有效数字
							{
								lcdwrd(0x2e);//显示一个点
								//k=0;//倘若K=0，那么每隔三位就有一个小数点，计算器上的逗号就是这个原理。
							}		
						}
						if(c>99990000) 
						{
							for(ei=0;ei<=16;ei++)
							{
								lcdwrd(dat2[ei]);			
							}		
						}
						if(0<(a/b)<0.1001)
						{
							//lcdwrd(0x2e);
							
						}
						if((a/b)<1)	  //如果a比b小的话那么除的结果最高位是0
						{
							lcdwrd(0x30);	
						}
						if(b==0)//检错因为除数不能为0，否则就显示ERROR
						{
							lcdwrc(0x4f+0x80);
							lcdwrc(0x04);
							lcdwrd(0x52);
							lcdwrd(0x4f);
							lcdwrd(0x52);												
							lcdwrd(0x52);
							lcdwrd(0x45);
						}
						lcdwrd(0x3d); //显示等号
						a=0;
						b=0;
						flag=0;
						fuhao=0;//全部清除为0
					}
					break;
		}
	}
}
void main()
{
	lcdinit();
	show();//个性化界面
	while(1)
	{		
		keyscan();	
	}
}

#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "oled.h"
#include "usart.h"	 
#include "remote.h"


void show(u8 m,u8 n)//��ʾ����
	{
	 OLED_DrawPoint(m,n,1);
	 OLED_DrawPoint(m,n+1,1);
	 OLED_DrawPoint(m+1,n,1);
	 OLED_DrawPoint(m+1,n+1,1);
	}
	
	void showfood(u8 m,u8 n)//��ʾʳ��
	{
	 OLED_DrawPoint(m,n,0);
	 OLED_DrawPoint(m,n+1,1);
	 OLED_DrawPoint(m+1,n,1);
	 OLED_DrawPoint(m+1,n+1,0);
	}
	
		void clean (u8 m,u8 n)//�������
	{
	 OLED_DrawPoint(m,n,0);
	 OLED_DrawPoint(m,n+1,0);
	 OLED_DrawPoint(m+1,n,0);
	 OLED_DrawPoint(m+1,n+1,0);
	}
	
	int t,v,i,ate=0,key,score;//ȫ�ֱ���
  unsigned int seed=0;//�����������
	
	struct {
	int speed;
	int len;
	int x[100];
	int y[100];
}snake;


struct {						
	int x;
	int y;
}food;
int creatfood()//����ʳ�
{
	
	u8  m,n;
	t=0;
	if(food.x==snake.x[0]&&food.y==snake.y[0])//�ж���һ��ʳ���Ƿ񱻳ԣ�
{
  	srand(seed);
  	while(1)
  {
		 t=0;
  	 m=(rand()%60+2)*2;
  	 n=(rand()%28+2)*2;
  	for(i=snake.len ;i>0;i--)
  	{
  		if(m==snake.x[i]&&n==snake.y[i])
  		{
  			t=1;
  			break;
  		}
			if(m<2||m>124||n<2||n>60)
			{
				t=1;
				break;
			}
  	}
  	if(t!=1)break;
  }
  food.x=m;
  food.y=n;
  snake.len++;
	showfood(food.x,food.y);
	OLED_Refresh_Gram();	
	ate=1;
}
else
{
	ate=0;
}
	return 0;
}


void drawmap()//���Ƶ�ͼ��
{
	int i;
	u8 m=64,n=32;	 
	 snake.len=3;
	 key=1;
	 snake.x[0]=40;
	 snake.y[0]=32;
	/* ��ӡ�߿�*/	 
for(i=1;i<127;i++)
{
	 OLED_DrawPoint(i,1,1);
	 OLED_DrawPoint(i,62,1);
}
for(i=1;i<63;i++)
{ 
	 OLED_DrawPoint(1,i,1);
	 OLED_DrawPoint(126,i,1);
}
  OLED_Refresh_Gram();

   /*���ɳ�ʼʳ��*/
	 srand(seed);
	 food.x=(rand()%61+2)*2;
   food.y=(rand()%29+2)*2;
   showfood(food.x,food.y);


	  /*��ʼ������*/
show(snake.x[0],snake.y[0]);
for(i=1;i<snake.len;i++)
{
	snake.x[i]=snake.x[i-1]-2;
	snake.y[i]=snake.y[i-1];
	show(snake.x[i],snake.y[i]);
}

  OLED_Refresh_Gram();		//������ʾ��OLED 
}
/*��������*/
void keydown()
{
	int  pre_key;
	pre_key=key;
	if(Remote_Scan()==194||KEY_Scan(1)==1){key=1;LED0=1;LED1=0;}
	if(Remote_Scan()==168||KEY_Scan(1)==2){key=2;LED1=1;LED0=0;}
	if(Remote_Scan()==34||KEY_Scan(1)==3){key=3;LED0=0;LED1=0;}
	if(Remote_Scan()==98||KEY_Scan(1)==4){key=4;LED1=1;LED0=1;}
	if(ate==0)
	{
		clean(snake.x[snake.len-1],snake.y[snake.len-1]);//�����β
	}
	for (i = snake.len - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}
	//���������뵱ǰ�����෴
	if (pre_key == 4 && key == 2)
		key = 4;
	if (pre_key == 2 && key == 4)
		key = 2;
	if (pre_key == 3 && key == 1)
		key = 3;
	if (pre_key == 1 && key == 3)
		key = 1;
		switch (key)
	{
	case 3:
		snake.x[0] -= 2;
		break;
	case 1:
		snake.x[0] += 2;
		break;
	case 2:
		snake.y[0]+=2;
		break;
	case 4:
		snake.y[0]-=2;
		break;
	}
	show(snake.x[0],snake.y[0]);//������ͷ
	OLED_Refresh_Gram();	
	t=0;
}

int snakestatus()
{
		/*�ж���Ϸ�Ƿ����*/
	 v=0;
	if(snake.x[0]==0||snake.x[0]==1||snake.x[0]==126||snake.x[0]==127||
		snake.y[0]==0||snake.y[0]==1||snake.y[0]==62||snake.y[0]==63)v=1;
	for(i=1;i<snake.len;i++)
	{
		if(snake.x[0]==snake.x[i]&&snake.y[0]==snake.y[i])v=1;
	}
	return v;
}


 int main(void)
 {	 
	u8 key;
	u8 t=0;	
 	u8 *str=0;

	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	OLED_Init();	
	KEY_Init();	 	
	Remote_Init();			//������ճ�ʼ��		 	
  key=Remote_Scan();
	OLED_Init();			//��ʼ��OLED 
	drawmap();
	while(1) 
	{		
	keydown();
	if(snakestatus()==1)break;//�ж���Ϸ�Ƿ����
	creatfood();
	OLED_Refresh_Gram();//ˢ����Ļ
  delay_ms(150);
	seed+=5;
	}	  
	score=snake.len*10;
	OLED_Clear();//�����Ļ
	OLED_Refresh_Gram();	
	OLED_ShowString(0,0,"your score is",12);
  OLED_ShowNum(60,13,score,3,16);//��ʾ����
  OLED_ShowString(0,30,"try again by pressing reset",12);
	OLED_Refresh_Gram();	

  
}







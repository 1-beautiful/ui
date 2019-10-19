/*
*   author   : Fuqiang Xu
*   Done date: 2018-11-27
*   e-mail   : 17843124829@163.com
*/

#include "JLU.h"

unsigned char uSendBuf[32]={0};

/*
* ��16������ͨ��ѹ�����������
* adr:����ͨ����ţ�date������������
* adr:0~15;         date:-32768~32767
*/
void push(unsigned char adr,unsigned short date)
{
  uSendBuf[adr*2]=date/256;
  uSendBuf[adr*2+1]=date%256;
}

/*
* ʾ��������ר�ú���
* pushѹ����������ݺ�ִ�д˺���
* ͼ����ʾ���ܲ���Ҫ
*/
void uSendOnePage(void)
{
  unsigned char i; 
  uart_putchar(uart2,255);
  uart_putchar(uart2,37);
  for(i=0;i<16;i++)
  {
    uart_putchar(uart2, uSendBuf[i*2]);
    uart_putchar(uart2, uSendBuf[i*2+1]);
  }
  uart_putchar(uart2,37);
  uart_putchar(uart2,255);
  
}

/*
* ͼ����ʾ����ר�ú���
* �ɷ��ͻҶ�ͼ��Ͷ�ֵͼ��������
* �Ҷ�ͼ��һ���ֽڴ�1������
* ��ֵͼ��һ���ֽڴ�8������
* �ڷ���һ֡ͼ��֮ǰ��ִ�д˺���
* raw ���˴η���ͼ�����������Ϊ320����ÿ��������ص���
* line���˴η���ͼ�����������Ϊ240����ÿ��������ص���
*/
void push_head(unsigned int raw,unsigned int line)
{
  uart_putchar(uart2,255);
  uart_putchar(uart2,37);
  uart_putchar(uart2,(unsigned char)((raw/10)&0xff));
  uart_putchar(uart2,(unsigned char)((line/10)&0xff));
  for(int i=0;i<32;i++)
  {
      uart_putchar(uart2,uSendBuf[i]);
  }
}

/*
* ͼ����ʾ����ר�ú���
* ��������ͼ����������ѹ�뷢������
* byte_num:�˴η��͵��ֽ���
* buf     :�޷����ַ������飬����������ܳ���256
*/
void push_in_data(int byte_num,unsigned char *buf)
{
  for(int i=0;i<byte_num;i++)
    {
        uart_putchar(uart2,(buf[i]&0xff));
    } 
}

/*
* ͼ����ʾ����ר�ú���
* �ڷ������һ֡ͼ���ִ�д˺���
*/
void push_end(void)
{
  uart_putchar(uart2,37);  
  uart_putchar(uart2,255);
}

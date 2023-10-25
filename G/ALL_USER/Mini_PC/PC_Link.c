#include "PC_Link.h"
#include "usart.h"
#include "My_Crc.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "User_Debug.h"

//����PC���ݣ�һ����ഫ��255���ֽڣ�����512���ֽڳ��ȣ���ֹDMA����Խ��
static uint8_t pc_rx_buf[512];
static uint8_t pc_tx_buf[255];

VISION_DATA obj_data;	//��������

//����PCͨ��
void PC_Link_Init(void)
{
	__HAL_UART_ENABLE_IT(&PC_Uart, UART_IT_RXNE);  //�����ж�
  __HAL_UART_ENABLE_IT(&PC_Uart, UART_IT_IDLE);  //�����ж�
	Reset_PC_Data();	//��ֹ�����ȸ�λPC����
	HAL_UART_Receive_DMA(&PC_Uart,pc_rx_buf,512);//��ʼ���գ�ʹ��DMA��
}

//��PC��������
void PC_Link_Send(uint16_t cmd_id,uint8_t *tx_buff,uint16_t size)
{
	static uint8_t SEQ = 0;

	pc_tx_buf[0] = 0xA5;	//��ʼ��־
	pc_tx_buf[1] = (uint8_t)(size>>8);		//LEN�ĸ�8λ
	pc_tx_buf[2] = (uint8_t)(size&0xff);	//LEN�ĵ�8λ
	pc_tx_buf[3] = SEQ;
	if(SEQ < 255)
		SEQ++;
	else
		SEQ = 0;
	Append_CRC8_Check_Sum(pc_tx_buf,4);			//֡ͷУ��
	pc_tx_buf[5] = (uint8_t)(cmd_id>>8);		//cmd_id�ĸ�8λ
	pc_tx_buf[6] = (uint8_t)(cmd_id&0xff);	//cmd_id�ĵ�8λ
	memcpy(pc_tx_buf+7, tx_buff, size);			//��������
	Append_CRC16_Check_Sum(pc_tx_buf,9+size);			//����У��
	HAL_UART_Transmit(&PC_Uart,pc_tx_buf,size+9,0xffff);	//ʹ��DMA�������ݷ��������⣬�����
}

void Send_Robot_Id(uint16_t id)
{
	uint16_t tx_buff[4];
	tx_buff[0] = 0x03ee;	//��ϢID���ò���ϵͳʱ�����ֵӦ����0x0200��0x02ff֮�䣩
	tx_buff[1] = 0x1001;	//������ID�����ڲ���ϵͳʱ������Ӧ���ǻ�����ID��
	tx_buff[2] = 0x1000;	//������ID�����ڲ���ϵͳʱ������Ӧ���ǻ�����ID��
	tx_buff[3] = id;			//����ʱ������ʵ��ID���������Ӿ������ж���Ӫ��
	PC_Link_Send(0x0301,(uint8_t*)tx_buff,8);
}

void Send_Robot_Data(float shoot_speed, float yaw, float pitch, float roll, float move_speed_x, float move_speed_y, float move_speed_z)
{
	FormatTrans format;
	uint16_t tx_buff[17];
	tx_buff[0] = 0x0301;	//��ϢID���ò���ϵͳʱ�����ֵӦ����0x0200��0x02ff֮�䣩
	tx_buff[1] = 0x1001;	//������ID�����ڲ���ϵͳʱ������Ӧ���ǻ�����ID��
	tx_buff[2] = 0x1000;	//������ID�����ڲ���ϵͳʱ������Ӧ���ǻ�����ID��
	format.F = shoot_speed;
	tx_buff[3] = format.U16[0];		//װ���ӵ���������
	tx_buff[4] = format.U16[1];		//װ���ӵ���������
	format.F = yaw;
	tx_buff[5] = format.U16[0];			//װ��yaw������
	tx_buff[6] = format.U16[1];			//װ��yaw������
	format.F = pitch;
	tx_buff[7] = format.U16[0];			//װ��pitch������
	tx_buff[8] = format.U16[1];			//װ��pitch������
	format.F = roll;
	tx_buff[9] = format.U16[0];			//װ��roll������
	tx_buff[10] = format.U16[1];			//װ��roll������
	format.F = move_speed_x;
	tx_buff[11] = format.U16[0];			//װ��move_speed_x����
	tx_buff[12] = format.U16[1];		//װ��move_speed_x����
	format.F = move_speed_y;
	tx_buff[13] = format.U16[0];		//װ��move_speed_y����
	tx_buff[14] = format.U16[1];		//װ��move_speed_y����
	format.F = move_speed_z;
	tx_buff[15] = format.U16[0];		//װ��move_speed_z����
	tx_buff[16] = format.U16[1];		//װ��move_speed_z����
	
	PC_Link_Send(0x0301,(uint8_t*)tx_buff,34);//���͵�PC
}

//����PC����
void Reset_PC_Data()
{
	obj_data.new_data = 0;
//	uart_printf("pc data reset\r\n");
}

//�Ӿ����ݽ���
void Vision_Data()
{
	FormatTrans format;
	//��ȡ2ά����
	obj_data.x2d = ((uint16_t)pc_rx_buf[13])<<8 | pc_rx_buf[14];	
	obj_data.y2d = ((uint16_t)pc_rx_buf[15])<<8 | pc_rx_buf[16];
	//��ȡ3ά����
	format.U8[0] = pc_rx_buf[20];
	format.U8[1] = pc_rx_buf[19];
	format.U8[2] = pc_rx_buf[18];
	format.U8[3] = pc_rx_buf[17];
	obj_data.x3d = format.F;
	
	format.U8[0] = pc_rx_buf[24];
	format.U8[1] = pc_rx_buf[23];
	format.U8[2] = pc_rx_buf[22];
	format.U8[3] = pc_rx_buf[21];
	obj_data.y3d = format.F;

	format.U8[0] = pc_rx_buf[28];
	format.U8[1] = pc_rx_buf[27];
	format.U8[2] = pc_rx_buf[26];
	format.U8[3] = pc_rx_buf[25];
	obj_data.z3d = format.F;
	
	format.U8[0] = pc_rx_buf[32];
	format.U8[1] = pc_rx_buf[31];
	format.U8[2] = pc_rx_buf[30];
	format.U8[3] = pc_rx_buf[29];
	obj_data.d3d = format.F;
	//��ȡ��̨������Ϣ
	format.U8[0] = pc_rx_buf[36];
	format.U8[1] = pc_rx_buf[35];
	format.U8[2] = pc_rx_buf[34];
	format.U8[3] = pc_rx_buf[33];
	obj_data.yaw = format.F;
	
	format.U8[0] = pc_rx_buf[40];
	format.U8[1] = pc_rx_buf[39];
	format.U8[2] = pc_rx_buf[38];
	format.U8[3] = pc_rx_buf[37];
	obj_data.pitch = format.F;

	//������ȡ��ָ��
	obj_data.new_data =  1;
	obj_data.time = HAL_GetTick();

}

//������֮��Ľ�����Ϣ
void Robot_Msg()
{
	uint16_t msg_id = ((uint16_t)pc_rx_buf[7])<<8 | pc_rx_buf[8];
	uint16_t sender_id = ((uint16_t)pc_rx_buf[9])<<8 | pc_rx_buf[10];
	uint16_t receiver_id = ((uint16_t)pc_rx_buf[11])<<8 | pc_rx_buf[12];
	switch(msg_id)
	{
		case 0x0300://�������Ӿ�����
			if(sender_id == 0x1000 && receiver_id == 0x1001)
				//ȷ�����Ӿ�����
				Vision_Data();	
			break;
		case 0x03ff://������PC���ӷ���
			if(sender_id == 0x1000 && receiver_id == 0x1001)
				//�ܵ�����������Ҫ��ӦPC
				Send_Robot_Id(0x101);//�����������ID�ǴӲ���ϵͳ������ID
			break;
		default:break;
	}
}

//���ݽ���
void Analysis_RX_Buffer()
{
	uint8_t SOF = pc_rx_buf[0];
//	uint16_t LEN = ((uint16_t)pc_rx_buf[1])<<8 | pc_rx_buf[2];
	uint16_t cmd_id = ((uint16_t)pc_rx_buf[5])<<8 | pc_rx_buf[6];
	if(SOF == 0xA5)
	{
			switch(cmd_id)
			{
				case 0x0301:	//�����˽�����Ϣ
					Robot_Msg();
					break;
			default:break;
			}
	}

}

//����6�жϷ�����     
//C��3pin�Ĵ���
//��Ҫ��stm32f4xx_it������ε�
void USART6_IRQHandler(void)
{
	volatile uint8_t receive;
	if(PC_Uart.Instance->SR & UART_FLAG_RXNE)//���յ�����
	{
			__HAL_UART_CLEAR_PEFLAG(&PC_Uart);
	}
	//�����ж�
	if(PC_Uart.Instance->SR & UART_FLAG_IDLE)
	{
		receive = PC_Uart.Instance->DR;	//�ȶ�SR���ٶ�DR������������жϱ�־λ
		HAL_UART_DMAStop(&PC_Uart);			//�ȹر�DMA����
		HAL_UART_Receive_DMA(&PC_Uart,pc_rx_buf,512);//���¿�ʼ���գ�ʹ��DMA��
		Analysis_RX_Buffer();
	}
}

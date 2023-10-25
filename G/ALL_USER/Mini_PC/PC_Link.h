#ifndef PC_LINK_H_
#define PC_LINK_H_

#include "main.h"

#define PC_Uart  huart6

typedef struct
{
	uint8_t new_data;	//��ָ���־
	uint16_t x2d;			//2ά��X���꣬����ԭ����ͼ�����Ͻǣ���λ������
	uint16_t y2d;			//2ά��Y����
	float x3d;				//3ά��X���꣬����ԭ����ǹ�����ģ���λ��cm
	float y3d;				//3ά��Y����
	float z3d;				//3ά��Z����
	float d3d;				//Ŀ��ľ���
	float yaw;				//��̨����Ҫת����yaw��Ƕ�
	float pitch;			//��̨����Ҫת����pitch��Ƕ�
	uint32_t time;		//��ȡ���ݵ�ʱ��
}VISION_DATA;

typedef union{
	uint8_t U8[4];
	uint16_t U16[2];
	uint32_t U32;
	float F;
	int I;
}FormatTrans;

extern VISION_DATA obj_data;

void Send_Robot_Id(uint16_t id);
void Send_Robot_Data(float shoot_speed, float yaw, float pitch, float roll, float move_speed_x, float move_speed_y, float move_speed_z);
void PC_Link_Init(void);
void PC_Link_Send(uint16_t cmd_id,uint8_t *tx_buff,uint16_t size);
void Reset_PC_Data(void);

#endif


#ifndef USER_CAN_H_
#define USER_CAN_H_

#include "main.h"

//#define Yaw_Position_Init 		6400                 //2050
#define Yaw_Position_Init 		5594
#define Pitch_Position_Init 	3300  


//�������ֵת���ɻ���ֵ
#define Motor_Ang_to_Ecd			22.755555555555f				//=8192/360
//�������ֵת���ɻ���ֵ
#define Motor_Ecd_to_Rad 			0.000766990394f 			//=360/8192*��/180

#define CAN1_Motor_NUM  8
#define CAN2_Motor_NUM  8

typedef struct
{
	short Angle;					//��ǰ�Ƕ�
	short Last_Angle;				//��һ�εĽǶ�
	short Speed;					//��ǰ�ٶ�
	short Last_Speed;				//��һ�ε��ٶ�
	short Given_Current;			//�����ǰת�ص���
	uint8_t Temperate;				//����¶�
	short Circle;				    //ת����Ȧ��
	short Angle_Difference;		    //��\1�Ȳ�
	short Angle_Radian;			    //���ٶ�
	int   Continuous_Angle;		    //������
  int   diversity_Angle;           //��С������
	int   Last_Continuous_Angle;    //��һ�ε�������
	uint8_t    Flag;			    //��־λ
}MotorBack;

extern MotorBack CAN1_Motor[CAN1_Motor_NUM];	//CAN1�ϵ����е��������Ϣ

extern MotorBack CAN2_Motor[CAN2_Motor_NUM];	//CAN2�ϵ����е��������Ϣ

extern uint32_t n;

void CAN1_to_Motor(uint16_t id);
void CAN2_to_Motor(uint16_t id);
void CAN1_OPerate_Motor(uint8_t id,short i);
void CAN2_OPerate_Motor(uint8_t id,short i);
void CAN_Filter_Init(void);

#endif


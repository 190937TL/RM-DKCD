#ifndef USER_DBUS_CONTROL_H_
#define USER_DBUS_CONTROL_H_

#include "main.h"

enum chassis_mode
{
	chassis_follow_normol = 0,//0
  chassis_360,							//1
  chassis_wait,   					//2
};

extern float RC_Vx;
extern float RC_Vy;

void Dbus_Control_Init(void);

//��ȡ������ģʽ //���̸���0 	//С����1
uint8_t Read_Robot_mode(void);

//��ȡ���̿���ָ�� ��ȡ���Ƶķ���
void Read_chassis_opt(float *vx,float *vy);

//��ȡ��̨����ָ��
void Read_gimbal_opt(float *pitch, float *yaw);


#endif

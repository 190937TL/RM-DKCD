#ifndef Chassis_H_
#define Chassis_H_

#include "main.h"
#include "User_Pid.h"

//���̵���ٶȻ�PID
#define M3508_Speed_Pid_KP 				2.0f 			//3.0f
#define M3508_Speed_Pid_KI 				0.002f  	//0.002f
#define M3508_Speed_Pid_KD 				0.0f			//0.0f
#define M3508_Speed_Pid_Max_IOUT 	4000.0f 	//2000.0f
#define M3508_Speed_Pid_Max_OUT 	33000.0f	//16000.0f

//���̸���PID
#define Chassis_Follow_Angle_Pid_KP 				18.8f 			//8.8f
#define Chassis_Follow_Angle_Pid_KI 				0.2f  		//0.0f
#define Chassis_Follow_Angle_Pid_KD 				6.0f			//6.0f
#define Chassis_Follow_Angle_Pid_Max_IOUT 	0.0f 			//2000.0f
#define Chassis_Follow_Angle_Pid_Max_OUT 		20000.0f	//16000.0f
//���̸���PID
#define Chassis_Follow_Speed_Pid_KP 				2.4f 			//2.0f
#define Chassis_Follow_Speed_Pid_KI 				0.48f  		//0.4f
#define Chassis_Follow_Speed_Pid_KD 				0.0f			//0.0f
#define Chassis_Follow_Speed_Pid_Max_IOUT 	6000.0f 	//6000.0f
#define Chassis_Follow_Speed_Pid_Max_OUT 		300000.0f	//24000.0f


extern pid_type_def M3508_Speed_Pid[4];
extern float Vx_Input,Vy_Input,W_Iuput;
extern uint16_t RNG_Number;


void Chassis_Init(void);
void Chassis_Out(float I1, float I2, float I3, float I4);
void Chassis_Sleep(void);
void Chassis_Vector_To_Mecanum_Wheel_Speed(const float vx_set, const float vy_set, const float wz_set);
float Chassis_Follow(float except);
void Chassis_Control(void);

typedef struct
{
	float Chassis_Key_Vx;
	float Chassis_Key_Vy;
	float Chassis_W;
	float M3508_Speed_Max;
	uint16_t Shoot_Speed;
} Robot_Grade_T;

typedef struct
{
	uint16_t Red_1_Robot_HP;										//�� 1 Ӣ�ۻ�����Ѫ����δ�ϳ��Լ�����Ѫ��Ϊ 0
	uint16_t Red_2_Robot_HP;										//�� 2 ���̻�����Ѫ��
	uint16_t Red_3_Robot_HP;        						//�� 3 ����������Ѫ��
	uint16_t Red_4_Robot_HP;       					 		//�� 4 ����������Ѫ��
	uint16_t Red_5_Robot_HP;      					  	//�� 5 ����������Ѫ��
	uint16_t Red_7_Robot_HP;       					 		//�� 7 �ڱ�������Ѫ��
	uint16_t Red_Outpost_HP;										//�췽ǰ��սѪ��
	uint16_t Red_Base_HP;         					  	//�췽����Ѫ��
	uint16_t Blue_1_Robot_HP;    					   		//�� 1 Ӣ�ۻ�����Ѫ��
	uint16_t Blue_2_Robot_HP;    					   		//�� 2 ���̻�����Ѫ��
	uint16_t Blue_3_Robot_HP;     					  	//�� 3 ����������Ѫ��
	uint16_t Blue_4_Robot_HP;     					 	 	//�� 4 ����������Ѫ��
	uint16_t Blue_5_Robot_HP;      					 		//�� 5 ����������Ѫ��
	uint16_t Blue_7_Robot_HP;       						//�� 7 �ڱ�������Ѫ��
	uint16_t Blue_Outpost_HP;										//����ǰ��վѪ��
  uint16_t Blue_Base_HP;         							//��������Ѫ��
	
	uint8_t Robot_ID;           								//�������� ID
	uint8_t Robot_Level;												//�����˵ȼ�
	uint16_t Remain_HP;													//������ʣ��Ѫ��
	uint16_t Max_HP;														//����������Ѫ��
	uint16_t Shooter_ID1_17mm_Cooling_Rate; 		//������ 1 �� 17mm ǹ��ÿ����ȴֵ
	uint16_t Shooter_ID1_17mm_Cooling_Limit;		//������ 1 �� 17mm ǹ����������
	uint16_t Shooter_ID1_17mm_Speed_Limit;			//������ 1 �� 17mm ǹ�������ٶ� ��λ m/s
	uint16_t Shooter_ID2_17mm_Cooling_Rate;			//������ 2 �� 17mm ǹ��ÿ����ȴֵ
	uint16_t Shooter_ID2_17mm_Cooling_Limit;    //������ 2 �� 17mm ǹ����������
	uint16_t Shooter_ID2_17mm_Speed_Limit;      //������ 2 �� 17mm ǹ�������ٶ� ��λ m/s
	uint16_t Shooter_ID1_42mm_Cooling_Rate;     //������ 42mm ǹ��ÿ����ȴֵ
	uint16_t Shooter_ID1_42mm_Cooling_Limit;    //������ 42mm ǹ����������
	uint16_t Shooter_ID1_42mm_Speed_Limit;      //������ 42mm ǹ�������ٶ� ��λ m/s
	uint16_t Chassis_Power_Max;									//�����˵��̹�����������
	uint8_t Mains_Power_Gimbal_Output : 1;			//���ص�Դ������
	uint8_t Mains_Power_Chassis_Output : 1;			//���ص�Դ������
	uint8_t Mains_Power_Shooter_Output : 1;			//���ص�Դ������
	
	float Chassis_Power;                        //����������� ��λ W ��
	uint16_t Chassis_Power_Buffer;              //���̹��ʻ��� ��λ J ���� ��ע�����¸��ݹ��������� 250J
	uint16_t Shooter_ID1_17mm_Cooling_Heat;     //1 �� 17mm ǹ������
	uint16_t Shooter_ID2_17mm_Cooling_Heat;     //2 �� 17mm ǹ������
	uint16_t Shooter_ID1_42mm_Cooling_Heat;     //42mm ǹ������
	
	uint8_t Bullet_Freq;												//�ӵ���Ƶ ��λ Hz
	float Bullet_Speed;													//�ӵ����� ��λ m/s
	
	uint8_t	Cap_Voltage;
} Judge_User_T;

extern Robot_Grade_T	Robot_Grade;
extern Judge_User_T	Judge_User;

#endif



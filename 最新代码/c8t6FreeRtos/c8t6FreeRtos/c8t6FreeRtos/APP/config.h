#ifndef __CONFIG_H
#define __CONFIG_H
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include <stdio.h>
#include <stdbool.h>
#include "cmsis_os.h"
#include "FreeRTOS.h" 
#include "task.h"
#include "flash.h"
//#include "wifi.h"
#include "crc.h"
#include <time.h>

#pragma pack(1)

//#define DEV_ID "SQLS210300002"

/****************************��������ݰ�ͷ��β**************************/
typedef enum{
	TABLE_HEAD = 0XA0, 
	TABLE_TAIL = 0XA1,
	TO_APP_HEAD = 0xA2,
	TO_APP_TAIL = 0xA3,
	_485_CMD_HEAD = 0xA4,
	_485_CMD_TAIL = 0xA5,
	WIFI_SSID_HEAD = 0xA6,
	WIFI_SSID_TAIL = 0xA7,
	TIME_TAMP_HEAD = 0xA8,
	TIME_TAMP_TAIL = 0xA9,
	CHANGE_ID_HEAD = 0XAA,
  CHANGE_ID_TAIL = 0XAB,
  GET_DEV_STATUS_HEAD = 0XB1,
	GET_DEV_STATUS_TAIL = 0XB2,
	GET_NET_TIME_HEAD = 0XB3,
	GET_NET_TIME_TAIL = 0XB4,
	GET_AIR_CODE_HEAD   =   0xB5,
	GET_AIR_CODE_TAIL   =   0xB6,
}HEAD_TAIL_CMD;

typedef struct{
bool enable;
bool wif_conect_status;
char wifi_con[50];
char mqtt_con[60];
char mqtt_pub[100];
char mqtt_sub[100];
char name[25];
char pasw[25];
char id[200];
}WIFI_CFG_Typedef;

/*****************************һ �·�����Ƭ���ı� ***************************/
  /*(һ).���������������*/
    /*1.����������(������ݸ�ʽ)(8��)*/

		typedef struct{
			time_t  time_sta;
			uint8_t min_len;
		}SET_BREATH_TypeDef;
	   
	/*2.����������(������ݸ�ʽ)(4��)*/
		typedef struct{
			time_t  time_sta;
			uint8_t min_len;
		}SET_STERILIZE_TypeDef;
	/*3.���ղ�����(������ݸ�ʽ))(3��)*/
		typedef struct{
			time_t  time_sta;
			time_t  time_end;
		}SET_LIGHT_TypeDef;
	/*4.��ʪ���趨��(������ݸ�ʽ)))(1��)//����һλС��*/
		typedef struct{
			uint16_t temp_center;
			uint16_t temp_diff;
			uint16_t humi_center;
			uint16_t humi_diff;
		}SET_SENSOR_Type;
	/*5.�й������(������ݸ�ʽ)(3��)*/
		typedef struct{
			time_t  time_sta;
			time_t  time_end;
		}SET_SENSITIVE_TypeDef;
	/*6.������У׼ֵ(������ݸ�ʽ)(4��)//����һλС��*/
		typedef struct{
			int16_t temp_adjust;
			int16_t humi_adjust;	
		}SET_SENSOR_DIFF_TypeDef;
/******************************	(��).ͳһ������������� **************************/ 
     typedef struct{
		HEAD_TAIL_CMD head;
		char id[20];
		SET_BREATH_TypeDef set_breath[8];
		SET_STERILIZE_TypeDef set_sterilize[4];
		SET_LIGHT_TypeDef set_light[3];
		SET_SENSOR_Type  set_sensor[1];
		SET_SENSITIVE_TypeDef set_sensitive[3];
		SET_SENSOR_DIFF_TypeDef set_senser_diff[6];
		uint8_t set_wind_temp_diff; 
		HEAD_TAIL_CMD tail;
		uint16_t crc;
	 }UPDATE_ALL_TABLE_TYPEDEF;
	 
	 /***pc�˺�����˺ʹ������������һ�����浽flah����ȫ������***/
	 
	 
	 
/*************************************** ��  ������������ʪ�ȡ�����״̬����Ϣ��pc��:****************************************/
  /*(һ)�����������������*/
   /* 1.����״̬�ṹ��*/
        typedef struct{
			uint8_t heat:1;
			uint8_t humi:1;
			uint8_t dry:1;
			uint8_t breath:1;
			uint8_t wind:1;
			uint8_t light:1;//����״̬
			uint8_t sterilize:1;//����״̬
			uint8_t sensitive:1;//�й�״̬
		}RELAY_Typedef;
	/*2.�յ�״̬ö��	*/
		typedef enum {
			AIR_CLOSE = 0,
			AIR_HEAT = 1,
			AIR_COLD = 2,
		}AIR_STATUS;
		
	/*3.��������������*/
			 typedef enum{
				SENSER_OK = 0,
				SENSER_DIS_CON = 1,
				SENSER_FAIL = 2,
			}SENSER_STATUS;
			 
	    typedef struct{
		  uint16_t single_temp;
		  uint16_t signle_humi;
			SENSER_STATUS senser_status;
		}SINGLE_SENSER_Typedef;
 /*(��)�����������շ��͸�����*/		
		typedef union {
			RELAY_Typedef relay;
			uint8_t relay_vale;
		}RELAY;
		typedef struct{
		    HEAD_TAIL_CMD head;      
			char id[20];
			uint16_t temp;
			uint16_t humi;
      SET_SENSOR_Type now_sensor;
			SET_LIGHT_TypeDef next_light;
			SET_BREATH_TypeDef next_breath;
			SET_STERILIZE_TypeDef next_sterilize;
			SET_SENSITIVE_TypeDef next_sensitive;//�й�
			SINGLE_SENSER_Typedef signle_senser[6];
			AIR_STATUS air_status;
			RELAY relay_status;
			HEAD_TAIL_CMD tail;
			uint16_t crc;
		}TO_APP_Typedef;

		
	
/***********************************��  485-������ָ�����ݸ�ʽ: ************************************/
	typedef enum{
				GET_WIFI_SCAN = 0,//����wifiɨ��ָ��
				WIFI_CON_STA,//����wifi
				WIFI_CON_STOP,//�Ͽ�wifi
				WIFI_CON_OK,//����pc��wifi���ӳɹ�
				WIFI_CON_FAIL,//����ʧ��
				_4G_CON_STA,//����4G
				_4G_CON_OK,//����4G OK
				_4G_CON_FAIL,//����4G ʧ��
				AIR_HEAT_LEARN_STA,//��ʼ�յ�����ѧϰ
				AIR_HEAT_LEARN_END,//�����յ�����ѧϰ
				AIR_CLOD_LEARN_STA,//��ʼ�յ�����ѧϰ
				AIR_CLOD_LEARN_END,//�����յ�����ѧϰ
				AIR_CLOSE_LEARN_STA,//��ʼ�յ��ر�ѧϰ
				AIR_CLOSE_LEARN_END,//�����յ��ر�ѧϰ
				DEV_ALIVE_PACK,//PC�˷���������
				DEV_ALIVE_PACK_BACK,//�豸�˻�Ӧ������
		    GET_DEV_TABLE,//pc�˻�ȡ�豸��
			}__485_CMD_;
    /*1.pc�����豸�˵ļ���ָ���ʽ:*/
		typedef struct{
			HEAD_TAIL_CMD head;
			char id[20];
			__485_CMD_ cmd;
			HEAD_TAIL_CMD tail;
			uint16_t crc;
		}__485_CMD_Type;
        
    /*2.pc�����豸����wifi���˺ź�����:*/
		typedef struct{
			HEAD_TAIL_CMD head;
			char id[20];
			char name[30];
			char pass[30];
			HEAD_TAIL_CMD tail;
			uint16_t crc;
		}SEND_WIFI_DATA_Type;
	 /*3.pc�����豸����ʱ���:*/
		typedef struct{
			HEAD_TAIL_CMD head;
			uint32_t time_tamp;
			HEAD_TAIL_CMD tail;
			uint16_t crc;
		}SEND_TIME_TAMP_Type;
		
		
	 
	/***************************��ǰ����ʱ��*************************/ 
	 typedef struct{
		  HEAD_TAIL_CMD head;      
			uint8_t year;
		  uint8_t month;
		  uint8_t day;
		  uint8_t hour;
		  uint8_t minute;
		  uint8_t second;
		  uint8_t weekday;
			HEAD_TAIL_CMD tail;
			uint16_t crc;
	 }NET_TIME;

/***************************��ǰʱ��ʱ���*************************/
typedef struct{
uint32_t time_date_stamp;
uint32_t oneday_time_stamp;
}NOW_TIME_STAMP_Typedef;

/*********************���ڽ������ϰ�********************/
#define USARTx_RCV_MAX_LEN 300
typedef struct{
uint8_t ptr;
uint8_t arry[USARTx_RCV_MAX_LEN];
uint8_t count;
bool rcv_ok;
}USARTx_RCV_Typedef;

#define USART1_RCV_MAX_LEN 1000
typedef struct{
uint8_t ptr;
uint8_t arry[USART1_RCV_MAX_LEN];
uint16_t count;
bool rcv_ok;
}USART1_RCV_Typedef;

/******************�����������趨********************/
typedef enum{
READ_DATA = 0X03,
WRITE_ADDR = 0X06
}SHT30_CMD;

typedef enum{
SENSOR_ID = 0X01,
READ_TEMP_ADDR = 0X0002,
READ_HUMI_ADDR = 0X0001,
WRITE_DEV_ADDR = 0X0066
}SHT30_ADDR;
typedef struct{
uint8_t status;
uint8_t id;
uint32_t temp;
uint32_t humi;
}TEMP_HUMI_TypeDef;

typedef struct{
float temp;
float humi;
}LOCAL_TEMP_HUMI_TypeDef;

typedef struct{
uint8_t id;
uint8_t cmd;
uint8_t data_len;
short temp;
short humi;
uint16_t crc;
}RSHT30_READ_TypeDef;


typedef struct{
uint8_t id;
uint8_t cmd;
uint16_t addr;
uint16_t data_len;
uint16_t crc;
}SHT30_WRITE_TypeDef;

/********************��ȡ���֡�����������״̬�ṹ��*************************/
typedef enum{
BAOZHONG_STA = 0X00,
BAOZHONG_END = 0X01,
GONGYU_STA = 0X02,
GONGYU_END = 0X03,
CUIQING_STA = 0X04,
CUIQING_END = 0X05,
}WORK_WAY_STATUS;   
typedef struct{
HEAD_TAIL_CMD head;      
char id[20];
WORK_WAY_STATUS work_status;
uint16_t reasure_count;	
HEAD_TAIL_CMD tail;
uint16_t crc;
}WORK_WAY_TYEP; 
		
/**********���Ƹ����ܵľ���ṹ*************/	
typedef struct{
uint8_t id;
AIR_STATUS air;
RELAY   relay;
uint16_t crc;
}TO_MCU_Typedef;

typedef struct {
	uint16_t len;
	uint16_t data[400];
}AIR_SAVE_TYPE;

typedef struct{
    uint8_t head;
    uint16_t air;
    AIR_SAVE_TYPE data;
    uint8_t tail;
    uint16_t crc;
}AIR_SAVE_CODE_TYPE;
#pragma pack()
/**********�յ�ѧϰ״̬�ṹ******/
typedef struct{
bool air_close_learn_status;
bool air_heat_learn_status;
bool air_clod_learn_status;
}AIR_LEARN_STATUS;

extern UPDATE_ALL_TABLE_TYPEDEF  all_table_data;
extern TO_APP_Typedef to_app;
extern NOW_TIME_STAMP_Typedef now_time_stamp;

typedef enum{
IS_AUTO_MODE = 0,
IS_HAND_MODE = !IS_AUTO_MODE, 	
} LCD_WORK_MODE;  
typedef struct{
bool pc_to_mcu_trig;
bool net_to_mcu_trig;
bool lcd_to_mcu_trig;
bool mcu_to_pc_trig;
bool mcu_to_net_trig;
bool mcu_to_lcd_trig;
bool net_trig;
bool write_flash;
bool get_pc_heart;
bool mcu_send_to_app_to_pc;
bool wifi_con;
bool get_wifi_ok;
bool get_wifi_new_con;  
bool senser_is_ok;  
bool pc_wifi_con;   
bool change_id;
bool pc_change_work_status; 
bool net_change_work_status; 
bool update_net_time_trig;
bool update_net_trig_send;
bool lcd_id_mcu;
bool mcu_id_lcd;
bool wifi_pc_mode;
bool lcd_id_recover;
LCD_WORK_MODE lcd_work_mode;   
AIR_LEARN_STATUS pc_air_learn;
AIR_LEARN_STATUS lcd_air_learn;

}TABBLE_TRIG;

/**********************flash�洢wifi�͹���ģʽ************************/
typedef struct{
WIFI_CFG_Typedef wifi_cfg;
WORK_WAY_TYEP work_way_status;  
}FLASH_STORE;


/***************�������ݸ�ʽ**********************/
typedef enum {
	RES_OK = 0,
	RES_FAIL,
	RES_INVALID_PARA,
	RES_NO_SPACE
} ResultStatus;

typedef enum {
	STUDY_ORDER = 0,
	EXIT_ORDER,
	SEND_ORDER,
	RECV_ORDER,
	TEN_MS_ORDER,
} OrderEnum;

#define MAXSIZE 					5

typedef struct {
	uint8_t type;
	uint8_t nc;
	uint32_t para1;
} ElemType;

typedef struct{
	ElemType data[MAXSIZE];
	int front;
	int rear;
} Sequeue;

#define MAX_CODE_LENGTH			400

typedef struct {
	uint8_t valid;
	uint8_t nc;
	uint16_t len;
	uint16_t data[MAX_CODE_LENGTH];
} IrCode;



typedef struct {
	IrCode *ir;
} App;


typedef struct{
	bool isDetect;
	bool isSend;
	uint16_t pre_temp;
	uint32_t Ctime;
	uint8_t excute_air;
}INFRA_DETECT;


extern TABBLE_TRIG table_update_trig;


//typedef enum{
//IS_IDEL = 0,
//IS_BUSY = 1,
//}TASK_WRITE_FLAG;
//extern TASK_WRITE_FLAG task_write_flag;


extern UPDATE_ALL_TABLE_TYPEDEF download_update_table ;

extern USART1_RCV_Typedef usart1_rcv;
extern USARTx_RCV_Typedef usart2_rcv;
extern USARTx_RCV_Typedef usart3_rcv;


extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

extern IWDG_HandleTypeDef hiwdg;

extern AIR_LEARN_STATUS air_learn_status;
extern AIR_LEARN_STATUS air_learn_ok_status;
extern TO_MCU_Typedef mcu_control_data;
extern TO_APP_Typedef to_app;
extern __485_CMD_Type __485_send_cmd;
extern uint32_t get_tamp;
extern WORK_WAY_TYEP work_way_status; 
extern FLASH_STORE flash_store;
extern WIFI_CFG_Typedef wifi_cfg;
extern NET_TIME net_time;


extern INFRA_DETECT infraDetect;
extern AIR_SAVE_TYPE save_data;

/***************************���ü̵����˿�����***************************/
#define HEAT_PORT          GPIOB //����
#define HUMI_PORT          GPIOB //��ʪ
#define BREATH_PORT        GPIOB //����
#define SENSITIVE_PORT     GPIOB //�й�
#define WIND_PORT          GPIOB //�ȷ�
#define STERILIZE_PORT     GPIOA //����

#define LIGHT_PORT         GPIOA //����

#define DRY_PORT           GPIOA //��ʪ

#define WIFI_RST_PORT      GPIOB
#define WIFI_EN_PORT       GPIOB
#define IO0_EN_PORT        GPIOC
#define IO2_EN_PORT        GPIOC

 
#define HEAT_PIN           GPIO_PIN_7  //����
#define HUMI_PIN           GPIO_PIN_6  //��ʪ
#define BREATH_PIN         GPIO_PIN_5  //����
#define SENSITIVE_PIN      GPIO_PIN_4 //�й�
#define WIND_PIN           GPIO_PIN_3 //�ȷ�
#define STERILIZE_PIN      GPIO_PIN_15 //����

#define LIGHT_PIN          GPIO_PIN_12 //����

#define DRY_PIN            GPIO_PIN_11 //��ʪ

#define WIFI_RST_PIN       GPIO_PIN_0 
#define WIFI_EN_PIN        GPIO_PIN_1
#define IO0_EN_PIN         GPIO_PIN_15
#define IO2_EN_PIN         GPIO_PIN_14

#define LED_PORT GPIOA
#define LED_PIN	 GPIO_PIN_8 

#define LED_ON	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET)
#define LED_OFF	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET)

#define LED_Toggle			HAL_GPIO_TogglePin(LED_PORT, LED_PIN)

#define INS_LED_PORT	GPIOC
#define INS_LED_PIN		GPIO_PIN_13

#define wifi_LED_PORT	  GPIOA
#define wifi_LED_PIN		GPIO_PIN_0



#define INS_LED_ON	HAL_GPIO_WritePin(INS_LED_PORT, INS_LED_PIN, GPIO_PIN_RESET)
#define INS_LED_OFF	HAL_GPIO_WritePin(INS_LED_PORT, INS_LED_PIN, GPIO_PIN_SET)

#define LED_Toggle			HAL_GPIO_TogglePin(LED_PORT, LED_PIN)
//App������ʼ��
App *AppInit(void);

//��ȡ������
App *GetApp(void);

#endif

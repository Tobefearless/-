#ifndef __MODBUS_H
#define __MODBUS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "get_temp.h"
#include "relay.h"
#include "config.h"
#include "wifi.h"

#pragma pack(1)


//时间结构体，
typedef struct{
uint32_t time_start_addr;  //时间开始地址
uint32_t time_end_addr;		 //时间结束地址
}TIME_SHOW_ADDR;


//传感器显示地址
typedef struct{
uint32_t sensor_id_addr;								//传感器ID地址
uint32_t sigle_sensor_temp_addr;				//传感器温度地址
uint32_t sigle_sensor_humi_addr;				//传感器湿度地址
uint32_t sigle_sensor_adjust_temp_addr;	//传感器温度校准值地址
uint32_t sigle_sensor_adjust_humi_addr;	//传感器湿度校准值地址
}SENSOR_SHOW_ADDR;


//TXT文本显示结构体
typedef struct{
uint8_t head;					//头
uint16_t fun_cmd;			//功能码
uint32_t addr;				//地址
char data[20];				//数据
uint32_t tail;				//尾
}TXT_SEND_Typedef;

//TXT发送文本命令
typedef struct{
uint8_t head;					//头
uint16_t fun_cmd;			//功能码
uint32_t addr;				//地址
uint32_t tail;				//尾
}TXT_SEND_CMD_Typedef;

//读TXT文本结构体
typedef struct{
uint8_t head;					//头
uint16_t fun_cmd;			//功能码
uint32_t addr;				//地址
char data[30];				//数据
uint32_t tail;				//尾
}TXT_READ_Typedef;


//HEX发送结构体
typedef struct{
uint8_t head;				//头
uint16_t fun_cmd;		//功能码
uint32_t addr;			//地址
uint8_t data;				//数据
uint32_t tail;			//尾
}HEX_SEND_Typedef;

//hex发送命令码
typedef struct{
uint8_t head;					//头
uint16_t fun_cmd;			//功能码
uint32_t addr;				//地址
uint32_t tail;				//尾
}HEX_SEND_CMD_Typedef;


//读hex结构体
typedef struct{
uint8_t  head;				//头
uint16_t fun_cmd;			//功能码
uint32_t addr;				//地址
uint8_t  data[3];			//数据
uint32_t tail;				//尾
}HEX_READ_Typedef;

#pragma pack()


/*************************业务处理部分****************************/

//屏幕显示处理
void deal_lcd_show(void);
//将日期时间变为时间戳
time_t dateTime_to_secs(char* dataTime);
//将时间变为秒数
time_t time_to_secs(char* time);
//秒数变为日期时间
char* secs_to_dateTime(time_t secs);
//将秒数变为日期
char* secs_to_date(time_t secs);
//将秒数转换为时间
char* secs_to_time(time_t secs);


//继电器状态结构体
typedef enum{
SWITCH_CLOSE = 0,
SWITCH_OPEN = 1,
NO_DATA = 0XFF,
}SWITCH_STATUS;


#define HEAD  0xEE
#define TAIL  0XFFFCFFFF


typedef enum{
TXT_WRITE_FUN_CMD = 0XB110,		//单片机以文本格式向lcd写数据的功能码
TXT_GET_FUN_CMD = 0XB111,  		//单片机向lcd发送指令获取它文本信息的功能码
TXT_READ_FUN_CMD  = 0XB111,		//lcd发送到单片机数据的文本信息功能码
HEX_WRITE_FUN_CMD = 0XB110,		//单片机以控件格式向lcd写数据的功能码
HEX_GET_FUN_CMD = 0XB111,  		//单片机向lcd发送指令获取它控件信息的功能码
HEX_READ_FUN_CMD  = 0XB111,   //lcd发送到单片机数据的控件信息功能码
HEX_ICONWRITE_FUN_CMD=0XB123, //单片机以图标控件格式向LCD写功能码
}FUN_CMD_Typedef;


/**************以下为各控件的地址(页码和地址绑定的总地址4字节)*************/
typedef enum{
	
/*****************主页文本**************************/
SAVE_DEV_ID_ADDR 							= 0x00140001,			//屏幕存储ID地址
DEV_ID_ADDR 		 							= 0x00000002,						//设备id存储
TEMP_ADDR 			 							= 0x00000004,             //温度值
HUMI_SETTING_ADDR 						= 0x00000005,     //湿度值
TEMP_CENTER_ADDR							= 0x00002710,        //温度中心值
	
TEMP_HOME_CENTER_ADDR					= 0x0000001E,        //主页温度中心值
HUMI_HOME_CENTER_ADDR					= 0x0000001F,        //主页湿度中心值
	
	
	
TEMP_DIFF_ADDR								= 0x000d0005,					//温度回差值
HUMI_CENTER_ADDR							= 0x00002711,			//湿度中心值
HUMI_DIFF_ADDR								= 0x000d0006,				//湿度回差值
UNIFORM_RETURN_DIFFERENCE_ADDR= 0x000D0007,//匀风回差值
LIGHT_START_ADDR							= 0x00000017,				//下次光照时间开始
LIGHT_END_ADDR								= 0x00000018,					//下次光照时间结束
AERATION_START_ADDR						= 0x00000011,			//下次换气开始时间
AERATION_END_ADDR							= 0x00000012,				//下次换气运行时间
STERILIZE_START_ADDR					= 0x00000015,		//下次消毒开始时间
STERILIZE_TIME_ADDR						= 0x00000016,			//下次消毒运行时间
SENSITIVE_START_ADDR					= 0x00000013,		//下次感光开始时间
SENSITIVE_TIME_ADDR						= 0x00000014,			//下次感光运行时间
	
DEV_WORK_STATUS_TXT_ADDR 			= 0X00000010,//自动控制运行模式文本 
DEV_WORK_STATUS_STATUS_ADDR 	= 0X0000000f,//自动控制运行模式图标

/******************主页图标*************************/
AIR_STATUS_ADDR								= 0x00000006,       //空调状态
HEAT_STATUS_ADDR							= 0x00000007,      //加热状态
HUMI_STATUS_ADDR							= 0x00000008,      //补湿状态
AERATION_STATUS_ADDR					= 0x00000009,  //换气状态
WIN_STATUS_ADDR								= 0x0000000A,       //匀风状态
SENSITIVE_STATUS_ADDR					= 0x0000000B, //感光状态
STERILIZE_STATUS_ADDR					= 0x0000000C, //消毒状态
LIGHT_STATUS_ADDR							= 0x0000000D,     //光照状态
DRY_STATUS_ADDR								= 0x0000000E,       //除湿状态
WIFI_STATUS_ADDR							= 0x00000003,      //wif连接状态

/******************设置*************************/
AERATION_ADDR 								= 0x00070002,					//换气
LIGHE_ADDR 										= 0x00070003,						//光照
SENSITIVE_ADDR 								= 0x00070003,				//感光
STERILIZE_ADDR 								= 0x00060005,				//消毒
SENSOR_ADDR 									= 0x00070007,				    //传感器校准
WIFI_NAME_ADDR 								= 0x00100002,			  //wifi账号地址
WIFI_PASSWD_ADDR 							= 0x00100003,		  //wifi密码地址
WIFI_CONNECT_ADDR 						= 0x00100005,		  //wifi连接状态地址

AIR_LEARN_OK_ADDR 						= 0x000E0005,	    //空调学习状态
SAVE_ALL_ADDR 								= 0x00070001,	        //保持所以控件的地址
ID_RECOVER_ADDR								= 0x000D000C,			//ID恢复
/******************空调学习*********************************/
HEATED_LEARNING_ADDR 					= 0x000E0002,  //空调加热学习
REFRIGERATION_LEARNING_ADDR  	= 0x000E0003,   //空调制冷学习
CLOSE_LEARNING_ADDR 					= 0x000E0004,  //空调关闭学习


/***********************换气参数周期****************/
FIRST_AERATION_START_ADDR			= 0x00082714,  //第一次换气开始
FIRST_AERATION_TIME_ADDR			= 0x00082715,	 //第一次运行时间
SECOND_AERATION_START_ADDR		= 0x00082716, //第二次换气开始 
SECOND_AERATION_TIME_ADDR			= 0x00082717,  //第二次运行时间
THIRD_AERATION_START_ADDR			= 0x00082718,  //第三次换气开始  
THIRD_AERATION_TIME_ADDR			= 0x00082719,   //第三次运行时间
FOURTH_AERATION_START_ADDR		= 0x0008271A, //第四次换气开始  
FOURTH_AERATION_TIME_ADDR			= 0x0008271B,  //第四次运行时间
FIFTH_AERATION_START_ADDR			=	0x0008271C,  //第五次换气开始   
FIFTH_AERATION_TIME_ADDR			=	0x0008271D,   //第五次运行时间
SIXTH_AERATION_START_ADDR			=	0x0008271E,  //第六次换气开始 
SIXTH_AERATION_TIME_ADDR			= 0x0008271F,   //第六次运行时间
SEVENTH_AERATION_START_ADDR		=	0x00082720,//第七次换气开始  
SEVENTH_AERATION_TIME_ADDR		=	0x00082721, //第七次运行时间
EIGHTH_AERATION_START_ADDR		=	0x00082722, //第八次换气开始  
EIGHTH_AERATION_TIME_ADDR			=	0x00082723,  //第八次运行时间

/********************感光参数周期*******************/
FIRST_SENSITIVE_START_ADDR		=	0x00092726,     //第一次感光开始时间
FIRST_SENSITIVE_END_ADDR			=	0x00092727,       //第一次感光结束时间
SECOND_SENSITIVE_START_ADDR		=	0x00092728,	   //第二次感光开始时间
SECOND_SENSITIVE_END_ADDR			=	0x00092729,		   //第二次感光结束时间
THIRD_SENSITIVE_START_ADDR		=	0x0009272A,		 //第三次感光开始时间
THIRD_SENSITIVE_END_ADDR			=	0x0009272B,			 //第三次感光结束时间

/********************光照参数周期*******************/
FIRST_LIGHT_START_ADDR				=	0x000A272C,     //第一次光照开始时间
FIRST_LIGHT_END_ADDR					=	0x000A272D,       //第一次光照结束时间
SECOND_LIGHT_START_ADDR				=	0x000A272E,	   //第二次光照开始时间
SECOND_LIGHT_END_ADDR					=	0x000A272F,		   //第二次光照结束时间
THIRD_LIGHT_START_ADDR				=	0x000A2730,		 //第三次光照开始时间
THIRD_LIGHT_END_ADDR					=	0x000A2731,			 //第三次光照结束时间

/**********************消毒参数周期*****************/
FIRST_STERILIZE_START_ADDR		=	0x000B2732, //第一次消毒开始时间
FIRST_STERILIZE_END_ADDR			=	0x000B2733,   //第一次消毒运行时间
SECOND_STERILIZE_START_ADDR		=	0x000B2734,//第二次消毒开始时间
SECOND_STERILIZE_END_ADDR			=	0x000B2735,  //第二次消毒运行时间
THIRD_STERILIZE_START_ADDR		=	0x000B2736, //第三次消毒开始时间
THIRD_STERILIZE_END_ADDR			=	0x000B2737,   //第三次消毒运行时间
FOURTH_STERILIZE_START_ADDR		=	0x000B2738,//第四次消毒开始时间
FOURTH_STERILIZE_END_ADDR			=	0x000B2739,  //第四次消毒运行时间

/******************温湿度传感器校准****************/
FIRST_SENSOR_ADDR							=	0x000C273A,											  //第一个传感器地址
FIRST_REAL_TIME_TEMP_VALUE_ADDR=0x000C273B,				  //第一个传感器实时温度值
FIRST_REAL_TIME_HUMI_VALUE_ADDR=0x000C273C,				  //第一个传感器实时湿度值
FIRST_TEMP_CALIBRATION_VALUE_ADDR=0x000C273D,       //第一个传感器温度校准值           
FIRST_HUMI_CALIBRATION_VALUE_ADDR=0x000C273E,       //第一个传感器湿度校准值  
SECOND_SENSOR_ADDR=0x000C273F,											//第二个传感器地址
SECOND_REAL_TIME_TEMP_VALUE_ADDR=0x000C2740,				//第二个传感器实时温度值
SECOND_REAL_TIME_HUMI_VALUE_ADDR=0x000C2741,				//第二个传感器实时湿度值
SECOND_TEMP_CALIBRATION_VALUE_ADDR=0x000C2742,      //第二个传感器温度校准值           
SECOND_HUMI_CALIBRATION_VALUE_ADDR=0x000C2743,      //第二个传感器湿度校准值   
THIRD_SENSOR_ADDR=0x000C2744,											  //第三个传感器地址
THIRD_REAL_TIME_TEMP_VALUE_ADDR=0x000C2745,				  //第三个传感器实时温度值
THIRD_REAL_TIME_HUMI_VALUE_ADDR=0x000C2746,				  //第三个传感器实时湿度值
THIRD_TEMP_CALIBRATION_VALUE_ADDR=0x000C2747,       //第三个传感器温度校准值           
THIRD_HUMI_CALIBRATION_VALUE_ADDR=0x000C2748,       //第三个传感器湿度校准值   
FOURTH_SENSOR_ADDR=0x000C2749,											//第四个传感器地址
FOURTH_REAL_TIME_TEMP_VALUE_ADDR=0x000C274A,				//第四个传感器实时温度值
FOURTH_REAL_TIME_HUMI_VALUE_ADDR=0x000C274B,				//第四个传感器实时湿度值
FOURTH_TEMP_CALIBRATION_VALUE_ADDR=0x000C274C,      //第四个传感器温度校准值           
FOURTH_HUMI_CALIBRATION_VALUE_ADDR=0x000C274D,      //第四个传感器湿度校准值   

/***********手动控制控件地址***********************/
MANUAL_AIR_CONDITIONING_ADDR=0x00110002,//空调控件
MANUAL_HEATING_ADDR=0x00110003,					//加热控件
MANUAL_FILL_WET=0x00110004,							//补湿控件
MANUAL_FOR_AIR_ADDR=0x00110005,         //换气控件
MANUAL_SENSITIVE_ADDR=0x00110006,       //感光控件
MANUAL_AND_THE_WIND_ADDR=0x00110007,		//匀风控件
MANUAL_LIGHT_ADDR=0x00110008,						//光照控件
MANUAL_STERILIZE_ADD=0x00110009,		    //消毒控件
MANUAL_DRY_ADDR=0x0011000A,             //除湿控件

RETURN_ADDR=0x0000001B,									//手动、自动模式控件

/***********屏幕修改id地址***********************/
LCD_CHANGE_ID_ADDR=0x00140002,
ID_CHANGE_OK_ADDR = 0x00140004
}ADDR_Typedef;


void write_txt_data(uint16_t write_fun_cmd,uint32_t addr, char* data);
char* read_txt_data(uint16_t get_fun_cmd,uint16_t read_fun_cmd,uint32_t addr);
void write_hex_data(uint16_t write_fun_cmd,uint32_t addr, uint8_t data);
SWITCH_STATUS read_hex_data(uint16_t get_fun_cmd, uint16_t read_fun_cmd, uint32_t addr);
time_t read_local_time(void);
void set_default_parameters(char *id);
void write_id_data(void);
void write_id_data1(void);
/*************************************************************************************************
**                                                                                              **
**                                                                                              **
******************************以下类型直接以文本格式发送数据到lcd*********************************
**																																															**
**																																															**
*************************************************************************************************/

/***************************** 更改lcd主页文本***********************/
#define devid_to_lcd_txt(id) write_txt_data(TXT_WRITE_FUN_CMD, DEV_ID_ADDR, id)     //显示设备ID
#define temp_to_lcd_txt(temp) write_txt_data(TXT_WRITE_FUN_CMD, TEMP_ADDR, temp)         //温度值
#define humi_to_lcd_txt(humi) write_txt_data(TXT_WRITE_FUN_CMD, HUMI_SETTING_ADDR,humi)  //湿度值
#define temp_center_to_lcd_txt(heat) write_txt_data(TXT_WRITE_FUN_CMD, TEMP_CENTER_ADDR,heat)  //中心温度设定

#define temp_home_center_to_lcd_txt(heat) write_txt_data(TXT_WRITE_FUN_CMD, TEMP_HOME_CENTER_ADDR,heat)  //主页中心温度设定
#define humi_home_center_to_lcd_txt(upper_limit) write_txt_data(TXT_WRITE_FUN_CMD, HUMI_HOME_CENTER_ADDR,upper_limit)  //主页中心湿度设定

#define temp_diff_to_lcd_txt(cooling) write_txt_data(TXT_WRITE_FUN_CMD, TEMP_DIFF_ADDR,cooling)//温度回差设定
#define humi_center_to_lcd_txt(upper_limit) write_txt_data(TXT_WRITE_FUN_CMD, HUMI_CENTER_ADDR,upper_limit)//中心湿度设定
#define humi_diff_to_lcd_txt(lower_limit) write_txt_data(TXT_WRITE_FUN_CMD, HUMI_DIFF_ADDR,lower_limit)    //湿度回差设置
#define light_start_to_lcd_txt( light_start) write_txt_data(TXT_WRITE_FUN_CMD, LIGHT_START_ADDR , light_start)//下次光照开始时间 
#define light_end_to_lcd_txt(light_end) write_txt_data(TXT_WRITE_FUN_CMD, LIGHT_END_ADDR, light_end)					//下次光照结束时间
#define aeration_start_to_lcd_txt( aeration_start) write_txt_data(TXT_WRITE_FUN_CMD, AERATION_START_ADDR, aeration_start)//下次换气开始时间
#define aeration_end_to_lcd_txt(aeration_end) write_txt_data(TXT_WRITE_FUN_CMD, AERATION_END_ADDR, aeration_end)         //下次换气结束时间
#define sterilize_start_to_lcd_txt(sterilize_start) write_txt_data(TXT_WRITE_FUN_CMD, STERILIZE_START_ADDR, sterilize_start)//下次消毒开始时间
#define sterilize_time_to_lcd_txt(sterilize_time) write_txt_data(TXT_WRITE_FUN_CMD, STERILIZE_TIME_ADDR, sterilize_time)    //下次消毒运行时间
#define sersitive_start_to_lcd_txt(sterilize_start) write_txt_data(TXT_WRITE_FUN_CMD, SENSITIVE_START_ADDR, sterilize_start)//下次感光开始时间
#define sersitive_time_to_lcd_txt(sterilize_time) write_txt_data(TXT_WRITE_FUN_CMD, SENSITIVE_TIME_ADDR, sterilize_time)    //下次感光运行时间

/***************************** 更改lcd换气文本***********************/
#define first_aeration_start_to_lcd_txt(first_aeration_start) write_txt_data(TXT_WRITE_FUN_CMD, FIRST_AERATION_START_ADDR, first_aeration_start)       //第一次换气开始
#define first_aeration_time_to_lcd_txt(first_aeration_time) write_txt_data(TXT_WRITE_FUN_CMD,  FIRST_AERATION_TIME_ADDR, first_aeration_time)			     //第一次运行时间
#define second_aeration_start_to_lcd_txt(second_aeration_start) write_txt_data(TXT_WRITE_FUN_CMD,  SECOND_AERATION_START_ADDR, second_aeration_start)  //第二次换气开始
#define second_aeration_time_to_lcd_txt(second_aeration_time) write_txt_data(TXT_WRITE_FUN_CMD,  SECOND_AERATION_TIME_ADDR, second_aeration_time)      //第二次运行时间
#define third_aeration_start_to_lcd_txt(third_aeration_start) write_txt_data(TXT_WRITE_FUN_CMD, THIRD_AERATION_START_ADDR, third_aeration_start)       //第三次换气开始
#define third_aeration_time_to_lcd_txt(third_aeration_time) write_txt_data(TXT_WRITE_FUN_CMD,  THIRD_AERATION_TIME_ADDR, third_aeration_time)          //第三次运行时间
#define fourth_aeration_start_to_lcd_txt(fourth_aeration_start) write_txt_data(TXT_WRITE_FUN_CMD, FOURTH_AERATION_START_ADDR, fourth_aeration_start)   //第四次换气开始
#define fourth_aeration_time_to_lcd_txt(fourth_aeration_time) write_txt_data(TXT_WRITE_FUN_CMD, FOURTH_AERATION_TIME_ADDR, fourth_aeration_time)       //第四次运行时间
#define fifth_aeration_start_to_lcd_txt(fifth_aeration_start) write_txt_data(TXT_WRITE_FUN_CMD,  FIFTH_AERATION_START_ADDR, fifth_aeration_start)      //第五次换气开始
#define fifth_aeration_time_to_lcd_txt(fifth_aeration_time) write_txt_data(TXT_WRITE_FUN_CMD,  FIFTH_AERATION_TIME_ADDR,fifth_aeration_time)           //第五次运行时间
#define sixth_aeration_start_to_lcd_txt(sixth_aeration_start) write_txt_data(TXT_WRITE_FUN_CMD, SIXTH_AERATION_START_ADDR, sixth_aeration_start)       //第六次换气开始 
#define sixth_aeration_time_to_lcd_txt(sixth_aeration_time) write_txt_data(TXT_WRITE_FUN_CMD, FIFSIXTH_AERATION_TIME_ADDR, sixth_aeration_time) 	     //第六次运行时间
#define seventh_aeration_start_to_lcd_txt(seventh_aeration_start) write_txt_data(TXT_WRITE_FUN_CMD, SEVENTH_AERATION_START_ADDR, seventh_aeration_start)//第七次换气开始
#define seventh_aeration_time_to_lcd_txt(seventh_aeration_time) write_txt_data(TXT_WRITE_FUN_CMD, SEVENTH_AERATION_TIME_ADDR, seventh_aeration_time)   //第七次运行时间
#define eighth_aeration_start_to_lcd_txt(eighth_aeration_start) write_txt_data(TXT_WRITE_FUN_CMD, EIGHTH_AERATION_START_ADDR, eighth_aeration_start)   //第八次换气开始
#define eighth_aeration_time_to_lcd_txt(eighth_aeration_time) write_txt_data(TXT_WRITE_FUN_CMD, EIGHTH_AERATION_TIME_ADDR, eighth_aeration_time)       //第八次运行时间

/***************************** 更改lcd感光文本***********************/
#define first_sensitive_start_to_lcd_txt(first_sensitive_start) write_txt_data(TXT_WRITE_FUN_CMD, FIRST_SENSITIVE_START_ADDR, first_sensitive_start)   //第一次感光开始时间
#define first_sensitive_end_to_lcd_txt(first_sensitive_end) write_txt_data(TXT_WRITE_FUN_CMD, FIRST_SENSITIVE_END_ADDR, first_sensitive_end)           //第一次感光结束时间
#define second_sensitive_start_to_lcd_txt(second_sensitive_start) write_txt_data(TXT_WRITE_FUN_CMD,SECOND_SENSITIVE_START_ADDR, second_sensitive_start)//第二次感光开始时间
#define second_sensitive_end_to_lcd_txt(second_sensitive_end) write_txt_data(TXT_WRITE_FUN_CMD, SECOND_SENSITIVE_END_ADDR, second_sensitive_end)       //第二次感光结束时间
#define third_sensitive_start_to_lcd_txt(third_sensitive_start) write_txt_data(TXT_WRITE_FUN_CMD, THIRD_SENSITIVE_START_ADDR, third_sensitive_start)   //第三次感光开始时间
#define third_sensitive_end_to_lcd_txt(third_sensitive_end) write_txt_data(TXT_WRITE_FUN_CMD, THIRD_SENSITIVE_END_ADDR, third_sensitive_end)           //第三次感光结束时间

/***************************** 更改lcd光照文本***********************/
#define first_light_start_to_lcd_txt(first_light_start) write_txt_data(TXT_WRITE_FUN_CMD, FIRST_LIGHT_START_ADDR, first_light_start)                  //第一次光照开始时间
#define first_light_end_to_lcd_txt(first_light_end) write_txt_data(TXT_WRITE_FUN_CMD,FIRST_LIGHT_END_ADDR, first_light_end)                           //第一次光照结束时间
#define second_light_start_to_lcd_txt(second_light_start) write_txt_data(TXT_WRITE_FUN_CMD,SECOND_LIGHT_START_ADDR, second_light_start)               //第二次光照开始时间
#define second_light_end_to_lcd_txt(second_light_end) write_txt_data(TXT_WRITE_FUN_CMD, SECOND_LIGHT_END_ADDR, second_light_end)                      //第二次光照结束时间
#define third_light_start_to_lcd_txt(third_light_start) write_txt_data(TXT_WRITE_FUN_CMD, THIRD_LIGHT_START_ADDR, third_light_start)                  //第三次光照开始时间
#define third_light_end_to_lcd_txt(third_light_end) write_txt_data(TXT_WRITE_FUN_CMD, THIRD_LIGHT_END_ADDR, third_light_end)                          //第三次光照结束时间

/***************************** 更改lcd消毒文本***********************/
#define first_sterilize_start_to_lcd_txt(first_sterilize_start) write_txt_data(TXT_WRITE_FUN_CMD, FIRST_STERILIZE_START_ADDR, first_sterilize_start)    //第一次消毒开始时间
#define first_sterilize_end_to_lcd_txt(first_sterilize_end) write_txt_data(TXT_WRITE_FUN_CMD, FIRST_STERILIZE_END_ADDR, first_sterilize_end)            //第一次消毒结束时间
#define second_sterilize_start_to_lcd_txt(second_sterilize_start) write_txt_data(TXT_WRITE_FUN_CMD, SECOND_STERILIZE_START_ADDR, second_sterilize_start)//第二次消毒开始时间
#define second_sterilize_end_to_lcd_txt(second_sterilize_end) write_txt_data(TXT_WRITE_FUN_CMD, SECOND_STERILIZE_END_ADDR, second_sterilize_end)        //第二次消毒结束时间
#define third_sterilize_start_to_lcd_txt(third_sterilize_start) write_txt_data(TXT_WRITE_FUN_CMD, THIRD_STERILIZE_START_ADDR, third_sterilize_start)	  //第三次消毒开始时间
#define third_sterilize_end_to_lcd_txt(third_sterilize_end) write_txt_data(TXT_WRITE_FUN_CMD, THIRD_STERILIZE_END_ADDR, third_sterilize_end)			      //第三次消毒结束时间
#define fourth_sterilize_start_to_lcd_txt(fourth_sterilize_start) write_txt_data(TXT_WRITE_FUN_CMD, FOURTH_STERILIZE_START_ADDR, fourth_sterilize_start)//第四次消毒开始时间
#define fourth_sterilize_end_to_lcd_txt(fourth_sterilize_end) write_txt_data(TXT_WRITE_FUN_CMD, FOURTH_STERILIZE_END_ADDR, fourth_sterilize_end)        //第四次消毒结束时间  

/************************* 更改lcd传感器校准文本*********************/
#define first_sensor_to_lcd_txt(first_sensor) write_txt_data(TXT_WRITE_FUN_CMD, FIRST_TEMP_CALIBRATION_VALUE_ADDR, first_sensor)                                                  //第一个传感器地址
#define first_real_time_temp_value_to_lcd_txt(first_real_time_value_temp) write_txt_data(TXT_WRITE_FUN_CMD, FIRST_TEMP_CALIBRATION_VALUE_ADDR, first_real_time_value_temp)        //第一个传感器实时温度
#define first_real_time_humi_value_to_lcd_txt(first_real_time_humi_value) write_txt_data(TXT_WRITE_FUN_CMD, FIRST_TEMP_CALIBRATION_VALUE_ADDR, first_real_time_humi_value)        //第一个传感器实时湿?
#define second_sensor_to_lcd_txt(second_sensor) write_txt_data(TXT_WRITE_FUN_CMD, SECOND_TEMP_CALIBRATION_VALUE_ADDR, second_sensor)                                              //第二个传感器地址 
#define second_real_time_temp_value_to_lcd_txt(second_real_time_value_temp) write_txt_data(TXT_WRITE_FUN_CMD, SECOND_TEMP_CALIBRATION_VALUE_ADDR, second_real_time_value_temp)    //第二个传感器实时温度
#define second_real_time_humi_value_to_lcd_txt(second_real_time_humi_value) write_txt_data(TXT_WRITE_FUN_CMD, SECOND_TEMP_CALIBRATION_VALUE_ADDR, second_real_time_humi_value)    //第二个传感器实时湿度
#define third_sensor_to_lcd_txt(third_sensor) write_txt_data(TXT_WRITE_FUN_CMD, THIRD_TEMP_CALIBRATION_VALUE_ADDR, third_sensor)                                                  //第三个传感器地址
#define third_real_time_temp_value_to_lcd_txt(third_real_time_value_temp) write_txt_data(TXT_WRITE_FUN_CMD, THIRD_TEMP_CALIBRATION_VALUE_ADDR, third_real_time_value_temp)        //第三个传感器实时温度
#define third_real_time_humi_value_to_lcd_txt(third_real_time_humi_value) write_txt_data(TXT_WRITE_FUN_CMD, THIRD_TEMP_CALIBRATION_VALUE_ADDR, third_real_time_humi_value)        //第三个传感器实时湿度
#define fourth_sensor_to_lcd_txt(fourth_sensor) write_txt_data(TXT_WRITE_FUN_CMD, FOURTH_TEMP_CALIBRATION_VALUE_ADDR, fourth_sensor)                                              //第四个传感器地址
#define fourth_real_time_temp_value_to_lcd_txt(fourth_real_time_value_temp) write_txt_data(TXT_WRITE_FUN_CMD, FOURTH_TEMP_CALIBRATION_VALUE_ADDR, fourth_real_time_value_temp)    //第四个传感器实时温度
#define fourth_real_time_humi_value_to_lcd_txt(fourth_real_time_humi_value) write_txt_data(TXT_WRITE_FUN_CMD, FOURTH_TEMP_CALIBRATION_VALUE_ADDR, fourth_real_time_humi_value)    //第四个传感器实时湿度

#define first_temp_calbration_value_to_lcd_txt(first_temp_calbration_value) write_txt_data(TXT_WRITE_FUN_CMD, FIRST_TEMP_CALIBRATION_VALUE_ADDR, first_temp_calbration_value)     //第一个传感器温度校准值
#define first_humi_calbration_value_to_lcd_txt(first_humi_calbration_value) write_txt_data(TXT_WRITE_FUN_CMD, FIRST_HUMI_CALIBRATION_VALUE_ADDR, first_humi_calbration_value)     //第一个传感器湿度校准值
#define second_temp_calbration_value_to_lcd_txt(second_temp_calbration_value) write_txt_data(TXT_WRITE_FUN_CMD, SECOND_TEMP_CALIBRATION_VALUE_ADDR, second_temp_calbration_value) //第二个传感器温度校准值
#define second_humi_calbration_value_to_lcd_txt(second_humi_calbration_value) write_txt_data(TXT_WRITE_FUN_CMD, SECOND_HUMI_CALIBRATION_VALUE_ADDR, second_humi_calbration_value) //第二个传感器湿度校准值
#define third_temp_calbration_value_to_lcd_txt(third_temp_calbration_value) write_txt_data(TXT_WRITE_FUN_CMD, THIRD_TEMP_CALIBRATION_VALUE_ADDR, third_temp_calbration_value)     //第三个传感器温度校准值
#define third_humi_calbration_value_to_lcd_txt(third_humi_calbration_value) write_txt_data(TXT_WRITE_FUN_CMD, THIRD_HUMI_CALIBRATION_VALUE_ADDR, third_humi_calbration_value)     //第三个传感器湿度校准值
#define fourth_temp_calbration_value_to_lcd_txt(fourth_temp_calbration_value) write_txt_data(TXT_WRITE_FUN_CMD, FOURTH_TEMP_CALIBRATION_VALUE_ADDR, fourth_temp_calbration_value) //第四个传感器温度校准值
#define fourth_humi_calbration_value_to_lcd_txt(fourth_humi_calbration_value) write_txt_data(TXT_WRITE_FUN_CMD, FOURTH_HUMI_CALIBRATION_VALUE_ADDR, fourth_humi_calbration_value) //第四个传感器湿度校准值

/*************************************更改存储ID文本*************************************************************************/
#define save_devId_to_lcd_txt(id) write_txt_data(TXT_WRITE_FUN_CMD, SAVE_DEV_ID_ADDR, id) 
/*************************************************************************************************
**                                                                                              **
**                                                                                              **
******************************以下类型直接向lcd发送图标数据***************************************
**																																															**
**																																															**
*************************************************************************************************/

/*************************主页图标**********************************/
#define wifi_status_to_lcd_hex(sterilize) write_hex_data(HEX_ICONWRITE_FUN_CMD, WIFI_STATUS_ADDR,sterilize)                            //wifi是否连接状态
#define air_status_to_lcd_hex(air_status) write_hex_data(HEX_ICONWRITE_FUN_CMD,AIR_STATUS_ADDR,air_status)                              //空调
#define heat_status_to_lcd_hex(heat_status) write_hex_data(HEX_ICONWRITE_FUN_CMD, HEAT_STATUS_ADDR, heat_status)                       //加热
#define humi_status_lcd_hex(humi_status) write_hex_data(HEX_ICONWRITE_FUN_CMD,HUMI_STATUS_ADDR,humi_status)                            //补湿
#define aerathion_status_to_lcd_hex(aerathion_status) write_hex_data(HEX_ICONWRITE_FUN_CMD, AERATION_STATUS_ADDR,aerathion_status)     //换气
#define win_status_to_lcd_hex(win_status) write_hex_data(HEX_ICONWRITE_FUN_CMD, WIN_STATUS_ADDR,win_status)                            //匀风
#define sensitive_staus_to_lcd_hex(sensitive_staus) write_hex_data(HEX_ICONWRITE_FUN_CMD, SENSITIVE_STATUS_ADDR,sensitive_staus)       //感光
#define sterilize_staus_to_lcd_hex(sterilize_staus) write_hex_data(HEX_ICONWRITE_FUN_CMD, STERILIZE_STATUS_ADDR,sterilize_staus)       //消毒
#define light_status_to_lcd_hex(light_status) write_hex_data(HEX_ICONWRITE_FUN_CMD, LIGHT_STATUS_ADDR,light_status)									 	 //光照
#define dry_status_to_lcd_hex(dry_status) write_hex_data(HEX_ICONWRITE_FUN_CMD, DRY_STATUS_ADDR,dry_status)                              //换气
#define work_mode_status_to_lcd_hex(status) write_hex_data(HEX_ICONWRITE_FUN_CMD, DEV_WORK_STATUS_STATUS_ADDR,status)                              //自动控制模式图标

#define wifi_connect_to_lcd_hex(data) write_hex_data(HEX_ICONWRITE_FUN_CMD, WIFI_CONNECT_ADDR,data)           //设置wifi连接状态
#define air_learn_status_to_lcd_hex(data) write_hex_data(HEX_ICONWRITE_FUN_CMD, AIR_LEARN_OK_ADDR,data)       //空调学习完成
#define save_all_to_lcd_hex(data) write_hex_data(TXT_WRITE_FUN_CMD, SAVE_ALL_ADDR,data)
//保持所有信息(存FLASH)
#define recover_id_to_lcd_hex(data) write_hex_data(HEX_ICONWRITE_FUN_CMD, ID_RECOVER_ADDR,data) 


/*************************************************************************************************
**                                                                                              **
**                                                                                              **
******************************以下类型直接从lcd读取文本数据***************************************
**																																															**
**																																															**
*************************************************************************************************/

#define temp_center_from_lcd_txt() read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, TEMP_CENTER_ADDR)  //中心温度设定
#define temp_diff_from_lcd_txt() read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, TEMP_DIFF_ADDR)			 //温度回差设定
#define humi_center_from_lcd_txt() read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, HUMI_CENTER_ADDR)  //中心湿度设定
#define humi_diff_from_lcd_txt() read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, HUMI_DIFF_ADDR)      //湿度回差设置
#define uniform_return_diffrence_from_lcd_txt() read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, UNIFORM_RETURN_DIFFERENCE_ADDR)      //匀风回差设定
#define uniform_return_diffrence_to_lcd_txt(uniform) write_txt_data(TXT_WRITE_FUN_CMD, UNIFORM_RETURN_DIFFERENCE_ADDR,uniform)//匀风回差设定
#define set_work_mode_to_lcd_txt(uniform) write_txt_data(TXT_WRITE_FUN_CMD, DEV_WORK_STATUS_TXT_ADDR,uniform)//工作模式设定


 
/**************************************换气时间读取*****************************************/
#define first_aeration_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FIRST_AERATION_START_ADDR)   //第一次换气开始
#define first_aeration_time_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FIRST_AERATION_TIME_ADDR)			//第一次运行时间
#define second_aeration_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, SECOND_AERATION_START_ADDR) //第二次换气开始
#define second_aeration_time_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, SECOND_AERATION_TIME_ADDR)   //第二次运行时间
#define third_aeration_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, THIRD_AERATION_START_ADDR)   //第三次换气开始
#define third_aeration_time_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, THIRD_AERATION_TIME_ADDR)     //第三次运行时间
#define fourth_aeration_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FOURTH_AERATION_START_ADDR) //第四次换气开始
#define fourth_aeration_time_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FOURTH_AERATION_TIME_ADDR)   //第四次运行时间
#define fifth_aeration_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FIFTH_AERATION_START_ADDR)   //第五次换气开始
#define fifth_aeration_time_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FIFTH_AERATION_TIME_ADDR)     //第五次运行时间
#define sixth_aeration_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, SIXTH_AERATION_START_ADDR)   //第六次换气开始 
#define sixth_aeration_time_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FIFSIXTH_AERATION_TIME_ADDR) 	//第六次运行时间
#define seventh_aeration_start_from_lcd_txt()  read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, SEVENTH_AERATION_START_ADDR)//第七次换气开始
#define seventh_aeration_time_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, SEVENTH_AERATION_TIME_ADDR) //第七次运行时间
#define eighth_aeration_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, EIGHTH_AERATION_START_ADDR) //第八次换气开始
#define eighth_aeration_time_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, EIGHTH_AERATION_TIME_ADDR)   //第八次运行时间

/*****************************************光照时间读取********************************************/
#define first_light_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FIRST_LIGHT_START_ADDR)  //第一次光照开始时间
#define first_light_end_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FIRST_LIGHT_END_ADDR)      //第一次光照结束时间
#define second_light_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, SECOND_LIGHT_START_ADDR)//第二次光照开始时间
#define second_light_end_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, SECOND_LIGHT_END_ADDR)    //第二次光照结束时间
#define third_light_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, THIRD_LIGHT_START_ADDR)  //第三次光照开始时间
#define third_light_end_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, THIRD_LIGHT_END_ADDR)      //第三次光照结束时间

/*****************************************感光时间读取********************************************/
#define first_sensitive_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FIRST_SENSITIVE_START_ADDR)  //第一次感光开始时间
#define first_sensitive_end_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FIRST_SENSITIVE_END_ADDR)      //第一次感光结束时间
#define second_sensitive_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, SECOND_SENSITIVE_START_ADDR)//第二次感光开始时间
#define second_sensitive_end_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, SECOND_SENSITIVE_END_ADDR)    //第二次感光结束时间
#define third_sensitive_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, THIRD_SENSITIVE_START_ADDR)  //第三次感光开始时间
#define third_sensitive_end_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, THIRD_SENSITIVE_END_ADDR)      //第三次感光结束时间

/*****************************************消毒时间读取*********************************************/
#define first_sterilize_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FIRST_STERILIZE_START_ADDR)  //第一次消毒开始时间
#define first_sterilize_end_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FIRST_STERILIZE_END_ADDR)      //第一次消毒结束时间
#define second_sterilize_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, SECOND_STERILIZE_START_ADDR)//第二次消毒开始时间
#define second_sterilize_end_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, SECOND_STERILIZE_END_ADDR)    //第二次消毒结束时间
#define third_sterilize_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, THIRD_STERILIZE_START_ADDR)	 //第三次消毒开始时间
#define third_sterilize_end_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, THIRD_STERILIZE_END_ADDR)			 //第三次消毒结束时间
#define fourth_sterilize_start_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FOURTH_STERILIZE_START_ADDR)//第四次消毒开始时间
#define fourth_sterilize_end_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FOURTH_STERILIZE_END_ADDR)    //第四次消毒结束时间  

/*************************************读取温湿度传感器校准信息***********************************/
#define first_temp_calbration_value_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FIRST_TEMP_CALIBRATION_VALUE_ADDR)     //第一个传感器温度校准值
#define first_humi_calbration_value_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FIRST_HUMI_CALIBRATION_VALUE_ADDR)     //第一个传感器湿度校准值
#define second_temp_calbration_value_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, SECOND_TEMP_CALIBRATION_VALUE_ADDR)   //第二个传感器温度校准值
#define second_humi_calbration_value_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, SECOND_HUMI_CALIBRATION_VALUE_ADDR)   //第二个传感器湿度校准值
#define third_temp_calbration_value_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, THIRD_TEMP_CALIBRATION_VALUE_ADDR)     //第三个传感器温度校准值
#define third_humi_calbration_value_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, THIRD_HUMI_CALIBRATION_VALUE_ADDR)     //第三个传感器湿度校准值
#define fourth_temp_calbration_value_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FOURTH_TEMP_CALIBRATION_VALUE_ADDR)   //第四个传感器温度校准值
#define fourth_humi_calbration_value_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, FOURTH_HUMI_CALIBRATION_VALUE_ADDR)   //第四个传感器湿度校准值

/**************************************wifi设置读取*****************************************/
#define wifi_name_from_lcd_txt()     read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, WIFI_NAME_ADDR)//读取wifi账号
#define wifi_passwd_from_lcd_txt()   read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, WIFI_PASSWD_ADDR)//读取wifi密码
/******************************读取存储ID****************************************************************/
#define save_devId_from_lcd_txt()     read_txt_data(TXT_GET_FUN_CMD, TXT_READ_FUN_CMD, SAVE_DEV_ID_ADDR)//

/*****************************读取空调学习状态*************************************************/
#define heated_learning_from_lcd_txt()            read_hex_data(HEX_GET_FUN_CMD, HEX_READ_FUN_CMD, HEATED_LEARNING_ADDR)								//读取空调加热学习
#define refrigeration_learning_from_lcd_txt()     read_hex_data(HEX_GET_FUN_CMD, HEX_READ_FUN_CMD, REFRIGERATION_LEARNING_ADDR) //读取空调制冷学习
#define close_learning_from_lcd_txt()             read_hex_data(HEX_GET_FUN_CMD, HEX_READ_FUN_CMD, CLOSE_LEARNING_ADDR)     


/*****************************更改id文本*************************************************/
#define change_id_to_lcd_txt(change_id) write_txt_data(TXT_WRITE_FUN_CMD, LCD_CHANGE_ID_ADDR, change_id)
/*****************************读取更改id文本*************************************************/
#define id_from_lcd_txt() read_txt_data(TXT_GET_FUN_CMD,TXT_READ_FUN_CMD,LCD_CHANGE_ID_ADDR)  //获取id文本
/*****************************id更改成功图标*************************************************/
#define id_change_ok_to_lcd_hex(sterilize) write_hex_data(HEX_ICONWRITE_FUN_CMD, ID_CHANGE_OK_ADDR,sterilize)
/*****************************以下类型直接从lcd读取控件数据填写功能码和地址***********************/


/*****************************手动模式下控制命令***********************/
#define air_condition_to_lcd_hex() read_hex_data(HEX_GET_FUN_CMD, HEX_READ_FUN_CMD, MANUAL_AIR_CONDITIONING_ADDR)    //空调

#define heat_from_lcd_hex() read_hex_data(HEX_GET_FUN_CMD, HEX_READ_FUN_CMD,MANUAL_HEATING_ADDR)                     //加热
#define fill_wet_from_lcd_hex() read_hex_data(HEX_GET_FUN_CMD, HEX_READ_FUN_CMD,MANUAL_FILL_WET)                     //补湿
#define aeration_from_lcd_hex() read_hex_data(HEX_GET_FUN_CMD, HEX_READ_FUN_CMD,MANUAL_FOR_AIR_ADDR)                 //换气
#define sensitive_from_lcd_hex() read_hex_data(HEX_GET_FUN_CMD, HEX_READ_FUN_CMD,MANUAL_SENSITIVE_ADDR)              //感光
#define air_uniform_from_lcd_hex() read_hex_data(HEX_GET_FUN_CMD, HEX_READ_FUN_CMD,MANUAL_AND_THE_WIND_ADDR)         //匀风
#define light_from_lcd_hex() read_hex_data(HEX_GET_FUN_CMD,HEX_READ_FUN_CMD, MANUAL_LIGHT_ADDR)                      //光照
#define sterilize_from_lcd_hex() read_hex_data(HEX_GET_FUN_CMD, HEX_READ_FUN_CMD,MANUAL_STERILIZE_ADD)               //消毒
#define dry_from_lcd_hex() read_hex_data(HEX_GET_FUN_CMD,HEX_READ_FUN_CMD, MANUAL_DRY_ADDR)                          //除湿
#define control_mode_from_lcd_hex() read_hex_data(HEX_GET_FUN_CMD, HEX_READ_FUN_CMD,RETURN_ADDR)                     //自动/手动获取

#endif

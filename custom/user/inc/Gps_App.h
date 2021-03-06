#ifndef	__GPS_APP_H
#define	__GPS_APP_H
//******************文件包含*********************
//#include "include.h"
#include "RadioProtocol.h"
extern u8	GpsOnOffFlag;//GPS开关标志,0为GPS关,1为GPS开

typedef struct 		
{
	u8  	Year;		//年	
	u8  	Month;		//月
	u8  	Date;		//日
	u8  	Hour;		//时
	u8  	Minute;		//分
	u8  	Second;		//秒
	u8		North;		//1:北纬0:南纬
	double  Latitue;
	u8  	Latitue_D;	//纬度,度
	u8  	Latitue_F;	//纬度,分
	u16 	Latitue_FX;	//纬度,分的小数,单位为0.0001分
	u8		East;		//1:东经0:西经
	double 	Longitue;	
	u8 		Longitue_D;	//经度,度,最大180度
	u8  	Longitue_F;	//经度,分		
	u16 	Longitue_FX;	//经度,分的小数,单位为0.0001分
	double	Speed_D;
	u8  	Speed;		//速度,单位为海里/小时
	u8		SpeedX;		//速度的小数
	u16 	Course;		//航向,单位为度
	s16 	High;		//海拔,单位为米
    s16     HighOffset;     //海拔偏差值
	u8  	SatNum;		//卫星数量
	u8		HDOP;		//水平精度因子
	u8		Status;		//1:有效定位 0:无效定位
	u8		Error;		//1:GPS模块出错，不发送数据  0:模块正常
}GPS_STRUCT;			//GPS定位数据结构体

#define QCELLOCLEN  15

typedef struct
{
  u8 LatitueLocation[QCELLOCLEN];//纬度
  u8 LongitueLocation[QCELLOCLEN];//经度
}CELLULAR_STRUCT;

//gps滤波
typedef enum
{
    WORKING = 0,
    ENTER_STOP,
    SLEEPING,
    WAKE_UP,
    SWITCHING,
}GPS_WORK_STATUS;

typedef struct 
{
	GPS_WORK_STATUS GPS_work_status;

    u8  Valid;            
	u8	Not_Locate_Cnt;
	u8	Reflash_Flag;
	u8  Speed_Up_Cnt;
	u16 Speed_Down_Cnt;
}TDF_STU_GPS;

//**************函数声明********************
/*********************************************************************
//函数名称	:Gps_ReadStaNum(void)
//功能		:获取GPS的定位星数
//备注		:
*********************************************************************/
u8 Gps_ReadStaNum(void);
/*********************************************************************
//函数名称	:GPS_AdjustRtc(GPS_STRUCT *Position)
//功能		:GPS校时
//备注		:
*********************************************************************/
ErrorStatus Gps_AdjustRtc(GPS_STRUCT *Position);
/*********************************************************************
//函数名称	:GPS_GprmcIsLocation(u8 *pBuffer, u8 BufferLen)
//功能		:判断GPRMC数据是否定位
//返回		:正确返回1，错误返回0
//备注		:
*********************************************************************/
u8 Gps_GprmcIsLocation(u8 *pBuffer, u8 BufferLen);
/*********************************************************************
//函数名称	:GPS_GpsDataIsOk(u8 *pBuffer, u8 BufferLen)
//功能		:判断GPS数据是否正确
//返回		:正确返回1，错误返回0
//备注		:
*********************************************************************/
u8 Gps_DataIsOk(u8 *pBuffer, u8 BufferLen);
/*********************************************************************
//函数名称	:GPS_GprmcParse(u8 *pBuffer, u8 BufferLen)
//功能		:解析GPRMC数据
//备注		:
*********************************************************************/
void Gps_GprmcParse(u8 *pBuffer, u8 BufferLen);
/*********************************************************************
//函数名称	:GPS_GpggaParse(u8 *pBuffer, u8 BufferLen)
//功能		:解析GPGGA数据
//备注		:
*********************************************************************/
void Gps_GpggaParse(u8 *pBuffer, u8 BufferLen);
/*********************************************************************
//函数名称	:GPS_CopygPosition(GPS_STRUCT *dest, GPS_STRUCT *src)
//功能		:获取一份最新的gps位置数据，它是有效的定位数据
//备注		:
*********************************************************************/
void Gps_CopyToPosition(GPS_STRUCT *dest);
void Gps_CopygPosition(GPS_STRUCT *dest);
/*********************************************************************
//函数名称	:GPS_CopyPosition(GPS_STRUCT *dest, GPS_STRUCT *src)
//功能		:拷贝一份最新收到的gps位置数据，它不一定是有效的定位数据
//备注		:
*********************************************************************/
void Gps_CopyPosition(GPS_STRUCT *dest);
/*********************************************************************
//函数名称	:GPS_UpdatagPosition(void)
//功能		:更新变量gPosition
//备注		:
*********************************************************************/
void Gps_UpdatagPosition(void);
/*********************************************************************
//函数名称	:GPS_ReadGpsSpeed(void)
//功能		:获取GPS速度
//备注		:单位是km/h
*********************************************************************/
u8 Gps_ReadSpeed(void);
/*********************************************************************
//函数名称	:GPS_ReadGpsStatus(void)
//功能		:获取GPS的状态
//备注		:
*********************************************************************/
u8 Gps_ReadStatus(void);
/*********************************************************************
//函数名称	:GPS_ReadGpsCourse(void)
//功能		:获取GPS的方向
//备注		:
*********************************************************************/
u16 Gps_ReadCourse(void);
/*********************************************************************
//函数名称	:GPS_ReadGpsCourseDiv2(void)
//功能		:获取GPS的方向（除以了2）
//备注		:
*********************************************************************/
u8 Gps_ReadCourseDiv2(void);
/*********************************************************************
//函数名称	:Gps_PowerOnClearPosition(void)
//功能		:初次使用经纬度初始化为零
*********************************************************************/
void Gps_PowerOnClearPosition(void);
/*********************************************************************
//函数名称	:GPS_PowerOnUpdataPosition(void)
//功能		:上电更新经纬度
//备注		:
*********************************************************************/
void Gps_PowerOnUpdataPosition(void);
/*********************************************************************
//函数名称	:GPS_SavePositionToFram(void)
//功能		:把位置保存到eeprom中
//备注		:
*********************************************************************/
void Gps_SavePositionToFram(void);
/*********************************************************************
//函数名称	:GpsParse_EvTask(void)
//功能		:GPS解析任务
//备注		:
*********************************************************************/
/*********************************************************************
//函数名称	:Gps_GetRunFlag
//功能		:获取去漂移行驶标志 
//返回		:1为行驶，0为停驶
//备注		:
*********************************************************************/
u8 Gps_GetRunFlag(void);
/*********************************************************************
//函数名称	:Gps_IsInRunning
//功能		:判断当前是处于行驶状态还是停驶状态 
//返回		:1为行驶，0为停驶
//备注		:1秒调用1次
*********************************************************************/
void Gps_IsInRunning(void);
/*********************************************************************
//函数名称	:GpsParse_EvTask(void)
//功能		:GPS解析任务
*********************************************************************/
void Gps_EvTask(void);
/*********************************************************************
//函数名称	:Gps_TimeTask(void)
//功能		:GPS时间任务
//备注		:1秒调度1次
*********************************************************************/
FunctionalState  Gps_TimeTask(void);
/*********************************************************************
//函数名称	:Gps_UpdateParam
//功能		
//输入		:
//输出		:
//使用资源	:
//全局变量	:   
//调用函数	:
//中断资源	:  
//返回		:
//备注		:
*********************************************************************/
void Gps_UpdateParam(void);
u8 Gps_Off_flag(void);
void Gps_Qcellloc_ASCII2(u8 *pBuffer);
//清除GPS数据解析错误计数器
void Gps_ClrParseErr(void);

#endif


#ifndef __REPORT_H
#define __REPORT_H


#define PRAM_TEMP_TRACK_TIME 	3
#define PRAM_TEMP_TRACK_COUNT 	4

#define REPORT_OVERTIME					(15000)	// 上报超时时间ms

typedef struct
{
	u8 *pBuf;
	ST_Time DateTime;
	u8 BufLen;
	u32 interval;
}BlindSavePara,*pBlindSavePara;

typedef enum 
{
	ReportStatus_Off=0,//未鉴权不上班
	ReportStatus_Init,//上报初始化
	ReportStatus_Wait,//没上线在等待
	ReportStatus_On		//正常上报
}ReportStatus_TypeDef;
/**************************************************************************
//函数名：Report_GetReportStatus
//功能：获取上报状态
//输入：
//输出：
//返回值：
//备注：
***************************************************************************/
ReportStatus_TypeDef Report_GetReportStatus(void);
/**************************************************************************
//函数名：Report_SetReportStatus
//功能：置位上报状态
//输入：参数类型
//输出：
//返回值：无
//备注：
***************************************************************************/
void Report_SetReportStatus(ReportStatus_TypeDef reportSta);

/**************************************************************************
//函数名：Report_TimeTask
//功能：实现位置汇报（包括实时跟踪、紧急报警、超速报警、超时报警、定时定距等位置汇报）
//输入：无
//输出：无
//返回值：始终是ENABLE
//备注：位置汇报定时任务，1秒钟进入1次，任务调度器需要调用此函数
***************************************************************************/
FunctionalState Report_TimeTask(void);
/**************************************************************************
//函数名：Report_UpdatePram
//功能：更新位置汇报所有变量
//输入：无
//输出：无
//返回值：无
//备注：主要是更新位置汇报模块所使用到的变量，运行任务调度之前需调用此函数
***************************************************************************/
void Report_UpdatePram(void);
/**************************************************************************
//函数名：Report_UpdateOnePram
//功能：更新某个参数
//输入：参数类型
//输出：该参数类型对应的变量
//返回值：无
//备注：串口或远程设置位置汇报相关参数时需要调用此函数
***************************************************************************/
void Report_UpdateOnePram(u8 type);
/**************************************************************************
//函数名：Report_CmdAck
//功能：位置上报应答处理
//输入：通道号
//输出：无
//返回值：无
//备注：收到位置上报的通用应答时需调用此函数
***************************************************************************/
void Report_CmdAck(void);
/**************************************************************************
//函数名：Report_UploadPositionInfo
//功能：上传一条位置信息
//输入：通道号
//输出：无
//返回值：0上传成功，1上传失败
//备注：当前的位置信息==位置基本信息+位置附加信息，位置信息最长为150字节
***************************************************************************/
u8 Report_UploadPositionInfo(void);
/**************************************************************************
//函数名：Report_GetPositionInfo
//功能：获取当前的位置信息
//输入：无
//输出：位置信息
//返回值：位置信息长度
//备注：当前的位置信息==位置基本信息+位置附加信息，位置信息最长为150字节
***************************************************************************/
u16 Report_GetPositionInfo(u8 *pBuffer);
/**************************************************************************
//函数名：Report_GetPositionBasicInfo
//功能：获取位置基本信息
//输入：无
//输出：位置基本信息
//返回值：位置基本信息长度
//备注：长度固定为28字节，位置基本信息：报警字、状态字、纬度、经度、高程、速度、方向、时间
***************************************************************************/
u16 Report_GetPositionBasicInfo(u8 *pBuffer);
/**************************************************************************
//函数名：Report_ClearReportTimeCount
//功能：上报时间计数变量清0
//输入：无
//输出：无
//返回值：无
//备注：两个连接的计数变量都清0
***************************************************************************/
void Report_ClearReportTimeCount(void);
/**************************************************************************
//函数名：Report_GetReportEventSwitch
//功能：获取ReportEventSwitch的值
//输入：无
//输出：无
//返回值：无
//备注：ReportEventSwitch的值等于参数ID 0xF27D的设置值
***************************************************************************/
u32 Report_GetReportEventSwitch(void);
/**************************************************************************
//函数名：Report_GetOverSpeedReportTimeSpace
//功能：获取OverSpeedReportTimeSpace的值
//输入：无
//输出：无
//返回值：无
//备注：OverSpeedReportTimeSpace的值等于参数ID 0xF259的设置值
***************************************************************************/
u32 Report_GetOverSpeedReportTimeSpace(void);
/**************************************************************************
//函数名：Report_GetOverTimeReportTimeSpace
//功能：获取OverTimeReportTimeSpace的值
//输入：无
//输出：无
//返回值：无
//备注：OverTimeReportTimeSpace的值等于参数ID 0xF277的设置值
***************************************************************************/
u32 Report_GetOverTimeReportTimeSpace(void);
/**************************************************************************
//函数名：GetNextReportTime
//功能：获取距离下一次上报的时间
//输入：无
//输出：无
//返回值：
//备注：
***************************************************************************/
u32 GetNextReportTime(void);
/**************************************************************************
//函数名：Report_EnterPowerDownAfterReported
//功能：上报完成后进入关机模式
//输入：参数类型
//输出：
//返回值：无
//备注：
***************************************************************************/
void Report_EnterPowerDownAfterReported(void* param);
/**************************************************************************
//函数名：Report_GetReportInterval
//功能：获取缺省汇报时间间隔
//输入：无
//输出：无
//返回值：
//备注：
***************************************************************************/
u32 Report_GetDefaultReportInterval(void);
/**************************************************************************
//函数名：Report_Blind_Callback_Init
//功能：位置上报后盲区回调函数初始化
//			注册盲区回调函数，设置回调参数
//输入：参数类型
//输出：
//返回值：无
//备注：
***************************************************************************/
void Report_Blind_Callback_Init(void);

//追踪信息备份
void Report_PramBackup(void);

//上电恢复追踪信息
void Report_PramResume(void);

void Report_RtcWakeUpOffsetResume(void);

#endif



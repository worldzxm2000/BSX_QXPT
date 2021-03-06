#ifndef PARAM_H
#define PARAM_H
#define WIN32_LEAN_AND_MEAN
#include<WinSock2.h>
#include<Windows.h>
#include"SimpleProducer.h"
#include"WebCommServer.h"
#include<QDateTime> 
typedef LRESULT(*Char2Json)(QString &buff,QJsonObject &json);//解析数据函数
typedef int(*GetServiceTypeID_Lib)();//获取业务类型
typedef QString(*GetServiceTypeName_Lib)();//获取业务名称
typedef int(*GetPort_Lib)();//获取端口
typedef QString(*GetVersionNo_Lib)();//获取版本号
typedef void(*GetControlWidget_Lib)(QString StationID, uint Socket, QWidget* parent);//获取调试窗体
typedef void(*SetTime_Lib)(QString StationID, uint Socket);//对时命令
typedef void(*SetCommand_Lib)(uint Socket, int CommandType,QString Params1,QString Params2,QString StationID);//终端命令
typedef void(*SetValueToControlWidget_Lib)(QStringList ValueList);//返回值
extern 	SimpleProducer g_SimpleProducer, g_SimpleProducer_ZDH,g_SimpleProducer_Command;
extern WebCommServer g_WebCommServer ;
const int DataBuffSize = 4 * 1024;
typedef void* HLIB;		//动态库句柄
typedef struct
{
	OVERLAPPED overlapped;
	WSABUF databuff;//单次接收字节
	char buffer[DataBuffSize]; //总接收字节
	int BufferLen;  //单次接收字节大小
	int operationType; // 记录重叠IO操作类型 accp或recv
	

}PER_IO_OPERATEION_DATA, *LPPER_IO_OPERATION_DATA, *LPPER_IO_DATA, PER_IO_DATA;

typedef struct
{
	SOCKET Socket;  //客户端socekt
	QString ClientIP;//客户端IP
	int Port;//客户端端口
	int Count;//总数据接收量
	QString Frame;//一帧数据
	QString StationID;//台站号
	QString DeviceID;//设备号
}PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

//IOCP中结构体
typedef struct
{
	HANDLE CompletionPort;//IO端口号
	HANDLE Parent;//父类地址
}PARAMS,*LPPARAMS;


//业务列表
enum ServiceID
{
	NW = 01,//农委
	JTQX = 02,//交通气象
	NTXQH = 03,//农田小气候
	TRSF = 04,//土壤水分
	HKQX = 05,//航空气象
	SH_NTXQH = 8,//湿地农田小气候
	TRSF_NM = 9,//土壤水分内蒙
	TRSF_XJ=10,//土壤水分新疆
	SH_NTXQH_SZ = 11,//湿地农田小气候水质
	SH_DQFY = 12,//湿地大气负氧离子
	SH_TRSF_QY = 13,//是地铁土壤水分区域
	SH_TRSF_SQ=14,//湿地土壤水分墒情
	SH_TRSF_SW=15//湿地土壤水分地下水
};

//错误返回值
enum ErrorMSG
{
	SOCKET_INIT_ERROR=10300,//SOCKET初始化失败
	IOCP_INIT_ERROR=10301,//IOCP创建失败
	SOCKET_BIND_ERROR=10302,//SOCKET绑定失败
	SOCKET_LISTEN_ERROR=10303,//SOCKET监听失败
	MQ_SEND_ERROR=10304//消息中间件发送数据失败
};

//区站号信息
typedef struct
{
	//IP号
	QString IP;
	//端口号
	int Port;
	//socket号
	SOCKET SocketID;
	//区站号
	QString StationID;
	//设备号
	QString DeviceID;
	//最新心跳时间
	QDateTime LatestTimeOfHeartBeat;
	//状态
	bool Online;
	//登录时间
	QDateTime LoginTime;
} CLIENTINFO, *LPCLIENTINFO;

//UDP信息
typedef struct
{
	SOCKADDR_IN from;//udp socket号
	int ServiceID;//业务号
	QString StationID;//台站号
	QString DeviceID;//设备号
	int Count;//计数器

} UDPClient,*LPUDPClient;
//终端命令
enum OPCommand
{
	NONE = -1,
	BASEINFO = 231,
	DATETIME = 232,
	ID = 201,
	LAT = 234,
	LONGITUDE = 235,
	ALT = 236,
	CFSET = 237,
	CAPTIME = 238,
	CAPINTERVAL = 239,
	SNAPSHOT = 2310,
	RESET = 2311,
	UPDATE = 2312,
	DMTD=2313
};

//上传文件类型
enum FileType
{
	IMAGE = 1,
	TXT=2,
	XML=3
};
#endif // PARAM_H

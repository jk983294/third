/////////////////////////////////////////////////////////////////////////
///@system 新一代交易所系统
///@company 中国金融期货交易所股份有限公司
///@file CFFEXFtdcTraderApi.h
///@brief 定义了客户端接口
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(_FTDCTRADERAPI_H)
#define _FTDCTRADERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CFFEXFtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport)
#else
#define TRADER_API_EXPORT __declspec(dllimport)
#endif
#else
#define TRADER_API_EXPORT 
#endif

class CFfexFtdcTraderSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason){};
		
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse){};
	
	///报文回调开始通知。当API收到一个报文后，首先调用本方法，然后是各数据域的回调，最后是报文回调结束通知。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageStart(int nTopicID, int nSequenceNo){};
	
	///报文回调结束通知。当API收到一个报文后，首先调用报文回调开始通知，然后是各数据域的回调，最后调用本方法。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo){};


	///错误应答
	virtual void OnRspError(CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户登录应答
	virtual void OnRspUserLogin(CFfexFtdcRspUserLoginField *pRspUserLogin, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户退出应答
	virtual void OnRspUserLogout(CFfexFtdcRspUserLogoutField *pRspUserLogout, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单录入应答
	virtual void OnRspOrderInsert(CFfexFtdcInputOrderField *pInputOrder, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单操作应答
	virtual void OnRspOrderAction(CFfexFtdcOrderActionField *pOrderAction, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报价录入应答
	virtual void OnRspQuoteInsert(CFfexFtdcInputQuoteField *pInputQuote, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报价操作应答
	virtual void OnRspQuoteAction(CFfexFtdcQuoteActionField *pQuoteAction, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户密码修改应答
	virtual void OnRspUserPasswordUpdate(CFfexFtdcUserPasswordUpdateField *pUserPasswordUpdate, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///执行宣告录入应答
	virtual void OnRspExecOrderInsert(CFfexFtdcInputExecOrderField *pInputExecOrder, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///执行宣告操作应答
	virtual void OnRspExecOrderAction(CFfexFtdcExecOrderActionField *pExecOrderAction, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///管理报单录入应答
	virtual void OnRspAdminOrderInsert(CFfexFtdcInputAdminOrderField *pInputAdminOrder, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///非标组合报单录入应答
	virtual void OnRspCombOrderInsert(CFfexFtdcInputCombOrderField *pInputCombOrder, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅主题应答
	virtual void OnRspSubscribeTopic(CFfexFtdcDisseminationField *pDissemination, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///会员资金查询应答
	virtual void OnRspQryPartAccount(CFfexFtdcRspPartAccountField *pRspPartAccount, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单查询应答
	virtual void OnRspQryOrder(CFfexFtdcOrderField *pOrder, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报价查询应答
	virtual void OnRspQryQuote(CFfexFtdcQuoteField *pQuote, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///成交单查询应答
	virtual void OnRspQryTrade(CFfexFtdcTradeField *pTrade, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///会员客户查询应答
	virtual void OnRspQryClient(CFfexFtdcRspClientField *pRspClient, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///会员持仓查询应答
	virtual void OnRspQryPartPosition(CFfexFtdcRspPartPositionField *pRspPartPosition, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///客户持仓查询应答
	virtual void OnRspQryClientPosition(CFfexFtdcRspClientPositionField *pRspClientPosition, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///合约查询应答
	virtual void OnRspQryInstrument(CFfexFtdcRspInstrumentField *pRspInstrument, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///合约交易状态查询应答
	virtual void OnRspQryInstrumentStatus(CFfexFtdcInstrumentStatusField *pInstrumentStatus, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///保值额度应答
	virtual void OnRspQryHedgeVolume(CFfexFtdcHedgeVolumeField *pHedgeVolume, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///信用限额查询应答
	virtual void OnRspQryCreditLimit(CFfexFtdcCreditLimitField *pCreditLimit, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///非标组合报单查询应答
	virtual void OnRspQryCombOrder(CFfexFtdcCombOrderField *pCombOrder, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///普通行情查询应答
	virtual void OnRspQryMarketData(CFfexFtdcMarketDataField *pMarketData, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///交易所公告查询请求应答
	virtual void OnRspQryBulletin(CFfexFtdcBulletinField *pBulletin, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///主题查询应答
	virtual void OnRspQryTopic(CFfexFtdcDisseminationField *pDissemination, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///合约价位查询应答
	virtual void OnRspQryMBLMarketData(CFfexFtdcMBLMarketDataField *pMBLMarketData, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///成交回报
	virtual void OnRtnTrade(CFfexFtdcTradeField *pTrade) {};

	///报单回报
	virtual void OnRtnOrder(CFfexFtdcOrderField *pOrder) {};

	///执行宣告回报
	virtual void OnRtnExecOrder(CFfexFtdcExecOrderField *pExecOrder) {};

	///报价回报
	virtual void OnRtnQuote(CFfexFtdcQuoteField *pQuote) {};

	///非标组合报单回报
	virtual void OnRtnCombOrder(CFfexFtdcCombOrderField *pCombOrder) {};

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CFfexFtdcInstrumentStatusField *pInstrumentStatus) {};

	///增加合约通知
	virtual void OnRtnInsInstrument(CFfexFtdcInstrumentField *pInstrument) {};

	///删除合约通知
	virtual void OnRtnDelInstrument(CFfexFtdcInstrumentField *pInstrument) {};

	///增加合约单腿通知
	virtual void OnRtnInsCombinationLeg(CFfexFtdcCombinationLegField *pCombinationLeg) {};

	///删除合约单腿通知
	virtual void OnRtnDelCombinationLeg(CFfexFtdcCombinationLegField *pCombinationLeg) {};

	///别名定义通知
	virtual void OnRtnAliasDefine(CFfexFtdcAliasDefineField *pAliasDefine) {};

	///数据流回退通知
	virtual void OnRtnFlowMessageCancel(CFfexFtdcFlowMessageCancelField *pFlowMessageCancel) {};

	///公告通知
	virtual void OnRtnBulletin(CFfexFtdcBulletinField *pBulletin) {};

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(CFfexFtdcInputOrderField *pInputOrder, CFfexFtdcRspInfoField *pRspInfo) {};

	///报单操作错误回报
	virtual void OnErrRtnOrderAction(CFfexFtdcOrderActionField *pOrderAction, CFfexFtdcRspInfoField *pRspInfo) {};

	///报价录入错误回报
	virtual void OnErrRtnQuoteInsert(CFfexFtdcInputQuoteField *pInputQuote, CFfexFtdcRspInfoField *pRspInfo) {};

	///报价操作错误回报
	virtual void OnErrRtnQuoteAction(CFfexFtdcQuoteActionField *pQuoteAction, CFfexFtdcRspInfoField *pRspInfo) {};

	///执行宣告录入错误回报
	virtual void OnErrRtnExecOrderInsert(CFfexFtdcInputExecOrderField *pInputExecOrder, CFfexFtdcRspInfoField *pRspInfo) {};

	///执行宣告操作错误回报
	virtual void OnErrRtnExecOrderAction(CFfexFtdcExecOrderActionField *pExecOrderAction, CFfexFtdcRspInfoField *pRspInfo) {};

	///非标组合报单录入错误回报
	virtual void OnErrRtnCombOrderInsert(CFfexFtdcInputCombOrderField *pInputCombOrder, CFfexFtdcRspInfoField *pRspInfo) {};

	///询价应答
	virtual void OnRspForQuote(CFfexFtdcInputReqForQuoteField *pInputReqForQuote, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///询价通知
	virtual void OnRtnForQuote(CFfexFtdcInputReqForQuoteField *pInputReqForQuote) {};

	///客户申请组合应答
	virtual void OnRspMarginCombAction(CFfexFtdcMarginCombActionField *pMarginCombAction, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///交易编码组合持仓查询应答
	virtual void OnRspQryPartClientCombPosition(CFfexFtdcPartClientCombPositionField *pPartClientCombPosition, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///组合规则通知
	virtual void OnRtnMarginCombinationLeg(CFfexFtdcMarginCombinationLegField *pMarginCombinationLeg) {};

	///交易编码单腿持仓查询应答
	virtual void OnRspQryPartClientLegPosition(CFfexFtdcPartClientLegPositionField *pPartClientLegPosition, CFfexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///客户申请组合通知
	virtual void OnRtnMarginCombAction(CFfexFtdcMarginCombActionField *pMarginCombAction) {};
};

class TRADER_API_EXPORT CFfexFtdcTraderApi
{
public:
	///创建TraderApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///@return 创建出的UserApi
	static CFfexFtdcTraderApi *CreateFtdcTraderApi(const char *pszFlowPath = "");
	
	///获取系统版本号
	///@param nMajorVersion 主版本号
	///@param nMinorVersion 子版本号
	///@return 系统标识字符串
	static const char *GetVersion(int &nMajorVersion, int &nMinorVersion);
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init() = 0;
	
	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;
	
	///获取当前交易日
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	virtual const char *GetTradingDay() = 0;
	
	///注册名字服务器网络地址
	///@param pszNsAddress：名字服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CFfexFtdcTraderSpi *pSpi) = 0;
	
	///加载证书
	///@param pszCertFileName 用户证书文件名
	///@param pszKeyFileName 用户私钥文件名
	///@param pszCaFileName 可信任CA证书文件名
	///@param pszKeyFilePassword 用户私钥文件密码
	///@return 0 操作成功
	///@return -1 可信任CA证书载入失败
	///@return -2 用户证书载入失败
	///@return -3 用户私钥载入失败	
	///@return -4 用户证书校验失败
	virtual int RegisterCertificateFile(const char *pszCertFileName, const char *pszKeyFileName, 
		const char *pszCaFileName, const char *pszKeyFilePassword) = 0;

	///订阅私有流。
	///@param nResumeType 私有流重传方式  
	///        TERT_RESTART:从本交易日开始重传
	///        TERT_RESUME:从上次收到的续传
	///        TERT_QUICK:只传送登录后私有流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
	virtual void SubscribePrivateTopic(TE_RESUME_TYPE nResumeType) = 0;
	
	///订阅公共流。
	///@param nResumeType 公共流重传方式  
	///        TERT_RESTART:从本交易日开始重传
	///        TERT_RESUME:从上次收到的续传
	///        TERT_QUICK:只传送登录后公共流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
	virtual void SubscribePublicTopic(TE_RESUME_TYPE nResumeType) = 0;

	///订阅交易员流。
	///@param nResumeType 交易员流重传方式  
	///        TERT_RESTART:从本交易日开始重传
	///        TERT_RESUME:从上次收到的续传
	///        TERT_QUICK:只传送登录后交易员流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到交易员流的数据。
	virtual void SubscribeUserTopic(TE_RESUME_TYPE nResumeType) = 0;
	
	///设置心跳超时时间。
	///@param timeout 心跳超时时间(秒)  
	virtual void SetHeartbeatTimeout(unsigned int timeout) = 0;
	
	///打开请求日志文件
	///@param pszReqLogFileName 请求日志文件名  
	///@return 0 操作成功
	///@return -1 打开日志文件失败
	virtual int OpenRequestLog(const char *pszReqLogFileName) = 0;

	///打开应答日志文件
	///@param pszRspLogFileName 应答日志文件名  
	///@return 0 操作成功
	///@return -1 打开日志文件失败
	virtual int OpenResponseLog(const char *pszRspLogFileName) = 0;
	
	///订阅询价流。
	///@param nResumeType 询价流重传方式  
	///        TERT_RESTART:从本交易日开始重传
	///        TERT_RESUME:从上次收到的续传
	///        TERT_QUICK:只传送登录后询价流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到询价流的数据。
	virtual void SubscribeForQuote(TE_RESUME_TYPE nResumeType) = 0;


	///用户登录请求
	virtual int ReqUserLogin(CFfexFtdcReqUserLoginField *pReqUserLogin, int nRequestID) = 0;

	///用户退出请求
	virtual int ReqUserLogout(CFfexFtdcReqUserLogoutField *pReqUserLogout, int nRequestID) = 0;

	///报单录入请求
	virtual int ReqOrderInsert(CFfexFtdcInputOrderField *pInputOrder, int nRequestID) = 0;

	///报单操作请求
	virtual int ReqOrderAction(CFfexFtdcOrderActionField *pOrderAction, int nRequestID) = 0;

	///报价录入请求
	virtual int ReqQuoteInsert(CFfexFtdcInputQuoteField *pInputQuote, int nRequestID) = 0;

	///报价操作请求
	virtual int ReqQuoteAction(CFfexFtdcQuoteActionField *pQuoteAction, int nRequestID) = 0;

	///用户密码修改请求
	virtual int ReqUserPasswordUpdate(CFfexFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) = 0;

	///执行宣告录入请求
	virtual int ReqExecOrderInsert(CFfexFtdcInputExecOrderField *pInputExecOrder, int nRequestID) = 0;

	///执行宣告操作请求
	virtual int ReqExecOrderAction(CFfexFtdcExecOrderActionField *pExecOrderAction, int nRequestID) = 0;

	///管理报单录入请求
	virtual int ReqAdminOrderInsert(CFfexFtdcInputAdminOrderField *pInputAdminOrder, int nRequestID) = 0;

	///非标组合报单录入请求
	virtual int ReqCombOrderInsert(CFfexFtdcInputCombOrderField *pInputCombOrder, int nRequestID) = 0;

	///订阅主题请求
	virtual int ReqSubscribeTopic(CFfexFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///会员资金查询请求
	virtual int ReqQryPartAccount(CFfexFtdcQryPartAccountField *pQryPartAccount, int nRequestID) = 0;

	///报单查询请求
	virtual int ReqQryOrder(CFfexFtdcQryOrderField *pQryOrder, int nRequestID) = 0;

	///报价查询请求
	virtual int ReqQryQuote(CFfexFtdcQryQuoteField *pQryQuote, int nRequestID) = 0;

	///成交单查询请求
	virtual int ReqQryTrade(CFfexFtdcQryTradeField *pQryTrade, int nRequestID) = 0;

	///会员客户查询请求
	virtual int ReqQryClient(CFfexFtdcQryClientField *pQryClient, int nRequestID) = 0;

	///会员持仓查询请求
	virtual int ReqQryPartPosition(CFfexFtdcQryPartPositionField *pQryPartPosition, int nRequestID) = 0;

	///客户持仓查询请求
	virtual int ReqQryClientPosition(CFfexFtdcQryClientPositionField *pQryClientPosition, int nRequestID) = 0;

	///合约查询请求
	virtual int ReqQryInstrument(CFfexFtdcQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///合约交易状态查询请求
	virtual int ReqQryInstrumentStatus(CFfexFtdcQryInstrumentStatusField *pQryInstrumentStatus, int nRequestID) = 0;

	///保值额度查询
	virtual int ReqQryHedgeVolume(CFfexFtdcQryHedgeVolumeField *pQryHedgeVolume, int nRequestID) = 0;

	///信用限额查询请求
	virtual int ReqQryCreditLimit(CFfexFtdcQryCreditLimitField *pQryCreditLimit, int nRequestID) = 0;

	///非标组合报单查询请求
	virtual int ReqQryCombOrder(CFfexFtdcQryCombOrderField *pQryCombOrder, int nRequestID) = 0;

	///普通行情查询请求
	virtual int ReqQryMarketData(CFfexFtdcQryMarketDataField *pQryMarketData, int nRequestID) = 0;

	///交易所公告查询请求
	virtual int ReqQryBulletin(CFfexFtdcQryBulletinField *pQryBulletin, int nRequestID) = 0;

	///主题查询请求
	virtual int ReqQryTopic(CFfexFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///合约价位查询
	virtual int ReqQryMBLMarketData(CFfexFtdcQryMBLMarketDataField *pQryMBLMarketData, int nRequestID) = 0;

	///询价请求
	virtual int ReqForQuote(CFfexFtdcInputReqForQuoteField *pInputReqForQuote, int nRequestID) = 0;

	///客户申请组合请求
	virtual int ReqMarginCombAction(CFfexFtdcMarginCombActionField *pMarginCombAction, int nRequestID) = 0;

	///交易编码组合持仓查询请求
	virtual int ReqQryPartClientCombPosition(CFfexFtdcQryPartClientCombPositionField *pQryPartClientCombPosition, int nRequestID) = 0;

	///交易编码单腿持仓查询请求
	virtual int ReqQryPartClientLegPosition(CFfexFtdcQryPartClientLegPositionField *pQryPartClientLegPosition, int nRequestID) = 0;
protected:
	~CFfexFtdcTraderApi(){};
};

#endif

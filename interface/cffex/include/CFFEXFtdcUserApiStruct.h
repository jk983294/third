/////////////////////////////////////////////////////////////////////////
///@system 新一代交易所系统
///@company 中国金融期货交易所股份有限公司
///@file CFFEXFtdcUserApiStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(_FTDCSTRUCT_H)
#define _FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CFFEXFtdcUserApiDataType.h"

///信息分发
struct CFfexFtdcDisseminationField
{
	///序列系列号
	TFfexFtdcSequenceSeriesType	SequenceSeries;
	///序列号
	TFfexFtdcSequenceNoType	SequenceNo;
};
///响应信息
struct CFfexFtdcRspInfoField
{
	///错误代码
	TFfexFtdcErrorIDType	ErrorID;
	///错误信息
	TFfexFtdcErrorMsgType	ErrorMsg;
};
///通讯阶段
struct CFfexFtdcCommPhaseField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///通讯时段号
	TFfexFtdcCommPhaseNoType	CommPhaseNo;
};
///交易所交易日
struct CFfexFtdcExchangeTradingDayField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///交易所代码
	TFfexFtdcExchangeIDType	ExchangeID;
};
///结算会话
struct CFfexFtdcSettlementSessionField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
};
///当前时间
struct CFfexFtdcCurrentTimeField
{
	///当前日期
	TFfexFtdcDateType	CurrDate;
	///当前时间
	TFfexFtdcTimeType	CurrTime;
	///当前时间（毫秒）
	TFfexFtdcMillisecType	CurrMillisec;
};
///用户登录请求
struct CFfexFtdcReqUserLoginField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///密码
	TFfexFtdcPasswordType	Password;
	///用户端产品信息
	TFfexFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TFfexFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TFfexFtdcProtocolInfoType	ProtocolInfo;
	///数据中心代码
	TFfexFtdcDataCenterIDType	DataCenterID;
};
///用户登录应答
struct CFfexFtdcRspUserLoginField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///登录成功时间
	TFfexFtdcTimeType	LoginTime;
	///最大本地报单号
	TFfexFtdcOrderLocalIDType	MaxOrderLocalID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///交易系统名称
	TFfexFtdcTradingSystemNameType	TradingSystemName;
	///数据中心代码
	TFfexFtdcDataCenterIDType	DataCenterID;
	///会员私有流当前长度
	TFfexFtdcSequenceNoType	PrivateFlowSize;
	///交易员私有流当前长度
	TFfexFtdcSequenceNoType	UserFlowSize;
};
///用户登出请求
struct CFfexFtdcReqUserLogoutField
{
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
};
///用户登出应答
struct CFfexFtdcRspUserLogoutField
{
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
};
///输入报单
struct CFfexFtdcInputOrderField
{
	///报单编号
	TFfexFtdcOrderSysIDType	OrderSysID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///报单价格条件
	TFfexFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TFfexFtdcDirectionType	Direction;
	///组合开平标志
	TFfexFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TFfexFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TFfexFtdcPriceType	LimitPrice;
	///数量
	TFfexFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TFfexFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TFfexFtdcDateType	GTDDate;
	///成交量类型
	TFfexFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TFfexFtdcVolumeType	MinVolume;
	///触发条件
	TFfexFtdcContingentConditionType	ContingentCondition;
	///止损价
	TFfexFtdcPriceType	StopPrice;
	///强平原因
	TFfexFtdcForceCloseReasonType	ForceCloseReason;
	///本地报单编号
	TFfexFtdcOrderLocalIDType	OrderLocalID;
	///自动挂起标志
	TFfexFtdcBoolType	IsAutoSuspend;
	///业务单元
	TFfexFtdcBusinessUnitType	BusinessUnit;
};
///报单操作
struct CFfexFtdcOrderActionField
{
	///报单编号
	TFfexFtdcOrderSysIDType	OrderSysID;
	///本地报单编号
	TFfexFtdcOrderLocalIDType	OrderLocalID;
	///报单操作标志
	TFfexFtdcActionFlagType	ActionFlag;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///价格
	TFfexFtdcPriceType	LimitPrice;
	///数量变化
	TFfexFtdcVolumeType	VolumeChange;
	///操作本地编号
	TFfexFtdcOrderLocalIDType	ActionLocalID;
	///业务单元
	TFfexFtdcBusinessUnitType	BusinessUnit;
};
///OTC报单
struct CFfexFtdcOTCOrderField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///OTC报单编号
	TFfexFtdcOTCOrderSysIDType	OTCOrderSysID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TFfexFtdcDirectionType	Direction;
	///开平标志
	TFfexFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TFfexFtdcHedgeFlagType	HedgeFlag;
	///价格
	TFfexFtdcPriceType	Price;
	///数量
	TFfexFtdcVolumeType	Volume;
	///对手方会员代码
	TFfexFtdcParticipantIDType	OtherParticipantID;
	///对手方客户代码
	TFfexFtdcClientIDType	OtherClientID;
	///对手方交易用户代码
	TFfexFtdcUserIDType	OtherUserID;
	///对手方开平标志
	TFfexFtdcOffsetFlagType	OtherOffsetFlag;
	///对手方套保标志
	TFfexFtdcHedgeFlagType	OtherHedgeFlag;
	///本地OTC报单编号
	TFfexFtdcOrderLocalIDType	OTCOrderLocalID;
	///OTC报单状态
	TFfexFtdcOTCOrderStatusType	OTCOrderStatus;
	///插入时间
	TFfexFtdcTimeType	InsertTime;
	///撤销时间
	TFfexFtdcTimeType	CancelTime;
	///结算会员编号
	TFfexFtdcParticipantIDType	ClearingPartID;
	///对手方结算会员编号
	TFfexFtdcParticipantIDType	OtherClearingPartID;
};
///输入报价
struct CFfexFtdcInputQuoteField
{
	///报价编号
	TFfexFtdcQuoteSysIDType	QuoteSysID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///买入数量
	TFfexFtdcVolumeType	BidVolume;
	///卖出数量
	TFfexFtdcVolumeType	AskVolume;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///本地报价编号
	TFfexFtdcOrderLocalIDType	QuoteLocalID;
	///业务单元
	TFfexFtdcBusinessUnitType	BusinessUnit;
	///买方组合开平标志
	TFfexFtdcCombOffsetFlagType	BidCombOffsetFlag;
	///买方组合套保标志
	TFfexFtdcCombHedgeFlagType	BidCombHedgeFlag;
	///买方价格
	TFfexFtdcPriceType	BidPrice;
	///卖方组合开平标志
	TFfexFtdcCombOffsetFlagType	AskCombOffsetFlag;
	///卖方组合套保标志
	TFfexFtdcCombHedgeFlagType	AskCombHedgeFlag;
	///卖方价格
	TFfexFtdcPriceType	AskPrice;
};
///报价操作
struct CFfexFtdcQuoteActionField
{
	///报价编号
	TFfexFtdcQuoteSysIDType	QuoteSysID;
	///本地报价编号
	TFfexFtdcOrderLocalIDType	QuoteLocalID;
	///报单操作标志
	TFfexFtdcActionFlagType	ActionFlag;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///操作本地编号
	TFfexFtdcOrderLocalIDType	ActionLocalID;
	///业务单元
	TFfexFtdcBusinessUnitType	BusinessUnit;
};
///输入执行宣告
struct CFfexFtdcInputExecOrderField
{
	///合约编号
	TFfexFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///本地执行宣告编号
	TFfexFtdcOrderLocalIDType	ExecOrderLocalID;
	///数量
	TFfexFtdcVolumeType	Volume;
	///业务单元
	TFfexFtdcBusinessUnitType	BusinessUnit;
};
///执行宣告操作
struct CFfexFtdcExecOrderActionField
{
	///执行宣告编号
	TFfexFtdcExecOrderSysIDType	ExecOrderSysID;
	///本地执行宣告编号
	TFfexFtdcOrderLocalIDType	ExecOrderLocalID;
	///报单操作标志
	TFfexFtdcActionFlagType	ActionFlag;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///操作本地编号
	TFfexFtdcOrderLocalIDType	ActionLocalID;
	///业务单元
	TFfexFtdcBusinessUnitType	BusinessUnit;
};
///用户登录退出
struct CFfexFtdcUserLogoutField
{
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
};
///用户口令修改
struct CFfexFtdcUserPasswordUpdateField
{
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///旧密码
	TFfexFtdcPasswordType	OldPassword;
	///新密码
	TFfexFtdcPasswordType	NewPassword;
};
///输入非标组合报单
struct CFfexFtdcInputCombOrderField
{
	///组合报单编号
	TFfexFtdcOrderSysIDType	CombOrderSysID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///价格
	TFfexFtdcPriceType	LimitPrice;
	///数量
	TFfexFtdcVolumeType	VolumeTotalOriginal;
	///本地报单编号
	TFfexFtdcOrderLocalIDType	CombOrderLocalID;
	///业务单元
	TFfexFtdcBusinessUnitType	BusinessUnit;
	///合约代码1
	TFfexFtdcInstrumentIDType	InstrumentID1;
	///买卖方向1
	TFfexFtdcDirectionType	Direction1;
	///分腿乘数1
	TFfexFtdcLegMultipleType	LegMultiple1;
	///开平标志1
	TFfexFtdcOffsetFlagType	OffsetFlag1;
	///投机套保标志1
	TFfexFtdcHedgeFlagType	HedgeFlag1;
	///合约代码2
	TFfexFtdcInstrumentIDType	InstrumentID2;
	///买卖方向2
	TFfexFtdcDirectionType	Direction2;
	///分腿乘数2
	TFfexFtdcLegMultipleType	LegMultiple2;
	///开平标志2
	TFfexFtdcOffsetFlagType	OffsetFlag2;
	///投机套保标志2
	TFfexFtdcHedgeFlagType	HedgeFlag2;
	///合约代码3
	TFfexFtdcInstrumentIDType	InstrumentID3;
	///买卖方向3
	TFfexFtdcDirectionType	Direction3;
	///分腿乘数3
	TFfexFtdcLegMultipleType	LegMultiple3;
	///开平标志3
	TFfexFtdcOffsetFlagType	OffsetFlag3;
	///投机套保标志3
	TFfexFtdcHedgeFlagType	HedgeFlag3;
	///合约代码4
	TFfexFtdcInstrumentIDType	InstrumentID4;
	///买卖方向4
	TFfexFtdcDirectionType	Direction4;
	///分腿乘数4
	TFfexFtdcLegMultipleType	LegMultiple4;
	///开平标志4
	TFfexFtdcOffsetFlagType	OffsetFlag4;
	///投机套保标志4
	TFfexFtdcHedgeFlagType	HedgeFlag4;
};
///强制用户退出
struct CFfexFtdcForceUserExitField
{
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
};
///会员资金帐户入金
struct CFfexFtdcAccountDepositField
{
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///资金账号
	TFfexFtdcAccountIDType	Account;
	///入金金额
	TFfexFtdcMoneyType	Deposit;
};
///报单查询
struct CFfexFtdcQryOrderField
{
	///起始会员代码
	TFfexFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TFfexFtdcParticipantIDType	PartIDEnd;
	///报单编号
	TFfexFtdcOrderSysIDType	OrderSysID;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///开始时间
	TFfexFtdcTimeType	TimeStart;
	///结束时间
	TFfexFtdcTimeType	TimeEnd;
};
///报价查询
struct CFfexFtdcQryQuoteField
{
	///起始会员代码
	TFfexFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TFfexFtdcParticipantIDType	PartIDEnd;
	///报价编号
	TFfexFtdcQuoteSysIDType	QuoteSysID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
};
///成交查询
struct CFfexFtdcQryTradeField
{
	///起始会员代码
	TFfexFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TFfexFtdcParticipantIDType	PartIDEnd;
	///起始合约代码
	TFfexFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TFfexFtdcInstrumentIDType	InstIDEnd;
	///成交编号
	TFfexFtdcTradeIDType	TradeID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///开始时间
	TFfexFtdcTimeType	TimeStart;
	///结束时间
	TFfexFtdcTimeType	TimeEnd;
};
///行情查询
struct CFfexFtdcQryMarketDataField
{
	///产品代码
	TFfexFtdcProductIDType	ProductID;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
};
///客户查询
struct CFfexFtdcQryClientField
{
	///起始会员代码
	TFfexFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TFfexFtdcParticipantIDType	PartIDEnd;
	///起始客户代码
	TFfexFtdcClientIDType	ClientIDStart;
	///结束客户代码
	TFfexFtdcClientIDType	ClientIDEnd;
};
///会员持仓查询
struct CFfexFtdcQryPartPositionField
{
	///起始会员代码
	TFfexFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TFfexFtdcParticipantIDType	PartIDEnd;
	///起始合约代码
	TFfexFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TFfexFtdcInstrumentIDType	InstIDEnd;
};
///客户持仓查询
struct CFfexFtdcQryClientPositionField
{
	///起始会员代码
	TFfexFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TFfexFtdcParticipantIDType	PartIDEnd;
	///起始客户代码
	TFfexFtdcClientIDType	ClientIDStart;
	///结束客户代码
	TFfexFtdcClientIDType	ClientIDEnd;
	///起始合约代码
	TFfexFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TFfexFtdcInstrumentIDType	InstIDEnd;
	///客户类型
	TFfexFtdcClientTypeType	ClientType;
};
///交易资金查询
struct CFfexFtdcQryPartAccountField
{
	///起始会员代码
	TFfexFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TFfexFtdcParticipantIDType	PartIDEnd;
	///资金帐号
	TFfexFtdcAccountIDType	AccountID;
};
///合约查询
struct CFfexFtdcQryInstrumentField
{
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///产品组代码
	TFfexFtdcProductGroupIDType	ProductGroupID;
	///产品代码
	TFfexFtdcProductIDType	ProductID;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
};
///合约状态查询
struct CFfexFtdcQryInstrumentStatusField
{
	///起始合约代码
	TFfexFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TFfexFtdcInstrumentIDType	InstIDEnd;
};
///结算组状态查询
struct CFfexFtdcQrySGDataSyncStatusField
{
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
};
///用户在线查询
struct CFfexFtdcQryUserSessionField
{
	///起始交易用户代码
	TFfexFtdcUserIDType	UserIDStart;
	///结束交易用户代码
	TFfexFtdcUserIDType	UserIDEnd;
};
///用户查询
struct CFfexFtdcQryUserField
{
	///起始交易用户代码
	TFfexFtdcUserIDType	UserIDStart;
	///结束交易用户代码
	TFfexFtdcUserIDType	UserIDEnd;
};
///公告查询
struct CFfexFtdcQryBulletinField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///市场代码
	TFfexFtdcMarketIDType	MarketID;
	///公告编号
	TFfexFtdcBulletinIDType	BulletinID;
	///公告类型
	TFfexFtdcNewsTypeType	NewsType;
	///紧急程度
	TFfexFtdcNewsUrgencyType	NewsUrgency;
};
///会员查询
struct CFfexFtdcQryParticipantField
{
	///起始会员代码
	TFfexFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TFfexFtdcParticipantIDType	PartIDEnd;
};
///保值额度查询
struct CFfexFtdcQryHedgeVolumeField
{
	///起始会员代码
	TFfexFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TFfexFtdcParticipantIDType	PartIDEnd;
	///起始客户代码
	TFfexFtdcClientIDType	ClientIDStart;
	///结束客户代码
	TFfexFtdcClientIDType	ClientIDEnd;
	///起始合约代码
	TFfexFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TFfexFtdcInstrumentIDType	InstIDEnd;
};
///合约价位查询
struct CFfexFtdcQryMBLMarketDataField
{
	///起始合约代码
	TFfexFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TFfexFtdcInstrumentIDType	InstIDEnd;
	///买卖方向
	TFfexFtdcDirectionType	Direction;
};
///信用限额查询
struct CFfexFtdcQryCreditLimitField
{
	///交易会员编号
	TFfexFtdcParticipantIDType	ParticipantID;
	///结算会员编号
	TFfexFtdcParticipantIDType	ClearingPartID;
};
///非标组合报单查询
struct CFfexFtdcQryCombOrderField
{
	///起始会员代码
	TFfexFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TFfexFtdcParticipantIDType	PartIDEnd;
	///组合报单编号
	TFfexFtdcOrderSysIDType	CombOrderSysID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
};
///会员资金应答
struct CFfexFtdcRspPartAccountField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///上次结算准备金
	TFfexFtdcMoneyType	PreBalance;
	///当前保证金总额
	TFfexFtdcMoneyType	CurrMargin;
	///平仓盈亏
	TFfexFtdcMoneyType	CloseProfit;
	///期权权利金收支
	TFfexFtdcMoneyType	Premium;
	///入金金额
	TFfexFtdcMoneyType	Deposit;
	///出金金额
	TFfexFtdcMoneyType	Withdraw;
	///期货结算准备金
	TFfexFtdcMoneyType	Balance;
	///可提资金
	TFfexFtdcMoneyType	Available;
	///资金帐号
	TFfexFtdcAccountIDType	AccountID;
	///冻结的保证金
	TFfexFtdcMoneyType	FrozenMargin;
	///冻结的权利金
	TFfexFtdcMoneyType	FrozenPremium;
	///基本准备金
	TFfexFtdcMoneyType	BaseReserve;
};
///会员持仓应答
struct CFfexFtdcRspPartPositionField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///投机套保标志
	TFfexFtdcHedgeFlagType	HedgeFlag;
	///持仓多空方向
	TFfexFtdcPosiDirectionType	PosiDirection;
	///上日持仓
	TFfexFtdcVolumeType	YdPosition;
	///今日持仓
	TFfexFtdcVolumeType	Position;
	///多头冻结
	TFfexFtdcVolumeType	LongFrozen;
	///空头冻结
	TFfexFtdcVolumeType	ShortFrozen;
	///昨日多头冻结
	TFfexFtdcVolumeType	YdLongFrozen;
	///昨日空头冻结
	TFfexFtdcVolumeType	YdShortFrozen;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///交易角色
	TFfexFtdcTradingRoleType	TradingRole;
};
///客户持仓应答
struct CFfexFtdcRspClientPositionField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///投机套保标志
	TFfexFtdcHedgeFlagType	HedgeFlag;
	///持仓多空方向
	TFfexFtdcPosiDirectionType	PosiDirection;
	///上日持仓
	TFfexFtdcVolumeType	YdPosition;
	///今日持仓
	TFfexFtdcVolumeType	Position;
	///多头冻结
	TFfexFtdcVolumeType	LongFrozen;
	///空头冻结
	TFfexFtdcVolumeType	ShortFrozen;
	///昨日多头冻结
	TFfexFtdcVolumeType	YdLongFrozen;
	///昨日空头冻结
	TFfexFtdcVolumeType	YdShortFrozen;
	///当日买成交量
	TFfexFtdcVolumeType	BuyTradeVolume;
	///当日卖成交量
	TFfexFtdcVolumeType	SellTradeVolume;
	///持仓成本
	TFfexFtdcMoneyType	PositionCost;
	///昨日持仓成本
	TFfexFtdcMoneyType	YdPositionCost;
	///占用的保证金
	TFfexFtdcMoneyType	UseMargin;
	///冻结的保证金
	TFfexFtdcMoneyType	FrozenMargin;
	///多头冻结的保证金
	TFfexFtdcMoneyType	LongFrozenMargin;
	///空头冻结的保证金
	TFfexFtdcMoneyType	ShortFrozenMargin;
	///冻结的权利金
	TFfexFtdcMoneyType	FrozenPremium;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
};
///合约查询应答
struct CFfexFtdcRspInstrumentField
{
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///产品代码
	TFfexFtdcProductIDType	ProductID;
	///产品组代码
	TFfexFtdcProductGroupIDType	ProductGroupID;
	///基础商品代码
	TFfexFtdcInstrumentIDType	UnderlyingInstrID;
	///产品类型
	TFfexFtdcProductClassType	ProductClass;
	///持仓类型
	TFfexFtdcPositionTypeType	PositionType;
	///执行价
	TFfexFtdcPriceType	StrikePrice;
	///期权类型
	TFfexFtdcOptionsTypeType	OptionsType;
	///合约数量乘数
	TFfexFtdcVolumeMultipleType	VolumeMultiple;
	///合约基础商品乘数
	TFfexFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///合约名称
	TFfexFtdcInstrumentNameType	InstrumentName;
	///交割年份
	TFfexFtdcYearType	DeliveryYear;
	///交割月
	TFfexFtdcMonthType	DeliveryMonth;
	///提前月份
	TFfexFtdcAdvanceMonthType	AdvanceMonth;
	///当前是否交易
	TFfexFtdcBoolType	IsTrading;
	///创建日
	TFfexFtdcDateType	CreateDate;
	///上市日
	TFfexFtdcDateType	OpenDate;
	///到期日
	TFfexFtdcDateType	ExpireDate;
	///开始交割日
	TFfexFtdcDateType	StartDelivDate;
	///最后交割日
	TFfexFtdcDateType	EndDelivDate;
	///挂牌基准价
	TFfexFtdcPriceType	BasisPrice;
	///市价单最大下单量
	TFfexFtdcVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TFfexFtdcVolumeType	MinMarketOrderVolume;
	///限价单最大下单量
	TFfexFtdcVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TFfexFtdcVolumeType	MinLimitOrderVolume;
	///最小变动价位
	TFfexFtdcPriceType	PriceTick;
	///交割月自然人开仓
	TFfexFtdcMonthCountType	AllowDelivPersonOpen;
};
///信息查询
struct CFfexFtdcQryInformationField
{
	///起始信息代码
	TFfexFtdcInformationIDType	InformationIDStart;
	///结束信息代码
	TFfexFtdcInformationIDType	InformationIDEnd;
};
///信息查询
struct CFfexFtdcInformationField
{
	///信息编号
	TFfexFtdcInformationIDType	InformationID;
	///序列号
	TFfexFtdcSequenceNoType	SequenceNo;
	///消息正文
	TFfexFtdcContentType	Content;
	///正文长度
	TFfexFtdcContentLengthType	ContentLength;
	///是否完成
	TFfexFtdcBoolType	IsAccomplished;
};
///信用限额
struct CFfexFtdcCreditLimitField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///上次结算准备金
	TFfexFtdcMoneyType	PreBalance;
	///当前保证金总额
	TFfexFtdcMoneyType	CurrMargin;
	///平仓盈亏
	TFfexFtdcMoneyType	CloseProfit;
	///期权权利金收支
	TFfexFtdcMoneyType	Premium;
	///入金金额
	TFfexFtdcMoneyType	Deposit;
	///出金金额
	TFfexFtdcMoneyType	Withdraw;
	///期货结算准备金
	TFfexFtdcMoneyType	Balance;
	///可提资金
	TFfexFtdcMoneyType	Available;
	///交易会员编号
	TFfexFtdcParticipantIDType	ParticipantID;
	///结算会员编号
	TFfexFtdcParticipantIDType	ClearingPartID;
	///冻结的保证金
	TFfexFtdcMoneyType	FrozenMargin;
	///冻结的权利金
	TFfexFtdcMoneyType	FrozenPremium;
};
///客户查询应答
struct CFfexFtdcRspClientField
{
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///客户名称
	TFfexFtdcPartyNameType	ClientName;
	///证件类型
	TFfexFtdcIdCardTypeType	IdentifiedCardType;
	///原证件号码
	TFfexFtdcIdentifiedCardNoV1Type	UseLess;
	///交易角色
	TFfexFtdcTradingRoleType	TradingRole;
	///客户类型
	TFfexFtdcClientTypeType	ClientType;
	///是否活跃
	TFfexFtdcBoolType	IsActive;
	///会员号
	TFfexFtdcParticipantIDType	ParticipantID;
	///证件号码
	TFfexFtdcIdentifiedCardNoType	IdentifiedCardNo;
};
///数据流回退
struct CFfexFtdcFlowMessageCancelField
{
	///序列系列号
	TFfexFtdcSequenceSeriesType	SequenceSeries;
	///交易日
	TFfexFtdcDateType	TradingDay;
	///数据中心代码
	TFfexFtdcDataCenterIDType	DataCenterID;
	///回退起始序列号
	TFfexFtdcSequenceNoType	StartSequenceNo;
	///回退结束序列号
	TFfexFtdcSequenceNoType	EndSequenceNo;
};
///会员
struct CFfexFtdcParticipantField
{
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///会员名称
	TFfexFtdcParticipantNameType	ParticipantName;
	///会员简称
	TFfexFtdcParticipantAbbrType	ParticipantAbbr;
	///会员类型
	TFfexFtdcMemberTypeType	MemberType;
	///是否活跃
	TFfexFtdcBoolType	IsActive;
};
///用户
struct CFfexFtdcUserField
{
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///交易用户类型
	TFfexFtdcUserTypeType	UserType;
	///密码
	TFfexFtdcPasswordType	Password;
	///交易员权限
	TFfexFtdcUserActiveType	IsActive;
};
///客户
struct CFfexFtdcClientField
{
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///客户名称
	TFfexFtdcPartyNameType	ClientName;
	///证件类型
	TFfexFtdcIdCardTypeType	IdentifiedCardType;
	///证件号码
	TFfexFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///交易角色
	TFfexFtdcTradingRoleType	TradingRole;
	///客户类型
	TFfexFtdcClientTypeType	ClientType;
	///是否活跃
	TFfexFtdcBoolType	IsActive;
	///客户交易类型
	TFfexFtdcHedgeFlagType	HedgeFlag;
};
///用户会话
struct CFfexFtdcUserSessionField
{
	///前置编号
	TFfexFtdcFrontIDType	FrontID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///交易用户类型
	TFfexFtdcUserTypeType	UserType;
	///会话编号
	TFfexFtdcSessionIDType	SessionID;
	///登录时间
	TFfexFtdcTimeType	LoginTime;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///IP地址
	TFfexFtdcIPAddressType	IPAddress;
	///用户端产品信息
	TFfexFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TFfexFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TFfexFtdcProtocolInfoType	ProtocolInfo;
};
///产品组
struct CFfexFtdcProductGroupField
{
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///产品组代码
	TFfexFtdcProductGroupIDType	ProductGroupID;
	///产品组名称
	TFfexFtdcProductGroupNameType	ProductGroupName;
	///商品代码
	TFfexFtdcCommodityIDType	CommodityID;
};
///产品
struct CFfexFtdcProductField
{
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///产品代码
	TFfexFtdcProductIDType	ProductID;
	///产品组代码
	TFfexFtdcProductGroupIDType	ProductGroupID;
	///产品名称
	TFfexFtdcProductNameType	ProductName;
	///产品类型
	TFfexFtdcProductClassType	ProductClass;
};
///合约
struct CFfexFtdcInstrumentField
{
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///产品代码
	TFfexFtdcProductIDType	ProductID;
	///产品组代码
	TFfexFtdcProductGroupIDType	ProductGroupID;
	///基础商品代码
	TFfexFtdcInstrumentIDType	UnderlyingInstrID;
	///产品类型
	TFfexFtdcProductClassType	ProductClass;
	///持仓类型
	TFfexFtdcPositionTypeType	PositionType;
	///执行价
	TFfexFtdcPriceType	StrikePrice;
	///期权类型
	TFfexFtdcOptionsTypeType	OptionsType;
	///合约数量乘数
	TFfexFtdcVolumeMultipleType	VolumeMultiple;
	///合约基础商品乘数
	TFfexFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///合约名称
	TFfexFtdcInstrumentNameType	InstrumentName;
	///交割年份
	TFfexFtdcYearType	DeliveryYear;
	///交割月
	TFfexFtdcMonthType	DeliveryMonth;
	///提前月份
	TFfexFtdcAdvanceMonthType	AdvanceMonth;
	///当前是否交易
	TFfexFtdcBoolType	IsTrading;
};
///组合交易合约的单腿
struct CFfexFtdcCombinationLegField
{
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///组合合约代码
	TFfexFtdcInstrumentIDType	CombInstrumentID;
	///单腿编号
	TFfexFtdcLegIDType	LegID;
	///单腿合约代码
	TFfexFtdcInstrumentIDType	LegInstrumentID;
	///买卖方向
	TFfexFtdcDirectionType	Direction;
	///单腿乘数
	TFfexFtdcLegMultipleType	LegMultiple;
	///推导层数
	TFfexFtdcImplyLevelType	ImplyLevel;
};
///账户资金信息
struct CFfexFtdcAccountInfoField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///上次结算准备金
	TFfexFtdcMoneyType	PreBalance;
	///当前保证金总额
	TFfexFtdcMoneyType	CurrMargin;
	///平仓盈亏
	TFfexFtdcMoneyType	CloseProfit;
	///期权权利金收支
	TFfexFtdcMoneyType	Premium;
	///入金金额
	TFfexFtdcMoneyType	Deposit;
	///出金金额
	TFfexFtdcMoneyType	Withdraw;
	///期货结算准备金
	TFfexFtdcMoneyType	Balance;
	///可提资金
	TFfexFtdcMoneyType	Available;
	///开户日期
	TFfexFtdcDateType	DateAccountOpen;
	///上次结算的日期
	TFfexFtdcDateType	PreDate;
	///上结算的编号
	TFfexFtdcSettlementIDType	PreSettlementID;
	///上次保证金总额
	TFfexFtdcMoneyType	PreMargin;
	///期货保证金
	TFfexFtdcMoneyType	FuturesMargin;
	///期权保证金
	TFfexFtdcMoneyType	OptionsMargin;
	///持仓盈亏
	TFfexFtdcMoneyType	PositionProfit;
	///当日盈亏
	TFfexFtdcMoneyType	Profit;
	///利息收入
	TFfexFtdcMoneyType	Interest;
	///手续费
	TFfexFtdcMoneyType	Fee;
	///总质押金额
	TFfexFtdcMoneyType	TotalCollateral;
	///用质押抵的保证金金额
	TFfexFtdcMoneyType	CollateralForMargin;
	///上次资金利息积数
	TFfexFtdcMoneyType	PreAccmulateInterest;
	///资金利息积数
	TFfexFtdcMoneyType	AccumulateInterest;
	///质押手续费积数
	TFfexFtdcMoneyType	AccumulateFee;
	///冻结资金
	TFfexFtdcMoneyType	ForzenDeposit;
	///帐户状态
	TFfexFtdcAccountStatusType	AccountStatus;
	///资金帐号
	TFfexFtdcAccountIDType	AccountID;
};
///会员合约持仓
struct CFfexFtdcPartPositionField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///投机套保标志
	TFfexFtdcHedgeFlagType	HedgeFlag;
	///持仓多空方向
	TFfexFtdcPosiDirectionType	PosiDirection;
	///上日持仓
	TFfexFtdcVolumeType	YdPosition;
	///今日持仓
	TFfexFtdcVolumeType	Position;
	///多头冻结
	TFfexFtdcVolumeType	LongFrozen;
	///空头冻结
	TFfexFtdcVolumeType	ShortFrozen;
	///昨日多头冻结
	TFfexFtdcVolumeType	YdLongFrozen;
	///昨日空头冻结
	TFfexFtdcVolumeType	YdShortFrozen;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///交易角色
	TFfexFtdcTradingRoleType	TradingRole;
};
///客户合约持仓
struct CFfexFtdcClientPositionField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///投机套保标志
	TFfexFtdcHedgeFlagType	HedgeFlag;
	///持仓多空方向
	TFfexFtdcPosiDirectionType	PosiDirection;
	///上日持仓
	TFfexFtdcVolumeType	YdPosition;
	///今日持仓
	TFfexFtdcVolumeType	Position;
	///多头冻结
	TFfexFtdcVolumeType	LongFrozen;
	///空头冻结
	TFfexFtdcVolumeType	ShortFrozen;
	///昨日多头冻结
	TFfexFtdcVolumeType	YdLongFrozen;
	///昨日空头冻结
	TFfexFtdcVolumeType	YdShortFrozen;
	///当日买成交量
	TFfexFtdcVolumeType	BuyTradeVolume;
	///当日卖成交量
	TFfexFtdcVolumeType	SellTradeVolume;
	///持仓成本
	TFfexFtdcMoneyType	PositionCost;
	///昨日持仓成本
	TFfexFtdcMoneyType	YdPositionCost;
	///占用的保证金
	TFfexFtdcMoneyType	UseMargin;
	///冻结的保证金
	TFfexFtdcMoneyType	FrozenMargin;
	///多头冻结的保证金
	TFfexFtdcMoneyType	LongFrozenMargin;
	///空头冻结的保证金
	TFfexFtdcMoneyType	ShortFrozenMargin;
	///冻结的权利金
	TFfexFtdcMoneyType	FrozenPremium;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
};
///保值额度量
struct CFfexFtdcHedgeVolumeField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///多头保值额度最初申请量
	TFfexFtdcVolumeType	LongVolumeOriginal;
	///空头保值额度最初申请量
	TFfexFtdcVolumeType	ShortVolumeOriginal;
	///多头保值额度
	TFfexFtdcVolumeType	LongVolume;
	///空头保值额度
	TFfexFtdcVolumeType	ShortVolume;
};
///市场行情
struct CFfexFtdcMarketDataField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///最新价
	TFfexFtdcPriceType	LastPrice;
	///昨结算
	TFfexFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TFfexFtdcPriceType	PreClosePrice;
	///昨持仓量
	TFfexFtdcLargeVolumeType	PreOpenInterest;
	///今开盘
	TFfexFtdcPriceType	OpenPrice;
	///最高价
	TFfexFtdcPriceType	HighestPrice;
	///最低价
	TFfexFtdcPriceType	LowestPrice;
	///数量
	TFfexFtdcVolumeType	Volume;
	///成交金额
	TFfexFtdcMoneyType	Turnover;
	///持仓量
	TFfexFtdcLargeVolumeType	OpenInterest;
	///今收盘
	TFfexFtdcPriceType	ClosePrice;
	///今结算
	TFfexFtdcPriceType	SettlementPrice;
	///涨停板价
	TFfexFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TFfexFtdcPriceType	LowerLimitPrice;
	///昨虚实度
	TFfexFtdcRatioType	PreDelta;
	///今虚实度
	TFfexFtdcRatioType	CurrDelta;
	///最后修改时间
	TFfexFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TFfexFtdcMillisecType	UpdateMillisec;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
};
///深度市场行情
struct CFfexFtdcDepthMarketDataField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///最新价
	TFfexFtdcPriceType	LastPrice;
	///昨结算
	TFfexFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TFfexFtdcPriceType	PreClosePrice;
	///昨持仓量
	TFfexFtdcLargeVolumeType	PreOpenInterest;
	///今开盘
	TFfexFtdcPriceType	OpenPrice;
	///最高价
	TFfexFtdcPriceType	HighestPrice;
	///最低价
	TFfexFtdcPriceType	LowestPrice;
	///数量
	TFfexFtdcVolumeType	Volume;
	///成交金额
	TFfexFtdcMoneyType	Turnover;
	///持仓量
	TFfexFtdcLargeVolumeType	OpenInterest;
	///今收盘
	TFfexFtdcPriceType	ClosePrice;
	///今结算
	TFfexFtdcPriceType	SettlementPrice;
	///涨停板价
	TFfexFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TFfexFtdcPriceType	LowerLimitPrice;
	///昨虚实度
	TFfexFtdcRatioType	PreDelta;
	///今虚实度
	TFfexFtdcRatioType	CurrDelta;
	///最后修改时间
	TFfexFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TFfexFtdcMillisecType	UpdateMillisec;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///申买价一
	TFfexFtdcPriceType	BidPrice1;
	///申买量一
	TFfexFtdcVolumeType	BidVolume1;
	///申卖价一
	TFfexFtdcPriceType	AskPrice1;
	///申卖量一
	TFfexFtdcVolumeType	AskVolume1;
	///申买价二
	TFfexFtdcPriceType	BidPrice2;
	///申买量二
	TFfexFtdcVolumeType	BidVolume2;
	///申卖价二
	TFfexFtdcPriceType	AskPrice2;
	///申卖量二
	TFfexFtdcVolumeType	AskVolume2;
	///申买价三
	TFfexFtdcPriceType	BidPrice3;
	///申买量三
	TFfexFtdcVolumeType	BidVolume3;
	///申卖价三
	TFfexFtdcPriceType	AskPrice3;
	///申卖量三
	TFfexFtdcVolumeType	AskVolume3;
	///申买价四
	TFfexFtdcPriceType	BidPrice4;
	///申买量四
	TFfexFtdcVolumeType	BidVolume4;
	///申卖价四
	TFfexFtdcPriceType	AskPrice4;
	///申卖量四
	TFfexFtdcVolumeType	AskVolume4;
	///申买价五
	TFfexFtdcPriceType	BidPrice5;
	///申买量五
	TFfexFtdcVolumeType	BidVolume5;
	///申卖价五
	TFfexFtdcPriceType	AskPrice5;
	///申卖量五
	TFfexFtdcVolumeType	AskVolume5;
	///上带价
	TFfexFtdcPriceType	BandingUpperPrice;
	///下带价
	TFfexFtdcPriceType	BandingLowerPrice;
	///基准价
	TFfexFtdcPriceType	ReferencePrice;
};
///分价表
struct CFfexFtdcMBLMarketDataField
{
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TFfexFtdcDirectionType	Direction;
	///价格
	TFfexFtdcPriceType	Price;
	///数量
	TFfexFtdcVolumeType	Volume;
};
///别名定义
struct CFfexFtdcAliasDefineField
{
	///起始位置
	TFfexFtdcStartPosType	StartPos;
	///别名
	TFfexFtdcAliasType	Alias;
	///原文
	TFfexFtdcOriginalTextType	OriginalText;
};
///行情基础属性
struct CFfexFtdcMarketDataBaseField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///昨结算
	TFfexFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TFfexFtdcPriceType	PreClosePrice;
	///昨持仓量
	TFfexFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TFfexFtdcRatioType	PreDelta;
};
///行情静态属性
struct CFfexFtdcMarketDataStaticField
{
	///今开盘
	TFfexFtdcPriceType	OpenPrice;
	///最高价
	TFfexFtdcPriceType	HighestPrice;
	///最低价
	TFfexFtdcPriceType	LowestPrice;
	///今收盘
	TFfexFtdcPriceType	ClosePrice;
	///涨停板价
	TFfexFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TFfexFtdcPriceType	LowerLimitPrice;
	///今结算
	TFfexFtdcPriceType	SettlementPrice;
	///今虚实度
	TFfexFtdcRatioType	CurrDelta;
};
///行情最新成交属性
struct CFfexFtdcMarketDataLastMatchField
{
	///最新价
	TFfexFtdcPriceType	LastPrice;
	///数量
	TFfexFtdcVolumeType	Volume;
	///成交金额
	TFfexFtdcMoneyType	Turnover;
	///持仓量
	TFfexFtdcLargeVolumeType	OpenInterest;
};
///行情最优价属性
struct CFfexFtdcMarketDataBestPriceField
{
	///申买价一
	TFfexFtdcPriceType	BidPrice1;
	///申买量一
	TFfexFtdcVolumeType	BidVolume1;
	///申卖价一
	TFfexFtdcPriceType	AskPrice1;
	///申卖量一
	TFfexFtdcVolumeType	AskVolume1;
};
///行情申买二、三属性
struct CFfexFtdcMarketDataBid23Field
{
	///申买价二
	TFfexFtdcPriceType	BidPrice2;
	///申买量二
	TFfexFtdcVolumeType	BidVolume2;
	///申买价三
	TFfexFtdcPriceType	BidPrice3;
	///申买量三
	TFfexFtdcVolumeType	BidVolume3;
};
///行情申卖二、三属性
struct CFfexFtdcMarketDataAsk23Field
{
	///申卖价二
	TFfexFtdcPriceType	AskPrice2;
	///申卖量二
	TFfexFtdcVolumeType	AskVolume2;
	///申卖价三
	TFfexFtdcPriceType	AskPrice3;
	///申卖量三
	TFfexFtdcVolumeType	AskVolume3;
};
///行情申买四、五属性
struct CFfexFtdcMarketDataBid45Field
{
	///申买价四
	TFfexFtdcPriceType	BidPrice4;
	///申买量四
	TFfexFtdcVolumeType	BidVolume4;
	///申买价五
	TFfexFtdcPriceType	BidPrice5;
	///申买量五
	TFfexFtdcVolumeType	BidVolume5;
};
///行情申卖四、五属性
struct CFfexFtdcMarketDataAsk45Field
{
	///申卖价四
	TFfexFtdcPriceType	AskPrice4;
	///申卖量四
	TFfexFtdcVolumeType	AskVolume4;
	///申卖价五
	TFfexFtdcPriceType	AskPrice5;
	///申卖量五
	TFfexFtdcVolumeType	AskVolume5;
};
///行情更新时间属性
struct CFfexFtdcMarketDataUpdateTimeField
{
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TFfexFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TFfexFtdcMillisecType	UpdateMillisec;
};
///行情价格波动带属性
struct CFfexFtdcMarketDataRealPriceBandingField
{
	///上带价
	TFfexFtdcPriceType	BandingUpperPrice;
	///下带价
	TFfexFtdcPriceType	BandingLowerPrice;
	///基准价
	TFfexFtdcPriceType	ReferencePrice;
};
///报价
struct CFfexFtdcQuoteField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///报价编号
	TFfexFtdcQuoteSysIDType	QuoteSysID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///买入数量
	TFfexFtdcVolumeType	BidVolume;
	///卖出数量
	TFfexFtdcVolumeType	AskVolume;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///本地报价编号
	TFfexFtdcOrderLocalIDType	QuoteLocalID;
	///业务单元
	TFfexFtdcBusinessUnitType	BusinessUnit;
	///买方组合开平标志
	TFfexFtdcCombOffsetFlagType	BidCombOffsetFlag;
	///买方组合套保标志
	TFfexFtdcCombHedgeFlagType	BidCombHedgeFlag;
	///买方价格
	TFfexFtdcPriceType	BidPrice;
	///卖方组合开平标志
	TFfexFtdcCombOffsetFlagType	AskCombOffsetFlag;
	///卖方组合套保标志
	TFfexFtdcCombHedgeFlagType	AskCombHedgeFlag;
	///卖方价格
	TFfexFtdcPriceType	AskPrice;
	///插入时间
	TFfexFtdcTimeType	InsertTime;
	///撤销时间
	TFfexFtdcTimeType	CancelTime;
	///成交时间
	TFfexFtdcTimeType	TradeTime;
	///买方报单编号
	TFfexFtdcOrderSysIDType	BidOrderSysID;
	///卖方报单编号
	TFfexFtdcOrderSysIDType	AskOrderSysID;
	///结算会员编号
	TFfexFtdcParticipantIDType	ClearingPartID;
};
///成交
struct CFfexFtdcTradeField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///成交编号
	TFfexFtdcTradeIDType	TradeID;
	///买卖方向
	TFfexFtdcDirectionType	Direction;
	///报单编号
	TFfexFtdcOrderSysIDType	OrderSysID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易角色
	TFfexFtdcTradingRoleType	TradingRole;
	///资金帐号
	TFfexFtdcAccountIDType	AccountID;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///开平标志
	TFfexFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TFfexFtdcHedgeFlagType	HedgeFlag;
	///价格
	TFfexFtdcPriceType	Price;
	///数量
	TFfexFtdcVolumeType	Volume;
	///成交时间
	TFfexFtdcTimeType	TradeTime;
	///成交类型
	TFfexFtdcTradeTypeType	TradeType;
	///成交价来源
	TFfexFtdcPriceSourceType	PriceSource;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///本地报单编号
	TFfexFtdcOrderLocalIDType	OrderLocalID;
	///结算会员编号
	TFfexFtdcParticipantIDType	ClearingPartID;
	///业务单元
	TFfexFtdcBusinessUnitType	BusinessUnit;
};
///报单
struct CFfexFtdcOrderField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///报单编号
	TFfexFtdcOrderSysIDType	OrderSysID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///报单价格条件
	TFfexFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TFfexFtdcDirectionType	Direction;
	///组合开平标志
	TFfexFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TFfexFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TFfexFtdcPriceType	LimitPrice;
	///数量
	TFfexFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TFfexFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TFfexFtdcDateType	GTDDate;
	///成交量类型
	TFfexFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TFfexFtdcVolumeType	MinVolume;
	///触发条件
	TFfexFtdcContingentConditionType	ContingentCondition;
	///止损价
	TFfexFtdcPriceType	StopPrice;
	///强平原因
	TFfexFtdcForceCloseReasonType	ForceCloseReason;
	///本地报单编号
	TFfexFtdcOrderLocalIDType	OrderLocalID;
	///自动挂起标志
	TFfexFtdcBoolType	IsAutoSuspend;
	///报单来源
	TFfexFtdcOrderSourceType	OrderSource;
	///报单状态
	TFfexFtdcOrderStatusType	OrderStatus;
	///报单类型
	TFfexFtdcOrderTypeType	OrderType;
	///今成交数量
	TFfexFtdcVolumeType	VolumeTraded;
	///剩余数量
	TFfexFtdcVolumeType	VolumeTotal;
	///报单日期
	TFfexFtdcDateType	InsertDate;
	///插入时间
	TFfexFtdcTimeType	InsertTime;
	///激活时间
	TFfexFtdcTimeType	ActiveTime;
	///挂起时间
	TFfexFtdcTimeType	SuspendTime;
	///最后修改时间
	TFfexFtdcTimeType	UpdateTime;
	///撤销时间
	TFfexFtdcTimeType	CancelTime;
	///最后修改交易用户代码
	TFfexFtdcUserIDType	ActiveUserID;
	///优先权
	TFfexFtdcPriorityType	Priority;
	///按时间排队的序号
	TFfexFtdcTimeSortIDType	TimeSortID;
	///结算会员编号
	TFfexFtdcParticipantIDType	ClearingPartID;
	///业务单元
	TFfexFtdcBusinessUnitType	BusinessUnit;
};
///执行宣告
struct CFfexFtdcExecOrderField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///合约编号
	TFfexFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///本地执行宣告编号
	TFfexFtdcOrderLocalIDType	ExecOrderLocalID;
	///数量
	TFfexFtdcVolumeType	Volume;
	///业务单元
	TFfexFtdcBusinessUnitType	BusinessUnit;
	///执行宣告编号
	TFfexFtdcExecOrderSysIDType	ExecOrderSysID;
	///报单日期
	TFfexFtdcDateType	InsertDate;
	///插入时间
	TFfexFtdcTimeType	InsertTime;
	///撤销时间
	TFfexFtdcTimeType	CancelTime;
	///执行结果
	TFfexFtdcExecResultType	ExecResult;
	///结算会员编号
	TFfexFtdcParticipantIDType	ClearingPartID;
};
///非标组合报单
struct CFfexFtdcCombOrderField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///组合报单编号
	TFfexFtdcOrderSysIDType	CombOrderSysID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///价格
	TFfexFtdcPriceType	LimitPrice;
	///数量
	TFfexFtdcVolumeType	VolumeTotalOriginal;
	///本地报单编号
	TFfexFtdcOrderLocalIDType	CombOrderLocalID;
	///业务单元
	TFfexFtdcBusinessUnitType	BusinessUnit;
	///合约代码1
	TFfexFtdcInstrumentIDType	InstrumentID1;
	///买卖方向1
	TFfexFtdcDirectionType	Direction1;
	///分腿乘数1
	TFfexFtdcLegMultipleType	LegMultiple1;
	///开平标志1
	TFfexFtdcOffsetFlagType	OffsetFlag1;
	///投机套保标志1
	TFfexFtdcHedgeFlagType	HedgeFlag1;
	///合约代码2
	TFfexFtdcInstrumentIDType	InstrumentID2;
	///买卖方向2
	TFfexFtdcDirectionType	Direction2;
	///分腿乘数2
	TFfexFtdcLegMultipleType	LegMultiple2;
	///开平标志2
	TFfexFtdcOffsetFlagType	OffsetFlag2;
	///投机套保标志2
	TFfexFtdcHedgeFlagType	HedgeFlag2;
	///合约代码3
	TFfexFtdcInstrumentIDType	InstrumentID3;
	///买卖方向3
	TFfexFtdcDirectionType	Direction3;
	///分腿乘数3
	TFfexFtdcLegMultipleType	LegMultiple3;
	///开平标志3
	TFfexFtdcOffsetFlagType	OffsetFlag3;
	///投机套保标志3
	TFfexFtdcHedgeFlagType	HedgeFlag3;
	///合约代码4
	TFfexFtdcInstrumentIDType	InstrumentID4;
	///买卖方向4
	TFfexFtdcDirectionType	Direction4;
	///分腿乘数4
	TFfexFtdcLegMultipleType	LegMultiple4;
	///开平标志4
	TFfexFtdcOffsetFlagType	OffsetFlag4;
	///投机套保标志4
	TFfexFtdcHedgeFlagType	HedgeFlag4;
	///报单来源
	TFfexFtdcOrderSourceType	OrderSource;
	///今成交数量
	TFfexFtdcVolumeType	VolumeTraded;
	///剩余数量
	TFfexFtdcVolumeType	VolumeTotal;
	///报单日期
	TFfexFtdcDateType	InsertDate;
	///插入时间
	TFfexFtdcTimeType	InsertTime;
	///结算会员编号
	TFfexFtdcParticipantIDType	ClearingPartID;
};
///管理报单
struct CFfexFtdcAdminOrderField
{
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///管理报单命令
	TFfexFtdcAdminOrderCommandFlagType	AdminOrderCommand;
	///结算会员编号
	TFfexFtdcParticipantIDType	ClearingPartID;
	///交易会员编号
	TFfexFtdcParticipantIDType	ParticipantID;
	///金额
	TFfexFtdcMoneyType	Amount;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
};
///管理报单输入
struct CFfexFtdcInputAdminOrderField
{
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///管理报单命令
	TFfexFtdcAdminOrderCommandFlagType	AdminOrderCommand;
	///结算会员编号
	TFfexFtdcParticipantIDType	ClearingPartID;
	///交易会员编号
	TFfexFtdcParticipantIDType	ParticipantID;
	///金额
	TFfexFtdcMoneyType	Amount;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
};
///公告
struct CFfexFtdcBulletinField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///公告编号
	TFfexFtdcBulletinIDType	BulletinID;
	///序列号
	TFfexFtdcSequenceNoType	SequenceNo;
	///公告类型
	TFfexFtdcNewsTypeType	NewsType;
	///紧急程度
	TFfexFtdcNewsUrgencyType	NewsUrgency;
	///发送时间
	TFfexFtdcTimeType	SendTime;
	///消息摘要
	TFfexFtdcAbstractType	Abstract;
	///消息来源
	TFfexFtdcComeFromType	ComeFrom;
	///消息正文
	TFfexFtdcContentType	Content;
	///WEB地址
	TFfexFtdcURLLinkType	URLLink;
	///市场代码
	TFfexFtdcMarketIDType	MarketID;
};
///交易所数据同步状态
struct CFfexFtdcExchangeDataSyncStatusField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///交易所代码
	TFfexFtdcExchangeIDType	ExchangeID;
	///交易所数据同步状态
	TFfexFtdcExchangeDataSyncStatusType	ExchangeDataSyncStatus;
};
///结算组数据同步状态
struct CFfexFtdcSGDataSyncStatusField
{
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///结算组数据同步状态
	TFfexFtdcSGDataSyncStatusType	SGDataSyncStatus;
};
///合约状态
struct CFfexFtdcInstrumentStatusField
{
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///合约交易状态
	TFfexFtdcInstrumentStatusType	InstrumentStatus;
	///交易阶段编号
	TFfexFtdcTradingSegmentSNType	TradingSegmentSN;
	///进入本状态时间
	TFfexFtdcTimeType	EnterTime;
	///进入本状态原因
	TFfexFtdcInstStatusEnterReasonType	EnterReason;
};
///客户持仓查询
struct CFfexFtdcQryClientPositionV1Field
{
	///起始会员代码
	TFfexFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TFfexFtdcParticipantIDType	PartIDEnd;
	///起始客户代码
	TFfexFtdcClientIDType	ClientIDStart;
	///结束客户代码
	TFfexFtdcClientIDType	ClientIDEnd;
	///起始合约代码
	TFfexFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TFfexFtdcInstrumentIDType	InstIDEnd;
};
///询价
struct CFfexFtdcInputReqForQuoteField
{
	///询价编号
	TFfexFtdcQuoteSysIDType	ReqForQuoteID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///交易日期
	TFfexFtdcTradingDayType	TradingDay;
	///询价时间
	TFfexFtdcTimeType	ReqForQuoteTime;
};
///申请组合
struct CFfexFtdcMarginCombActionField
{
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///交易用户代码
	TFfexFtdcUserIDType	UserID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///操作本地编号
	TFfexFtdcOrderLocalIDType	ActionLocalID;
	///组合合约代码
	TFfexFtdcInstrumentIDType	CombInstrumentID;
	///组合数量
	TFfexFtdcVolumeType	CombVolume;
	///组合动作方向
	TFfexFtdcCombDirectionType	CombDirection;
};
///交易编码组合持仓查询
struct CFfexFtdcQryPartClientCombPositionField
{
	///起始会员代码
	TFfexFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TFfexFtdcParticipantIDType	PartIDEnd;
	///起始客户代码
	TFfexFtdcClientIDType	ClientIDStart;
	///结束客户代码
	TFfexFtdcClientIDType	ClientIDEnd;
	///起始组合合约代码
	TFfexFtdcInstrumentIDType	combInstIDStart;
	///结束组合合约代码
	TFfexFtdcInstrumentIDType	combInstIDEnd;
};
///交易编码组合持仓
struct CFfexFtdcPartClientCombPositionField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///组合合约代码
	TFfexFtdcInstrumentIDType	CombInstrumentID;
	///组合持仓
	TFfexFtdcVolumeType	CombPosition;
	///组合一手释放的保证金
	TFfexFtdcMoneyType	CombFreeMargin;
};
///组合规则
struct CFfexFtdcMarginCombinationLegField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///组合合约代码
	TFfexFtdcInstrumentIDType	CombInstrumentID;
	///单腿编号
	TFfexFtdcLegIDType	LegID;
	///单腿合约代码
	TFfexFtdcInstrumentIDType	LegInstrumentID;
	///买卖方向
	TFfexFtdcDirectionType	Direction;
	///单腿乘数
	TFfexFtdcLegMultipleType	LegMultiple;
	///优先级
	TFfexFtdcPriorityType	Priority;
	///组合规则类型
	TFfexFtdcRuleTypeType	RuleType;
};
///交易编码单腿持仓
struct CFfexFtdcQryPartClientLegPositionField
{
	///起始会员代码
	TFfexFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TFfexFtdcParticipantIDType	PartIDEnd;
	///起始客户代码
	TFfexFtdcClientIDType	ClientIDStart;
	///结束客户代码
	TFfexFtdcClientIDType	ClientIDEnd;
	///起始单腿合约代码
	TFfexFtdcInstrumentIDType	LegInstIDStart;
	///结束单腿合约代码
	TFfexFtdcInstrumentIDType	LegInstIDEnd;
};
///交易编码单腿持仓
struct CFfexFtdcPartClientLegPositionField
{
	///交易日
	TFfexFtdcDateType	TradingDay;
	///结算组代码
	TFfexFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TFfexFtdcSettlementIDType	SettlementID;
	///会员代码
	TFfexFtdcParticipantIDType	ParticipantID;
	///客户代码
	TFfexFtdcClientIDType	ClientID;
	///单腿合约代码
	TFfexFtdcInstrumentIDType	InstrumentID;
	///多头持仓
	TFfexFtdcVolumeType	LongPosition;
	///空头持仓
	TFfexFtdcVolumeType	ShortPosition;
	///多头平仓冻结持仓
	TFfexFtdcVolumeType	LongCloseFrozenPosition;
	///空头平仓冻结持仓
	TFfexFtdcVolumeType	ShortCloseFrozenPosition;
};
///导出内存表
struct CFfexFtdcDumpMemTableField
{
	///内存表名称
	TFfexFtdcTableNameType	TableName;
};
///流量控制
struct CFfexFtdcFlowControlField
{
	///API端每秒可发送请求数量的最大值
	TFfexFtdcCommFluxType	MaxReqCntPerSec;
	///每个连接在途最大流量
	TFfexFtdcCommFluxType	OnWayMaxCommFlux;
};


#endif

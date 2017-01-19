#pragma once
#ifndef __CKTYPES_H__
#define __CKTYPES_H__

#include "ckdef.h"
#include "datablk.h"
#include <string>
#include <functional>
#include <memory>
#include <mutex>

struct CK_EXPORTS Task
{
	std::string type;        //�¼�����
	Datablk task_data;		//���ݽṹ��
};

typedef std::function<void(Datablk)> Handle;

//ctp
struct CK_EXPORTS CtpData
{
	int task_name;		//�ص��������ƶ�Ӧ�ĳ���
	Datablk task_data;		//���ݽṹ��
	Datablk task_error;		//����ṹ��
	int task_id;		//����id
	bool task_last;		//�Ƿ�Ϊ��󷵻�
};

//lts
struct CK_EXPORTS LtsData
{
	int task_name;		//�ص��������ƶ�Ӧ�ĳ���
	Datablk task_data;		//���ݽṹ��
	Datablk task_error;		//����ṹ��
	int task_id;		//����id
	bool task_last;		//�Ƿ�Ϊ��󷵻�
};

struct CK_EXPORTS BarData
{
	std::string symbol;
	std::string exchange;
	double open;
	double high;
	double low;
	double close;
	std::string date;
	std::string time;
	int volume;
	int openInterest;
};

struct CK_EXPORTS TickData
{
	std::string symbol;
	std::string exchange;
	double lastPrice;
	double volume;
	double openInterest;
	double upperLimit;
	double lowerLimit;
	std::string date;
	std::string time;
	double bidPrice1;
	double bidPrice2;
	double bidPrice3;
	double bidPrice4;
	double bidPrice5;
	double askPrice1;
	double askPrice2;
	double askPrice3;
	double askPrice4;
	double askPrice5;
	double bidVolume1;
	double bidVolume2;
	double bidVolume3;
	double bidVolume4;
	double bidVolume5;
	double askVolume1;
	double askVolume2;
	double askVolume3;
	double askVolume4;
	double askVolume5;
	std::string tSymbol;
	std::string gateWayName;
	double openPrice;
	double highPrice;
	double lowPrice;
	double preClosePrice;
	int lastVolume;
};

struct CK_EXPORTS OrderData
{
	std::string symbol;
	std::string exchange;
	std::string orderID;
	std::string direction;
	std::string offset;
	double price;
	double totalVolume;
	double tradedVolume;
	std::string status;
	std::string orderTime;
	std::string cancelTime;
	int frontID;
	int sessionID;
	std::string tOrderID;
	std::string gateWayName;
	std::string tSymbol;
};

struct CK_EXPORTS TradeData
{
	std::string symbol;
	std::string exchange;
	std::string tradeID;
	std::string orderID;
	std::string direction;
	std::string offset;
	double price;
	double volume;
	std::string tradeTime;
	std::string tTradeID;
	std::string tOrderID;
	std::string gateWayName;
	std::string tSymbol;
};

struct CK_EXPORTS PositionData
{
	std::string symbol;
	std::string exchange;
	std::string tSymbol;
	std::string direction;
	double position;
	double frozen;
	double price;
	std::string tPositionName;
	double ydPosition;
	std::string gateWayName;
	double todayPosition;
	double todayPositionCost;
	double ydPositionCost;
};

struct CK_EXPORTS AccountData
{
	std::string accountID;
	std::string tAccountID;
	double preBalance;
	double balance;
	double available;
	double commission;
	double margin;
	double closeProfit;
	double positionProfit;
	std::string gateWayName;
};

struct CK_EXPORTS ErrorData
{
	std::string errorID;
	std::string errorMsg;
	std::string additionalInfo;
	std::string gateWayName;
};

struct CK_EXPORTS LogData
{
	std::string logContent;
	std::string gateWayName;
};

struct CK_EXPORTS ContractData
{
	std::string symbol;
	std::string exchange;
	std::string tSymbol;
	std::string name;
	std::string productClass;
	int size;
	double priceTick;
	double strikePrice;
	std::string underlyingSymbol;
	std::string optionType;
	std::string gateWayName;
};

struct CK_EXPORTS SubscribeReq
{
	std::string symbol;//�Զ��ŷָ������Ķ��Լ
	std::string exchange;
	std::string productClass;
	std::string currency;
	std::string expiry;
	double strikePrice;
	std::string optionType;
	std::string strateyName;
};

struct CK_EXPORTS OrderReq
{
	std::string symbol;
	std::string exchange;
	double price;
	double volume;
	std::string priceType;
	std::string direction;
	std::string offset;
	std::string productClass;
	std::string currency;
	std::string expiry;
	double strikePrice;
	std::string optionType;
	std::string strateyName;
};

struct CK_EXPORTS CancelOrderReq
{
	std::string symbol;
	std::string exchange;
	std::string orderID;
	std::string frontID;
	std::string sessionID;
	std::string strateyName;
};

struct CK_EXPORTS StopOrder
{
	std::string tSymbol;
	std::string orderType;
	std::string direction;
	std::string offset;
	double price;
	double volume;

	std::string stopOrderID; // ֹͣ���ı��ر��
	std::string status; // ֹͣ��״̬
};

#endif
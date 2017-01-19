#pragma once
#ifndef __CKDEF_H__
#define __CKDEF_H__

#include <cstdint>

#if (defined WIN32 || defined _WIN32 || defined WINCE || defined __CYGWIN__)&& defined CKAPI_EXPORTS
#  define CK_EXPORTS __declspec(dllexport)
#elif defined __GNUC__ && __GNUC__ >= 4
#  define CK_EXPORTS __attribute__ ((visibility ("default")))
#else
#  define CK_EXPORTS
#endif

using Id = std::uint64_t;

/*event type*/
#define EVENT_INFO "eInfo."
#define EVENT_STOCK_HQ "eStockHq."
#define EVENT_TIMER "eTimer."
#define EVENT_TICK  "eTick."
#define EVENT_SUB "eSubcribe."
#define EVENT_READY_SUB "eReadySubcribe."
#define EVENT_ERROR "eError."
#define EVENT_LOG "eLog."
#define EVENT_CONTRACT "eContract."
#define EVENT_ACCOUNT "eAccount."
#define EVENT_POSITION "ePosition."
#define EVENT_ORDER "eOrder."
#define EVENT_TRADE "eTrade."
#define EVENT_CANCEL_ORDER "eCancelOrder."
#define EVENT_SEND_ORDER "eSendOrder."
#define EVENT_CONNECT_CTP "eConnectCTP."

#define EVENT_CAL_BACKTEST "eCalBacktest."

#define PRODUCT_EQUITY "��Ʊ"
#define PRODUCT_FUTURES "�ڻ�"
#define PRODUCT_OPTION "��Ȩ"
#define PRODUCT_INDEX "ָ��"
#define PRODUCT_COMBINATION "���"
#define PRODUCT_FOREX "���"
#define PRODUCT_UNKNOWN "δ֪"
#define PRODUCT_SPOT "�ֻ�"
#define PRODUCT_DEFER "����"
#define PRODUCT_NONE = ""

#define OPTION_CALL "������Ȩ"
#define OPTION_PUT "������Ȩ"

#define DIRECTION_NONE "�޷���"
#define DIRECTION_LONG "��"
#define DIRECTION_SHORT "��"
#define DIRECTION_UNKNOWN "δ֪"
#define DIRECTION_NET "��"
#define DIRECTION_SELL "����"

#define OFFSET_NONE "�޿�ƽ"
#define OFFSET_OPEN "����"
#define OFFSET_CLOSE "ƽ��"
#define OFFSET_CLOSETODAY "ƽ��"
#define OFFSET_CLOSEYESTERDAY "ƽ��"
#define OFFSET_UNKNOWN "δ֪"

#define STATUS_NOTTRADED "δ�ɽ�"
#define STATUS_PARTTRADED "���ֳɽ�"
#define STATUS_ALLTRADED "ȫ���ɽ�"
#define STATUS_CANCELLED "�ѳ���"
#define STATUS_UNKNOWN "δ֪"

#define PRICETYPE_LIMITPRICE "�޼�"
#define PRICETYPE_MARKETPRICE "�м�"
#define PRICETYPE_FAK "FAK"
#define PRICETYPE_FOK "FOK"

#define CTP_PATH_COM "\\ctp_temp\\"
#define LTS_PATH_COM "\\lts_temp\\"

//db
#define DB_PATH "./data"


//strategy
#define ST_ORDER_BUY "��"
#define ST_ORDER_SELL "��ƽ"
#define ST_ORDER_SHORT "����"
#define ST_ORDER_COVER "��ƽ"

#define STOPORDER_WAITING "�ȴ���"
#define STOPORDER_CANCELLED "�ѳ���"
#define STOPORDER_TRIGGERED "�Ѵ���"

#define STOPORDERPREFIX "StopOrder."

//����������
#define EXCHANGE_SSE "SSE"       //�Ͻ���
#define EXCHANGE_SZSE "SZSE"     // ���
#define EXCHANGE_CFFEX "CFFEX"   // �н���
#define EXCHANGE_SHFE "SHFE"   //������
#define EXCHANGE_CZCE "CZCE"     //֣����
#define EXCHANGE_DCE "DCE"      //������
#define EXCHANGE_SGE "SGE"     //�Ͻ���
#define EXCHANGE_UNKNOWN "UNKNOWN" // δ֪������
#define EXCHANGE_NONE ""         // �ս�����
#define EXCHANGE_HKEX "HKEX"   //�۽���

#define EXCHANGE_SMART "SMART"	// IB����·�ɣ���Ʊ����Ȩ��
#define EXCHANGE_NYMEX "NYMEX" //       # IB �ڻ�
#define EXCHANGE_GLOBEX "GLOBEX" //     # CME���ӽ���ƽ̨
#define EXCHANGE_IDEALPRO "IDEALPRO"  // # IB���ECN

// ��������
#define CURRENCY_USD "USD"            //��Ԫ
#define CURRENCY_CNY "CNY"            // �����
#define CURRENCY_UNKNOWN "UNKNOWN"    // δ֪����
#define CURRENCY_NONE ""              // �ջ���

#endif 
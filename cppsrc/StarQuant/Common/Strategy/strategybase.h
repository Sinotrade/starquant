#ifndef _StarQuant_Common_StraegyBase_H_
#define _StarQuant_Common_StraegyBase_H_



#include <Common/config.h>
#include <Common/Util/util.h>
#include <Common/Data/tick.h>
#include <Common/Data/bar.h>
#include <Common/Order/order.h>
#include <Common/Order/fill.h>
#include <Common/Logger/logger.h>
#include <Common/Security/position.h>
#include <Common/Msgq/msgq.h>

#include <queue>

namespace StarQuant {
	struct Position;

	class StrategyBase {
//	protected:
	//与brokerage,datafeed 沟通消息
//		std::unique_ptr<CMsgq> msgq_pair_;
//		std::unique_ptr<CMsgq> msgq_sub_;
	public:
		bool initialized = false;
		static int m_orderId;
//通过msg序列传给strategymanager service间接发送消息		
		queue<string> msgstobrokerage;
		StrategyBase();
		virtual ~StrategyBase();
		virtual void initialize();
		virtual void reset();
		virtual void teardown();

		// ************  Incoming Message Handers ********************//
		virtual void OnTick(Tick& k) {}
		virtual void OnBar(Bar& k) {}
		virtual void OnOrderTicket(long oid) {}				// Order acknowledge
		virtual void OnOrderCancel(long oid) {}
		virtual void OnFill(Fill& f) {}
		virtual void OnPosition(Position& p) {}
		virtual void OnGeneralMessage(string& msg) {}
		// ************ End Incoming Message Handers ********************//

		// ************  Outgoing Methods ********************//
		void SendOrder(std::shared_ptr<Order> o);
		void SendOrderCancel(long oid);
		void SendSubscriptionRequest();
		void SendHistoricalBarRequest();
		void SendGeneralInformation();
		void SendLog();

		// ************  End Outgoing Methods ********************//
	};
}

#endif // _StarQuant_Common_StraegyBase_H_

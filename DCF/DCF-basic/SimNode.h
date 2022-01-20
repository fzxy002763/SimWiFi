#include <string>
#include <vector>
using namespace std;

#ifndef SIMNODE_H_
#define SIMNODE_H_

#define ulong unsigned long
#define uint  unsigned int

#define DOWN_TIMER               0
#define UP_TIMER                 1

#define IDLE                     0
#define BUSY                     1

#define IDLE_STATE               0
#define BACKOFF_STATE            1
#define SEND_STATE               2
#define RECEIVE_STATE            3
#define COLLISION_STATE          4
#define ACKTIMEOUT_STATE         5

#define Halt                     0
#define Not_Halt                 1

#define PHY                     (208)
#define MAC                     (224)
#define ACK                     (112)

#define PAYLOAD (1500*8)
#define MRate (54)

#define ulRAND_MAX               4294967295

class SimNode {

	public:
		ulong  CURRENT_TIME;
		ulong  ALARM_TIME;

		uint   TIMER_MODE;
		uint   WORK_MODE;

		uint   IP;

		uint   CWmin;
		uint   CWmax;
		uint   CW;
		uint   CW_COUNTER;

		uint   SLOT;
		uint   SIFS;
		uint   DIFS;
		uint   PHY_TIME;
		uint   TRANS;

		uint   PACKET_COUNTER;
		uint   DROP_COUNTER;

		double RATE;

		double Random_Num;

		double Prop_per;
		double Prop_d;
   
		uint Halt_flag;

		SimNode();
		virtual ~SimNode();

		unsigned long ulrand(void);

		void inital(int ip,double Pd,double Per);
		void run(int clock_in,int flag_channel);
		void timer(int flag_channel);
		void set_alarm(ulong alarm_time);

};

#endif /* SIMNODE_H_ */

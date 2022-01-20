#include "SimNode.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define ulong unsigned long

double sim_main(int num_node,double Pd,double Per,ulong sim_time)
{

	srand((unsigned)time(NULL));

	SimNode   *Node[num_node];
	int       index_node;
	int       flag_channel = IDLE;
	int       send_num;

	vector<int> send_index;
	vector<int>::iterator iterVector;

	for(index_node = 0 ; index_node < num_node ; index_node++)
	{
		Node[index_node] = new SimNode();
		Node[index_node]->inital(index_node,Pd,Per);
	}

	ulong bus_clock;
	for(bus_clock = 1 ; bus_clock <= sim_time ; bus_clock++)
	{
		send_num = 0;

		for(index_node = 0 ; index_node < num_node ; index_node++)
		{
			Node[index_node]->run(bus_clock,flag_channel);
			if(flag_channel==IDLE)
				if(Node[index_node]->WORK_MODE==SEND_STATE)
					send_num++;
		}

		if(send_num>=2 && flag_channel==IDLE){
			for(index_node = 0 ; index_node < num_node ; index_node++){
				if(Node[index_node]->WORK_MODE==SEND_STATE){
					Node[index_node]->WORK_MODE=COLLISION_STATE;
					if(Node[index_node]->CW <= Node[index_node]->CWmax)
						Node[index_node]->CW = Node[index_node]->CW*2;
					else
						Node[index_node]->CW = Node[index_node]->CWmin;
					send_index.push_back(index_node);
				}
			}
			flag_channel = BUSY;
		}

		else if(send_num==1 && flag_channel==IDLE){
			for(index_node = 0 ; index_node < num_node ; index_node++){
				if(Node[index_node]->WORK_MODE==SEND_STATE){
					send_index.push_back(index_node);
				}
			}
			flag_channel = BUSY;
		}

		if(!send_index.empty() && flag_channel==BUSY){
			for(iterVector=send_index.begin();iterVector!=send_index.end();){
				if(Node[*iterVector]->WORK_MODE==IDLE_STATE){
					iterVector = send_index.erase(iterVector);
					if(send_index.empty()){
						flag_channel = IDLE;
						break;
					}
				}
				else{
					iterVector++;
				}
			}
		}


	}

	int throughput = 0;
	for(index_node = 0 ; index_node < num_node ; index_node++){
		throughput = throughput + Node[index_node]->PACKET_COUNTER;
		//printf("node:%d packets:%d\n",Node[index_node]->IP,Node[index_node]->PACKET_COUNTER);
	}

	double throughput_all = (double)(throughput)*(double)(PAYLOAD)/(double)(sim_time);
	//printf("%.4lf ",throughput_all);

	return throughput_all;
}

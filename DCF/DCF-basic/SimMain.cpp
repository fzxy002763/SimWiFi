#include "SimNode.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

#include <vector>

#define ulong unsigned long

#include "SimSchedule.h"

int main(int argc, char ** argv)
{
	//ofstream trace(".\\traces\\trace.txt",ios::app);

	const int    allNum    = atoi(argv[1]);
	const double Pd        = atof(argv[2]);
	const double Per       = atof(argv[3]);
	const ulong  sim_time  = 1e6;

	printf("%.9lf ",sim_main(allNum,Pd,Per,sim_time));

	//trace.close();
	return EXIT_SUCCESS;
}


// Author: Damien Sudol
// Program: CPU Scheduling
// Version 1.0

#include <iostream>
#include <string>

using namespace std;

class Process
{
private:
int jID;		//job id
int bT;			//CPU burst time
int aT;			//process arrival time
int tT;			//turnaround time
int wT;			//wait Time
int rBT;		//remaining burst time
int terminationTime;	//time process rBT hits zero (done processing)
public:

Process();				//default constructor
Process(int jobID, int burstTime, int arrivalTime);		//takes in 3 arguments found in "jobs.txt"

void modRBT(int pT);			//returns true if rBT is greater than zero (requires furhter processing)

void setTerminationTime(int time);	//sets termination time to passed argument

int getRBT();				//returns rBT

int getBT();				//returns burst time

int getAT();				//returns arrival time

int getJID();				//returns job id

int getWT();				//returns wait time for process

int getTT();				//returns turnaround time for process

int getTerminationTime();		//returns termination time

void calcWT();				//calculates wait time for process

void calcTT();				//calculates turnaround time for process

void resetRBT();			//sets remaining burst time back to original value

};

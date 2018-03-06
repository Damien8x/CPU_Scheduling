// Author: Damien Sudol
// Program: CPU Scheduling
// Version 1.0

#include "Process.h"
#include <iostream>
#include <string>

using namespace std;



int jID;
int bT;
int aT;
int tT;
int wT;
int rBT;
int terminationTime;

Process::Process()
{
int jID = -1;
int bT = -1;
int aT = -1;
int tT = -1;
int wT = -1;
int rBT = -1;
int terminationTime = -1;
}

Process::Process(int jobID, int burstTime, int arrivalTime)
{
jID = jobID;
bT = burstTime;
aT = arrivalTime;
tT = 0;
wT = 0;
rBT = bT;
terminationTime = 0;
}

void Process::modRBT(int pT)
{
rBT = rBT - pT;
}

void Process::setTerminationTime(int time)
{
	terminationTime = time;
}
int Process::getRBT()
{
	return rBT;
}

int Process::getBT()
{
	return bT;
}

int Process::getAT()
{
	return aT;
}

int Process::getJID()
{
	return jID;
}

int Process::getWT()
{
	return wT;
}

int Process::getTT()
{
	return tT;
}

int Process::getTerminationTime()
{
	return terminationTime;
}

void Process::calcWT()
{
	wT = tT - bT;
}

void Process::calcTT()
{
	tT = terminationTime - aT;
}

void Process::resetRBT()
{
	rBT = bT;
}

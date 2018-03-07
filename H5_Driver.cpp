//Author: Damien Sudol
//Program: CPU Scheduling
//version: 1.0

#include "Process.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

void welcomeMessage();
void heapifyATJID(Process p[], int n, int i);
void heapsortATJID(Process p[], int n);
void roundRobin(Process p[], int n);
void SJF(Process p[], int n);
void heapifySJF(Process p[], int n, int i, int computationTime);
void heapsortSJF(Process p[], int n, int computationTime);
void SRTF(Process p[], int n);

int main()
{
string line;
string jobID;
string burstTime;
string arrivalTime;
string readFile = "";
int processCount=0;

welcomeMessage();

getline(cin, readFile);

ifstream jobFile;
jobFile.open(readFile);
while(getline(jobFile, line))
	processCount++;
jobFile.close();

Process p[processCount];

ifstream inFile;
inFile.open(readFile);

int fileCount = 0;
while (getline(inFile, line)){
	fileCount++;
	stringstream linestream(line);
	getline(linestream, jobID,',');
	getline(linestream, burstTime, ',');
	getline(linestream, arrivalTime, ',');
	
	int jID = stoi(jobID);
	int bT = stoi(burstTime);
	int aT = stoi(arrivalTime);
	Process add(jID, bT, aT);
	p[fileCount -1] = add;

}

inFile.close();

roundRobin(p, processCount);
cout << "**************************************" << endl;
SJF(p,processCount);
cout << "++++++++++++++++++++++++++++++++++++++" << endl;
SRTF(p, processCount);

return 0;
}
void welcomeMessage()
{
cout << "please enter name process file " << endl;
}

void heapifyATJID(Process p[], int n, int i)
{
int largest = i;
int l = 2*i + 1;
int r = 2*i + 2;

if(l<n && p[l].getAT() > p[largest].getAT())
	largest = l;
if(r<n && p[r].getAT() > p[largest].getAT())
	largest = r;
if(r<n && p[r].getAT() == p[largest].getAT() && p[r].getJID() > p[largest].getJID())
	largest = r;
if(l<n && p[l].getAT() == p[largest].getAT() && p[l].getJID() > p[largest].getJID())
	largest = l;

if(largest != i){
	Process temp = p[largest];
	p[largest] = p[i];
	p[i] = temp;
	heapifyATJID(p, n, largest);
}
}

void heapsortATJID(Process p[], int n)
{
for(int i = n/2 - 1; i >= 0; i --)
	heapifyATJID(p, n, i);
for(int i = n-1; i>=0; i--){
	Process temp = p[0];
	p[0] = p[i];
	p[i] = temp;
	heapifyATJID(p, i, 0);
}	
}

void roundRobin(Process p[], int  n)
{
int roundRobinPosition = 0;
int totalWaitTime = 0;
int totalTurnaroundTime = 0;
string processOrder = "Process Order: ";
double avgWaitTime = 0;
double avgTurnaroundTime = 0;
double overallThroughput = 0;
double computationTime = 0;
Process roundRobinOrder[n];

heapsortATJID(p, n);

for(int i = 0; i < n; i++)
	p[i].resetRBT();
while(roundRobinPosition < n){

	for(int i = 0; i < n; i++){
		if(p[i].getRBT() !=0){
			computationTime++;
			p[i].modRBT(1);
			processOrder += to_string(p[i].getJID()) + ", ";
		
			if(p[i].getRBT() == 0){
				p[i].setTerminationTime(computationTime);
				p[i].calcTT();
				p[i].calcWT();
				roundRobinOrder[roundRobinPosition] = p[i];
				roundRobinPosition++;
			}
		}
	}
}

for(int i = 0; i < n; i++){
	totalWaitTime += roundRobinOrder[i].getWT();
	totalTurnaroundTime += roundRobinOrder[i].getTT();
}

avgWaitTime = totalWaitTime/n;
avgTurnaroundTime = totalTurnaroundTime/n;
overallThroughput = n/computationTime;

cout << "ROUND ROBIN" << endl << endl;
cout << "avg wait time: \t\t" << avgWaitTime << endl;
cout << "avg turnaround time: \t" << avgTurnaroundTime << endl;
cout << "overall Throughput: \t" << overallThroughput << endl;
cout << "computation Time: \t" << computationTime << endl;
cout << processOrder << endl;
}
void heapifySJF(Process p[], int n, int i, int computationTime)
{
int largest = i;
int l = i * 2 + 1;
int r = i * 2 + 2;

if(l < n && p[l].getRBT() != 0 && p[l].getAT() <= computationTime && p[l].getRBT() < p[largest].getRBT())
	largest = l;
if(r < n && p[r].getRBT() != 0 &&  p[r].getAT() <= computationTime && p[r].getRBT() < p[largest].getRBT())
	largest = r;
if(r < n && p[r].getRBT() == p[largest].getRBT() && p[r].getJID() > p[largest].getJID())
	largest = r;
if(l < n && p[l].getRBT() == p[largest].getRBT() && p[l].getJID() > p[largest].getJID())
	largest = l;
if(largest !=i){
	Process temp = p[largest];
	p[largest] = p[i];
	p[i] = temp;
	heapifySJF(p,n,largest,computationTime);  

}
}
void heapsortSJF(Process p[], int n, int computationTime)
{
for(int i =n/2 - 1; i >=0; i--)
	heapifySJF(p,n,i, computationTime);
for(int i = n-1; i>=0; i--){
	Process temp = p[0];
	p[0] = p[i];
	p[i] = temp;
	heapifySJF(p, i, 0, computationTime);
}
}


void SJF(Process p[], int n)
{
string processOrder = "process order: ";
double compTime = 0;
int computationTime = 0;
int SJFPosition = 0;
int totalWaitTime = 0;
int totalTurnaroundTime = 0;
double avgWaitTime = 0;
double avgTurnaroundTime = 0;
double overallThroughput = 0;

Process SJFOrder[n];
heapsortSJF(p,n,computationTime);
for(int i = 0; i<n; i++)
	p[i].resetRBT();
while(SJFPosition < n){
	while(p[0].getRBT() !=0){
		computationTime++;
		p[0].modRBT(1);

	}
processOrder += to_string(p[0].getJID()) + ", ";
p[0].setTerminationTime(computationTime);
p[0].calcTT();
p[0].calcWT();
SJFOrder[SJFPosition] = p[0];
SJFPosition++;
heapsortSJF(p,n,computationTime);
}

for(int i=0; i < n; i++){
	
	totalWaitTime += p[i].getWT();
	totalTurnaroundTime += p[i].getTT();
}
compTime = computationTime;
avgWaitTime = totalWaitTime/n;
avgTurnaroundTime = totalTurnaroundTime/n;
overallThroughput = n/compTime;

cout << "SJF" << endl << endl;
cout << "avg wait time: \t\t" << avgWaitTime << endl;
cout << "avg turnaround time: \t" << avgTurnaroundTime << endl;
cout << "overall Throughput: \t" << overallThroughput << endl;
cout << "computation Time: \t" << computationTime << endl;
cout << processOrder << endl;
}

void SRTF(Process p[], int n)
{
string processOrder = "process order: ";
double compTime = 0;
int computationTime = 0;
int SJFPosition = 0;
int totalWaitTime = 0;
int totalTurnaroundTime = 0;
double avgWaitTime = 0;
double avgTurnaroundTime = 0;
double overallThroughput = 0;
int tempJobID = 0;

Process SJFOrder[n];
heapsortSJF(p,n,computationTime);
processOrder += to_string(p[0].getJID());


for(int i = 0; i<n; i++)
	p[i].resetRBT();
while(SJFPosition < n){
	while(p[0].getRBT() !=0){
		computationTime++;
		tempJobID = p[0].getJID();
		p[0].modRBT(1);
			if(p[0].getRBT() == 0){
				p[0].setTerminationTime(computationTime);
				p[0].calcTT();
				p[0].calcWT();
				SJFOrder[SJFPosition] = p[0];
				SJFPosition++;
			}
		heapsortSJF(p,n,computationTime);		
		if(tempJobID != p[0].getJID())
			processOrder += ", " + to_string(p[0].getJID());
	}
}

for(int i=0; i < n; i++){
	
	totalWaitTime += p[i].getWT();
	totalTurnaroundTime += p[i].getTT();
}
compTime = computationTime;
avgWaitTime = totalWaitTime/n;
avgTurnaroundTime = totalTurnaroundTime/n;
overallThroughput = n/compTime;

cout << "SRTF" << endl << endl;
cout << "avg wait time: \t\t" << avgWaitTime << endl;
cout << "avg turnaround time: \t" << avgTurnaroundTime << endl;
cout << "overall Throughput: \t" << overallThroughput << endl;
cout << "computation Time: \t" << computationTime << endl;
cout << processOrder << endl;
}

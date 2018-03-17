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

// function prototypes
void welcomeMessage();
void heapifyATJID(Process p[], int n, int i);
void heapsortATJID(Process p[], int n);
void roundRobin(Process p[], int n);
void SJF(Process p[], int n);
void heapifySJF(Process p[], int n, int i, int computationTime);
void heapsortSJF(Process p[], int n, int computationTime);
void SRTF(Process p[], int n);

string BLOCK = "-------------------------------------------------------------------------------------------------------------------------";
int main()
{

// main variables
string line;
string jobID;
string burstTime;
string arrivalTime;
string readFile = "";
int processCount=0;

welcomeMessage();

// receive filename from user to run against algorithms
getline(cin, readFile);

// create ifstream object and open input stream with respective file
ifstream jobFile;
jobFile.open(readFile);

// check if ifstream has been established. If not display error and abort program
if(!jobFile.is_open()){
	cout << "Error opening file. Check input and filename/extension. Aborting program.  ";
	abort();
}

// run while loop to determine number of processes in file
while(getline(jobFile, line))
	processCount++;

// close ifstream
jobFile.close();

// create an array of Process objects with size of lines in [file.txt]
Process p[processCount];

// create new ifstream with the same file as above
ifstream inFile;
inFile.open(readFile);

// parse information from file into respective variables, create Process object and add
// to Process array p[] for each line in file
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
// don't forget to close the ifstream!
inFile.close();

SJF(p,processCount);
roundRobin(p, processCount);
SRTF(p, processCount);


return 0;
}


void welcomeMessage()
{
cout << BLOCK << endl;
cout << "\t\t\t\t*Welcome to the CPU Scheduling Simulator*" << endl << endl << endl;
cout << " Simulator will show results for three scheduling algorithms:" << endl;
cout << " Shorteset Job First, Round Robin and Shortest Remaining Time First"  << endl << endl;
cout << " For more information please refer to README.txt" << endl;
cout << " To begin, please enter the file-name of the formatted text file in the CWD, followed by enter.\n\n" << endl;
}

// heapify with priorities: Arrival Time, Job ID (utilized by round robin)
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

// heapsort for priorites: Arrival Time, Job ID (utilized by round robin)
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

// Algorithm for Round Robin
// Computes: Avg wait time, avg turn around time, oberall throughput, and displays process 
// execution order
void roundRobin(Process p[], int  n)
{

int roundRobinPosition = 0;
double totalWaitTime = 0;
double totalTurnaroundTime = 0;
string processOrder = " Process Order: ";
double avgWaitTime = 0;
double avgTurnaroundTime = 0;
double overallThroughput = 0;
double computationTime = 0;
Process roundRobinOrder[n];
heapsortATJID(p, n);
int processOrderCount = 0;
Process temp[n];
queue<Process> Q1;
queue<Process> Q2;
bool Q1A = true;
bool Q2A = false;
// reset remaining burst time equal to burst time
for(int i = 0; i < n; i++){
	p[i].resetRBT();
	temp[i] = p[i];

}

// roundRobinPosition increased by one when RBT == 0.
// loop will break when all objects in array have an RBT == 0
while(roundRobinPosition < n){
	bool AT = false;
	for(int i = 0; i < n; i++)
	{
		if(p[i].getAT() <= computationTime && p[i].getRBT() > 0)
			AT = true;		
	}
	if(AT == false)
		computationTime++;
	else{
	for(int i = 0; i < n; i++){
		if(p[i].getRBT() !=0 && p[i].getAT() <= computationTime)
			Q1.push(p[i]);			
	}
		while(!Q1.empty() || !Q2.empty()){
			if(Q1A){
				if(Q1.empty()){
					Q1A = false;
					Q2A = true;
				}else{
					Process current = Q1.front();
					Q1.pop();
					computationTime++;
				 	for(int i = 0; i < n; i++){
						if(computationTime == p[i].getAT())
							Q2.push(p[i]);
					}
					
					current.modRBT(1);
					processOrder += to_string(current.getJID()) + ", ";
					processOrderCount++;
						if(processOrderCount %29 == 0)
							processOrder += "\n\t	";
					if(current.getRBT() == 0){
						current.setTerminationTime(computationTime);
						current.calcTT();
						current.calcWT();
						p[roundRobinPosition] = current;
						roundRobinPosition++;
			
					}else{
						Q2.push(current);
					}	
				}	
			}
			if(Q2A){
			if(Q2.empty()){
					Q2A = false;
					Q1A = true;
				}else{
					Process current = Q2.front();
					Q2.pop();
					computationTime++;
				 	for(int i = 0; i < n; i++){
						if(computationTime == p[i].getAT())
							Q1.push(p[i]);
					}
					
					current.modRBT(1);
					processOrder += to_string(current.getJID()) + ", ";
					processOrderCount++;
						if(processOrderCount %29 == 0)
							processOrder += "\n\t	";
					if(current.getRBT() == 0){
						current.setTerminationTime(computationTime);
						current.calcTT();
						current.calcWT();
						p[roundRobinPosition] = current;
						roundRobinPosition++;
			
					}else{
						Q1.push(current);
					}	
				}
			}
		
		
		}	
	
	}
}
// add for totals
for(int i = 0; i < n; i++){
	totalWaitTime += p[i].getWT();
	totalTurnaroundTime += p[i].getTT();
}

// calculate average
avgWaitTime = totalWaitTime/n;
avgTurnaroundTime = totalTurnaroundTime/n;
overallThroughput = n/computationTime;
// get rid of that pesky comma at the end of the list of processes
processOrder.resize(processOrder.size()-2);
// display results
cout << BLOCK << endl;
cout << "\t\t\t\t\t\t*ROUND ROBIN*" << endl << endl;
cout << " Avg Wait Time: \t" << avgWaitTime << endl;
cout << " Avg Turnaround Time: \t" << avgTurnaroundTime << endl;
cout << " Overall Throughput: \t" << overallThroughput << endl;
cout << processOrder << endl;
cout << "\n" << BLOCK << endl;
}

// heapify based on priorites in SJF. SO MANY CONDITIONS!!!!!
void heapifySJF(Process p[], int n, int i, int computationTime)
{

int largest = i;
int l = i * 2 + 1;
int r = i * 2 + 2;

if(l < n && p[l].getRBT() > 0 && p[l].getAT() <= computationTime && p[l].getRBT() < p[largest].getRBT() ||
l < n && p[l].getRBT() > 0 && p[l].getAT() <= computationTime && p[largest].getAT() > computationTime)
	largest = l;
if(r < n && p[r].getRBT() > 0 && p[r].getAT() <= computationTime && p[r].getRBT() < p[largest].getRBT() ||
r < n && p[r].getRBT() > 0 && p[r].getAT() <= computationTime && p[largest].getAT() > computationTime) 
	largest = r;
if(r < n && p[r].getRBT() > 0 && p[r].getAT() <= computationTime && p[r].getRBT() == p[largest].getRBT() && p[r].getJID() < p[largest].getJID() ||
r < n && p[r].getRBT() > 0 && p[r].getAT() <= computationTime && p[r].getRBT() == p[largest].getRBT() && p[largest].getAT() > computationTime)
	largest = r;
if (l < n && p[l].getRBT() > 0 && p[l].getAT() <= computationTime && p[l].getRBT() == p[largest].getRBT() && p[l].getJID() < p[largest].getJID() ||
l < n && p[l].getRBT() > 0 && p[l].getAT() <= computationTime && p[l].getRBT() == p[largest].getRBT() && p[largest].getAT() > computationTime)
	largest = l;
if(largest !=i){
	Process temp = p[largest];
	p[largest] = p[i];
	p[i] = temp;
	heapifySJF(p,n,largest,computationTime);  



}
}
// heapsort based on priorites for SJF
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

// SJF Algorithm
void SJF(Process p[], int n)
{

string processOrder = " Process Order: ";
double compTime = 0;
int computationTime = 0;
int SJFPosition = 0;
double totalWaitTime = 0;
double totalTurnaroundTime = 0;
double avgWaitTime = 0;
double avgTurnaroundTime = 0;
double overallThroughput = 0;
int processOrderCount = 0;

// reset RBT equal to BT
for(int i = 0; i<n; i++)
	p[i].resetRBT();

Process SJFOrder[n];
// initial sort
heapsortSJF(p,n,computationTime);

// nested while loop. determines shortest job and executes
// process until objects RBT is zero, then resorts and executes
// until all objects in array have a RBT of zero.
while(SJFPosition < n){
	while(p[n-1].getRBT() !=0){
		if(p[n-1].getAT() > computationTime)
			computationTime++;
		else{
			computationTime++;
			p[n-1].modRBT(1);
		}
	}
	processOrder += to_string(p[n-1].getJID()) + ", ";
	processOrderCount++;
	if(processOrderCount % 29 == 0)
		processOrder += "\n\t       ";
	p[n-1].setTerminationTime(computationTime);
	p[n-1].calcTT();
	p[n-1].calcWT();
	SJFOrder[SJFPosition] = p[n-1];
	SJFPosition++;
	heapsortSJF(p,n,computationTime);
}

// calculate totals
for(int i=0; i < n; i++){
	totalWaitTime += p[i].getWT();
	totalTurnaroundTime += p[i].getTT();
}

// calculate averages
compTime = computationTime;
avgWaitTime = totalWaitTime/n;
avgTurnaroundTime = totalTurnaroundTime/n;
overallThroughput = n/compTime;
// get RID of that last coma!
processOrder.resize(processOrder.size()-2);

//D display results
cout << BLOCK << endl;
cout << "      \t\t\t\t\t     *Shortest Job First*" << endl << endl;
cout << " Avg Wait Time: \t" << avgWaitTime << endl;
cout << " Avg Turnaround Time: \t" << avgTurnaroundTime << endl;
cout << " Overall Throughput: \t" << overallThroughput << endl;
cout << processOrder << endl;
cout << "\n" << BLOCK << endl;
}

// SRTF algorithm
void SRTF(Process p[], int n)
{

string processOrder = " Process Order: ";
double compTime = 0;
int computationTime = 0;
int SJFPosition = 0;
double totalWaitTime = 0;
double totalTurnaroundTime = 0;
double avgWaitTime = 0;
double avgTurnaroundTime = 0;
double overallThroughput = 0;
int tempPosition =n-1 ;
int check = 0;
int processOrderCount = 0;

// reset RBT equal to BT
for(int i = 0; i<n; i++)
	p[i].resetRBT();

Process SJFOrder[n];
// initial sort
heapsortSJF(p,n,computationTime);
// while loop executes until all objects have a RBT equal to zero
// checks object priority after each time quantum
while(SJFPosition < n){
	
	// determins next object to use based on SRTF criteria
	for(int i = 0; i < n; i ++)
	{
		if(p[i].getRBT() > 0 && p[i].getAT() <= computationTime){
			if(p[i].getRBT() < p[tempPosition].getRBT() || p[tempPosition].getRBT() == 0)
				tempPosition = i;
		}
	}
	// determins next object to use based on SRTF criteria for equal values
	for(int i = 0; i < n; i ++)
	{
		if(p[i].getRBT() > 0 && p[i].getAT() <= computationTime){
			if(p[i].getRBT() == p[tempPosition].getRBT() && p[i].getJID() < p[tempPosition].getJID())
				tempPosition = i;		
		}
	}
	if(p[tempPosition].getAT() > computationTime)
		computationTime++;
	else{
	p[tempPosition].modRBT(1);
	computationTime++;
	// add to process order 
	if(check != p[tempPosition].getJID()){
		processOrder += to_string(p[tempPosition].getJID()) + ", ";
		processOrderCount++;
		if(processOrderCount % 29 == 0)
			processOrder += "\n\t       ";
		check = p[tempPosition].getJID();
	}
	// calculations after a object newly has RBT equal to zero
	if(p[tempPosition].getRBT() == 0){
		p[tempPosition].setTerminationTime(computationTime);
		p[tempPosition].calcTT();
		p[tempPosition].calcWT();
		SJFPosition++;
	}
	}
	

}

// calculate totals
for(int i=0; i < n; i++){
	totalWaitTime += p[i].getWT();
	totalTurnaroundTime += p[i].getTT();
}

// calculate averages
compTime = computationTime;
avgWaitTime = totalWaitTime/n;
avgTurnaroundTime = totalTurnaroundTime/n;
overallThroughput = n/compTime;
// oh, those end commas need a while line of code to get rid of!
processOrder.resize(processOrder.size()-2);

// display results
cout << BLOCK << endl;
cout << "\t\t\t\t\t*Shortest Remaining Time First*" << endl << endl;
cout << " Avg Wait Time: \t" << avgWaitTime << endl;
cout << " Avg Turnaround Time: \t" << avgTurnaroundTime << endl;
cout << " Overall Throughput: \t" << overallThroughput << endl;
cout << processOrder << endl;
cout << "\n" << BLOCK << endl;
}



//Author: Damien Sudol
//Program: CPU Scheduling
//version: 1.0

#include "Process.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void welcomeMessage();
void heapify(Process p[], int n, int i);
void heapsort(Process p[], int n);

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


for(int i = 0; i <processCount ; i++){
	cout << p[i].getAT() << endl;
}

heapsort(p, processCount);

cout << "************************************************************" << endl;

for(int i = 0; i <processCount ; i++){
	cout << p[i].getAT() << "	";
	cout << p[i].getJID() << endl;
}

return 0;
}


void welcomeMessage()
{
cout << "please enter name process file " << endl;
}

void heapify(Process p[], int n, int i)
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
	heapify(p, n, largest);
}
}

void heapsort(Process p[], int n)
{
for(int i = n/2 - 1; i >= 0; i --)
	heapify(p, n, i);
for(int i = n-1; i>=0; i--){
	Process temp = p[0];
	p[0] = p[i];
	p[i] = temp;
	heapify(p, i, 0);
}	
}

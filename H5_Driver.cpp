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

int main()
{
string line;
string jobID;
string burstTime;
string arrivalTime;
string readFile = "";
Process p[25];

welcomeMessage();

getline(cin, readFile);

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

for(int i = 0; i < 30; i++){
	if(p[i].getBT() != -1)
		cout << p[i].getBT() << endl;
}


inFile.close();
return 0;
}


void welcomeMessage()
{
cout << "please enter name process file " << endl;
}

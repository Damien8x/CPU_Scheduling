*********************************************************************************************************
						READ ME

Thank-you for using the HW_CPU_SCHEDULING process scheduling simulation, veresion 1.0.
Program is designed to execute using a file contained within the HW_CPU_SCHEDULING folder.
Any text file adhering to the required format proposed by HW5 CPU Scheduling will execute
as intended. Choice of file will be determined at runtime through user's command line
input. If an error has occured relating to input or file contents an  error message will 
be displayed and program aborted.

Understanding Program: Program will simulate three Process Scheduling algorithms, Shortest Job
First (SJF), Round Robin, and Shortest Remaining Time First(SRTF). For all algorithms display will
include: Average Turnaround Time, Overall Throughput of system, Average Waiting Time, as well as
the order of process execution for the respective algorithm.

Run Program Instructions:

	Succesful program requires CWD to include the following files
		-Process.cpp
		-Process.h
		-HW_Driver.cpp
		-[file.txt] (text file of any name formatted to HW5 specifications)
	*multiple [file.txt] filest may be included in directory

	step 1)
		Enter directory HW_CPU_SCHEDULING with above contents
	step 2)
		Compile cpp files with the following command:
		"g++ -std=c++11 Process.cpp HW_Driver.cpp"
	step 3)
		Run program with the follwoing command
		"./a.out"
	step 4) 
		When prompted, enter the respective .txt file you wish to run against
		the simulations

********************************************************************************************************


/*
The following processes are being scheduled using a preemptive, round robin scheduling algorithm. 
Each process is assigned a numerical priority, with a higher number indicating a higher relative priority. 
In addition to the processes listed below, the system also has an idle task (which consumes no CPU resources and is identified as P_idle ). 
This task has priority 0 and is scheduled whenever the system has no other available processes to run.
 The length of a time quantum is 10 units. 
 If a process is preempted by a higher-priority process, the preempted process is placed at the end of the queue.
Thread Priority Burst Arrival.

P1 40 20 0
P2 30 25 25
P3 30 25 30
P4 35 15 60
P5 5 10 100
P6 10 10 105
*/

#include<stdio.h>

int clock = 0;//a clock having the current time
int cur_p=0;
int cur_index=0;

struct process{
	int id;//process id
	int at;//arival time
	int bt;//burst time
	int bt_copy;
	int p;//priority
	int start_time[10];//index containg all the starting times of process
	int start_index=0;//current index of start_time
	int finish_time[10];//index containg all the starting times of process
	int finish_index=0;//current index of start_time
	int waiting_time=0;//total time the process was in waiting
	int next_process_index;//next process address
	int my_index;//current process address
	int turn_around_time;
}proc[50];

int q_proc;//number of process in queue


int get_next(int index){
	for(int i=0;i<q_proc;i++){
		if(proc[i].at<=clock){
			if(proc[i].bt!=0){
				proc[i].my_index=i;
				if(proc[i].p>=cur_p){
					proc[index].next_process_index=i;
					cur_p=proc[i].p;
				}
			}
			else{
				if(proc[index].bt==0){
					proc[index].next_process_index=6;
					cur_p=0;
				}
			}
		}	
	}
}


main(){
	int res_index;
	struct process result[6];
	q_proc = 6;
	res_index = 0;
	//get the process imformation
	
	proc[0].id=1;
	proc[0].p=40;
	proc[0].bt=20;
	proc[0].bt_copy=20;
	proc[0].at=0;
		
	proc[1].id=2;
	proc[1].p=30;
	proc[1].bt=25;
	proc[1].bt_copy=25;
	proc[1].at=25;
		
	proc[2].id=3;
	proc[2].p=30;
	proc[2].bt=25;
	proc[2].bt_copy=25;
	proc[2].at=30;
	
	
	proc[3].id=4;
	proc[3].p=35;
	proc[3].bt=15;
	proc[3].bt_copy=15;
	proc[3].at=60;
	
	
	proc[4].id=5;
	proc[4].p=5;
	proc[4].bt=10;
	proc[4].bt_copy=10;
	proc[4].at=100;
	
	
	proc[5].id=6;
	proc[5].p=10;
	proc[5].bt=10;
	proc[5].bt_copy=10;
	proc[5].at=105;
	
	int burst=0;
	
	proc[6].id=-1; //idle process
	proc[6].p=0;
	proc[6].bt=1000;
	proc[6].bt_copy=1000;
	proc[6].at=0;
	
	for(int i=0;i<6;i++){
		burst = burst + proc[i].bt_copy;
	}
	
	printf("\nScheduling Order\n");
	
	while(burst!=0){
		if(proc[cur_index].bt!=0){
			
			//printf("\nid :%d",proc[cur_index].id);
			//printf("\nbst :%d",proc[cur_index].bt);
			if(proc[cur_index].bt==5 || proc[cur_index].id==-1){
				printf("\n process : %d",proc[cur_index].id);
				printf("\n start time : %d",clock);
				proc[cur_index].start_time[proc[cur_index].start_index]=clock;
				proc[cur_index].start_index++;
				clock = clock+5;
				if(proc[cur_index].id!=-1){
					burst=burst-5;
				}
				proc[cur_index].bt = proc[cur_index].bt-5;
				proc[cur_index].finish_time[proc[cur_index].finish_index]=clock;
				proc[cur_index].finish_index++;
				if(proc[cur_index].bt==0){
					cur_p=0;
				}
				get_next(cur_index);
				cur_index = proc[cur_index].next_process_index;
				printf("\n end time : %d\n",clock);
			}
			else{
				printf("\n process : %d",proc[cur_index].id);
				printf("\n start time : %d",clock);
				proc[cur_index].start_time[proc[cur_index].start_index]=clock;
				proc[cur_index].start_index++;
				proc[cur_index].bt = proc[cur_index].bt-10;
				clock = clock+10;
				burst = burst-10;
				proc[cur_index].finish_time[proc[cur_index].finish_index]=clock;
				proc[cur_index].finish_index++;
				if(proc[cur_index].bt==0){
					cur_p=0;
				}
				get_next(cur_index);
				cur_index = proc[cur_index].next_process_index;
				printf("\n end time : %d\n",clock);
			}
		}
	}
	
	for(int i=0;i<6;i++){
		proc[i].waiting_time = proc[i].waiting_time + (proc[i].start_time[0]-proc[i].at);
		for(int j=1;j<proc[i].start_index;j++){
			proc[i].waiting_time = proc[i].waiting_time + (proc[i].start_time[j] - proc[i].finish_time[j-1]);
		}
		printf("\nThe process %d has waiting time : %d\n",proc[i].id,proc[i].waiting_time);
	}
	
	
	for(int i=0;i<6;i++){
		
		proc[i].turn_around_time = proc[i].waiting_time + proc[i].bt_copy;
		printf("\nThe process %d has turn around time : %d",proc[i].id,proc[i].turn_around_time);
	}
	
	
	printf("\n\nCPU Utilization..");
	//printf("%d",clock);
	printf("\n %.2f", ((clock-15)/float(clock))*100);
}

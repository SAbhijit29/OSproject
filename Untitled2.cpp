#include<stdio.h>

int n=0;//total number of processes
int clock = 0;//a clock having the current time
int cur_p=9999;
int cur_index=-1;
int rr_index=0;

struct process{
	int id;//process id
	int at;//arival time
	int bt;//burst time
	int p;//priority
	int start_time[100];//index containg all the starting times of process
	int start_index=0;//current index of start_time
	int status = -1;//process status waiting: -1 , finished: 0, running:1;
	int waiting_time=0;//total time the process was in waiting
	int next_process_index;//next process address
	int my_index;//current process address
}proc[50];

int queue=0;//queue number
int q_proc;//number of process in q1 qnd q2

//to sort by arrival time
void sort_arival(int n){
	struct process a;
	int min,pos;
	
	for(int i=0;i<n-1;i++){
		min = proc[i].at;
		pos = i;	
		for(int j=i+1;j<n;j++){
			if(min>proc[j].at){
				min = proc[j].at;
				pos = j;
			}
		}
		
		if(i!=pos){
			a=proc[i];
			proc[i]=proc[pos];
			proc[pos]=a;
		}
	}
}

int get_next(int index){
	for(int i=0;i<q_proc;i++){
		if(proc[i].at<=clock && proc[i].status!=0){
			proc[i].my_index=i;
			if(proc[i].p<cur_p){
				proc[index].next_process_index=i;
				cur_p=proc[i].p;
			}
		}
	}
}

void move_to_last(){
	struct process a;
	int i=0;
	a = proc[0];
	
	while(i<q_proc-1){
		proc[i]=proc[i+1];
		i++;
	}
	proc[i]=a;
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
	proc[0].at=0;
	
	proc[1].id=2;
	proc[1].p=30;
	proc[1].bt=20;
	proc[1].at=25;
	
	proc[2].id=3;
	proc[2].p=30;
	proc[2].bt=25;
	proc[2].at=30;
	
	proc[3].id=4;
	proc[3].p=35;
	proc[3].bt=15;
	proc[3].at=60;
	
	proc[4].id=5;
	proc[4].p=5;
	proc[4].bt=10;
	proc[4].at=100;
	
	proc[5].id=6;
	proc[5].p=10;
	proc[5].bt=10;
	proc[5].at=105;
	
	printf("3");
	sort_arival(q_proc);
	
	printf("2");
	get_next(0);
	cur_index = proc[cur_index].next_process_index;
	
	while(q_proc!=0){
		printf("1");
			if(proc[cur_index].status==0){
				clock++;
			}
			else{
				proc[cur_index].start_time[proc[cur_index].start_index]=clock;
				proc[cur_index].start_index++;
				clock++;
				proc[cur_index].bt--;
				if(proc[cur_index].bt==0){
					q_proc--;
					proc[cur_index].status=0;
					result[res_index]=proc[cur_index];
					res_index++;
				}
				get_next(proc[cur_index].my_index);
				move_to_last();
			}
	}
	
	for(int i=0;i<=res_index;i++){
		for(int j=0;j<=result[i].start_index;j++){
			printf("\nThe process %d was running at time %d sec.",result[i].id,result[i].start_time[j]);
		}
	}
}

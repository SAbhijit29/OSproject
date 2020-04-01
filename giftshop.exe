/*
Ten students (s1,s2,s3,s4,s5,s6,s7,s8,s9,s10) are going to attend an event. There are lots of gift shops,
 they all are going to the gift shops and randomly picking the gifts.
  After picking the gifts they are randomly arriving in the billing counter. 
  The accountant gives the preference to that student who has maximum number of gifts.
   Create a C program to define order of billed students?
*/

#include<stdio.h>

struct student{
	int no_of_gift;
	int at;
	int id;
}s[10];

void sort_arival(){
	struct student a;
	int min,pos;
	for(int i=0;i<10;i++){
		min = s[i].at;
		pos = i;	
		for(int j=i+1;j<10;j++){
			if(min>s[j].at){
				min = s[j].at;
				pos = j;
			}
		}
		
		if(i!=pos){
			a=s[i];
			s[i]=s[pos];
			s[pos]=a;
		}
	}
}

int main(){
	for(int i=0;i<10;i++){
		s[i].id=i+1;
		printf("\nEnter the arrival time for s%d: ",i+1);
		scanf("%d",&s[i].at);
		printf("\nEnter the number of gift items for s%d: ",i+1);
		scanf("%d",&s[i].no_of_gift);
	}
	
	sort_arival();
	
	struct student m;
	int pos;
	
	for(int i=0;i<10;i++){
		m = s[i];
		pos = i;
		for(int j=i+1;j<10;j++){
			if(m.no_of_gift<s[j].no_of_gift){
				m = s[j];
				pos = j;
			}
		}
		s[pos]=s[i];
		s[i]=m;
		printf("\nBill turn for student s%d having %d items",s[i].id,s[i].no_of_gift);
	}
	
	return 0;
}

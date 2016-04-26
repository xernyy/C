//Program a simulation of the banker’s algorithm. Your program should cycle through each of the bank clients asking for a request and evaluating whether it is safe or unsafe. Output a log of requests and decisions to a file.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void){
	printf("There are 10 resources in existence\n");
	printf("The maximum needs of Customer 1-4 is assumed as 6, 5, 4, and 7, respectively.\n\n");
	printf("===========================================================\n");
	
	int allo[4]={0,0,0,0};
	int allo_copy[4];
	
	int need[4]={6,5,4,7};
	int need_copy[4];
	
	int available=10;
	
	int i;
	for (i=0;i<=3;i++){		//Asks each process for a request and processes the request
		srand(time(NULL));
		int a= rand()%4;	//random number between 0-3
		printf("Customer %d has requested %d resources\n\n", i+1, a);
			
		allo[i]=a;
		need[i]=need[i]-a;
		
		//calculate allocated resources to determine available resources
		int allocated=0;
		int k;
		for (k=0;k<=3;k++){
			allocated=allocated+allo[k];
		}
		available=10-allocated;
		
		//copy stuff from allo to allo_copy
		int c;
		for(c=0;c<=3;c++){
			allo_copy[c]=allo[c];
		}
		
		//copy stuff from need to need_copy
		int b;
		for(b=0;b<=3;b++){
			need_copy[b]=need[b];
		}
		
		//Bankers algorithm
		printf("Checking if request can be granted...\n");
		while(need_copy[0]<=available || need_copy[1]<=available || need_copy[2]<=available || need_copy[3]<=available ){
			int j;
			for (j=0;j<=3;j++){
				if (need_copy[j]<=available){
					available=available+allo_copy[j];
					need_copy[j]=100;	//If 100, process has terminated
				}
			}		
		}
		printf("Done checking!\n\n");
		
		if(need_copy[0]==100 && need_copy[1]==100 && need_copy[2]==100 && need_copy[3]==100){
			printf("System will be SAFE if Customer %d was granted %d resources!\n\n", i+1, a);
		}
		else{
			printf("System will be UNSAFE if Customer %d was granted %d resources\n\n", i+1,a);
			need[i]=need[i]+allo[i];
			allo[i]=0;
		}
		
		//Print table
		printf("\t\tAllocated\tNeed\n");
		int x;
		for(x=0;x<=3;x++){
			printf("Customer %d\t%d\t\t%d\n", x+1, allo[x], need[x]);
		}	
		printf("\n===========================================================\n");
	}
} 

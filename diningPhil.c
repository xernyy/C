//Solve the dining philosopher's problem using monitors instead of semaphores

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

//GLOBAL VARIABLES

sem_t lock1;
sem_t lock2;
sem_t self[5];

int N=5; 
char* state[5]={"Thinking", "Thinking", "Thinking", "Thinking", "Thinking"};

//PROTOTYPE

void *philosopher (void *myvar);
void test(int k);

//MAIN

int main(void){
    pthread_t thread1, thread2, thread3, thread4, thread5;
    
    int philo [5]={0, 1, 2, 3, 4};
    
    sem_init(&lock1, 0, 1);
    sem_init(&lock2, 0, 1);
    int i;
    for(i=0;i<5;i++){
        sem_init(&self[i], 0, 0);
    }      
    
    pthread_create(&thread1, NULL, philosopher, (void*)&philo[0]);
    pthread_create(&thread2, NULL, philosopher, (void*)&philo[1]);
    pthread_create(&thread3, NULL, philosopher, (void*)&philo[2]);
    pthread_create(&thread4, NULL, philosopher, (void*)&philo[3]);
    pthread_create(&thread5, NULL, philosopher, (void*)&philo[4]);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);   
}

void *philosopher (void *myvar){
    while(1){
        int x;
        x=*((int *)myvar);
        
        //Pickup chopstick

            sem_wait(&lock1);
            state[x]="Hungry";
            printf("Philosopher %d is %s\n", x+1, state[x]);
            sleep(1);
            test(x);
            if(state[x]!="Eating"){
            printf("Philosopher %d is WAITING\n", x+1);
                sem_wait(&self[x]);
            }
            sem_post(&lock1);

            //Eat

            sem_wait(&lock2);
            state[x]="Thinking";
            printf("Philosopher %d is %s\n", x+1, state[x]);
            sleep(1);

            int RIGHT=(x+1)%N;
            test(RIGHT);

            int LEFT=(x+N-1)%N;
            test(LEFT);

            sem_post(&lock2);

            //Think 
        }
}

void test(int k){
    if(((state[(k+N-1)%N])!="Eating")&&(state[k]=="Hungry")&&((state[(k+1)%N])!="Eating")){
        state[k]="Eating";
            printf("Philosopher %d is %s\n", k+1, state[k]);
            sleep(1);
        sem_post(&self[k]);
    }
}

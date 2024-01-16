#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "queue.h"


#define SIZE 1000
int count;
Queue ProcList;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

Process* generateProcess(){
	Process* v=(Process*)malloc(sizeof(Process));
	v->id=random();
	v->exec_time=random() % 1000;
	return v;
}

void excProcess(){
	        Process* proc=dequeue(&ProcList);  //estrazione del processo dalla  ProcList
		proc->start=;   //inizio dell'esecuzione del processo
		sleep(proc->exec_time);  //tempo di esecuzione
		proc->end=;    //fine dell'esecuzione
		count--;
}

void insertProcess(Process* newProc){
	        enqueue(&ProcList, newProc);
		newProc->arrival=;
		count++;
}


void* producer(void* arg){
	while(1){
		int sleep=(int)random() % 1000;
		usleep(sleep);
		pthread_mutex_lock(&lock);
		while(count==SIZE){
			pthread_cond_wait(&lock,&cond);
		}
		for(int i=0 ; i<10 ; i++){
			Process* newProc=generateProcess();
			insertProcess(newProc);
		}
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

void* consumer1(void* arg){
	while(1){
		int sleep=(int)random() % 1000;
		usleep(sleep);
		pthread_mutex_lock(&lock);
		while(count==0){
			pthread_cond_wait(&lock,&cond);
		}
		excProcess();
		
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

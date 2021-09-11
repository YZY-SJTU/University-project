#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

#define CookTime 1

sem_t sem_rack_distance_to_full, sem_rack_distance_to_empty, sem_current_order, sem_cashier_available, sem_ready;
int total_cook, total_cashier, total_customer, MaxRackSize;
pthread_t *pthread_cook, *pthread_cashier, *pthread_customer;
int *cookID, *cashierID, *customerID;

void *cook(void *cookID){
	int id = *(int *)cookID;
	usleep((rand()%999)*1000);//make cook not make a burger at the same time for CookTime is the same
	while(1)
	{		
		sem_wait(&sem_rack_distance_to_full);//if rack is full, wait
		sleep(CookTime);//time to make a burger
		printf("Cooks [%d] make a burger.\n", id);
		sem_post(&sem_rack_distance_to_empty);//burger in rack + 1
	}
}

void *cashier(void *cashierID){
	int id = *(int *)cashierID;
	while(1)
	{
		sem_wait(&sem_current_order);//wait for an order
		printf("Cashier [%d] accepts an order.\n", id);
		sem_wait(&sem_rack_distance_to_empty);
		//wait and fetch a burger from the rack
		sem_post(&sem_rack_distance_to_full);
		printf("Cashier [%d] take a burger to customer.\n", id);
		sem_post(&sem_ready);		//make the customer able to leave
	}
}

void *customer(void *customerID){
	int id = *(int *)customerID;
	//wait a time and approach a cashier
	usleep((rand()%(total_customer*1000))*1000);//make time distance between customers long
	printf("Customer [%d] comes.\n", id);
	sem_wait(&sem_cashier_available);
	//approaching a cashier and start ordering
	sem_post(&sem_current_order);
	sem_wait(&sem_ready);
	//get the burger and leave
	sem_post(&sem_cashier_available);	//cashier is able to receive order again
}
	
int main(int argc, char **argv){
	if(argc != 5)
	{
		printf("Wrong Input!\n");
		exit(1);
	}

	//initialization
	srand(time(NULL));
	total_cook = atoi(argv[1]);
	total_cashier = atoi(argv[2]);
	total_customer = atoi(argv[3]);
	MaxRackSize = atoi(argv[4]);
	printf("Cooks [%d], Cashiers [%d], Customers [%d]\n", total_cook, total_cashier, total_customer);
	
	sem_init(&sem_rack_distance_to_full, 0, MaxRackSize);
	sem_init(&sem_rack_distance_to_empty, 0, 0);
	sem_init(&sem_current_order, 0, 0);
	sem_init(&sem_cashier_available, 0, total_cashier);
	sem_init(&sem_ready,0, 0);
	
	//allocate memory space
	pthread_cook = malloc(total_cook * sizeof(pthread_t));
	pthread_cashier = malloc(total_cashier * sizeof(pthread_t));
	pthread_customer = malloc(total_customer * sizeof(pthread_t));
	cookID = malloc(total_cook * sizeof(int));
	cashierID = malloc(total_cashier * sizeof(int));
	customerID = malloc(total_customer * sizeof(int));
	
	printf("Begin run.\n");

	//create pthread
	int i;
	for(i=0; i<total_cook; ++i)
	{
		cookID[i] = i + 1;
		pthread_create(pthread_cook+i, NULL, cook, cookID+i); 
	}
	for(i=0; i<total_cashier; ++i)
	{
		cashierID[i] = i + 1;
		pthread_create(pthread_cashier+i, NULL, cashier, cashierID+i); 
	}
	for(i=0; i<total_customer; ++i)
	{
		customerID[i] = i + 1;
		pthread_create(pthread_customer+i, NULL, customer, customerID+i); 
	}
	for(i=0; i<total_customer; ++i)
		pthread_join(pthread_customer[i], NULL);//ensure customer processes will not finish after cook and cashier finish

	printf("Finish run.\n");

	//release the space and destroy semaphore
	free(pthread_cook);
	free(pthread_cashier);
	free(pthread_customer);
	free(cookID);
	free(cashierID);
	free(customerID);
	
	sem_destroy(&sem_rack_distance_to_full);
	sem_destroy(&sem_rack_distance_to_empty);
	sem_destroy(&sem_current_order);
	sem_destroy(&sem_cashier_available);
	sem_destroy(&sem_ready);

	return 0;
}

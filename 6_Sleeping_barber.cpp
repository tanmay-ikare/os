#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX_CUSTOMERS 25
void *customer(void *num);
void *barber(void *);
void randwait(int secs);
sem_t waitingRoom;
sem_t barberChair;
sem_t barberPillow;
sem_t seatBelt;
int allDone = 0;
int main(int argc, char *argv[])
{
    pthread_t btid;
    pthread_t tid[MAX_CUSTOMERS];
    long RandSeed;
    int i, numCustomers, numChairs;
    int Number[MAX_CUSTOMERS];
    printf("\n\n--- Sleeping Barber Problem ---\n\n");
    printf("\tEnter no of Customers: ");
    scanf("%d,", &numCustomers);
    printf("\tEnter no of Chairs: ");
    scanf("%d", &numChairs);
    printf("\n");
    if (numCustomers > MAX_CUSTOMERS)
    {
        printf("\n\n--- Maximum no of Customers is %d ---\n\n", MAX_CUSTOMERS);
        exit(-1);
    }
    // Initialize the numbers array.
    for (i = 0; i < MAX_CUSTOMERS; i++)
    {
        Number[i] = i;
    }
    // Initialize the semaphores with initial values…
    sem_init(&waitingRoom, 0, numChairs);
    sem_init(&barberChair, 0, 1);
    sem_init(&barberPillow, 0, 0);
    sem_init(&seatBelt, 0, 0);
    // Create the barber.
    pthread_create(&btid, NULL, barber, NULL);
    // Create the customers.
    for (i = 0; i < numCustomers; i++)
    {
        pthread_create(&tid[i], NULL, customer, (void *)&Number[i]);
        sleep(1);
    }
    // Join each of the threads to wait for them to finish.
    for (i = 0; i < numCustomers; i++)
    {
        pthread_join(tid[i], NULL);
        sleep(1);
    }
    // When all of the customers are finished, kill the
    // barber thread.
    allDone = 1;
    sem_post(&barberPillow); // Wake the barber so he will exit.
    pthread_join(btid, NULL);
}
void *customer(void *number)
{
    int num = *(int *)number;
    printf("--> Customer %d leaving for barber shop.\n", num);
    randwait(2);
    printf("--> Customer %d arrived at barber shop.\n", num);
    sem_wait(&waitingRoom);
    printf("--> Customer %d entering waiting room.\n", num);
    sem_wait(&barberChair);
    sem_post(&waitingRoom);
    printf("--> Customer %d waking the barber.\n", num);
    sem_post(&barberPillow);
    // Wait for the barber to finish cutting your hair.
    sem_wait(&seatBelt);
    // Give up the chair.
    sem_post(&barberChair);
    printf("--> Customer %d leaving barber shop.\n", num);
}
void *barber(void *junk)
{
    while (!allDone)
    {
        // Sleep until someone arrives and wakes you..
        printf("--> The barber is sleeping\n");
        sem_wait(&barberPillow);
        // Skip this stuff at the end…
        if (!allDone)
        {
            printf("--> The barber is cutting hair\n");
            randwait(2);
            printf("--> The barber has finished cutting hair.\n\n");
            // Release the customer when done cutting…
            sem_post(&seatBelt);
        }
        else
        {
            printf("--> The barber is going home for the day.\n");
        }
    }
}
void randwait(int secs)
{
    int len;
    len = (int)((1 * secs) + 1);
    sleep(len);
}

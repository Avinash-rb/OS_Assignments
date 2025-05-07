//Dinning Philosopher
// /with deadlock starvation
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  

sem_t chopstick[N]; 

void *philosopher(void *num) {
    int i = *(int*)num;
    
    while (1) {
        printf("Philosopher %d is thinking\n", i);
        sleep(2);  
        
        printf("Philosopher %d is hungry\n", i);
        
        
        sem_wait(&chopstick[i]);                 
        sem_wait(&chopstick[(i + 1) % N]);    
        
        printf("Philosopher %d is eating\n", i);
        sleep(2);  
        
    
        sem_post(&chopstick[i]);                  
        sem_post(&chopstick[(i + 1) % N]);       
        
        printf("Philosopher %d finished eating\n", i);
    }
}

int main() {
    int i;
    pthread_t philosophers[N];
    int philosopher_nums[N];
    for (i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 1);
    }
    for (i = 0; i < N; i++) {
        philosopher_nums[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_nums[i]);
    }
    
    for (i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    return 0;
}

//Without deadlock odd even
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2

sem_t chopstick[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];
int state[NUM_PHILOSOPHERS];

void think(int phil_id) {
    printf("Philosopher %d is thinking\n", phil_id);
    sleep(2);
}

void eat(int phil_id) {
    printf("Philosopher %d is eating\n", phil_id);
    sleep(2);
}

void* philosopher(void* arg) {
    int phil_id = *(int*)arg;
    int left = phil_id;
    int right = (phil_id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        think(phil_id);

        state[phil_id] = HUNGRY;
        printf("Philosopher %d is hungry\n", phil_id);

        if (phil_id % 2 == 0) {
            sem_wait(&chopstick[right]);
            printf("Philosopher %d picked up right chopstick %d\n", phil_id, right);
            sem_wait(&chopstick[left]);
            printf("Philosopher %d picked up left chopstick %d\n", phil_id, left);
        } else {
            sem_wait(&chopstick[left]);
            printf("Philosopher %d picked up left chopstick %d\n", phil_id, left);
            sem_wait(&chopstick[right]);
            printf("Philosopher %d picked up right chopstick %d\n", phil_id, right);
        }

        state[phil_id] = EATING;
        eat(phil_id);

        sem_post(&chopstick[left]);
        sem_post(&chopstick[right]);

        state[phil_id] = THINKING;
        printf("Philosopher %d put down chopsticks\n", phil_id);
    }
    return NULL;
}

int main() {
    int i;
    int ids[NUM_PHILOSOPHERS];

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&chopstick[i], 0, 1);
        state[i] = THINKING;
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&chopstick[i]);
    }

    return 0;
}


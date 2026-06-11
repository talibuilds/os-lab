#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t forks[N];
pthread_t philosophers[N];

void* philosopher(void *num)
{
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % N;

    while(1)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // Deadlock prevention
        if(id % 2 == 0)
        {
            pthread_mutex_lock(&forks[left]);
            printf("Philosopher %d picked up left fork %d\n", id, left);

            pthread_mutex_lock(&forks[right]);
            printf("Philosopher %d picked up right fork %d\n", id, right);
        }
        else
        {
            pthread_mutex_lock(&forks[right]);
            printf("Philosopher %d picked up right fork %d\n", id, right);

            pthread_mutex_lock(&forks[left]);
            printf("Philosopher %d picked up left fork %d\n", id, left);
        }

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);

        printf("Philosopher %d put down forks %d and %d\n",
               id, left, right);
    }

    return NULL;
}

int main()
{
    int ids[N];

    // Initialize forks
    for(int i = 0; i < N; i++)
        pthread_mutex_init(&forks[i], NULL);

    // Create threads
    for(int i = 0; i < N; i++)
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL,
                       philosopher, &ids[i]);
    }

    // Wait for threads
    for(int i = 0; i < N; i++)
        pthread_join(philosophers[i], NULL);

    // Destroy mutexes
    for(int i = 0; i < N; i++)
        pthread_mutex_destroy(&forks[i]);

    return 0;
}
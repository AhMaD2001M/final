#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

const int TOTAL_TICKETS = 10;
int available_tickets = TOTAL_TICKETS;
sem_t semaphore;

void *book_tickets(void *arg)
{
    int user_id = *((int *)arg);
    int tickets_to_book = rand() % 3 + 1;

    sem_wait(&semaphore);

    if (available_tickets >= tickets_to_book)
    {
        available_tickets -= tickets_to_book;
        cout << "Booking successful: User " << user_id << " booked " << tickets_to_book << " tickets. Tickets left: " << available_tickets << endl;
    }
    else
    {
        cout << "Booking failed: User " << user_id << " requested " << tickets_to_book << " tickets. Not enough tickets available." << endl;
    }

    sem_post(&semaphore);
    return NULL;
}

int main()
{
    srand(time(NULL));
    pthread_t threads[15];
    int user_ids[15];

    sem_init(&semaphore, 0, 1);

    for (int i = 0; i < 15; ++i)
    {
        user_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, book_tickets, (void *)&user_ids[i]);
    }

    for (int i = 0; i < 15; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);

    return 0;
}
//Kebba Demba
//CST - 221
//Dead Lock avoidance

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX 5
int buffer[MAX];

// monitor
typedef struct Monitor
{
	int mutex;
	int full;
	int empty;

} Monitor;

//stores how many products
int counter = 0;

//timer
clock_t start_t, end_t, total_t;

//buffer size
int length = sizeof(buffer) / sizeof(int);


//define methods
int produce();
void put();
void *producer();
void *consumer();
void consume();
int get();

//code given by instructor
int theProduct;

//add product
int produce()
{
	return theProduct + 1;
}

void consume(int i)
{
	printf("Consumed: %i\n", i);
}

//add to buffer
void *producer(Monitor *monitor)
{
	//start the timer
	start_t = clock();
	printf("Timer has been started. start_t = %ld\n", start_t);
	printf("/***Producing***/\n");

	int i;
	int total;

	//unlock the mutex until the producer and consumer functions are finished
	monitor->mutex = 1;

	printf("Mutex has been unlocked.\n");

	//check if monitor is NOT full
	while (monitor->full == 0)
	{

		//check if the buffer is full
		if (length == counter)
		{

			printf("Buffer is full.\n");

			//stop the timer
			end_t = clock();
			printf("Timer has been stopped. end_t = %ld\n", end_t);

			//calculate the total time that was taken
			total = end_t - start_t;
			printf("Total time: %d\n", total);

			//put the producer to sleep
			printf("Producergoing to sleep.\n");
			sleep(10); 
		}
		else
		{
	
			printf("Buffer has available spot.\n");

			//produce the new product
			i = produce();

			//put the product into the buffer
			put(i);
			counter++;
		}

		//call the consumer process & set the monitor to full/not empty -- without this, the consumer process would end in a deadlock
		//check if timer is finished
		if (total > 5)
		{
			//set monitor to full & not empty
			monitor->full = 1;
			monitor->empty = 0;
			//call the consumer process & pass the monitor
			consumer(monitor);
		}
	}
	return 0;
}

//method to consumer the product from the buffer
void *consumer(Monitor *monitor)
{
	printf("/***Consuming***/\n");

	int i;
	//loop while monitor is NOT deemed as empty
	while (monitor->empty == 0)
	{

		//check if buffer is full
		if (counter <= 5 && counter > 0)
		{
			
			printf("Buffer is full. Products may now be consumed.\n");

			i = get();

			//consume the product
			consume(i);

			counter--;
			if (counter == 0)
			{
				printf("Buffer is empty.\n");

				//set monitor to not full & empty
				monitor->full = 0;
				monitor->empty = 1;

				//lock the mutex and block until it becomes available
				//the consumer function is done so the mutex must be locked
				monitor->mutex = 0;

				//put consumer to sleep
				printf("Consumer going to sleep.\n");
				sleep(20);
			}
		}
	}
	return 0;
}

//method to receive what the producer creates
void put(int i)
{
	//set the product to the given int
	theProduct = i;

	//output what has been produced
	printf("Produced: %i\n", i);

	//put into buffer
	buffer[counter] = i;

	return;
}

//method to get the product from the buffer
int get()
{
	//get the most recent product produced from the buffer
	int productToBeConsumed = buffer[counter];
	return productToBeConsumed;
}

int main(int argc, char *argv[])
{

	//create monitor struct
	Monitor monitor = {
			//lock the mutex by setting to 0
			.mutex = 0,
			//set the full attribute to 0 (false)
			.full = 0,
			//set the empty attribute to 1 (true)
			.empty = 1};

	//call the producer function first and pass the monitor
	producer(&monitor);

	return 0;
}
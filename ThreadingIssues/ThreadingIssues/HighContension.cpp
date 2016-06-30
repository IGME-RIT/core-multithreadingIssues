#include "ClassDeclarations.h"

//what does it mean for a lock to be highly contended?
	//This means that threads try to acquire locks faster than the thread can execute the corresponding critical section
	//The threads end up forming a queue waiting for the currently executing thread to finish

//This can be caused by having too many threads among other reasons

static std::mutex m;
static unsigned int n = 0;

void test(int numThread);

void HighContension::highContensionExample()
{
	//lets make a lot of threads to showcase this issue
	std::thread threadArr[8];

	//initialize all of them with the test function
	for (int i = 0; i < 8; i++)
	{
		threadArr[i] = std::thread(test, i);
	}

	//Join the threads back to the main thread
	for (int i = 0; i < 8; i++)
	{
		if (threadArr[i].joinable())
			threadArr[i].join();
	}
}

void test(int numThread)
{
	m.lock();
	//The critical section to be run
	//The rest of the threads have to wait until the mutex is unlocked to use n
	//Since n++ is a short operation the for loop doesn't take too long, but it still takes a bit and can slow down the program
	for (int i = 0; i < 100; i++)
	{
		n++;
		printf("Thread %d N: %d\n", numThread, n);
	}
	//This is to show when one thread is finished
	printf("Thread Switch!\n");
	m.unlock();

	//You saw how each thread had to wait until the other threads were done to execute
	//Due to the lock being highly contended, Multithreading was pointless in this example
	//You could have just as easily have done a for loop 100,000 times in a single thread instead of 10 threads working 10,000 times
}

//The solution is dependant on the current issue.
	//In this case,
		//Could just not use multithreading
		//Could increment 10 different numbers and then add them together later - not the best idea, since that is 9 extra variables
		//There could be more.
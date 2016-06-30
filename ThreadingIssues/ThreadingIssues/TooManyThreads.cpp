#include "ClassDeclarations.h"

void fnctn1(int num);
void fnctn2();

//Used:
	//http://web.stanford.edu/class/cs140/cgi-bin/lecture.php?topic=process
//Needs more work

//Too Many Threads
	//This is essentially when you create too many threads

//too many threads can degrade performance

//partitioning a fixed amount of work among too many threads, with each having too little work

//more software threads than hardware threads
	//round robin scheduling
	//time slicing - prevents starvation of other processes

//Forms of Overhead:
	//Saving and Restoring a thread's register state
	//Saving and Restoring a thread's cache state
	//thrashing virtual memory
		//When a computer's virtual memory is in a constant state of paging
		//http://searchstorage.techtarget.com/definition/virtual-memory - look into
	//convoying or in other words highy contested locks - when threads line up waiting to acquire a lock




//IGNORE THE BELOW EXAMPLE, IT ISN'T EVEN CLOSE TO FINISHED




static const int numThreads = 8;
//static const int numThreads = 64;

//Something to time the amount of time each thread takes
static std::chrono::time_point<std::chrono::system_clock> starts[numThreads];	//When the thread's function starts
static std::chrono::time_point<std::chrono::system_clock> ends[numThreads];		//When the thread's function ends
static std::chrono::duration<double, std::milli> elapsedTimes[numThreads];		//The change in time from start to end

void TooManyThreads::tooManyThreads()
{
	//Create several threads?
	//Create a lot of threads to do a task

	std::thread threads[numThreads];
	for (int i = 0; i < numThreads; i++)
	{
		threads[i] = std::thread(fnctn1, i);
	}

	//Join them to the main thread
	for (int i = 0; i < numThreads; i++)
	{
		threads[i].join();
	}

	//Calculate the amount of time it took each thread to complete
	for (int i = 0; i < numThreads; i++)
	{
		elapsedTimes[i] = ends[i] - starts[i];
		std::cout << "Elapsed Times: " << elapsedTimes[i].count() << std::endl;
	}

	//Find which thread took the most time
		//This will be the total time it took all threads to finish
	std::chrono::duration<double, std::milli> totalTime;
	for (int i = 0; i < numThreads; i++)
	{
		if (elapsedTimes[i] > totalTime)
			totalTime = elapsedTimes[i];
	}
	//print the longest time
	std::cout << "\nTotal Time Function1: " << totalTime.count() << std::endl;
	
	fnctn2();

	std::cout << "" << std::endl;

}

static std::mutex m;

//int ps[numThreads] = {0, 0, 0, 0, 0, 0, 0, 0,
//					  0, 0, 0, 0, 0, 0, 0, 0,
//					  0, 0, 0, 0, 0, 0, 0, 0,
//					  0, 0, 0, 0, 0, 0, 0, 0,
//					  0, 0, 0, 0, 0, 0, 0, 0,
//					  0, 0, 0, 0, 0, 0, 0, 0,
//					  0, 0, 0, 0, 0, 0, 0, 0,
//					  0, 0, 0, 0, 0, 0, 0, 0 };

static int ps[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

static int p = 0;

void fnctn1(int num)
{
	starts[num] = std::chrono::system_clock::now();
	//Things to happen
	
	//So, we aren't locking and unlocking 10,000,000 times
		//We mutex the loop itself
	
	int counter = 0;
	for (int i = 0; i < 1000000; i++)
	{
		counter++;
	}
	m.lock();
	ps[num] += counter;
	m.unlock();
	
	ends[num] = std::chrono::system_clock::now();
}

void fnctn2()
{
	std::chrono::time_point<std::chrono::system_clock> s, e;

	s = std::chrono::system_clock::now();
	for (int i = 0; i < 1000000*numThreads; i++)
	{
		p++;
	}
	e = std::chrono::system_clock::now();

	std::chrono::duration<double, std::milli> totalTime = e - s;
	std::cout << "\nTotal Time Function2: " << totalTime.count() << std::endl;
}
#include "ClassDeclarations.h"

//A great example of how to use condition variables
	//http://www.cplusplus.com/reference/condition_variable/condition_variable/

static std::mutex m;
static std::condition_variable cv;	//Has no copy constructor

static void foo1();
static void bar1();

static void foobar(int numThreads);

static void foo2();
static void bar2();

//A condition variable is an object able to block the calling thread until notified to resume.
	//From: http://www.cplusplus.com/reference/condition_variable/condition_variable/

void ConditionVariables::conditionVariablesExample()
{
	//This is for the basic example
	/*std::thread t1(foo1);
	std::thread t2(bar1);

	if (t1.joinable())
		t1.join();
	if (t2.joinable())
		t2.join();*/


	//printf("\nnotify_one() example:\n");

	////notify_one() example
	//std::thread threads1[4];
	//
	//for (int i = 3; i >= 0; i--)
	//{
	//	printf("i: %d\n", i);
	//	threads1[i] = std::thread(foobar, i);
	//}

	//for (int i = 3; i >= 0; i--)
	//{
	//	if (threads1[i].joinable())
	//		threads1[i].join();
	//}

	printf("\nnotify_all() example:\n");

	//notify_all() example
	std::thread threads2[4];

	

	for (int i = 3; i >= 0; i--)
	{
		if ( i != 0)
			threads2[i] = std::thread(bar2);
		else
			threads2[0] = std::thread(foo2);
	}

	for (int i = 3; i >= 0; i--)
	{
		if (threads2[i].joinable())
			threads2[i].join();
	}
}

void foo1()
{
	//So we put a unique_lock on this thread function
		//this is an object that manages a mutex with sole ownership while it is locked or unlocked
	std::unique_lock<std::mutex> lck(m);

	//We are waiting until this thread is notified it can continue
		//The execution of the current thread is blocked until notified
	cv.wait(lck);
	printf("Finally ready!\n");
}

void bar1()
{
	//Just waiting
	for (int i = 100; i > 0; --i)
	{
		printf("Waiting: %d\n", i);
	}

	//unblocks 1 of the threads currently waiting for this condition
		//From:http://www.cplusplus.com/reference/condition_variable/condition_variable/notify_one/
		//In this case the only thing waiting on this condition variable is lck in foo()
	cv.notify_one();
	//Can also use
	//cv.notify_all();
	//uncomment the above and comment "cv.notify_one();" and try it
}

//Now the question is, when should you use notify_one() versus notify_all()

//notify_one()
	//This is for when you have many threads sleeping and you only want to wake one at a time and not all of them at once
		//Used: http://stackoverflow.com/questions/9015748/whats-the-difference-between-notify-all-and-notify-one-of-stdcondition-va
	//Below is a naive example
void foobar(int numThread)
{
	//Acquire the lock
	std::unique_lock<std::mutex> lck(m);

	//Check to see if this is the last thread
		//if it isn't, wait
		//This statement exists so that not all threads are waiting cv to notify them
			//This would mean that no thread makes progress and that would be bad

	if (numThread != 0)
	{
		cv.wait(lck);
	}

	
	//Just waiting
	for (int i = 100; i > 0; --i)
	{
		printf("T%d Waiting: %d\n", numThread, i);
	}
	cv.notify_one();
	
	printf("Finally ready!\n");
}

//notify_all()
	//this can be used when one thread is holding up the other threads with an important task it is doing
	//The other threads are reliant on this task, but the do not care about the others, since they aren't sharing data between them
//Below is a naive example
void foo2()
{
	//Important Task for the first thread that the other threads need done
	for (int i = 100; i > 0; --i)
	{
		printf("Important Tasking: %d\n", i);
	}

	cv.notify_all();
	printf("Finally ready!\n");
}

void bar2()
{
	//Acquire the lock
	std::unique_lock<std::mutex> lck(m);

	//Wait until the first thread is done, so that this may go
	cv.wait(lck);

	//Random task that this thread is doing
	for (int i = 100; i > 0; --i)
	{
		printf("Random Other Tasking: %d\n", i);
	}

	printf("Finally ready!\n");
}
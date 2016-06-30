#include "ClassDeclarations.h"

//A great example of how to use condition variables
	//http://www.cplusplus.com/reference/condition_variable/condition_variable/

static std::mutex m;
static std::condition_variable cv;	//Has no copy constructor

static void foo();
static void bar();

//A condition variable is an object able to block the calling thread until notified to resume.
	//From: http://www.cplusplus.com/reference/condition_variable/condition_variable/

void ConditionVariables::conditionVariablesExample()
{
	std::thread t1(foo);
	std::thread t2(bar);

	if (t1.joinable())
		t1.join();
	if (t2.joinable())
		t2.join();
}

void foo()
{
	//So we put a unique_lock on this thread function
		//this is an object that manages a mutex with sole ownership while it is locked or unlocked
	std::unique_lock<std::mutex> lck(m);

	//We are waiting until this thread is notified it can continue
		//The execution of the current thread is blocked until notified
	cv.wait(lck);
	printf("Finally ready!");
}

void bar()
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
}
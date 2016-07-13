#include "ClassDeclarations.h"

//Used:
	//http://austingwalters.com/multithreading-common-pitfalls/
	//https://www.youtube.com/watch?v=lVBvHbJsg5Y

//Race Condition
	//This is merely the behavior of our code when the output is dependent on the sequence of uncontrollable events
		//Used: https://en.wikipedia.org/wiki/Race_condition
	//This can happen when one or more threads simultaneously access a critical section with out any guarantee of the memory ordering
		//By memory ordering I merely mean the order in which the reads (if(num) <- reading num's value) and the writes (num = 5 <- writing the value 5 into num) happen in the code

//Below we will show an example of a race condition

void functionRC(int threadNum);
void functionRCSol(int threadNum);

//void function2RC();
//void function2RCSol();

void RaceConditions::raceConditionsExample()
{
	std::thread t1, t2;
	t1 = std::thread(functionRC, 1);
	t2 = std::thread(functionRC, 2);


	t1.join();
	t2.join();
	//to solve, need to make sure the critical sections are atomic
		//essentially make sure it the critical section can only be used by a single thread at a time
}

static std::mutex m;

//long long is required to be at least a 64 bit integer value
static long long dataRace = 0;

//This is merely a function that increments a number 10 times
//since this number is being incremented and stored and there is no mutex this, you will notice a problem with the output
void functionRC(int threadNum)
{
	for (int i = 0; i < 10; i++)
	{
		//First you load dataRace and save it into numy
		//Then you store 1 plus numy in dataRace
		//These are two separate operations in assembly and that is what it compiles down into

		int numy = (int)dataRace;
		//A data race can occur here.
		//After Data Race has been loaded, but before it is stored a thread may access it and change it,
			//which means your operation is using invalid/old data
		dataRace = numy+1;
		//A data race can also occur here.
		//This thread loads data Race, but another thread can come along and start using dataRace
		//This then means that the value of dataRace becomes obsolete
		printf("F%d Data Race Num: %d\n", threadNum, dataRace);
	}
	printf("Function1RC Done\n");
}


//Run this set of examples a few times and look at the output
//Notice how variables will be printed to the screen in the incorrect order
	//(the number 5 printing after the number 17 for example)
	//whether it was printed by F1 or F2 doesn't matter

//To solve this issue requires a few steps
	//1) figure out the critical section
	//2) make the critical section uninterruptible or make the operations atomic
		//Can be done with locks or more advanced techniques

//The simplest way to solve this is to mutex the critical section
//Try it by passing in these functions into the threads

void functionRCSol(int threadNum)
{
	//since locking and unlocking does take some time
		//we don't want to lock and unlock one each loop, so we will just mutex the for loop
			//this will be faster
			//Also it encompasses the critical section which is what we want
	m.lock();
	for (int i = 0; i < 10; i++)
	{
		int numy = (int)dataRace;
		dataRace = numy+1;
		printf("F%d Data Race Num: %d\n", threadNum, dataRace);
	}
	printf("Function1RC Done\n");
	m.unlock();
}
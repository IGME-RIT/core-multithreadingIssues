/*
Multithreading Issues
(c) 2016
original authors: Sean Connolly
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*	This tutorial deals with the various issues that can occure when multithreading in C/C++.
*	It covers issues such as Deadlock, Livelock, High Contentsion, Priority Inversion, Data Races, and too many threads.
*/
#include "ClassDeclarations.h"

void func1();
void func2();
void func1Sol();
void func2Sol();
static std::mutex mtx1;
static std::mutex mtx2;

//Used:
	//http://stackoverflow.com/questions/1036364/good-example-of-livelock
		//Used almost as is, but made slight changes and added comments
		//Also has more examples of livelock
	//http://stackoverflow.com/questions/6155951/whats-the-difference-between-deadlock-and-livelock
		//Used for definitions

//Livelock is where the states of the threads constantly change in regard to one another with neither progressing
	//Can be a risk with algorithms that detect and recover from deadlock

void Livelock::livelockExample()
{
	std::thread t1(func1);
	std::thread t2(func2);

	/*std::thread t1(func1Sol);
	std::thread t2(func2Sol);*/

	if(t1.joinable())
		t1.join();
	if (t2.joinable())
		t2.join();
}

//This is a contrived example, but it gives a basic idea of what it can look like
//Also, this is not an example of a stable livelock as it will eventually break out,
	//but put a breakpoint on lines on the entrance to the while loops

//If these went at the exact same time, this would produce a livelock
void func1()
{
	//Lock mutex1
	mtx1.lock();

	//Wait so mtx2 can lock when the other function starts
	std::this_thread::sleep_for(std::chrono::milliseconds(2));

	//loop while mutex2 is locked
		//try_lock() will try to lock the mutex, if it fails then it returns false
		//if it locks the mutex, then it will return true
	while (mtx2.try_lock() == false)
	{
		printf("Trying to get Mutex 2\n");
		//Step aside for the other thread
		mtx1.unlock();
		//Wait a bit
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		//Lock yourself again
		mtx1.lock();
	}

	printf("F1 Done!\n");
	//Need to unlock both incase the function has both
	mtx1.unlock();
	mtx2.unlock();
}

void func2()
{
	//Lock mutex2
	mtx2.lock();

	//Loop while mutex1 is locked
		//try_lock() will try to lock the mutex, if it fails then it returns false
		//if it locks the mutex, then it will return true
	while (mtx1.try_lock() == false)
	{
		printf("Trying to get Mutex 1\n");
		//Step aside for the other thread
		mtx2.unlock();
		//Wait a bit
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		//Lock yourself again
		mtx2.lock();
	}

	printf("F2 Done!\n");
	//Need to unlock both incase the function has both at this point
	mtx1.unlock();
	mtx2.unlock();
}

//Now when you go through these functions,
	//you will notice that both will be locked at the same time, so it will get stuck in the while loop
	//Now there will eventually come a time when mtx2 is unlocked when func1's while loop check happens
		//This will break it out of the while loop
		//Since we can't account for when actions will happen on other threads, this will happen eventually
	//If it will break out of the while loop, why do we care?
		//It does a few useless loops that could slow down our program if it was bigger and had more working parts
		//Also, this is not the only way to livelock, but it is a pretty good example of a livelock

static std::condition_variable cv;

//Solve by ensuring only one process has priority
//In this case we will use condition variables to make sure when thread goes before the other
void func1Sol()
{
	//lock mtx1
	std::unique_lock<std::mutex> lck1(mtx1);
	//pause execution of current thread until we can get mtx2
		//this unlocks lck1 until notified by cv to continue
		//when notified to continue it will relock lck1
	cv.wait(lck1);

	//gain access to mtx2
	std::unique_lock<std::mutex> lck2(mtx2);
	//print that this thread is done are done
	printf("F1 Done!\n");
}

void func2Sol()
{
	//Gain control of the two mutexes

	//lock mtx2
	std::unique_lock<std::mutex> lck2(mtx2);
	//lock mtx1
	std::unique_lock<std::mutex> lck1(mtx1);
	//print that this thread is done are done
	printf("F2 Done!\n");
	//notify the other thread that you are done and no longer need the mutexes
	cv.notify_one();
}
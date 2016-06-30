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

//Used:
	//https://en.wikipedia.org/wiki/Deadlock
	//http://stackoverflow.com/questions/6155951/whats-the-difference-between-deadlock-and-livelock

//Another Good Example:
	//http://stackoverflow.com/questions/1385843/simple-deadlock-examples

void foo();
void bar();

void fooSol();
void barSol();

//What is deadlock?
	//An issue that occurs when two actions wait for each other to finish and neither does

//Shows a basic example of deadlock
void Deadlock::deadlockExample()
{
	std::thread t1(foo);
	std::thread t2(bar);

	//std::thread t1(fooSol);
	//std::thread t2(barSol);

	t1.join();
	t2.join();

	
}

//why the double mutexes?
	//Required to show off deadlock
static std::mutex m1;
static std::mutex m2;
static int num = 1;
void foo()
{
	//why the for loop?
		//To have the code run long enough to cause a deadlock
	for (int i = 0; i < 100; i++)
	{
		//why the double mutexes?
		m1.lock();
		m2.lock();
		num++;
		printf("Foo Num: %d\n", num);
		m2.unlock();
		m1.unlock();
		//Why this will cause a deadlock?
			//Since m1 and m2 are constantly being locked and unlocked by foo() and bar(),
			//there will be a point where foo() will try to call m1.lock() or m2.lock()
			//and it will already be locked by the other thread and the other thread will be in the same situation
			//This means that neither will go anywhere

		//Way to Resolve This?
			//Always lock the mutexes in the same order is one way
	}
}

void bar()
{
	//why the for loop?
		//To have the code run long enough to cause a deadlock
	for (int i = 0; i < 100; i++)
	{
		m2.lock();
		m1.lock();
		num--;
		printf("Bar Num: %d\n", num);
		m1.unlock();
		m2.unlock();
	}
}

//Another example of Deadlock()
//Foo()
	//A.Lock();
	//Bar();
//Bar();
	//B.Lock()
	//Foo();

//Solution to fix foo() and bar()
	//You just have to reorder the locks
	//Try it by passing in these functions into the threads
void fooSol()
{
	for (int i = 0; i < 100; i++)
	{
		m1.lock();
		m2.lock();
		num++;
		printf("Foo Num: %d\n", num);
		m2.unlock();
		m1.unlock();
	}
}

void barSol()
{
	for (int i = 0; i < 100; i++)
	{
		m1.lock();
		m2.lock();
		num--;
		printf("FBar Num: %d\n", num);
		m2.unlock();
		m1.unlock();
	}
}
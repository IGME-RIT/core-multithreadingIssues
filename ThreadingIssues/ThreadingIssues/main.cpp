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
*	This tutorial deals with the various issues that can occur when multithreading in C/C++.
*	It covers issues such as Deadlock, Livelock, High Contentsion, Priority Inversion, Data Races, and too many threads.
*/
#include "ClassDeclarations.h"

//Used:
	//http://austingwalters.com/multithreading-common-pitfalls/
	//http://www.drdobbs.com/tools/avoiding-classic-threading-problems/231000499

//Thread Issues
	//Too Many Threads			?
	//Data Races
	//Deadlocks					x
		//thread a		thread b
		//lock1			lock2
		//lock2			lock1
	//Livelocks					?
	//highly contended Locks	x
	//Priority Inversion
		//Requires Conditional Variables for

/*On all modern processors, you can assume that reads and writes of naturally aligned native types are atomic.
As long as the memory bus is at least as wide as the type being read or written,
the CPU reads and writes these types in a single bus transaction,
making it impossible for other threads to see them in a half-completed state.
On x86 and x64 there, is no guarantee that reads and writes larger than eight bytes are atomic.
This means that 16-byte reads and writes of streaming SIMD extension (SSE) registers, and string operations, might not be atomic.*/
	//From: Preshing On Programming


//More resources on Threading:
	//http://baptiste-wicht.com/posts/2012/03/cpp11-concurrency-part1-start-threads.html
	//http://baptiste-wicht.com/posts/2012/03/cp11-concurrency-tutorial-part-2-protect-shared-data.htmls
	//http://baptiste-wicht.com/posts/2012/04/c11-concurrency-tutorial-advanced-locking-and-condition-variables.html
	//http://baptiste-wicht.com/posts/2012/07/c11-concurrency-tutorial-part-4-atomic-type.html

//A few definitions before we start.

//Atomic - of or forming a single irreducible unit or component in a larger system
	//Found by googling atomic

//Atomic Operation - an operation that appears to the rest of the system to occur instantaneously
	//https://en.wikipedia.org/wiki/Linearizability

//Paging - rapidly exchanging memory(RAM) for data on disk(HDD or SSD)
	//It grabs data from the secondary storage(HDD or SSD) in same size blocks called pages

//Below are a few threading issues that should be talked about, but are not able to be easily shown using C++11 code using VS2013

//Starvation - When a process hogs a resource that another process needs, thus starving it
	//I bring this up, since hardware, softawre, and processes are all going to be talked about in this tutorial
	//And this can be a problem if another process starves one of your threads

//Priority Inversion - When one thread with a lower priority gets a hold of a mutex that a higher priority thread requires
	//This means that the priorities get inverted as the higher priority thread must wait for the lower priority thread to finish it's job
	//Priority Inversion tends to happen in real time systems
	//Also, on Posix based systems you can set the Job Scheduler's priority for the threads themselves
	//Used for Definition: http://www.drdobbs.com/tools/avoiding-classic-threading-problems/231000499?pgno=1
	//For more info: http://www.drdobbs.com/jvm/what-is-priority-inversion-and-how-do-yo/230600008

int main()
{
	//Go to the individual CPP files for the tutorials

	RaceConditions raceCondtionExample;
	//raceCondtionExample.raceConditionsExample();

	Deadlock deadlockExample;
	//deadlockExample.deadlockExample();

	//Not done?
	Livelock livelockExample;
	//livelockExample.livelockExample();

	ConditionVariables conditionVariableExample;
	//conditionVariableExample.conditionVariablesExample();

	//Not done - has weird issue with most threads showing that they took zero seconds
		//still weird
		//might get rid of
	TooManyThreads tooManyThreadsExample;
	//tooManyThreadsExample.tooManyThreads();

	HighContension highContensionExample;
	//highContensionExample.highContensionExample();

	//Not done
	PriorityInversion priorityInversionExample;
	//priorityInversionExample.priorityInversionExample();

	

	getchar();
	return 0;
}


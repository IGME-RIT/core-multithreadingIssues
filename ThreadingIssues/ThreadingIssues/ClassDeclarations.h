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
#pragma once
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>
#include <Windows.h>
#include <condition_variable>

class RaceConditions
{
public:
	void raceConditionsExample();

};

class Deadlock
{
public:
	void deadlockExample();
	
};

class Livelock
{
public:
	void livelockExample();

};

class ConditionVariables
{
public:
	void conditionVariablesExample();
};

class TooManyThreads
{
public:
	void tooManyThreads();
};

class HighContension
{
public:
	void highContensionExample();

};

class PriorityInversion
{
public:
	void priorityInversionExample();

};
#include "ClassDeclarations.h"



//Used:
	





//Resources:
	//



//IGNORE THE BELOW EXAMPLE, IT ISN'T EVEN CLOSE TO FINISHED



//struct PriorityThread
//{
//	//nothing more than an 8bit integer type
//	unsigned char priority;
//	std::thread t;
//};
//
//static std::mutex m;
//static std::condition_variable cv;
//
//static void func1();
//static void func2();
//static void func1Sol();
//static void func2Sol();
//
//PriorityThread pts[2];
//
////I have some kind of infinite loop
//
//void PriorityInversion::priorityInversionExample()
//{
//	pts[0].priority = 0;
//	pts[0].t = std::thread(func1);
//
//	std::this_thread::sleep_for(std::chrono::milliseconds(2));
//
//	pts[1].priority = 1;
//	pts[1].t = std::thread(func1);
//
//	if (pts[0].t.joinable())
//		pts[0].t.join();
//	if (pts[1].t.joinable())
//		pts[1].t.join();
//
//
//}
//
//void func1()
//{
//	std::unique_lock<std::mutex> lck(m);
//	if (pts[1].priority >= pts[0].priority)
//		cv.wait(lck);
//
//	//Something that isn't important, but takes time
//	for (int i = 100; i >= 0; i++)
//	{
//		printf("Waiting: %d\n", i);
//	}
//	printf("Func1 Finished!");
//	cv.notify_one();
//}
//
//void func2()
//{
//	std::unique_lock<std::mutex> lck(m);
//	if (pts[1].priority <= pts[0].priority)
//		cv.wait(lck);
//	//Something important here ...
//	printf("Func2 Finished!");
//	cv.notify_one();
//}
//
//void funcSol1()
//{
//}
//
//void funcSol2()
//{
//}
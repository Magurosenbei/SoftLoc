#include "stdafx.h"
#include <process.h>
#include "ThreadProc.h"
#include "Threads.h"

System_Thread :: System_Thread()
:	mThreadHandle(NULL), mbEnded(true), mbActive(false), 
	mStep(16), mPriority(NORMAL_PRIORITY_CLASS), mLastState(THREAD_LASTSTATE)
{
}

System_Thread :: ~System_Thread()
{
}

bool System_Thread :: Begin(int StepRate)
{
	mStep = StepRate;

	mThreadHandle = (HANDLE)_beginthreadex(
		NULL, 0, System_Thread::Exercute, 
		static_cast<void *>(this), 0, &mThreadId);
	mbActive = true;
	return true;
}

void System_Thread :: Stop()
{
	// Post message to thread
	PostThreadMessage(mThreadId, THREAD_STOP, 0, 0);
}

void System_Thread :: Pause(const bool & State)
{
	PostThreadMessage(mThreadId, THREAD_STOP, State, 0);
}

bool System_Thread :: ThreadProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	lParam;
	switch(uMsg)
	{
	case THREAD_PAUSE:
		mbActive = (wParam > 0)? true : false;
		return true;

	case THREAD_STOP:
		mbEnded = true;
		return true;
	}
	return false;	
}

unsigned int System_Thread :: Exercute(void * vParam)
{
	MSG msg;
	System_HiResTimer Timer;
	float Interval = 0.0f, Difference = 0.0f;
	System_Thread * pThread = static_cast<System_Thread *>(vParam);
	SetPriorityClass(GetCurrentProcess(), pThread->mPriority);
	while(!pThread->mbEnded)
	{
		if(PeekMessage(&msg, NULL, THREAD_PAUSE, pThread->mLastState, PM_REMOVE))
		{
			pThread->ThreadProc(msg.message, msg.wParam, msg.lParam);
			continue;
		}
		if(!pThread->mbActive) 
		{
			SleepEx(16, true);
			continue;
		}
		/*if(GetMessage(&msg, NULL, THREAD_PAUSE, pThread->mLastState))
		{
			pThread->ThreadProc(msg.message, msg.wParam, msg.lParam);
			continue;
		}*/
		Timer.Start();
		pThread->Work(Interval);
		Interval = Timer.End();
		Difference = pThread->mStep - Interval;
		if(Difference > 0)
			SleepEx(Difference, true);
	}
	_endthreadex(0);
	return 0;
}

void System_Thread :: Work(const float & Interval)
{
	
}


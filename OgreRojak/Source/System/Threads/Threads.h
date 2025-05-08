#pragma once

class System_Thread
{
protected:
	HANDLE			mThreadHandle;
	unsigned int	mThreadId;
	bool			mbEnded, mbActive;
	long			mStep;

	unsigned long	mPriority;
	unsigned int	mLastState;

	// Overload Work 
	virtual void	Work(const float & Interval);
	// Thread Message Handler
	// Returns false if message not handled
	virtual bool	ThreadProc(UINT uMsg, WPARAM wParam, LPARAM lParam);				
	// Leave this untouched
	static	unsigned int __stdcall	Exercute(void * vParam);
public:
	System_Thread();
	virtual ~System_Thread();
	/* Query */
	inline const unsigned long & Priority() const { return mPriority; }
	inline const bool & Ended()		const	{ return mbEnded;	}
	inline const bool & IsActive()	const	{ return mbActive;	} 
	inline const HANDLE & ThreadHandle() const { return mThreadHandle; }
	inline const unsigned int & ThreadId() const { return mThreadId; }
	//	Start the Thread
	bool	Begin(int StepRate = 16);
	//	Stop the Thread, don't call this
	void	Stop();
	// Pause the Thread
	void	Pause(const bool & State);
};
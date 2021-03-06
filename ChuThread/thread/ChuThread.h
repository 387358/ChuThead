
/*************************************************************************//**

	@file		ChuThread.h
	@authors	Ting-Sheng Chu
	@version	1.0
	@date		2013-11
	@copyright	GNU Public License.
	
	@brief		This is a windows thread class, and it can be inherited by 
				other class which needs multi-thread fucntion. 

	@pre		Windows_API
	@bug		Currently no bug found yet

	@section Revise_Log

	13/11/20	Add the close thread function in.	\n
	13/12/22	Modify the close thread function and add comment.	\n

****************************************************************************/

#ifndef CHUTHREAD_H
#define CHUTHREAD_H

#include <iostream>
#include <vector>
#include "windows.h"
#include "process.h"

namespace chuThreadNamespace
{
	using namespace std;

	template<class  T1, class T2>		// T1 is for local variable
	class ChuThread						// T2 is for glaobal variable
	{

	public:
		ChuThread();		
		void startThread();										/// Create a new thread to run the thread funciton
		virtual void thread();									/// This function need to be override by inheriting class

		void setLocalVariable(T1 arg){localVariable = arg;};	/// Set local variable in template T1
		const T1 getLocalVariable(){return localVariable;}		/// Get local variable in template T1
		
		void setShareVariable(T2 arg);							/// Set global variable in template T2
		const T2 getShareVariable();							/// Get local variable in template T2

		void setInterruptFlag(){interruptFlag = 1;};			/// Let thread can be interrup by other threads

		bool stopThread();										/// Stop and close the new thread running the thread funciton

	private:

		static void openThread(void* o);

		/*	Thread Synchronize Control */
		static HANDLE ghMutex;
		static int interruptFlag;

		/*	Shared Variable & Static Variable	*/
		static T2 shareVariable;					//share variable in template T1
		T1 localVariable;							//local variable in template T2
		
	protected:

		/*	The Local Handler and All Global Handelr	*/
		HANDLE localhostHANDLE;						// save the handler for new thread
		//static vector<HANDLE> threadHANDLE;		// using for future multi-thread in one class
	};

}	// chuThreadNamespace


/*	The Template Function Definition	*/ 
namespace chuThreadNamespace
{
	using namespace std;

	template<class  T1, class T2>
	HANDLE ChuThread<T1, T2>::ghMutex = CreateMutex( NULL, FALSE, NULL);	// initialize mutex
	
	template<class  T1, class T2>
	int ChuThread<T1, T2>::interruptFlag = 0;	// initialize interruput flag

	template<class  T1, class T2>
	T2 ChuThread<T1, T2>::shareVariable;		// declare shareTempl1

	//template<class  T1, class T2>
	//vector<HANDLE> ChuThread<T1, T2>::threadHANDLE;

	/**
	* Function Name:	Constructor
	* Function Purpose:	Do noting
	*/
	template<class  T1, class T2>			
	ChuThread<T1, T2>::ChuThread()
	{
	}

	/**
	* Function Name:	startThread
	* Function Purpose:	Create an other thread to execute openThread function by WIN_API
	*/
	template<class  T1, class T2>
	void ChuThread<T1, T2>::startThread()	//argTempl1
	{
		DWORD dwThreadId;
		HANDLE createThreadHandel;
		createThreadHandel = (HANDLE)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&ChuThread<T1, T2>::openThread, (void*)this, 0, &dwThreadId);
		localhostHANDLE = createThreadHandel;
		//threadHANDLE.push_back(createThreadHandel);
	}

	/**
	* Function Name:	setShareVariable
	* Function Purpose:	Set the global variabel to a static class variable for all thread access
	*/
	template<class  T1, class T2>
	void ChuThread<T1, T2>::setShareVariable(T2 arg)
	{
		shareVariable = arg;
	}

	/**
	* Function Name:	getShareVariable
	* Function Purpose:	Get the static global variabel and return
	*/
	template<class  T1, class T2>
	const T2 ChuThread<T1, T2>::getShareVariable()
	{
		return shareVariable;
	}

	/**
	* Function Name:	openThread
	* Function Purpose:	Using this function to execute the content of thread fucntion overrided by user 
	*/
	template<class  T1, class T2>
	void ChuThread<T1, T2>::openThread(void* ptrOfCallingObject)
	{
		ChuThread<T1, T2> *callingObject = static_cast<ChuThread<T1, T2>*>(ptrOfCallingObject);

		/*	Check Can Interrupt Or Not	*/
		if(interruptFlag==0){WaitForSingleObject(ghMutex, INFINITE);}

		callingObject->thread();

		if(interruptFlag==0){ReleaseMutex(ghMutex);}	// check interrupt

		_endthread();
	}

	/**
	* Function Name:	thread
	* Function Purpose:	The fucntion will be overrided by thread and run in multi-thread 
	*/
	template<class  T1, class T2>
	void ChuThread<T1, T2>::thread()
	{
		// you can use your arguement directly in there
		cout << "You need to override ChuThread::thread to do your things " << endl;
	}

	/**
	* Function Name:	stopThread
	* Function Purpose:	Stop the created thread using the WIN_API and handler
	*/
	template<class  T1, class T2>
	bool ChuThread<T1, T2>::stopThread()	//argTempl1
	{
		bool retVal;
		if(TerminateThread(localhostHANDLE, 0))
			if(CloseHandle(localhostHANDLE))
				retVal = true;
			else
				retVal = false;
		else
			retVal = false;

		if(retVal==true)
			cout << "The create thread already been close" << endl;
		return retVal;
	}
}




#endif //CHUTHREAD_H
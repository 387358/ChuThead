


#include <iostream>

#include "ChuThread.h"

namespace chuThreadNamespace
{
	using namespace std;

	template<class  T1, class T2>
	HANDLE ChuThread<T1, T2>::ghMutex = CreateMutex( NULL, FALSE, NULL);	// initialize mutex
	
	template<class  T1, class T2>
	int ChuThread<T1, T2>::interruptFlag = 0;	// initialize interruput flag

	template<class  T1, class T2>
	double ChuThread<T1, T2>::shareVariable;	//shareTempl1

	template<class  T1, class T2>
	ChuThread<T1, T2>::ChuThread()
	{
	}

	template<class  T1, class T2>
	void ChuThread<T1, T2>::startThread()	//argTempl1
	{
		_beginthread(&ChuThread<T1, T2>::openThread, 0, (void*)this);
	}

	template<class  T1, class T2>
	void ChuThread<T1, T2>::setShareVariable(T2 arg)
	{
		shareVariable = arg;
	}

	template<class  T1, class T2>
	const T2 ChuThread<T1, T2>::getShareVariable()
	{
		return shareVariable;
	}


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

	template<class  T1, class T2>
	void ChuThread<T1, T2>::thread()
	{
		// you can use your arguement directly in there
		cout << "You need to override ChuThread::thread to do your things " << endl;
	}

}	//chuThreadNamespace
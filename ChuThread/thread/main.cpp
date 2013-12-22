

//<template class T1, class T2>

#include "ChuThread.h"

struct Sturct
{
	int intData;
	double doubleData;
};


using namespace chuThreadNamespace;

class MyThread : public ChuThread<Sturct, Sturct>
{
	virtual void thread();
};

void MyThread::thread()
{
	while(1)
	{
		//cout << "the int LocalVariable: " << getLocalVariable().intData << endl;
		//cout << "the double LocalVariable: " << getLocalVariable().doubleData << endl;
		cout << "the int ShareVariable: " << getShareVariable().intData << endl;
		//cout << "the double ShareVariable: " << getShareVariable().doubleData << endl;
		cout << endl;
		Sleep(1000);
	}
}


int main()
{
	int i(0);
	MyThread t1,t2,t3;

	Sturct s;
/*
	s.intData = 1;
	s.doubleData = 1.1;
	t1.setLocalVariable(s);

	s.intData = 2;
	s.doubleData = 2.2;
	t2.setLocalVariable(s);

	s.intData = 3;
	s.doubleData = 3.3;
	t3.setLocalVariable(s);

	t1.setShareVariable(s);
	t2.setShareVariable(s);
	t3.setShareVariable(s);

	t1.startThread();
	t2.startThread();
	t3.startThread();
*/

	t1.startThread();
	for(int k(0); k<5; k++)
	{
		i++;
		s.intData = i;
		t1.setShareVariable(s);
		Sleep(1000);
	}

	t1.stopThread();

	Sleep(5000);

	return 0;
}

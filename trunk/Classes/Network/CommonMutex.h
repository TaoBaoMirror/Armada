#ifndef KOMUTEX_H_2015_09_18
#define KOMUTEX_H_2015_09_18

#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#include <winsock2.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class CommonMutex
{
public:
	CommonMutex()
	{
		InitializeCriticalSection(&cs);
	}
	~CommonMutex()
	{
		DeleteCriticalSection(&cs);
	}

	void lock()
	{
		EnterCriticalSection(&cs);

		
	}

	void unlock()
	{
		LeaveCriticalSection(&cs);
	}

private:
	CRITICAL_SECTION cs;
};




#else // defined(__linux__) || defined(__linux)
#include <pthread.h>

//锁被多次释放会怎么样，如何处理
//答：经测试，unlock过多，没有什么影响。

class CommonMutex
{
public:
	CommonMutex()
	{
		pthread_mutex_init(&mutex, NULL);
	}
	~CommonMutex()
	{
		pthread_mutex_destroy(&mutex);
	}

	void lock()
	{
		pthread_mutex_lock(&mutex);
	}

	void unlock()
	{
		pthread_mutex_unlock(&mutex);
	}
	pthread_mutex_t* getmutex()
	{
		return &mutex;
	}

public:
	pthread_mutex_t mutex;
};



#endif


#endif
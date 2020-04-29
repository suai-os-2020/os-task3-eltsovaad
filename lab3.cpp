#include "lab3.h"
#include <windows.h> 
#include <iostream>

#define MAX_SEM_COUNT 1
#define THREADCOUNT 11

HANDLE ghSemaphore[11];
HANDLE aThread[THREADCOUNT];
HANDLE ghMutex;


const char threadName[11] = { 'a','b','c','d','e','f','g','h','i','k','m' };

void PrintAndCompute(int threadName, bool isSynchronized, int nextThread);
HANDLE createMyThread(DWORD& ThreadID, DWORD WINAPI ThreadProc(LPVOID));

DWORD WINAPI thread_a(LPVOID);
DWORD WINAPI thread_b(LPVOID);
DWORD WINAPI thread_c(LPVOID);
DWORD WINAPI thread_d(LPVOID);
DWORD WINAPI thread_e(LPVOID);
DWORD WINAPI thread_f(LPVOID);
DWORD WINAPI thread_g(LPVOID);
DWORD WINAPI thread_h(LPVOID);
DWORD WINAPI thread_i(LPVOID);
DWORD WINAPI thread_k(LPVOID);
DWORD WINAPI thread_m(LPVOID);

//
// lab3 code should be located here!
//

//using namespace std;

unsigned int lab3_thread_graph_id()
{
	return 10;
}

const char* lab3_unsynchronized_threads()
{
	return "dghi";
}

const char* lab3_sequential_threads()
{
	return "bcde";


}


int lab3_init()
{
	
	DWORD ThreadID;
	int i;
	ghMutex = CreateMutex(NULL,	FALSE, 	NULL); 
	if (ghMutex == NULL)
	{
		std::cout << "CreateMutex error: "<< GetLastError()<<std::endl;
		return 1;
	}
	// Create a semaphore with initial and max counts of MAX_SEM_COUNT
	// Создание семафора с начальным и максимальным значениями счетчика равными MAX_SEM_COUNT

	for (i = 0; i < THREADCOUNT; i++)
	{
		ghSemaphore[i] = CreateSemaphore(
			NULL,           // default security attributes // аттрибуты безопасности по умолчанию
			0,  // initial count               // начальное значение счетчика
			MAX_SEM_COUNT,  // maximum count               // максимаьлное значение счетчика
			NULL);          // unnamed semaphore           // безымянный семафор
		if (ghSemaphore[i] == NULL)
		{
			std::cout << "CreateSemaphore error: " << GetLastError() << std::endl;
			return 1;
		}
	}
	
	if (!ReleaseSemaphore(
		ghSemaphore[0],  // handle to semaphore              // дескриптор семафора
		1,            // increase count by one            // увеличиваем значение счетчика на единицу
		NULL))       // not interested in previous count // игнорируем предыдущее значение счетчика
	{
		std::cout << "ReleaseSemaphore " << threadName[i] << " error: " << GetLastError() << std::endl;
	}
	

	// Create worker threads
	// Создаем потоки

	aThread[0] = createMyThread(ThreadID, thread_a); 
	aThread[1] = createMyThread(ThreadID, thread_b);
	aThread[2] = createMyThread(ThreadID, thread_c);
	aThread[3] = createMyThread(ThreadID, thread_d);
	aThread[4] = createMyThread(ThreadID, thread_e);
	aThread[5] = createMyThread(ThreadID, thread_f);
	aThread[6] = createMyThread(ThreadID, thread_g);
	aThread[7] = createMyThread(ThreadID, thread_h);
	aThread[8] = createMyThread(ThreadID, thread_i);
	aThread[9] = createMyThread(ThreadID, thread_k);
	aThread[10] = createMyThread(ThreadID, thread_m);

	/*for (i = 0; i < THREADCOUNT; i++)
	{
		if (aThread[i] = NULL) {
			std::cout << "CreateThread " << threadName[i] << " error: " << GetLastError() << std::endl;
			return 1;
		}
	}*/


	// Wait for all threads to terminate
	// Ждем завершения всех потоков

	/*WaitForSingleObject(aThread[6], INFINITE);
	WaitForSingleObject(aThread[7], INFINITE);
	WaitForSingleObject(aThread[3], INFINITE);
	WaitForSingleObject(aThread[8], INFINITE);*/
	WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);

	// Close thread and semaphore handles
	// Закрываем потоки и дескриптор семафора

	//for (i = 0; i < THREADCOUNT; i++)
		CloseHandle(aThread[0]);
	for (i = 0; i < THREADCOUNT; i++)
		CloseHandle(ghSemaphore[i]);
	//system("pause");
	return 0;
}

void PrintAndCompute(int threadNumber, bool isSynchronized, int nextThread)
{
	DWORD dwWaitResult, mutexWaitResult;

	if (!isSynchronized) {
		dwWaitResult = WaitForSingleObject(ghSemaphore[threadNumber], INFINITE);    
		// zero-second time-out interval // нулевое время ожидания
	}
	for (int i = 0; i < 3; i++) {
		if (isSynchronized) {
			dwWaitResult = WaitForSingleObject(ghSemaphore[threadNumber], INFINITE);           // zero-second time-out interval // нулевое время ожидания
		}
		if (dwWaitResult == WAIT_OBJECT_0) {
			mutexWaitResult = WaitForSingleObject(ghMutex, INFINITE);
			if (mutexWaitResult == WAIT_OBJECT_0) {
				std::cout << threadName[threadNumber];
				ReleaseMutex(ghMutex);
				computation();
				if ((nextThread != -1) && (isSynchronized)) {
					if (!ReleaseSemaphore(ghSemaphore[nextThread], 1, NULL)) {
						std::cout << "ReleaseSemaphore error: " << GetLastError() << std::endl;
					}
				}
			}
		}
	}
	if ((nextThread != -1) && (!isSynchronized)) {
		if (!ReleaseSemaphore(ghSemaphore[nextThread], 1, NULL))
		{
			std::cout << "ReleaseSemaphore " << threadName[nextThread] << " error: " << GetLastError() << std::endl;
		}
	}


}

HANDLE createMyThread(DWORD& ThreadID, DWORD WINAPI ThreadProc(LPVOID)) {
	HANDLE ret = CreateThread(NULL, 0, ThreadProc,NULL, 0, &ThreadID);

	if (ret == NULL)
	{
		std::cout << "CreateThread error: " << GetLastError() << std::endl;
		return NULL;
	}
	return ret;
}

DWORD WINAPI thread_a(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	PrintAndCompute(0, false, 2);
	return TRUE;
}
DWORD WINAPI thread_b(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	PrintAndCompute(1, true, 2);
	return TRUE;
}
DWORD WINAPI thread_c(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	//WaitForSingleObject(aThread[0], INFINITE);
	PrintAndCompute(2, false, 3);
	PrintAndCompute(2, true, 3);
	return TRUE;
}
DWORD WINAPI thread_d(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	//WaitForSingleObject(aThread[2], INFINITE);
	PrintAndCompute(3, false, 4);
	PrintAndCompute(3, true, 4);
	PrintAndCompute(3, false, 3);
	WaitForSingleObject(aThread[4], INFINITE);
	WaitForSingleObject(aThread[5], INFINITE);
	PrintAndCompute(3, false, 9);
	return TRUE;
}
DWORD WINAPI thread_e(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	//WaitForSingleObject(aThread[3], INFINITE);
	PrintAndCompute(4, false, 1);
	PrintAndCompute(4, true, 1);
	if (!ReleaseSemaphore(ghSemaphore[3], 1, NULL))
	{
		std::cout << "ReleaseSemaphore " << threadName[3] << " error: " << GetLastError() << std::endl;
	}
	if (!ReleaseSemaphore(ghSemaphore[4], 1, NULL))
	{
		std::cout << "ReleaseSemaphore " << threadName[4] << " error: " << GetLastError() << std::endl;
	}
	if (!ReleaseSemaphore(ghSemaphore[5], 1, NULL))
	{
		std::cout << "ReleaseSemaphore " << threadName[5] << " error: " << GetLastError() << std::endl;
	}
	if (!ReleaseSemaphore(ghSemaphore[6], 1, NULL))
	{
		std::cout << "ReleaseSemaphore " << threadName[6] << " error: " << GetLastError() << std::endl;
	}
	PrintAndCompute(4, false, 6);
	return TRUE;
}
DWORD WINAPI thread_f(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	PrintAndCompute(5, false, 7);
	return TRUE;
}
DWORD WINAPI thread_g(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	PrintAndCompute(6, false, 8);
	WaitForSingleObject(aThread[5], INFINITE);
	PrintAndCompute(6, false, -1);
	return TRUE;
}
DWORD WINAPI thread_h(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	WaitForSingleObject(aThread[4], INFINITE);
	PrintAndCompute(7, false, 8);
	
	return TRUE;
}
DWORD WINAPI thread_i(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	WaitForSingleObject(aThread[5], INFINITE);
	WaitForSingleObject(aThread[4], INFINITE);
	PrintAndCompute(8, false, -1);
	WaitForSingleObject(aThread[3], INFINITE);
	WaitForSingleObject(aThread[7], INFINITE);
	PrintAndCompute(8, false, 10);
	return TRUE;
}
DWORD WINAPI thread_k(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	WaitForSingleObject(aThread[6], INFINITE);
	WaitForSingleObject(aThread[7], INFINITE);
	PrintAndCompute(9, false, -1);
	return TRUE;
}
DWORD WINAPI thread_m(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	WaitForSingleObject(aThread[8], INFINITE);
	WaitForSingleObject(aThread[9], INFINITE);
	PrintAndCompute(10, false, -1);
	return TRUE;
}
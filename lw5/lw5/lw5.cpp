#include <windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstdlib>

CRITICAL_SECTION CriticalSection;

using namespace std;

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
    EnterCriticalSection(&CriticalSection);
    for (auto i = 0; i < 100000; i++)
    {
        int j = *(int*)lpParam;
        *(int*)lpParam = j + 1;
    }
    LeaveCriticalSection(&CriticalSection);

    //cout << *(int*)lpParam << endl;
    ExitThread(0); // функция устанавливает код завершения потока в 0
}

int main(int argc, char* argv[])
{
   
    int numThread = 2;

    int WorkingVariable = 0;

    // создание потоков
    HANDLE* handles = new HANDLE[numThread];
    for (auto i = 0; i < numThread; i++)
    {
        handles[i] = CreateThread(NULL, 0, &ThreadProc, &WorkingVariable, CREATE_SUSPENDED, NULL);
        SetThreadAffinityMask(handles[i], 2);
    }

    if (!InitializeCriticalSectionAndSpinCount(&CriticalSection,
        0x00000400))
        return 1;

    // запуск  потоков   
    for (auto i = 0; i < numThread; i++)
    {
        ResumeThread(handles[i]);
    }

    // ожидание окончания работы  потоков
    WaitForMultipleObjects(numThread, handles, true, INFINITE);

    DeleteCriticalSection(&CriticalSection);
    cout << WorkingVariable;
    
    return 0;
}


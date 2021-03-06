﻿#include <windows.h>
#include <iostream>
#include <vector>

using namespace std;

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
    cout << "Thread number" << *(int*)lpParam << endl;

    ExitThread(0); // функция устанавливает код завершения потока в 0
}

int main(int argc, char* argv[])
{
    int numThread = 0;
    
    if (argc != 0) {
        numThread = atoi(argv[1]);
        vector<int> param(numThread);
   
        // создание потоков
        HANDLE* handles = new HANDLE[numThread];
        for (auto i = 0; i < numThread; i++)
        {

            param[i] = i + 1;
            handles[i] = CreateThread(NULL, 0, &ThreadProc, &param[i], CREATE_SUSPENDED, NULL);
        }

        // запуск  потоков   
        for (auto i = 0; i < numThread; i++)
        {
            ResumeThread(handles[i]);
        }

        // ожидание окончания работы  потоков
        WaitForMultipleObjects(numThread, handles, true, INFINITE);
    }
    return 0;
}


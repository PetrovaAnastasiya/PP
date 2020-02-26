#include <windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <ctime> 


using namespace std;
clock_t start = clock();

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{

    string OUTPUT_FILE_FIRST = "output" + to_string(*(int*)lpParam) + ".txt";
    ofstream fout(OUTPUT_FILE_FIRST);
    //cout << "Thread number" << *(int*)lpParam << endl;
    for (auto i = 0; i < 100000; i++)
    {
        clock_t end = clock();
        fout << difftime(end, start) << endl;
    }
    ExitThread(0); // функция устанавливает код завершения потока в 0
    fout.close();
}

int main(int argc, char* argv[])
{
    char x;
    cin>>x;
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


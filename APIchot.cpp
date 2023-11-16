#include <bits/stdc++.h>

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <iomanip>
#include <math.h>
using namespace std;
//Ham huy tien trình
void TerminateProcessById(DWORD processId) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processId);
    if (hProcess != NULL) {
        BOOL terminateSuccess = TerminateProcess(hProcess, 1);

        if (terminateSuccess) {
            cout << "The process was terminated successfully!" << endl;
        }
        else {
            cout << "Unfortunately, cannot terminate the process!" << endl;
        }

        CloseHandle(hProcess);
    }	
    else {
        cout << "The process could not be found!" << endl;
    }
}


void DisplayProcessTime(HANDLE hProcess) {
    FILETIME creationTime, exitTime, kernelTime, userTime;
    if (GetProcessTimes(hProcess, &creationTime, &exitTime, &kernelTime, &userTime)) {
        ULARGE_INTEGER kernelTimeValue;
        kernelTimeValue.LowPart = kernelTime.dwLowDateTime;
        kernelTimeValue.HighPart = kernelTime.dwHighDateTime;

        ULARGE_INTEGER userTimeValue;
        userTimeValue.LowPart = userTime.dwLowDateTime;
        userTimeValue.HighPart = userTime.dwHighDateTime;

        double kernelDuration = kernelTimeValue.QuadPart * 0.0000001;
        double userDuration = userTimeValue.QuadPart * 0.0000001;

        cout << left << setw(7) << "" << fixed << setprecision(3) << round(kernelDuration * 3) / 3;
        int x = floor(round(kernelDuration * 3) / 3);
        if (x < 10) cout << "       |";
        else if (x >= 10 && x < 100)  cout << "      |";
        else if (x >= 100 && x < 1000) cout << "     |";
        else cout << "    |";

        int y = floor(round(userDuration * 3) / 3);
        if (y < 10) cout << left << "      " << fixed << setprecision(3) << round(userDuration * 3) / 3 << "      |";
        else if (y >= 10 && y < 100)  cout << left << "      " << fixed << setprecision(3) << round(userDuration * 3) / 3 << "     |";
        else if (y >= 100 && y < 1000) cout << left << "      " << fixed << setprecision(3) << round(userDuration * 3) / 3 << "    |";
        else cout << left << "      " << fixed << setprecision(3) << round(userDuration * 3) / 3 << "   |";
    }
}

void ShowProcessList() {
    int i = 0;
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &processEntry) || hProcessSnap == INVALID_HANDLE_VALUE) {
        cerr << "The information for the process is not available!" << endl;
        CloseHandle(hProcessSnap);
        return;
    }

    cout << left << setw(12) << "|    ID" << left << setw(16) << "|  Thread Count" << left << setw(20) << "|    Kernel Time  " << left << setw(18) << "|    User Time  " << left << setw(30) << "| Process Name                    |" << endl;
    cout << "|---------------------------------------------------------------------------------------------------|" << endl;

    do {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processEntry.th32ProcessID);
        if (hProcess != NULL) {

            cout << left << "   " << setw(9) << processEntry.th32ProcessID;
            if (processEntry.cntThreads >= 10)    cout << left << "|       " << processEntry.cntThreads << "      |";
            else     cout << left << "|       " << processEntry.cntThreads << "       |";

            DisplayProcessTime(hProcess);
            cout << left << setw(2) << "" << processEntry.szExeFile << endl;
            cout << "|---------------------------------------------------------------------------------------------------|" << endl;

            CloseHandle(hProcess);
            i++;
        }
    } while (Process32Next(hProcessSnap, &processEntry));
    cout << "=> Total processes: " << i << " processes" << endl;
    CloseHandle(hProcessSnap);
}

DWORD WINAPI CreateProcessThread(LPVOID lpParam) {
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInfo;
    ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
    startupInfo.cb = sizeof(STARTUPINFO);

    BOOL createProcessSuccess = CreateProcess(
        "C:\\Windows\\System32\\notepad.exe",
        NULL,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &startupInfo,
        &processInfo);

    DWORD newProcessId;
    if (createProcessSuccess) {
        cout << "The process was created successfully!" << endl;
        newProcessId = processInfo.dwProcessId;
    }
    else {
        cout << "Create the process failed!" << endl;
    }

    DWORD processId = GetCurrentProcessId();

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if (hProcess == NULL) {
        cout << "Failed to open process\n";
        return 1;
    }

    DisplayProcessTime(hProcess);

    CloseHandle(hProcess);

    cout << "Current Process ID: " << processId << endl;
    cout << "New Process ID: " << newProcessId << endl;
    cout << "Thread ID: " << processInfo.dwThreadId << endl;

    WaitForSingleObject(processInfo.hProcess, INFINITE);
}

int main() {
    int choice = 0;
    do {
        cout << "OPTIONS:\n";
        cout << "  1. Terminate           " << setw(17) << "2. Display" << endl;
        cout << "  3. Create              " << setw(14) << "4. Exit" << endl;
        cout << "->Enter selection: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "You are terminating the process..." << endl;
                int processIdToTerminate;
                cout << "Enter Process ID: ";
                cin >> processIdToTerminate;
                TerminateProcessById(processIdToTerminate);
                break;
            }
            case 2:
                cout << "Process List:" << endl;
                ShowProcessList();
                break;
            case 3: {
                HANDLE hThread = CreateThread(NULL, 0, CreateProcessThread, NULL, 0, NULL);
                if (hThread == NULL) {
                    std::cout << "Failed to create thread." << std::endl;
                    return 1;
                }
                WaitForSingleObject(hThread, INFINITE);

                CloseHandle(hThread);
                break;
            }
            case 4:
                cout << "Exiting the program!" << endl;
                break;
            default:
                cout << "Invalid choice, please enter again!" << endl;
                break;
        }
    } while (choice != 4);
    return 0;
}


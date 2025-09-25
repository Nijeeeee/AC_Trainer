#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>

// Function to get process ID by name
DWORD GetProcessIdByName(const std::wstring& processName) {
    DWORD processId = 0;
    PROCESSENTRY32W entry;
    entry.dwSize = sizeof(PROCESSENTRY32W);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Process32FirstW(snapshot, &entry)) {
        do {
            if (processName == entry.szExeFile) {
                processId = entry.th32ProcessID;
                break;
            }
        } while (Process32NextW(snapshot, &entry));
    }

    CloseHandle(snapshot); // Always close the handle
    return processId;      // Always return a value
}
int main() {
    DWORD pid = GetProcessIdByName(L"ac_client.exe");
    if (!pid) {
        std::cout << "AC Not Running !!" << std::endl;
        return 1;
    }
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    if (!hProcess) {
        std::cout << "Failed to open process" << std::endl;
        return 1;
    }
}
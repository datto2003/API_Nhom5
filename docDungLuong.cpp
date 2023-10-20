#include <iostream>
#include <windows.h>
using namespace std;
int main() {
    ULARGE_INTEGER freeBytesAvailable;
    ULARGE_INTEGER totalNumberOfBytes;
    ULARGE_INTEGER totalNumberOfFreeBytes;

    // Duong dan o dia can kiem tra
    LPCWSTR drivePath = L"C:\\";

    if (GetDiskFreeSpaceExW(drivePath, &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
        // Dung luong o dia trong
        double freeGB = static_cast<double>(freeBytesAvailable.QuadPart) / (1024 * 1024 * 1024);

        // Tong dung luong o
        double totalGB = static_cast<double>(totalNumberOfBytes.QuadPart) / (1024 * 1024 * 1024);

        wcout << L"Dung luong trong: " << freeGB << L" GB" << endl;
        wcout << L"Tong dung luong: " << totalGB << L" GB" << endl;
    } else {
        wcerr << "Khong the lay thong tin" << endl;
    }

    return 0;
}


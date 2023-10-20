#include <iostream>
#include <windows.h>
using namespace std;
int main() {
    const char* filePath = "docGhiDuLieu.txt";
    char buffer[1024]; // Khai bao mang char de luu tru noi dung doc duoc tu tep

    // Su dung ham CreateFile de  mo tep de doc
    HANDLE file = CreateFile(filePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (file == INVALID_HANDLE_VALUE) {
        cerr << "Loi khong the mo tep." << endl;
        return 1;
    }

    // Doc du lieu tu tep
    DWORD bytesRead;
    if (ReadFile(file, buffer, sizeof(buffer), &bytesRead, NULL)) {
        // In ra noi dung doc duoc
        cout << "Noi dung doc duoc: " << buffer << endl;
    } else {
        cerr << "Loi doc file." << endl;
    }

    // Dong tep
    CloseHandle(file);

    return 0;
}


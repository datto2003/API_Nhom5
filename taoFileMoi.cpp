#include<iostream>
#include <windows.h>
using namespace std;
int main() {
	wstring tenFile;
	wcout<<L"Nhap ten file: "; wcin>>tenFile;
    wstring fileName = L"C:\\TestTaoFile\\"; 
    wstring fullPath = fileName + tenFile;
    LPCWSTR total = fullPath.c_str();
    HANDLE handleFile;

    handleFile = CreateFileW(
        total,               // T�n tep moi
        GENERIC_WRITE,          // Quyen truy cap
        0,                      // Kh�ng chia se voi ung dung khac
        NULL,                   // Kh�ng c� bao mat tuy chon
        CREATE_NEW,             // Tao tep moi; CREATE_ALWAYS de ghi de neu tep da ton tai
        FILE_ATTRIBUTE_NORMAL,   // Thuoc tinh cua tep
        NULL                    // Kh�ng can xac dinh thong so mo rong
    );

    if (handleFile == INVALID_HANDLE_VALUE) {
        wcout<<"Tao that bai"<<endl;
        return 1;
    }
	else
	{
		wcout<<"Tao thanh cong"<<endl;
		 // �ong tep
		CloseHandle(handleFile);
	}

    return 0;
}


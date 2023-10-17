#include <stdio.h>
#include <windows.h>

DWORD WINAPI thread_function(LPVOID lpParameter) {
printf("Hello depuis le thread!\n");
return 0;
}

int main() {
    HANDLE thread_handle;
    thread_handle = CreateThread(NULL, 0, thread_function, NULL, 0, NULL);
    WaitForSingleObject(thread_handle, INFINITE);
    return 0;
}
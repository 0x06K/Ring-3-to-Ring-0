#include <windows.h>
#include <stdio.h>

int main(void)
{
    HANDLE hThread = GetCurrentThread();
    int priority = GetThreadPriority(hThread);

    if (priority == THREAD_PRIORITY_ERROR_RETURN) {
        printf("GetThreadPriority failed\n");
    } else {
        printf("Thread priority: %d\n", priority);
    }

    return 0;
}

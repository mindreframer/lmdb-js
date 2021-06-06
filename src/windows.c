#ifdef _WIN32
#include <windows.h>

static int initializeMemoryPriority = 1;
static MEMORY_PRIORITY_INFORMATION lowMemPriority;
static MEMORY_PRIORITY_INFORMATION normalMemPriority;
int lowerMemoryPriority(int priority) {
    if (initializeMemoryPriority) {
        GetThreadInformation(GetCurrentThread(), ThreadMemoryPriority, &normalMemPriority, sizeof(normalMemPriority));
//      fprintf(stderr, "initialized memory %u setting to %u\n", normalMemPriority.MemoryPriority, priority);
        ZeroMemory(&lowMemPriority, sizeof(lowMemPriority));
        lowMemPriority.MemoryPriority = priority;
        initializeMemoryPriority = 0;
    }
    SetProcessInformation(GetCurrentProcess(), ProcessMemoryPriority, &lowMemPriority, sizeof(lowMemPriority));
    return SetThreadInformation(GetCurrentThread(), ThreadMemoryPriority, &lowMemPriority, sizeof(lowMemPriority));
}
int restoreMemoryPriority() {
    return 0;
    //return SetThreadInformation(GetCurrentThread(), ThreadMemoryPriority, &normalMemPriority, sizeof(normalMemPriority));
}
#endif
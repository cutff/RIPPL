#include "exploit.h"

BOOL g_bVerbose = false;
BOOL g_bDebug = false;
BOOL g_bForce = false;
DWORD g_dwProcessId = 0;
LPWSTR g_pwszExecutionMode = nullptr;
LPWSTR g_pwszDumpFilePath = nullptr;
LPWSTR g_pwszProcessName = nullptr;
int g_intExecutionMode = -1;

int wmain(int argc, wchar_t* argv[])
{
    if (!ParseArguments(argc, argv))
        return 1;

    PRINTARGUMENTS();

    if (g_pwszProcessName != NULL)
    {
        DWORD dwProcessId = 0;

        if (ProcessGetPIDFromName(g_pwszProcessName, &dwProcessId))
        {
            PRINTVERBOSE(L"[*] Found a process with name '%ws' and PID %d\n", g_pwszProcessName, dwProcessId);

            return RunExploit(dwProcessId);
        }
    }
    else if (g_dwProcessId != 0)
    {
        RunExploit(g_dwProcessId);
    }

    return 0;
}

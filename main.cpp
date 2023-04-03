// 212 Клипалко Михаил Михайлович
// ClusterAnalyses

#include "headers.h"
#include "interface.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

STRICT_MODE_ON

int main()
{
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    Interface interface;

    std::cout << "Start! Enter HELP to see the list of available commands\n";

    while (interface.Starts());
    _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG );
    _CrtDumpMemoryLeaks();
}

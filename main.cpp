// 212 Клипалко Михаил Михайлович
// ClusterAnalyses

#include "headers.h"
#include "interface.h"

STRICT_MODE_ON

int main()
{
    Interface interface;

    std::cout << "Start! Enter HELP to see the list of available commands\n";

    while (interface.Starts());
}

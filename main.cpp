// 212 �������� ������ ����������
// Clouds, K-means, Wave, DBscan, Spanning tree

#include "headers.h"
#include "interface.h"

int main()
{
    // ������� ���������
    Interface s;

    std::cout << "Start! Enter HELP to see the list of available commands\n";

    s.logfile_interface.open("logfile_interface.txt");
    while (s.Starts());
    s.logfile_interface.close();
}

#ifndef SAVE_BD
#define SAVE_BD
#include "field.h"
#include "config.h"

class DataBase
{
    private:
        Loader loader;
        Saver saver;
    public:
        int SizeOfLineFieldFile;
        int SizeOfLineFindFile;
        int SizeOfLineClusterFile;
};

#endif
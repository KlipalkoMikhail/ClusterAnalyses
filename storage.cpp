#include "cluster.h"
#include "headers.h"
#include "storage.h"

Storage::Storage(){}

void Storage::resize(int n)
{
    clusters.resize(n);
}

Storage::~Storage(){}
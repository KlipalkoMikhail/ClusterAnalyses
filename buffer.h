#ifndef BUFFER_H
#define BUFFER_H
#include "headers.h"
#include "cloud.h"
#include "field.h"
using namespace std;

class Buffer
{
    private:
        bool state;
    public:
        Buffer();
        Cloud cloud;
        void copy(Cloud &cld);
        void past(Field &field);
        void shift(Cloud &cld, double stepx, double stepy);
        void rotate(Cloud &cld, double degrees);
        void print();
        ~Buffer();
};

#endif
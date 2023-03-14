#pragma once              
#include <cstring>        

enum ErrorCode           
{
   EC_RANGE = -3,
   EC_MEMORY = -2,
   EC_UNKNOWN = -1,
   EC_OK = 0
};

class MyException
{
   string message;
   ErrorCode  code;
 public:
   MyException(ErrorCode c, string msg) {
      code = c;
      message = msg;
   }
   MyException(string msg)
   {
      message = msg;
   }
   string getMessage() const { return message; }
   ErrorCode   getCode() const { return code; }
};

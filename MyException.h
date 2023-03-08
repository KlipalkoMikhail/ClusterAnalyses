//  файл MyException.h

#pragma once              // для однократного включения этого файла
#include <cstring>        // для функций формирования С-строк

enum ErrorCode            // список условных кодов отказов
{
   EC_RANGE = -3,
   EC_MEMORY = -2,
   EC_UNKNOWN = -1,
   EC_OK = 0
};

class MyException
{
   char message[256];
   ErrorCode  code;
 public:
   MyException(ErrorCode c, const char *msg) {
      code = c;
      strncpy(message, msg, 255);
   }
   const char * Message() const { return message; }
   ErrorCode   Code() const { return code; }
};

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/dart_api.h"
#include "include/dart_native_api.h"

int calcSum(int x, int y) 
{
  return x+y;
}

//
// https://www.dartlang.org/articles/dart-vm/native-extensions
//
Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool *auto_setup_scope);

DART_EXPORT Dart_Handle hello_Init(Dart_Handle parent_library)
{
  printf(">> called hello_init\n");
  if (Dart_IsError(parent_library))
  {
    printf(">>>> error in parent_library\n");
    return parent_library;
  }

  Dart_Handle result_code = Dart_SetNativeResolver(parent_library, ResolveName, NULL);
  if (Dart_IsError(result_code))
  {
    printf(">>>> error in result code\n");
    return result_code;
  }

  return Dart_Null();
}

void sum(Dart_NativeArguments arguments)
{
  printf(">> called sum\n");
  Dart_EnterScope();
  Dart_Handle arg1 = Dart_GetNativeArgument(arguments, 0);
  Dart_Handle arg2 = Dart_GetNativeArgument(arguments, 1);

  int64_t x;
  int64_t y;
  if (Dart_IsError(Dart_IntegerToInt64(arg1, &x)))
  {
    Dart_ThrowException(Dart_NewStringFromCString("error at x\n"));
  }
  if (Dart_IsError(Dart_IntegerToInt64(arg2, &y)))
  {
    Dart_ThrowException(Dart_NewStringFromCString("error at y\n"));
  }

  printf(">>>> x=%lld y=%lld\n", x, y);
  Dart_SetReturnValue(arguments, Dart_NewInteger(calcSum(x,y)));
  Dart_ExitScope();
}

Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool *auto_setup_scope)
{
  printf(">> called resolve name\n");
  if (!Dart_IsString(name))
  {
    return NULL;
  }
  if (auto_setup_scope == NULL)
  {
    return NULL;
  }

  Dart_NativeFunction result = NULL;
  Dart_EnterScope();
  const char *cname;
  Dart_StringToCString(name, &cname);

  if (0 == strcmp(cname, "sum"))
  {
    result = sum;
  }

  Dart_ExitScope();
  return result;
}

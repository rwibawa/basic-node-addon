#include <napi.h>

#include "tools/writeFile.h"

Napi::Object InitAll( Napi::Env env, Napi::Object exports ) {
  exports[ "writeFile" ] = Napi::Function::New( env, writeFile );

  return exports;
}

NODE_API_MODULE( NODE_GYP_MODULE_NAME, InitAll )
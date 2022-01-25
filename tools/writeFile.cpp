#include <napi.h>
#include <iostream>
#include <string>
#include <fstream>

#include "writeFile.h"


class WriteFileWorker : public Napi::AsyncWorker {
 public:
  WriteFileWorker( Napi::Function& callback, std::string filename, std::string message ) 
    : Napi::AsyncWorker(callback), filename( filename ), message( message ) {}
  ~WriteFileWorker() {}

  void Execute() { 
    try 
    {
      std::ofstream myfile;
      myfile.open(filename.c_str());
      myfile << message.c_str() << "\n";
      myfile.close();      
    }
    catch( ... ) 
    {
      SetError( "Failed to write to the file!" );
    }
  }

  void OnOK() {
    Napi::HandleScope scope( Env() );
    Callback().Call( GetResult() );
  }

  std::vector< napi_value > GetResult() {
    Napi::Object success = Napi::Object::New( Env() );
    success.Set( "result", "success" );
    success.Set( "filename",  filename.c_str() );
    std::vector<napi_value> result = { Env().Undefined(), success };
    return result;
  }

 private:
  std::string filename;
  std::string message;
};

Napi::Value writeFile( const Napi::CallbackInfo& args )
{
  Napi::Env env = args.Env();
  
  if ( args.Length() < 2 ) {
    Napi::Error::New( env, "Wrong number of arguments, needs: path-dst-file, message, callback-fn()"  )
    .ThrowAsJavaScriptException();
    return env.Undefined();
  }
  else if ( !args[0].IsString() ) {
    Napi::Error::New( env, "First argument must be string destination file path" )
    .ThrowAsJavaScriptException();
    return env.Undefined();
  }
  else if ( !args[1].IsString() ) {
    Napi::Error::New( env, "Second argument must be string message" )
    .ThrowAsJavaScriptException();
    return env.Undefined();
  }
  else if ( !args[2].IsFunction() ) {
    Napi::Error::New( env, "Third argument must be a callback( error, data ) function" )
    .ThrowAsJavaScriptException();
    return env.Undefined();
  }

  std::string filename( args[0].As<Napi::String>().Utf8Value() );
  std::string message( args[1].As<Napi::String>().Utf8Value() );
  Napi::Function callback = args[2].As< Napi::Function >();

  WriteFileWorker * worker = new WriteFileWorker( callback, filename, message);
  worker->Queue();
  
  return args.Env().Undefined();    
}
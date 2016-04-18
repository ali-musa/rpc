using namespace std;
#include "rpcstubhelper.h"
#include <cstdio>
#include <string>
#include "floatarithmetic.idl"

void send_char_ptr(const char* char_ptr)
{
	RPCSTUBSOCKET->write(char_ptr, strlen(char_ptr)+1);
}

void recv_char_ptr(char* char_ptr, unsigned int char_size) {
  unsigned int i;
  char *bufp;    // next char to read
  bool readnull;
  ssize_t readlen;             // amount of data read from socket
  
  //
  // Read a message from the stream
  // -1 in size below is to leave room for null
  //
  readnull = false;
  bufp = char_ptr;
  for (i=0; i< char_size; i++) {
    readlen = RPCSTUBSOCKET-> read(bufp, 1);  // read a byte
    // check for eof or error
    if (readlen == 0) {
      break;
    }
    // check for null and bump buffer pointer
    if (*bufp++ == '\0') {
      readnull = true;
      break;
    }
  }
  
  if (readlen == 0) {
    if (RPCSTUBSOCKET-> eof()) {}
    else {
      throw C150Exception("unexpected zero length read without eof");
    }
  }

  //
  // If we didn't get a null, input message was poorly formatted
  //
  else if(!readnull) 
    throw C150Exception("string not null terminated or too long");
}

void send_float(float float_val)
{
  RPCSTUBSOCKET->write(((const char *)(&float_val)),sizeof(float)); // send size of float
}

void recv_float(float* float_ptr)
{
  ssize_t readlen=0;             // amount of data read from socket
  char float_buf[sizeof(float)];

  while(readlen!=sizeof(float))
  { 
    readlen+=RPCSTUBSOCKET->read(float_buf+readlen,sizeof(float)-readlen); // read size of float
  }
  *float_ptr = *((float*)(&float_buf));
}

void __multiply(){
  float x;
  recv_float(&x);
  float y;
  recv_float(&y);
  float ret_val = multiply(x, y);
  send_float(ret_val);
}

void __add(){
  float x;
  recv_float(&x);
  float y;
  recv_float(&y);
  float ret_val = add(x, y);
  send_float(ret_val);
}

void __subtract(){
  float x;
  recv_float(&x);
  float y;
  recv_float(&y);
  float ret_val = subtract(x, y);
  send_float(ret_val);
}

void __divide(){
  float x;
  recv_float(&x);
  float y;
  recv_float(&y);
  float ret_val = divide(x, y);
  send_float(ret_val);
}

//
//                         dispatchFunction()
//
//   Called when we're ready to read a new invocation request from the stream
//

void dispatchFunction() {


  char function_name[256];
  recv_char_ptr(function_name,256);
  printf("invoking function: %s\n", function_name);
  //
  // We've read the function name, call the stub for the right one
  // The stub will invoke the function and send response.
  //

  if (!RPCSTUBSOCKET-> eof()) {
    if (strcmp(function_name,"")==0) //dummy test
    {
      printf("no function\n");
      return;
    }
    else if (strcmp(function_name,"multiply") == 0) {
      __multiply();
    }
    else if (strcmp(function_name,"add") == 0) {
      __add();
    }
    else if (strcmp(function_name,"subtract") == 0) {
      __subtract();
    }
    else if (strcmp(function_name,"divide") == 0) {
      __divide();
    }
  }
}


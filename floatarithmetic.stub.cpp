#include "floatarithmetic.idl"

#include "rpcstubhelper.h"

#include <cstdio>
#include <cstring>

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

void __add() {
    
  //init input args
  float x;
  float y;
  //recv input args
  recv_float(&x);
  recv_float(&y);
  //init return args
  float ret_val = add(x,y);
  //send retrun args
  send_float(ret_val);

}



// forward declaration
void getFunctionNameFromStream(char *buffer, unsigned int bufSize);



//
//                         dispatchFunction()
//
//   Called when we're ready to read a new invocation request from the stream
//

void dispatchFunction() {


  char functionNameBuffer[50];

  //
  // Read the function name from the stream -- note
  // REPLACE THIS WITH YOUR OWN LOGIC DEPENDING ON THE 
  // WIRE FORMAT YOU USE
  //
  getFunctionNameFromStream(functionNameBuffer,sizeof(functionNameBuffer));

  //
  // We've read the function name, call the stub for the right one
  // The stub will invoke the function and send response.
  //

  if (!RPCSTUBSOCKET-> eof()) {
    if (strcmp(functionNameBuffer,"add") == 0)
      __add();
    // else   if (strcmp(functionNameBuffer,"substract") == 0)
    //   __subtract();
    // else   if (strcmp(functionNameBuffer,"multiply") == 0)
    //   __multiply();
    // else   if (strcmp(functionNameBuffer,"divide") == 0)
    //   __divide();
    // else
    //   __badFunction(functionNameBuffer);
  }
}

 
//
//                   getFunctionNamefromStream
//
//   Helper routine to read function name from the stream. 
//   Note that this code is the same for all stubs, so can be generated
//   as boilerplate.
//
//   Important: this routine must leave the sock open but at EOF
//   when eof is read from client.
//
void getFunctionNameFromStream(char *buffer, unsigned int bufSize) {
  unsigned int i;
  char *bufp;    // next char to read
  bool readnull;
  ssize_t readlen;             // amount of data read from socket
  
  //
  // Read a message from the stream
  // -1 in size below is to leave room for null
  //
  readnull = false;
  bufp = buffer;
  for (i=0; i< bufSize; i++) {
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
  
  //
  // With TCP streams, we should never get a 0 length read
  // except with timeouts (which we're not setting in pingstreamserver)
  // or EOF
  //
  if (readlen == 0) {
    c150debug->printf(C150RPCDEBUG,"arithmetic.stub: read zero length message, checking EOF");
    if (RPCSTUBSOCKET-> eof()) {
      c150debug->printf(C150RPCDEBUG,"arithmetic.stub: EOF signaled on input");

    } else {
      throw C150Exception("arithmetic.stub: unexpected zero length read without eof");
    }
  }

  //
  // If we didn't get a null, input message was poorly formatted
  //
  else if(!readnull) 
    throw C150Exception("arithmetic.stub: method name not null terminated or too long");

  
  //
  // Note that eof may be set here for our caller to check
  //

}

using namespace std;
#include "rpcstubhelper.h"
#include <cstdio>
#include <string>
#include "testarray2.idl"

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

void send_int(int int_val)
{
  int_val = htonl(int_val); // convert to network order
  RPCSTUBSOCKET->write(((const char *)(&int_val)),sizeof(int)); // send size of int
}

void recv_int(int* int_ptr)
{
  ssize_t readlen=0;             // amount of data read from socket
  char int_buf[sizeof(int)];

  while(readlen!=sizeof(int))
  { 
    readlen+=RPCSTUBSOCKET->read(int_buf+readlen,sizeof(int)-readlen); // read size of int
  }

  *int_ptr = ntohl(*((int*)(&int_buf))); // convert to host order and cast
}

void send___int_24_(int __int_24__val[24]) {
  for(int i =0; i<24; i++) {
    send_int(__int_24__val[i]);
  }
}

void recv___int_24_(int* __int_24__ptr[24]) {
  for(int i =0; i<24; i++) {
    recv_int(__int_24__ptr[i]);
  }
}

void send___int_15_(int __int_15__val[15]) {
  for(int i =0; i<15; i++) {
    send_int(__int_15__val[i]);
  }
}

void recv___int_15_(int* __int_15__ptr[15]) {
  for(int i =0; i<15; i++) {
    recv_int(__int_15__ptr[i]);
  }
}

void send___int_24__15_(int __int_24__15__val[24][15]) {
  for(int i =0; i<24; i++) {
    send___int_15_(__int_24__15__val[i]);
  }
}

void recv___int_24__15_(int* __int_24__15__ptr[24][15]) {
  for(int i =0; i<24; i++) {
    recv___int_15_(__int_24__15__ptr[i]);
  }
}

void __sqrt(){
  int* x;
  recv___int_24_(&x);
  int** y;
  recv___int_24__15_(&y);
  int** z;
  recv___int_24__15_(&z);
  int ret_val = sqrt(x, y, z);
  send_int(ret_val);
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
    else if (strcmp(function_name,"sqrt") == 0) {
      __sqrt();
    }
  }
}


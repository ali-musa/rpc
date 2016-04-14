// --------------------------------------------------------------
//
//                        arithmetic.proxy.cpp
//
//        Author: Noah Mendelsohn         
//   
//       This is a hand-crafted demonstration proxy.
//
//       For your project, your "rpcgen" program will generate
//       proxies like this one automatically from the idl
//       file. Note that this proxy also #includes the 
//       arithmetics.idl file. Of course, your rpcgen
//       program will change that, as well as the number
//       of functions generated. More importantly, it will
//       generate code to handle function arguments and
//       return values.
//
//
//
//       Copyright: 2012 Noah Mendelsohn
//     
// --------------------------------------------------------------

// IMPORTANT! WE INCLUDE THE IDL FILE AS IT DEFINES THE INTERFACES
// TO THE FUNCTIONS WE'RE IMPLEMENTING. THIS MAKES SURE THE
// CODE HERE ACTUALLY MATCHES THE REMOTED INTERFACE

#include "arithmetic.idl"

#include "rpcproxyhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"

using namespace C150NETWORK;  // for all the comp150 utilities 

void print_bytes(const void *object, size_t size)
{
  size_t i;

  printf("[ ");
  for(i = 0; i < size; i++)
  {
    printf("%02x ", ((const unsigned char *) object)[i] & 0xff);
  }
  printf("]\n");
}


void send_function_name(const char* fname)
{
  RPCPROXYSOCKET->write(fname,strlen(fname)+1); //make sure it is null term
}

void send_int(int int_val)
{
  int_val = htonl(int_val); // convert to network order
  RPCPROXYSOCKET->write(((const char *)(&int_val)),sizeof(int)); // send size of int
}


void recv_int(int* int_ptr)
{
  ssize_t readlen=0;             // amount of data read from socket
  char int_buf[sizeof(int)];

  while(readlen!=sizeof(int))
  { 
    readlen+=RPCPROXYSOCKET->read(int_buf+readlen,sizeof(int)-readlen); // read size of int
  }

  *int_ptr = ntohl(*((int*)(&int_buf))); // convert to host order and cast
}


int add(int x, int y) {
  // char readBuffer[5];  // to read magic value DONE + null
  //
  // Send the Remote Call
  //
  // c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: add(int x, int y) invoked");
 
  //send function name
  send_function_name("add");
  //sent input args
  send_int(x);
  send_int(y);
  //init return args
  int ret_val;
  //recv return args
  recv_int(&ret_val);
  //return recvd args
  return ret_val;
 
  //
  // Read the response
  //
  // // c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: add(int x, int y) invocation sent, waiting for response");
  // // RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE

  // //
  // // Check the response
  // //
  // if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
  //   throw C150Exception("arithmetic.proxy: add(int x, int y) received invalid response from the server");
  // }
  // c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: add(int x, int y) successful return from remote call");
  // return 1;
}


// int subtract(int x, int y) {
//   char readBuffer[5];  // to read magic value DONE + null
//   //
//   // Send the Remote Call
//   //
//   c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: subtract(int x, int y)() invoked");
//   RPCPROXYSOCKET->write("subtract(int x, int y)", strlen("subtract(int x, int y)")+1); // write function name including null
//   //
//   // Read the response
//   //
//   c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: subtract(int x, int y)() invocation sent, waiting for response");
//   RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE

//   //
//   // Check the response
//   //
//   if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
//     throw C150Exception("arithmetic.proxy: subtract(int x, int y)() received invalid response from the server");
//   }
//   c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: subtract(int x, int y)() successful return from remote call");
//   return 1;
// }


// int multiply(int x, int y) {
//   char readBuffer[5];  // to read magic value DONE + null
//   //
//   // Send the Remote Call
//   //
//   c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: multiply(int x, int y)() invoked");
//   RPCPROXYSOCKET->write("multiply(int x, int y)", strlen("multiply(int x, int y)")+1); // write function name including null
//   //
//   // Read the response
//   //
//   c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: multiply(int x, int y)() invocation sent, waiting for response");
//   RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE

//   //
//   // Check the response
//   //
//   if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
//     throw C150Exception("arithmetic.proxy: multiply(int x, int y)() received invalid response from the server");
//   }
//   c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: multiply(int x, int y)() successful return from remote call");
//   return 1;
// }

// int divide(int x, int y) {
//   char readBuffer[5];  // to read magic value DONE + null
//   //
//   // Send the Remote Call
//   //
//   c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: divide(int x, int y)() invoked");
//   RPCPROXYSOCKET->write("divide(int x, int y)", strlen("divide(int x, int y)")+1); // write function name including null
//   //
//   // Read the response
//   //
//   c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: divide(int x, int y)() invocation sent, waiting for response");
//   RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE

//   //
//   // Check the response
//   //
//   if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
//     throw C150Exception("arithmetic.proxy: divide(int x, int y)() received invalid response from the server");
//   }
//   c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: divide(int x, int y)() successful return from remote call");
//   return 1;
// }
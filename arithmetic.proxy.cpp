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


int add(int x, int y) {
  char readBuffer[5];  // to read magic value DONE + null
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: add(int x, int y) invoked");
  RPCPROXYSOCKET->write("add", strlen("add")+1); // write function name including null
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: add(int x, int y) invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE

  //
  // Check the response
  //
  if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
    throw C150Exception("arithmetic.proxy: add(int x, int y) received invalid response from the server");
  }
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: add(int x, int y) successful return from remote call");
  return 1;
}


int subtract(int x, int y) {
  char readBuffer[5];  // to read magic value DONE + null
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: subtract(int x, int y)() invoked");
  RPCPROXYSOCKET->write("subtract(int x, int y)", strlen("subtract(int x, int y)")+1); // write function name including null
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: subtract(int x, int y)() invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE

  //
  // Check the response
  //
  if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
    throw C150Exception("arithmetic.proxy: subtract(int x, int y)() received invalid response from the server");
  }
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: subtract(int x, int y)() successful return from remote call");
  return 1;
}


int multiply(int x, int y) {
  char readBuffer[5];  // to read magic value DONE + null
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: multiply(int x, int y)() invoked");
  RPCPROXYSOCKET->write("multiply(int x, int y)", strlen("multiply(int x, int y)")+1); // write function name including null
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: multiply(int x, int y)() invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE

  //
  // Check the response
  //
  if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
    throw C150Exception("arithmetic.proxy: multiply(int x, int y)() received invalid response from the server");
  }
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: multiply(int x, int y)() successful return from remote call");
  return 1;
}

int divide(int x, int y) {
  char readBuffer[5];  // to read magic value DONE + null
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: divide(int x, int y)() invoked");
  RPCPROXYSOCKET->write("divide(int x, int y)", strlen("divide(int x, int y)")+1); // write function name including null
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: divide(int x, int y)() invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE

  //
  // Check the response
  //
  if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
    throw C150Exception("arithmetic.proxy: divide(int x, int y)() received invalid response from the server");
  }
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: divide(int x, int y)() successful return from remote call");
  return 1;
}
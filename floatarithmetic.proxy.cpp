#include "floatarithmetic.idl"

#include "rpcproxyhelper.h"

#include <cstdio>
#include <cstring>


void send_function_name(const char* fname)
{
  RPCPROXYSOCKET->write(fname,strlen(fname)+1); //make sure it is null term
}

void send_float(float float_val)
{

  RPCPROXYSOCKET->write(((const char *)(&float_val)),sizeof(float)); // send size of float
}


void recv_float(float* float_ptr)
{
  ssize_t readlen=0;             // amount of data read from socket
  char float_buf[sizeof(float)];

  while(readlen!=sizeof(float))
  { 
    readlen+=RPCPROXYSOCKET->read(float_buf+readlen,sizeof(float)-readlen); // read size of float
  }

  *float_ptr = *((float*)(&float_buf));
}

float add(float x, float y) {
 
  //send function name
  send_function_name("add");
  //sent input args
  send_float(x);
  send_float(y);
  //init return args
  float ret_val;
  //recv return args
  recv_float(&ret_val);
  //return recvd args
  return ret_val;
 
 
}
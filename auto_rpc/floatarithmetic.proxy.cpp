using namespace std;
#include "rpcproxyhelper.h"
#include <cstdio>
#include <string>
#include "floatarithmetic.idl"

void send_char_ptr(const char* char_ptr)
{
	RPCPROXYSOCKET->write(char_ptr, strlen(char_ptr)+1);
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
    readlen = RPCPROXYSOCKET-> read(bufp, 1);  // read a byte
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
    if (RPCPROXYSOCKET-> eof()) {}
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

float multiply(float x, float y) {
  send_char_ptr("multiply");
  send_float(x);
  send_float(y);
  float ret_val;
  recv_float(&ret_val);
  return ret_val;
}

float add(float x, float y) {
  send_char_ptr("add");
  send_float(x);
  send_float(y);
  float ret_val;
  recv_float(&ret_val);
  return ret_val;
}

float subtract(float x, float y) {
  send_char_ptr("subtract");
  send_float(x);
  send_float(y);
  float ret_val;
  recv_float(&ret_val);
  return ret_val;
}

float divide(float x, float y) {
  send_char_ptr("divide");
  send_float(x);
  send_float(y);
  float ret_val;
  recv_float(&ret_val);
  return ret_val;
}


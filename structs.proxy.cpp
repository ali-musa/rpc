using namespace std; 

#include "rpcproxyhelper.h"

#include <cstdio>
#include <string>
#include "structs.idl"

void send_string(const char* string_val)
{
  RPCPROXYSOCKET->write(string_val,strlen(string_val)+1); //make sure it is null term
}


void recv_string(char* string_ptr, unsigned int string_size) {
  unsigned int i;
  char *bufp;    // next char to read
  bool readnull;
  ssize_t readlen;             // amount of data read from socket
  
  //
  // Read a message from the stream
  // -1 in size below is to leave room for null
  //
  readnull = false;
  bufp = string_ptr;
  for (i=0; i< string_size; i++) {
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
  
  //
  // With TCP streams, we should never get a 0 length read
  // except with timeouts (which we're not setting in pingstreamserver)
  // or EOF
  //
  if (readlen == 0) {
    c150debug->printf(C150RPCDEBUG,"read zero length message, checking EOF");
    if (RPCPROXYSOCKET-> eof()) {
      c150debug->printf(C150RPCDEBUG,"EOF signaled on input");

    } else {
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


void send_rectangle(rectangle rectangle_val)
{
	//send all input args
	//for each input arg send each member
	send_int(rectangle_val.x);
	send_int(rectangle_val.y);
}

void recv_rectangle(rectangle* rectangle_ptr)
{
	//recv all input args
	//for each input arg send each member
	recv_int(&(*rectangle_ptr).x);
	recv_int(&(*rectangle_ptr).y);
}

int area(rectangle r)
{
	printf("sending string area\n");
	//send function name
  send_string("area");
  //sent input args
  send_rectangle(r);
    //init return args
  int ret_val;
  //recv return args
  recv_int(&ret_val);
  //return recvd args
  return ret_val;

}
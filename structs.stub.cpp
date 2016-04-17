using namespace std; 

#include "rpcstubhelper.h"

#include <cstdio>
#include <string>
#include "structs.idl"

void send_string(const char* string_val)
{
  RPCSTUBSOCKET->write(string_val,strlen(string_val)+1); //make sure it is null term
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
    c150debug->printf(C150RPCDEBUG,"read zero length message, checking EOF");
    if (RPCSTUBSOCKET-> eof()) {
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


void __area()
{
   
  //init input args
  rectangle r;
  
  //recv input args
  recv_rectangle(&r);
 
  //init return args
  int ret_val = area(r);
  
  //send retrun args
  send_int(ret_val);
}



//
//                         dispatchFunction()
//
//   Called when we're ready to read a new invocation request from the stream
//

void dispatchFunction() {


	char function_name[256];
	recv_string(function_name,256);
	// printf("function_name recvd: %s\n", function_name.c_str());
  //
  // We've read the function name, call the stub for the right one
  // The stub will invoke the function and send response.
  //

  if (!RPCSTUBSOCKET-> eof()) {
    if (strcmp(function_name,"area")==0)
    {
    	printf("invoking area\n");
      __area();
    }
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
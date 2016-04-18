using namespace std;
#include "rpcstubhelper.h"
#include <cstdio>
#include <string>
#include "structs.idl"

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

void send_string(string string_ptr)
{
  send_char_ptr(string_ptr.c_str());
}

void recv_string(string* string_ptr_ptr)
{
  recv_char_ptr((char*)string_ptr_ptr->c_str(),255); //255 is hardcoded max for strings
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

void send_Person(Person Person_val) {
  send_string(Person_val.firstname);
  send_string(Person_val.lastname);
  send_int(Person_val.age);
}

void recv_Person(Person* Person_ptr) {
  recv_string(&(*Person_ptr).firstname);
  recv_string(&(*Person_ptr).lastname);
  recv_int(&(*Person_ptr).age);
}

void send_ThreePeople(ThreePeople ThreePeople_val) {
  send_Person(ThreePeople_val.p1);
  send_Person(ThreePeople_val.p2);
  send_Person(ThreePeople_val.p3);
}

void recv_ThreePeople(ThreePeople* ThreePeople_ptr) {
  recv_Person(&(*ThreePeople_ptr).p1);
  recv_Person(&(*ThreePeople_ptr).p2);
  recv_Person(&(*ThreePeople_ptr).p3);
}

void __findPerson(){
  ThreePeople tp;
  recv_ThreePeople(&tp);
  Person ret_val = findPerson(tp);
  send_Person(ret_val);
}

void send_rectangle(rectangle rectangle_val) {
  send_int(rectangle_val.x);
  send_int(rectangle_val.y);
}

void recv_rectangle(rectangle* rectangle_ptr) {
  recv_int(&(*rectangle_ptr).x);
  recv_int(&(*rectangle_ptr).y);
}

void __area(){
  rectangle r;
  recv_rectangle(&r);
  int ret_val = area(r);
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
    else if (strcmp(function_name,"findPerson") == 0) {
      __findPerson();
    }
    else if (strcmp(function_name,"area") == 0) {
      __area();
    }
  }
}


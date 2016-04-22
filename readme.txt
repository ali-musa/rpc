This program is to generate the proxy and stub for a remote procedure call.

Please first define: 
- xxx.idl -- which contains the declarations of all the functions and structs used
- xxx.cpp -- which contains the implentations of the functions declared in xxx.idl
- xxxclient.cpp -- which calls the functions declared in xxx.idl (these will be remoted by the proxy we generate), make sure to include in it "rpcproxyhelper.h"

To make the server and client programs:
- make xxxclient
- make xxxserver

Files provided and required for the make other than xxx.idl, xxx.cpp, xxxclient.cpp (which the user defines as per need):
- Makefile
- rpcgenerate
- rpcproxyhelper.h
- rpcproxyhelper.cpp
- rpcserver.cpp
- rpcstubhelper.h
- rpcstubhelper.cpp
- idl_to_json.cpp

Known bugs:
- float conversion to network order and vice versa not implmented
- arrays and strings call new without calling delete (may have memory leaks)

#include "musa.idl"

#include "rpcproxyhelper.h"

#include "c150debug.h"
#include "c150grading.h"
#include <fstream>

using namespace std;          // for C++ std library
using namespace C150NETWORK;  // for all the comp150 utilities 


const int serverArg = 1;     // server name is 1st arg
 
int 
main(int argc, char *argv[]) {
     if (argc != 2) {
       fprintf(stderr,"Correct syntxt is: %s <servername> \n", argv[0]);
       exit(1);
     }
     GRADEME(argc, argv);

     try {
       int result; 

       //
       // Set up the socket so the proxies can find it
       //
       rpcproxyinitialize(argv[serverArg]);

       // 
       // Call (possibly remote) add
       //
       printf("Calling add(10,2)\n");
       result = add(10,2);                          // remote call (we hope!)
       printf("Returned from add(10,2). Result=%d\n",result);

     }

     //
     //  Handle networking errors -- for now, just print message and give up!
     //
     catch (C150Exception e) {
       // Write to debug log
       c150debug->printf(C150ALWAYSLOG,"Caught C150Exception: %s\n",
			 e.formattedExplanation().c_str());
       // In case we're logging to a file, write to the console too
       cerr << argv[0] << ": caught C150NetworkException: " << e.formattedExplanation() << endl;
     }

     return 0;
}

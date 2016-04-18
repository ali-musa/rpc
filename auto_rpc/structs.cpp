#include <string>
using namespace std;
#include "structs.idl"

int area(rectangle r) {
  return r.x*r.y;
}


Person findPerson(ThreePeople tp)
{
	return tp.p2;
}
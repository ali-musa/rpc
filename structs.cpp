using namespace std;
#include <string>

#include "structs.idl"


Person findPerson(ThreePeople tp)
{
	return tp.p1;
}

int area(rectangle r)
{
	return (r.x*r.y);
}

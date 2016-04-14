
SERVER

dispatchFunction
{
	getFunctionNameFromStream()
	__func() //call the corressponding function -- it will read if it has any input args, and call the coressponding types, this will wrtie output to socket if any 

	
}
readString()
readInt()

char size[4]; //establish message boundaries



//Primitive types


float read_float(): read a float from socket and return

send_float(float): send as char* 

int read_int: read a int from socket and return
send_int(int): send as char* 

string read_string: read a string uptil the null terminator from socket and return
send_string(string): send as char* (make sure it is null terminated)

read_void: do nothing -- raise warning
send_void:

struct* read_struct: create a struct of the object name match and read each memeber as defined from socket and return the struct
send_struct(struct*):

read_array: create a array of the object name match and read each memeber as defined uptil the 	element count defined from socket and return the array POINTER
send_array:

__func()
{
	
}




//.................STUB (server)................... Latest Example - 9 April 2016 Sana and Musa
--packed---
struct Person {
	string firstname; 
	string lastname; 
	int age;
};
--packed---
struct ThreePeople {
  Person p1;
  Person p2;
  Person p3;
};



send_Person(Person* p)
{	
	//type cast p to char* and write to sock
}

read_string(string str)
{
	//read socket till '/0' and cast to string
}

read_int(int *int_val)
{
	//read first 4 bytes and cast to int
}

read_Person(p)
{
	read_string(p.firstname)
	read_string(p.lastname)
	read_int(&p.age)
}


read_ThreePeople(*ThreePoeple tp)
{
	read_Person(tp.p1);
	read_Person(tp.p2);
	read_Person(tp.p3);
}


__findPerson()
{

	Person* p;
	ThreePeople *tp;
	read_ThreePeople(tp);
	p = find_person(tp);
	send_Person(p);

}
//....................PROXY (client)...................... 

--packed---
struct Person {
	string firstname; 
	string lastname; 
	int age;
};

--packed---
struct ThreePeople {
  Person p1;
  Person p2;
  Person p3;
};

send_ThreePeople(ThreePeople *tp)
{
	
	sock->write((char*)tp, sizeof(tp));	 // check if this works
}


send_function_name(char* fname)
{
	sock->write((fname),strlen(func_name)+1);	//make sure it is null term
}


Person findPerson(ThreePeople* tp)
{
	
	//make input and out args
	ThreePeople *tp = new ThreePeople();
	Person *p = new Person();

	//invoke functions
	send_function_name("findPerson");
	send_ThreePeople(tp); //send input args
	read_Person(p); // read output args
	return p;
	
}


struct __attribute__((__packed__)) header {
	unsigned short a;
	char b[20];
	char c[20];
	unsigned int d;
	unsigned int e; 

};

//............................................................


__add()

{
	
	

	//make input args
	int x = read_int();
	int y = read_int();

	//make output args
	int z;

	z = add(&x, &y)

}
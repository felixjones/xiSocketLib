#include "SmartPointer.h"

/*
====================
xiRefCounter::xiRefCounter

	Constructor
	Defaults the reference count to zero
	You must Grab() after this constructor if you want to use reference counting
====================
*/
xiRefCounter::xiRefCounter() : referenceCount( 0 ) {
}

/*
====================
xiRefCounter::~xiRefCounter

	Deconstructor
	Should be empty and virtual
====================
*/
xiRefCounter::~xiRefCounter() {
}

/*
====================
xiRefCounter::Grab

	Increments reference count
====================
*/
void xiRefCounter::Grab() const {
	++referenceCount;
}
	
/*
====================
xiRefCounter::Drop

	Decrements reference count
	If reference count hits zero, deconstruct the memory
	This does not protect against negative reference counts
====================
*/
void xiRefCounter::Drop() const {
	--referenceCount;

	if( referenceCount == 0 ) {
		Delete();
	}
}
	
/*
====================
xiRefCounter::Delete

	Calls the destructor
====================
*/
void xiRefCounter::Delete() const {
	delete ( xiRefCounter * )this;
}

/*
====================
xiArrayRefCounter::Delete

	Calls the destructor as an array destruction
====================
*/
void xiArrayRefCounter::Delete() const {
	delete[] ( xiArrayRefCounter * )this;
}
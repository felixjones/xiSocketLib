#include "SmartPointer.h"

xiRefCounter::xiRefCounter() : referenceCount( 0 ) {
}

xiRefCounter::~xiRefCounter() {
}

void xiRefCounter::Grab() const {
	++referenceCount;
}
	
void xiRefCounter::Drop() const {
	--referenceCount;

	if( referenceCount == 0 ) {
		Delete();
	}
}

void xiRefCounter::Delete() const {
	delete ( xiRefCounter * )this;
}

void xiArrayRefCounter::Delete() const {
	delete[] ( xiArrayRefCounter * )this;
}
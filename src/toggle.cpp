#include "toggle.hpp"

void BinaryToggle::trigger(){
	value = !value;
}

void BinaryToggle::set(bool b){
	value = b;
}

bool BinaryToggle::is(){
	return value;
}

BinaryToggle::operator bool(){
	value = !value;
	return value;
}
#include "receiver.hpp"

void Receiver::notify( Message m ){
	std::cout << m.content << std::endl;
};
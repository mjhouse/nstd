#include "broadcaster.hpp"

void Broadcaster::broadcast( std::string msg ){
	Message m;
	m.content = msg;
	channel->notify(m);
};
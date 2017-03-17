#ifndef _CHANNEL_HPP_
#define _CHANNEL_HPP_

#include <string>
#include <vector>
#include "message.hpp"
#include "receiver.hpp"
#include "broadcaster.hpp"

class Receiver( Channel* ch );

class Channel {
	private:
		std::string name;
		std::vector<Receiver*> subscribers;
		
	public:
		Channel( std::string n ) : name(n) {};
		~Channel(){};
		
		// public functions
		int notify( Message m );
		int subscribe( Receiver* r );
};

#endif
#ifndef _RECEIVER_HPP_
#define _RECEIVER_HPP_

#include <iostream>
#include "channel.hpp"
#include "message.hpp"

class Channel( std::string n );

class Receiver {
	private:
		Channel* channel;
		
	public:
		Receiver( Channel* ch ) : channel(ch) {
			ch->subscribe(this);
		};
		~Receiver(){};
		
		void notify( Message m );
};

#endif
#ifndef _BROADCASTER_HPP_
#define _BROADCASTER_HPP_

#include <string>
#include "channel.hpp"
#include "message.hpp"

class Channel( std::string n );

class Broadcaster {
	private:
		Channel* channel;
		
	public:
		Broadcaster( Channel* ch ) : channel(ch) {};
		~Broadcaster(){};
		
		void broadcast( std::string msg );
};

#endif
#include "channel.hpp"

int Channel::notify( Message m ){
	for(std::vector<Receiver*>::iterator it = subscribers.begin(); it != subscribers.end() ; it++){
		(*it)->notify( m );
	}
	return subscribers.size();
};

int Channel::subscribe( Receiver* r ){
	if(r){
		subscribers.push_back(r);
		return 1;
	}
	return 0;
};
#include <iostream>

#include "channel.hpp"
#include "receiver.hpp"
#include "broadcaster.hpp"

int main(){
	Channel* channel = new Channel("my_channel_name");
	
	Broadcaster* sender = new BroadCaster(channel);
	Subscriber* listener = new Subscriber(channel);
	
	return 0;
}
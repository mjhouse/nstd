# NSTD

This is an incomplete non-standard library in C++ that spun off from the [AFE](https://github.com/mjhouse/afe) project and provided some of the classes that were used there. There are two major chunks of code here- the **broadcaster**, and the **loop**.

### Broadcaster:
The broadcaster and associated classes are a messaging backbone that was going to transmit movement instructions through the back end of the AFE text editor. This would have made multiple cursors and simultaneous edits really simple. Each cursor would just subscribe to the messaging system on creation, and when the user tries to move or type while multiple cursors are active, the action is sent to all of them.

#### files:
* broadcaster.cpp
* broadcaster.hpp
* channel.cpp
* channel.hpp
* message.hpp
* receiver.cpp
* receiver.hpp

### Loop:
This was a data structure that I created specifically to hold each line of text in the AFE buffer. It's basically a homebrew 'String' class wrapped around a character array, except that a String class allocates memory when the internal char array is too long and then places the characters starting at the *beginning* of the newly allocated memory, leaving a gap at the end for new characters. This makes appending new characters an amortized constant time operation of O(1).

Loop does some internal calculation and places characters in the *middle third* of the allocated memory, making both append and prepend operations O(1). The down side is that at any given time, a Loop is going to take more memory than a String with the same characters.

#### files:
* loop.cpp
* loop.hpp

#ifndef _TOGGLE_HPP_
#define _TOGGLE_HPP_

class BinaryToggle {
	private:
		bool value;
		
	public:
		BinaryToggle(bool b){value = !b;};
		~BinaryToggle(){};
		
		void trigger();
		void set(bool b);
		bool is();
		operator bool();
};

#endif
#include "loop.hpp"

namespace afe {

	Loop::Loop(){
		// initial values
		error_state = error::GOOD;
		
		// init memory
		char* newbuf = (char*)malloc(16*sizeof(char)+1);
		if(newbuf){
			outer = newbuf;
			outer_length = 16;
			
			inner = outer + 8; // half of 16 
			inner_length = 0;
		}
		else {
			free(newbuf);
			
			outer = NULL;
			outer_length = 0;
			
			inner = NULL;
			inner_length = 0;
			
			error_state = error::BAD_MEMORY_INIT;
		}
	}

	Loop::~Loop(){
		free(outer);
		outer = NULL;
		outer_length = 0;
		
		inner = NULL;
		inner_length = 0;
	}

	void Loop::rshift( int pos, int shift ){
		if( (inner+inner_length+shift) >= (outer+outer_length) )
			resize((inner_length+shift)*3);

		for(int i = inner_length ; i >= pos ; i--)
			inner[i+shift] = inner[i];
		inner_length += shift;
		inner[inner_length] = '\0';
	}

	void Loop::lshift( int pos, int shift ){
		if( inner-shift <= outer )
			resize((inner_length+shift)*3);
		
		inner -= shift;	
		inner_length += shift;
		for(int i = 0 ; i < pos ; ++i){
			inner[i] = inner[i+shift];
			inner[i+shift] = '-';
		}
	}

	void Loop::resize( size_t new_outer_length ){
		char* new_outer = ( char* )malloc(new_outer_length*sizeof(char)+1);
		if(new_outer){
			char* new_inner = new_outer + (new_outer_length/3);
			
			memcpy( new_inner, inner, inner_length);
			
			inner = new_inner;
			free(outer);
			outer = new_outer;
			outer_length = new_outer_length;
		}
		else {
			free(new_outer);
			error_state = error::BAD_MEMORY_ALLOC;
		}
	}

	void Loop::pushb( char c, bool skip ){
		if( !skip && ((inner+inner_length+1) >= (outer+outer_length)) )
			resize((inner_length+1)*3);
		inner[inner_length] = c; inner_length++;
		inner[inner_length] = '\0';
	}

	char Loop::popb(){
		if( inner_length-1 >= 0 ){
			--inner_length;
			char retval = inner[inner_length];
			inner[inner_length] = '\0';
			return retval;
		}
		else {
			error_state = error::STR_EMPTY;
			return 0;
		}
	}

	void Loop::pushf( char c, bool skip ){
		if( !skip && (inner-1 <= outer) )
			resize(inner_length*3);
		--inner;
		++inner_length;
		
		inner[0] = c;
	}

	char Loop::popf(){
		if( inner_length-1 >= 0 ){
			char retval = inner[0];
			++inner;
			--inner_length;
			return retval;
		}
		else {
			error_state = error::STR_EMPTY;
			return 0;
		}
	}

	// -----------------------------------------------------------------
	// Public Functions
	char Loop::at( int i ){
		if( i >= 0 && i < inner_length){
			return inner[i];
		}
		else {
			error_state = error::OUT_OF_BOUNDS;
			return 0;
		}
	}
	
	void Loop::set( int i, char c ){
		if( i >= 0 && i < inner_length){
			inner[i] = c;
		}
		else {
			error_state = error::OUT_OF_BOUNDS;
		}
	}
	
	void Loop::insert( int i, char c ){
		if( i >= 0 && i < inner_length ){
			if( (inner_length-i) > (inner_length/2) ){
				if(i==0) {
					pushf(c);
				}
				else {
					lshift(i,1);
					inner[i] = c;
				}
			}
			else {
				if(i==inner_length) {
					pushb(c);
				}
				else {
					rshift(i,1);
					inner[i] = c;
				}
			}
		}
		else {
			error_state = error::OUT_OF_BOUNDS;
			return;
		}
	}

	void Loop::insert( int i, char* c ){
		int len = strlen(c);
		if( (signed int)(inner_length-i) > (signed int)(inner_length/2) ){
			if(i<=0) {
				for(int j=len-1;j>=0;--j) 
					pushf(c[j]);
			}
			else {
				lshift(i,len);
				for(int j=i;j<(i+len);++j) 
					inner[j] = c[j-i];
			}
		}
		else {
			if(i>=inner_length) {
				for(int j=0;j<len;++j) 
					pushb(c[j]);
			}
			else {
				rshift(i,len);
				for(int j=i;j<(i+len);++j) 
					inner[j] = c[j-i];
			}
		}
	}

	void Loop::push_front( char c ){
		pushf(c);
	}
	
	char Loop::pop_front(){
		return popf();
	}
	
	void Loop::push_back( char c ){
		pushb(c);
	}
	
	char Loop::pop_back(){
		return popb();
	}

	int Loop::begin(){
		return 0;
	}

	size_t Loop::end(){
		return inner_length-1;
	}
	
	int Loop::state(){
		return error_state;
	}
	
	size_t Loop::length(){
		return inner_length;
	}
	
	size_t Loop::allocated_memory(){
		return outer_length;
	}
	
	// -----------------------------------------------------------------
	// Overloaded Operators
	char& Loop::operator[]( int i ){
		if( i >= 0 && i <= inner_length){
			return inner[i];
		}
		else {
			error_state = error::OUT_OF_BOUNDS;
			static char c = 0;
			return c;
		}
	}

	// -----------------------------------------------------------------
	// Friend Functions
	std::ostream& operator<<(std::ostream& output, const Loop& l){
		if(l.inner) output << l.inner;
		return output;
	}
}

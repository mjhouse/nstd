#ifndef _LOOP_HPP_
#define _LOOP_HPP_

// system includes
#include <cstdlib>
#include <cstring>
#include <iostream>

// local includes
#include "constants.hpp"

namespace afe {

	class Loop {
		private:
			// variables
			char* outer;
			size_t outer_length;
			
			char* inner;
			size_t inner_length;
			
		protected:
			int error_state;
			
		private:
			// private functions
			void rshift( int pos, int shift );
			void lshift( int pos, int shift );
			void resize( size_t new_outer_length );
			
			void pushb( char c, bool skip=false );
			char popb();
			
			void pushf( char c, bool skip=false );
			char popf();
			
		public:
			Loop();
			~Loop();
			
			// -------------------------------------------------------------
			// Public Functions
			char at( int i );
			void set( int i, char c );
			void insert( int i, char c );
			void insert( int i, char* c );

			void push_front( char c );
			char pop_front();
			void push_back( char c );
			char pop_back();

			int begin();
			size_t end();
			int state();
			
			size_t length();
			size_t allocated_memory();
			
			// -------------------------------------------------------------
			// Overloaded Operators
			char& operator[]( int i );
			
			// -------------------------------------------------------------
			// Stream Functions
			friend std::ostream& operator<<( std::ostream& output, const Loop& l );
	};

}

#endif

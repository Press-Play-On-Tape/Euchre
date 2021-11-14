#pragma once

#include <stdarg.h>

namespace Utils {

	// Extract individual digits of a uint8_t -------------------------------------

	template< size_t size > void extractDigits(uint8_t (&buffer)[size], uint8_t value) {

		for(uint8_t i = 0; i < size; ++i) {
			buffer[i] = value % 10;
			value /= 10;
		}

	}

	// Extract individual digits of a uint16_t
	template< size_t size > void extractDigits(uint8_t (&buffer)[size], uint16_t value) {

		for(uint8_t i = 0; i < size; ++i) {
			buffer[i] = value % 10;
			value /= 10;
		}
	
	}


	// ----------------------------------------------------------------------------
	//  Swap two elements .. 
	//
	template <typename T> void swap(T& x,T& y) {
		T temp;
		temp = x;
		x = y;
		y = temp;
	}


	// ----------------------------------------------------------------------------
	//  A better absolute as it uses less memory than the standard one .. 
	//
	template<typename T> T absT(const T & v) {
	
		return (v < 0) ? -v : v;

	}


	// ----------------------------------------------------------------------------
	//  Clamp the value within the range .. 
	//
	template <typename T> inline T clamp(const T& value, const T& low, const T& high) {

		return (value < low) ? low : (value > high) ? high : value; 

	}


	// This gets the length of an array at compile time
	template< typename T, size_t N > constexpr size_t ArrayLength(T (&)[N]) {

		return N;

	}

	static inline void print(Debug mode, __const char *__restrict __format, ...) {

		#ifdef DEBUG

			bool printIt = false;

			switch (mode) {

				case Debug::None:
					printIt = true;
					break;

				case Debug::Bid:
					#ifdef DEBUG_BID
						printIt = true;
					#endif
					break;

				case Debug::Lead:
					#ifdef DEBUG_LEAD
						printIt = true;
					#endif
					break;

				case Debug::Follow:
					#ifdef DEBUG_FOLLOW
						printIt = true;
					#endif
					break;

				case Debug::Play:
					#ifdef DEBUG_PLAY
						printIt = true;
					#endif
					break;

				case Debug::State:
					#ifdef DEBUG_STATE
						printIt = true;
					#endif
					break;

				case Debug::Sounds:
					#ifdef DEBUG_SOUNDS
						printIt = true;
					#endif
					break;
					
			}

			if (printIt) {

				va_list args;
				va_start(args, __format);
				vfprintf(stdout, __format, args);
				va_end(args);

			}

		#endif

	}

}
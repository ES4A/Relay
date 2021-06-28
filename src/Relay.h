#ifndef Relay_h
	#define Relay_h
	
	extern "C" {
		
	}

	#if defined(ARDUINO) && ARDUINO >= 100
		#include "Arduino.h"
		#else
		#include "WProgram.h"
	#endif 
	
	class Relay{
		public:	

			enum RelayType{
				none,
				normal,
				bistable,
				powerSurge
			};

			Relay();
			Relay(uint8_t activePin);
            Relay(uint8_t changePin, bool initState);
			Relay(uint8_t activePin, uint8_t resetPin, bool initState);
		
            void tick();
            void setState(bool newState);
			bool getState();
            void setActiveLow(bool newActiveLow);
            void setSwitchTime(uint16_t newTime);
	
		private:
			bool currentState = false;
			bool newState = false;
			bool activeLow = false;
			uint8_t relayActivePin;
			uint8_t relayResetPin;
			RelayType Relaytype = none;
			long startChange;		
			uint16_t switchTime = 100;
		
	};
#endif //Relay
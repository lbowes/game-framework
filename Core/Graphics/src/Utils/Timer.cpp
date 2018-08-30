#include "Timer.h"

namespace GF {
	namespace Utils {

		std::chrono::time_point<std::chrono::high_resolution_clock> Timer::mStartTime, Timer::mStopTime;
		
		int64_t 
			Timer::mLatestEventDuration, 
			Timer::mResolution;

		std::vector<TimedEvent> Timer::mTimedEvents;

		void Timer::start(unsigned resolution) {
			mResolution = resolution;
			mStartTime = std::chrono::high_resolution_clock::now();
		}

		void Timer::stop(const std::string& eventName, bool addToEvents) {
			mStopTime = std::chrono::high_resolution_clock::now();
			
			switch (mResolution) {
			case HOURS:
				mLatestEventDuration = std::chrono::duration_cast<std::chrono::hours>(mStopTime - mStartTime).count();
				break;

			case MINUTES:
				mLatestEventDuration = std::chrono::duration_cast<std::chrono::minutes>(mStopTime - mStartTime).count();
				break;

			case SECONDS:
				mLatestEventDuration = std::chrono::duration_cast<std::chrono::seconds>(mStopTime - mStartTime).count();
				break;

			case MILLISECONDS:
				mLatestEventDuration = std::chrono::duration_cast<std::chrono::milliseconds>(mStopTime - mStartTime).count();
				break;

			case MICROSECONDS:
				mLatestEventDuration = std::chrono::duration_cast<std::chrono::microseconds>(mStopTime - mStartTime).count();
				break;

			case NANOSECONDS:
				mLatestEventDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(mStopTime - mStartTime).count();
				break;
			
			default:
				break;
			}

			if(addToEvents)
				addTimedEvent(eventName);
		}

		void Timer::addTimedEvent(const std::string& eventName) {
			TimedEvent tempEvent(eventName, mLatestEventDuration);
			mTimedEvents.push_back(tempEvent);
		}

		void Timer::showTimedEvents() {
			if (mTimedEvents.empty())
				std::cout << "No timed events recorded." << std::endl;
			else {
				std::string resolution;

				switch (mResolution) {
				case HOURS:
					resolution = "hours";
					break;

				case MINUTES:
					resolution = "minutes";
					break;

				case SECONDS:
					resolution = "seconds";
					break;

				case MILLISECONDS:
					resolution = "milliseconds";
					break;

				case MICROSECONDS:
					resolution = "microseconds";
					break;

				case NANOSECONDS:
					resolution = "nanoseconds";
					break;
				}

				for (TimedEvent timedEvent : mTimedEvents)
					std::cout << "Event '" << timedEvent.getName() << "' took " << timedEvent.getTimeTaken() << " " << resolution << "." << std::endl;
			}
		}

	}
}
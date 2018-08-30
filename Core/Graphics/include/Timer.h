#ifndef UTILS_TIMER_H
#define UTILS_TIMER_H
#pragma once

#include <iostream>
#include <chrono>
#include <string>
#include <vector>

namespace GF {
	namespace Utils {

		struct TimedEvent {
		private:
			std::string mName;
			unsigned long long mTimeTaken;

		public:
			TimedEvent(const std::string& eventName, unsigned long long timeTaken) : mName(eventName), mTimeTaken(timeTaken) { }
			inline std::string getName() const { return mName; }
			inline unsigned long long getTimeTaken() const { return mTimeTaken; }

		};

		class Timer {
		private:
			static std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime, mStopTime;
			
			static int64_t
				mLatestEventDuration, 
				mResolution;

			static std::vector<TimedEvent> mTimedEvents;

		public:
			enum { HOURS, MINUTES, SECONDS, MICROSECONDS, MILLISECONDS, NANOSECONDS };

		public:
			static void start(unsigned resolution);
			static void stop(const std::string& eventName, bool addToEvents);
			static void showLatestTime() { std::cout << mLatestEventDuration << std::endl; }
			static void addTimedEvent(const std::string& eventName);
			static void showTimedEvents();

		};

	}
}

#endif

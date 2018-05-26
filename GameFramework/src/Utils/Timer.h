#ifndef TIMER_H
#define TIMER_H
#pragma once

#include <iostream>
#include <chrono>
#include <string>
#include <vector>

namespace Framework {
	namespace Utils {

		struct TimedEvent {
		private:
			std::string mName;
			unsigned int mTimeTaken;

		public:
			TimedEvent(std::string eventName, unsigned int timeTaken) : mName(eventName), mTimeTaken(timeTaken) { }
			inline std::string getName() const { return mName; }
			inline unsigned int getTimeTaken() const { return mTimeTaken; }

		};

		class Timer {
		private:
			static std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime, mStopTime;
			static unsigned int mLatestEventDuration, mResolution;
			static std::vector<TimedEvent> mTimedEvents;

		public:
			enum {
				HOURS, MINUTES, SECONDS, MICROSECONDS, MILLISECONDS, NANOSECONDS
			};

		public:
			static void start(unsigned int resolution);
			static void stop(std::string eventName, bool addToEvents);
			static void showLatestTime() { std::cout << mLatestEventDuration << std::endl; }
			static void addTimedEvent(std::string eventName);
			static void showTimedEvents();

		};

	}
}

#endif

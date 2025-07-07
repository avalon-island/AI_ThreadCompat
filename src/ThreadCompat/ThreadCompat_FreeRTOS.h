/*
 * AI_ThreadCompat -- wrapper library to simplify code writing for cross-
 *                    thread-implementation software.
 *                    Now it supports mbedOS and FreeRTOS RTOSes.
 *
 * Copyright © 2025 Andrei Kolchugin
 * Written, refactored and debugged with assistance of LLM
 * "GPT-4" © OpenAI, Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#pragma once

// C++
#include <cstdint>

// Arduino Core
#include <Arduino.h>

// FreeRTOS
#include <FreeRTOS.h>
#include <semphr.h>

namespace ai {

	namespace thread {


		class Mutex {

		public:

			Mutex() { _handle = xSemaphoreCreateMutex(); }
			virtual ~Mutex() { if (_handle) vSemaphoreDelete(_handle); }

			/*
			 * Copying of mutexes doesn't have a much sense
			 */
			Mutex(const Mutex&) = delete;
			Mutex& operator=(const Mutex&) = delete;

			inline void lock(void) { xSemaphoreTake(_handle, portMAX_DELAY); }
			inline bool try_lock(uint32_t timeout_ms = 0) {

				TickType_t ticks = pdMS_TO_TICKS(timeout_ms);

				return xSemaphoreTake(_handle, ticks) == pdTRUE;
			}
			inline void unlock() { xSemaphoreGive(_handle); }

			inline SemaphoreHandle_t native_handle() const { return _handle; }

		private:

			SemaphoreHandle_t _handle;
		};

		class [[nodiscard]] ScopedMutexLock {

		public:

			explicit ScopedMutexLock(Mutex &m) : _mutex(m) {

				_mutex.lock();
			}
			~ScopedMutexLock() {

				_mutex.unlock();
			}

			ScopedMutexLock(const ScopedMutexLock &) = delete;
			ScopedMutexLock& operator=(const ScopedMutexLock &) = delete;

		private:

			Mutex& _mutex;
		};

		inline auto
		callback(void *arg, void (*func)(void)) {

			return [=]() { func(); };
		}

		template <typename T, typename R, typename... Args>
		auto
		callback(T *obj, R(T::*method)(Args...)) {

			return [=](Args... args) { return (obj->*method)(std::forward<Args>(args)...); };
		}

		template <typename T, typename R, typename... Args>
		auto
		callback(const T *obj, R(T::*method)(Args...) const) {

			return [=](Args... args) { return (obj->*method)(std::forward<Args>(args)...); };
		}
	}

	constexpr UBaseType_t osPriorityIdle		= 0;
	constexpr UBaseType_t osPriorityLow		= 1;
	constexpr UBaseType_t osPriorityNormal		= 2;
	constexpr UBaseType_t osPriorityHigh		= 3;
	constexpr UBaseType_t osPriorityRealtime	= 4;
}


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

namespace ai {

	namespace thread {

#include "rtos/mbed_rtos_types.h"
#ifdef RTOS_TYPES_H_
#undef RTOS_TYPES_H_
#endif

#include "rtos/internal/mbed_rtos1_types.h"
#ifdef MBED_RTOS_RTX1_TYPES_H
#undef MBED_RTOS_RTX1_TYPES_H
#endif

	}
}

#include <mbed.h>
#include <rtos.h>

namespace ai {

	namespace thread {

		using Mutex = rtos::Mutex;
		using ScopedMutexLock = rtos::ScopedMutexLock;

		constexpr int osPriorityIdle		= 1; // osPriority_t::osPriorityIdle;
		constexpr int osPriorityLow		= 8; // osPriority_t::osPriorityLow;
		constexpr int osPriorityNormal		= 16; // osPriority_t::osPriorityNormal;
		constexpr int osPriorityHigh		= 24; // osPriority_t::osPriorityHigh;
		constexpr int osPriorityRealtime	= 32; // osPriority_t::osPriorityRealtime;
	}
}


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

#if defined(ARDUINO_ARCH_MBED)

#include <ThreadCompat/ThreadCompat_mbedOS.h>

#else /* defined(ARDUINO_ARCH_MBED) */

#include <ThreadCompat/ThreadCompat_FreeRTOS.h>

#endif /* defined(ARDUINO_ARCH_MBED) */

using namespace ai;


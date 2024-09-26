#ifndef _BEBONE_CORE_CORE_H_
#define _BEBONE_CORE_CORE_H_

#include "types/types.h"

// Debug
#include "debug/ilogger.h"
#include "debug/console_logger.h"

#include "debug/profiler.h"

// Memory
#include "memory/arena_allocator.h"
#include "memory/arena_container.h"

// Events
#include "events/listeners/event_dispatcher.tpp"
#include "events/delegates/action.h"

// Input
#include "input/input.h"
#include "input/input_executor.h"

// Timestamp
#include "timestamp/watch.h"

#endif
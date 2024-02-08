#ifndef _BEBONE_CORE_PROFILER_H_
#define _BEBONE_CORE_PROFILER_H_

#include <vector>

#include <cassert>

#include <sstream>
#include <iostream>

#include <chrono>
#include <fstream>
#include <string>

#include <functional>

#include "types.h"

namespace bebone::core {
    struct Profile {
        private:
            std::chrono::high_resolution_clock::time_point recordStartTimestamp;
            std::vector<Profile*> childs;

        public:
            const char* label;

            u64 executionCount;

            f64 totalExecutionTime;
            f64 minExecutionTime;
            f64 maxExecutionTime;

            explicit Profile(const char* label);

            void record();
            void stop();

            void push_child_profile(Profile *profile);
            u32 count_child_profiles();

            std::vector<Profile*>& get_childs();
    };

    struct ProfilerCloser {
        ProfilerCloser();
    };

    class Profiler {
        public:
            std::vector<Profile*> stack;
            std::vector<Profile*> entryPoints;

            void bind_top_profile(Profile *profile);
            void unbind_top_profile();
            void sumup();

            static Profiler& get_instance();
    };

    void trace_profiles(Profile *profile, Profile *parent, unsigned long depth, const std::function<void(Profile*)>& lamda);
}

#define BEBONE_PROFILE_RECORD(LABEL) static bebone::core::Profile LABEL(#LABEL); LABEL.record();
#define BEBONE_PROFILE_STOP(LABEL) static bebone::core::ProfilerCloser LABEL ## _CLOSER; LABEL.stop();

#endif
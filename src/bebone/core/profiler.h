#ifndef _BEBONE_CORE_PROFILER_H_
#define _BEBONE_CORE_PROFILER_H_

#include <vector>
#include <array>

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
            std::string label;

            u64 executionCount;

            f64 totalExecutionTime;
            f64 minExecutionTime;
            f64 maxExecutionTime;

            explicit Profile(std::string label);
            explicit Profile(const char* label);

            void record();
            void stop();

            void push_child_profile(Profile *profile);
            u32 count_child_profiles();

            std::vector<Profile*>& get_childs();
    };

    class Profiler {
        private:
            Profiler();

            std::array<Profile*, 1024> stack;
            unsigned int stackIndex;

            std::vector<Profile*> entryPoints;

        public:
            void push_profile(Profile* profile);

            void bind_top_profile(Profile *profile);
            void unbind_top_profile();

            const unsigned int& get_stack_index() const;
            const std::array<Profile*, 1024>& get_stack() const;
            const std::vector<Profile*>& get_entry_points() const;

            std::string sum_up() const;

            static Profiler& get_instance();
    };

    void trace_profiles(
        Profile *profile,
        Profile *parent,
        unsigned long depth,
        const std::function<void(Profile*, unsigned int depth)>& lamda
    );
}

#ifdef DEBUG
    #define BEBONE_PROFILE_RECORD(LABEL) static bebone::core::Profile LABEL(#LABEL); LABEL.record();
    #define BEBONE_PROFILE_STOP(LABEL) LABEL.stop();
    #define BEBONE_PROFILER_SUM_UP() Profiler::get_instance().sum_up()
#else
    #define BEBONE_PROFILE_RECORD(LABEL)
    #define BEBONE_PROFILE_STOP(LABEL)
    #define BEBONE_PROFILER_SUM_UP() ""
#endif

#endif
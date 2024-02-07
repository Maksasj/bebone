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

namespace bebone::core {
    struct Profile {
        private:
            std::chrono::high_resolution_clock::time_point recordStartTimestamp;
            std::vector<Profile*> childs;

        public:
            unsigned long long executionTimes;
            double exceptionTime;

            std::string label;

            Profile(const std::string& label);

            void record();
            void stop();

            void push_child_profile(Profile *profile);
            unsigned long count_child_profiles();
            std::pair<std::vector<bebone::core::Profile*>::iterator, std::vector<bebone::core::Profile*>::iterator> get_childs();
    };

    struct ProfilerCloser {
        ProfilerCloser();
    };

    class Profiler {
        public:
            static std::vector<Profile*> stack;
            static std::vector<Profile*> entryPoints;

            static void bind_top_profile(Profile *profile);
            static void unbind_top_profile();
            static void sumup();
    };

    void trace_profiles(Profile *profile, Profile *parent, unsigned long depth, const std::function<void(Profile*)>& lamda);
}

#define BEBONE_PROFILE_RECORD(LABEL) static bebone::core::Profile LABEL(#LABEL); LABEL.record();
#define BEBONE_PROFILE_STOP(LABEL) static bebone::core::ProfilerCloser LABEL ## _CLOSER; LABEL.stop();

#endif
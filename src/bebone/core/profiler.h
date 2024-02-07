#ifndef _BEBONE_CORE_PROFILER_H_
#define _BEBONE_CORE_PROFILER_H_

#include <vector>

#include <cassert>

#include <sstream>
#include <iostream>

#include <chrono>
#include <fstream>
#include <string>

namespace bebone::core {
    struct Profile {
        private:
            std::chrono::high_resolution_clock::time_point record_start_timestamp;
            std::vector<Profile*> childs;

        public:
            unsigned long long _execution_times;
            double _exception_time;

            std::string _label;

            Profile(std::string label);

            void record();
            void push_child_profile(Profile *profile);
            unsigned long count_child_profiles();
            std::pair<std::vector<bebone::core::Profile*>::iterator, std::vector<bebone::core::Profile*>::iterator> get_childs();
            void stop();
    };

    struct ProfilerCloser {
        ProfilerCloser();
    };

    class Profiler {
        private:
            static std::vector<Profile*> stack;
            static std::vector<Profile*> entryPoints;

        public:
            static void bind_top_profile(Profile *profile);
            static void unbind_top_profile();
            static void sumup();
    };

    void trace_profiles(std::stringstream *ss, bebone::core::Profile *profile, bebone::core::Profile *parent, unsigned long depth);
}

#define BEBONE_PROFILE_RECORD(LABEL) static bebone::core::Profile LABEL(#LABEL); LABEL.record();
#define BEBONE_PROFILE_STOP(LABEL) static bebone::core::ProfilerCloser LABEL ## _CLOSER; LABEL.stop();

#endif
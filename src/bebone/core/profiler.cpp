#include "profiler.h"

namespace bebone::core {
    Profile::Profile(const char* label)
        : label(label),
          executionCount(0),
          totalExecutionTime(0.0),
          minExecutionTime(std::numeric_limits<f64>::max()),
          maxExecutionTime(0.0)
    {

        Profiler::get_instance().bind_top_profile(this);
    }

    ProfilerCloser::ProfilerCloser() {
        Profiler::get_instance().unbind_top_profile();
    }

    u32 Profile::count_child_profiles() {
        return childs.size();
    }

    std::vector<Profile*>& Profile::get_childs() {
        return childs;
    }

    void Profile::record() {
        ++executionCount;

        recordStartTimestamp = std::chrono::high_resolution_clock::now();
    }

    void Profile::push_child_profile(Profile *profile) {
        childs.push_back(profile);
    }

    void Profile::stop() {
        auto record_stop_timestamp = std::chrono::high_resolution_clock::now();
        
        f64 duration = std::chrono::duration_cast<std::chrono::nanoseconds>(record_stop_timestamp - recordStartTimestamp).count();

        totalExecutionTime += duration;
        minExecutionTime = std::min(minExecutionTime, duration);
        maxExecutionTime = std::max(maxExecutionTime, duration);
    }

    void Profiler::bind_top_profile(Profile *profile) {
        if(stack.size() == 0) {
            entryPoints.push_back(profile);
        } else {
            stack[stack.size() - 1]->push_child_profile(profile);
        }

        stack.push_back(profile);
    }

    void Profiler::unbind_top_profile() {
        stack.pop_back();
    }

    void trace_profiles(Profile *profile, Profile *parent, unsigned long depth, const std::function<void(Profile*)>& lamda) {
        const auto& childs = profile->get_childs();

        for(auto& pp : childs) {
            lamda(pp);

            trace_profiles(pp, profile, depth + 1, lamda);
        }
    }

    void Profiler::sumup() {
        for(auto& profile : entryPoints) {
            std::stringstream ss;

            ss  << "Profile: '"<< profile->label
                << "' executed " << profile->executionCount << " times, total execution time: "
                << profile->totalExecutionTime / 1000000.0 << "ms, "
                << "100% \n";

            trace_profiles(profile, profile, 1, [&](Profile* pp) {
                ss  << "Profile: '"<< pp->label
                    << "' executed " << pp->executionCount << " times, total execution time: "
                    << pp->totalExecutionTime / 1000000.0 << "ms, "
                    << "100% \n";
            });

            std::cout << ss.str();
        }
    }

    Profiler& Profiler::get_instance() {
        static Profiler profiler;
        return profiler;
    }
}

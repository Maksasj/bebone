#include "profiler.h"

namespace bebone::core {
    std::vector<Profile*> Profiler::stack;
    std::vector<Profile*> Profiler::entryPoints;

    Profile::Profile(const std::string& label) : label(label) {
        Profiler::bind_top_profile(this);
    }

    ProfilerCloser::ProfilerCloser() {
        Profiler::unbind_top_profile();
    }

    unsigned long Profile::count_child_profiles() {
        return childs.size();
    }

    std::pair<std::vector<Profile*>::iterator, std::vector<Profile*>::iterator> Profile::get_childs() {
        return std::make_pair(childs.begin(), childs.end());
    }

    void Profile::record() {
        ++executionTimes;

        recordStartTimestamp = std::chrono::high_resolution_clock::now();
    }

    void Profile::push_child_profile(Profile *profile) {
        childs.push_back(profile);
    }

    void Profile::stop() {
        auto record_stop_timestamp = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(record_stop_timestamp - recordStartTimestamp).count();
        exceptionTime += duration;
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
        auto childs = profile->get_childs();

        for(auto i = childs.first; i < childs.second; ++i) {
            lamda(*i);

            trace_profiles((*i), profile, depth + 1, lamda);
        }
    }

    void Profiler::sumup() {
        for(auto profile : entryPoints) {
            std::stringstream ss;

            ss  << "Profile: '"<<profile->label
                << "' executed " << profile->executionTimes << " times, total execution time: "
                << profile->exceptionTime / 1000000.0 << "ms, "
                << "100% \n";

            trace_profiles(profile, profile, 1, [&](Profile* pp) {
                ss  << "Profile: '"<< pp->label
                    << "' executed " << pp->executionTimes << " times, total execution time: "
                    << pp->exceptionTime / 1000000.0 << "ms, "
                    << "100% \n";
            });

            std::cout << ss.str();
        }
    }
}

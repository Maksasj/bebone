#include "profiler.h"

namespace bebone::core {
    std::vector<Profile*> Profiler::stack;
    std::vector<Profile*> Profiler::entryPoints;

    Profile::Profile(std::string label) {
        _label = label;

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
        ++_execution_times;

        record_start_timestamp = std::chrono::high_resolution_clock::now();
    }

    void Profile::push_child_profile(Profile *profile) {
        childs.push_back(profile);
    }

    void Profile::stop() {
        auto record_stop_timestamp = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(record_stop_timestamp - record_start_timestamp).count();
        _exception_time += duration;
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

    void trace_profiles(std::stringstream *ss, Profile *profile, Profile *parent, unsigned long depth) {
        auto childs = profile->get_childs();

        for(auto i = childs.first; i < childs.second; ++i) {
            for(auto k = 0; k < depth; ++k)
                (*ss) << "    ";

            (*ss) << "Profile: '"<<(*i)->_label << "' executed " << (*i)->_execution_times << " times, total execution time: " << (*i)->_exception_time / 1000000.0 << "ms, " << 100.0*((*i)->_exception_time / profile->_exception_time) << "% | " << 100.0*((*i)->_exception_time / parent->_exception_time) << "% \n";

            trace_profiles(ss, (*i), profile, depth + 1);
        }
    }

    void Profiler::sumup() {
        for(auto profile : entryPoints) {
            std::stringstream ss;

            ss  << "Profile: '"<<profile->_label
                << "' executed " << profile->_execution_times << " times, total execution time: "
                << profile->_exception_time / 1000000.0 << "ms, "
                << "100% \n";

            trace_profiles(&ss, profile, profile, 1);

            std::cout << ss.str();
        }
    }
}

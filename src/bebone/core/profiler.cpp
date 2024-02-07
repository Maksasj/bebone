#include "profiler.h"

std::vector<bebone::core::Profile*> bebone::core::Profiler::stack;
std::vector<bebone::core::Profile*> bebone::core::Profiler::entryPoints;

bebone::core::Profile::Profile(std::string label) {
    _label = label;

    Profiler::BindTopProfile(this);
}

bebone::core::ProfilerCloser::ProfilerCloser() {
    Profiler::UnBindTopProfile();
}

unsigned long bebone::core::Profile::CountChildProfiles() {
    return childs.size();
}

std::pair<std::vector<bebone::core::Profile*>::iterator, std::vector<bebone::core::Profile*>::iterator> bebone::core::Profile::GetChilds() {
    return std::make_pair(childs.begin(), childs.end());
}

void bebone::core::Profile::Record() {
    ++_execution_times;

    record_start_timestamp = std::chrono::high_resolution_clock::now();
}

void bebone::core::Profile::PushChildProfile(Profile *profile) {
    childs.push_back(profile);
}

void bebone::core::Profile::Stop() {
    auto record_stop_timestamp = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(record_stop_timestamp - record_start_timestamp).count();
    _exception_time += duration;
}

void bebone::core::Profiler::BindTopProfile(Profile *profile) {
    if(stack.size() == 0) {
        entryPoints.push_back(profile);
    } else {
        stack[stack.size() - 1]->PushChildProfile(profile);
    }

    stack.push_back(profile);
}

void bebone::core::Profiler::UnBindTopProfile() {
    stack.pop_back();
}

void bebone::core::traceProfiles(std::stringstream *ss, bebone::core::Profile *profile, bebone::core::Profile *parent, unsigned long depth) {
    auto childs = profile->GetChilds();

    for(auto i = childs.first; i < childs.second; ++i) {
        for(auto k = 0; k < depth; ++k)
            (*ss) << "    ";

        (*ss) << "Profile: '"<<(*i)->_label << "' executed " << (*i)->_execution_times << " times, total execution time: " << (*i)->_exception_time / 1000000.0 << "ms, " << 100.0*((*i)->_exception_time / profile->_exception_time) << "% | " << 100.0*((*i)->_exception_time / parent->_exception_time) << "% \n";

        bebone::core::traceProfiles(ss, (*i), profile, depth + 1);
    }
}

void bebone::core::Profiler::SumUp() {
    for(auto profile : entryPoints) {
        std::stringstream ss;

        ss  << "Profile: '"<<profile->_label
            << "' executed " << profile->_execution_times << " times, total execution time: "
            << profile->_exception_time / 1000000.0 << "ms, "
            << "100% \n";

        traceProfiles(&ss, profile, profile, 1);

        std::cout << ss.str();
    }
}
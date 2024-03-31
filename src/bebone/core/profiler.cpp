#include "profiler.h"

#include <utility>

namespace bebone::core {
    Profile::Profile(std::string label)
            : label(std::move(label)),
              executionCount(0),
              totalExecutionTime(0.0),
              minExecutionTime(std::numeric_limits<f64>::max()),
              maxExecutionTime(0.0)
    {
        Profiler::get_instance().push_profile(this);
    }

    Profile::Profile(const char* label)
        : label(label),
          executionCount(0),
          totalExecutionTime(0.0),
          minExecutionTime(std::numeric_limits<f64>::max()),
          maxExecutionTime(0.0)
    {
        Profiler::get_instance().push_profile(this);
    }

    u32 Profile::count_child_profiles() {
        return childs.size();
    }

    std::vector<Profile*>& Profile::get_childs() {
        return childs;
    }

    void Profile::record() {
        Profiler::get_instance().bind_top_profile(this);

        ++executionCount;

        recordStartTimestamp = std::chrono::high_resolution_clock::now();
    }

    void Profile::stop() {
        Profiler::get_instance().unbind_top_profile();

        auto record_stop_timestamp = std::chrono::high_resolution_clock::now();
        
        f64 duration = std::chrono::duration_cast<std::chrono::nanoseconds>(record_stop_timestamp - recordStartTimestamp).count();

        totalExecutionTime += duration;
        minExecutionTime = std::min(minExecutionTime, duration);
        maxExecutionTime = std::max(maxExecutionTime, duration);
    }

    void Profile::push_child_profile(Profile *profile) {
        childs.push_back(profile);
    }

    Profiler::Profiler() : stack(), stackIndex(0) {

    }

    void Profiler::push_profile(Profile* profile) {
        if(stackIndex == 0)
            entryPoints.push_back(profile);
        else
            stack[stackIndex - 1]->push_child_profile(profile);
    }

    void Profiler::bind_top_profile(Profile *profile) {
        stack[stackIndex] = profile;
        ++stackIndex;
    }

    void Profiler::unbind_top_profile() {
        if(stackIndex <= 0) {
            // Todo throw profiler exception
        } else {
            stack[stackIndex] = nullptr;
            --stackIndex;
        }
    }

    void trace_profiles(
        Profile *profile,
        Profile *parent,
        unsigned long depth,
        const std::function<void(Profile*, unsigned int depth)>& lamda
    ) {
        std::ignore = parent;

        const auto& childs = profile->get_childs();

        for(auto& pp : childs) {
            lamda(pp, depth + 1);

            trace_profiles(pp, profile, depth + 1, lamda);
        }
    }

    const unsigned int& Profiler::get_stack_index() const {
        return stackIndex;
    }

    const std::array<Profile*, 1024>& Profiler::get_stack() const {
        return stack;
    }

    const std::vector<Profile*>& Profiler::get_entry_points() const {
        return entryPoints;
    }

    std::string Profiler::sum_up() const {
        std::stringstream ss;

        for(auto& profile : entryPoints) {

            ss << "Profile: '" << profile->label << "' ("
               << "times = " << profile->executionCount << ", "
               << "total = " << profile->totalExecutionTime / 1000000.0 << " ms, "
               << "min = " << profile->minExecutionTime / 1000000.0 << " ms, "
               << "max = " << profile->maxExecutionTime / 1000000.0 << " ms, "
               << "avg = " << (profile->totalExecutionTime / profile->executionCount) / 1000000.0 << " ms) \n";

            trace_profiles(profile, profile, 1, [&](Profile* pp, unsigned int depth) {
                for(unsigned int i = 0; i < depth; ++i)
                    ss << "    ";

                ss << "Profile :'" << pp->label << "' ("
                    << "times = " << pp->executionCount << ", "
                    << "total = " << pp->totalExecutionTime / 1000000.0 << " ms, "
                    << "min = " << pp->minExecutionTime / 1000000.0 << " ms, "
                    << "max = " << pp->maxExecutionTime / 1000000.0 << " ms, "
                    << "avg = " << (pp->totalExecutionTime / pp->executionCount) / 1000000.0 << " ms) \n";
            });

        }

        return ss.str();
    }

    Profiler& Profiler::get_instance() {
        static Profiler profiler;
        return profiler;
    }
}

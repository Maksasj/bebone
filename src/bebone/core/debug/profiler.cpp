#include "profiler.h"

#include <utility>

namespace bebone::core {
    Profile::Profile(std::string label)
            : label(std::move(label)),
              execution_count(0),
              total_execution_time(0.0),
              min_execution_time(std::numeric_limits<f64>::max()),
              max_execution_time(0.0)
    {
        Profiler::get_instance().push_profile(this);
    }

    Profile::Profile(const char* label)
        : label(label),
          execution_count(0),
          total_execution_time(0.0),
          min_execution_time(std::numeric_limits<f64>::max()),
          max_execution_time(0.0)
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

        ++execution_count;

        record_start_timestamp = std::chrono::high_resolution_clock::now();
    }

    void Profile::stop() {
        Profiler::get_instance().unbind_top_profile();

        auto record_stop_timestamp = std::chrono::high_resolution_clock::now();
        
        f64 duration = std::chrono::duration_cast<std::chrono::nanoseconds>(record_stop_timestamp - record_start_timestamp).count();

        total_execution_time += duration;
        min_execution_time = std::min(min_execution_time, duration);
        max_execution_time = std::max(max_execution_time, duration);
    }

    void Profile::push_child_profile(Profile *profile) {
        childs.push_back(profile);
    }

    Profiler::Profiler() : stack(), stack_index(0) {

    }

    void Profiler::push_profile(Profile* profile) {
        if(stack_index == 0)
            entry_points.push_back(profile);
        else
            stack[stack_index - 1]->push_child_profile(profile);
    }

    void Profiler::bind_top_profile(Profile *profile) {
        stack[stack_index] = profile;
        ++stack_index;
    }

    void Profiler::unbind_top_profile() {
        if(stack_index <= 0) {
            // Todo throw profiler exception
        } else {
            stack[stack_index] = nullptr;
            --stack_index;
        }
    }

    void trace_profiles(
        Profile *profile,
        Profile *parent,
        unsigned long depth,
        const std::function<void(Profile* profile, Profile* parent, unsigned int depth)>& lamda
    ) {
        std::ignore = parent;

        const auto& childs = profile->get_childs();

        for(auto& pp : childs) {
            lamda(pp, profile, depth + 1);

            trace_profiles(pp, profile, depth + 1, lamda);
        }
    }

    const unsigned int& Profiler::get_stack_index() const {
        return stack_index;
    }

    const std::array<Profile*, 1024>& Profiler::get_stack() const {
        return stack;
    }

    const std::vector<Profile*>& Profiler::get_entry_points() const {
        return entry_points;
    }

    std::string Profiler::result() const {
        std::stringstream ss;

        for(auto& profile : entry_points) {
            ss << "Profile: '" << profile->label << "' ("
               << "times = " << profile->execution_count << ", "
               << "total = " << profile->total_execution_time / 1000000.0 << " ms, "
               << "min = " << profile->min_execution_time / 1000000.0 << " ms, "
               << "max = " << profile->max_execution_time / 1000000.0 << " ms, "
               << "avg = " << (profile->total_execution_time / profile->execution_count) / 1000000.0 << " ms, "
               << "perc = 100.0 %) \n";

            trace_profiles(profile, profile, 1, [&](Profile* pp, Profile* parent, unsigned int depth) {
                for(unsigned int i = 0; i < depth; ++i)
                    ss << "    ";

                ss << "Profile :'" << pp->label << "' ("
                    << "times = " << pp->execution_count << ", "
                    << "total = " << pp->total_execution_time / 1000000.0 << " ms, "
                    << "min = " << pp->min_execution_time / 1000000.0 << " ms, "
                    << "max = " << pp->max_execution_time / 1000000.0 << " ms, "
                    << "avg = " << (pp->total_execution_time / pp->execution_count) / 1000000.0 << " ms, "
                    << "perc = " << (pp->total_execution_time / parent->total_execution_time) * 100.0 << "%) \n";
            });
        }

        return ss.str();
    }

    Profiler& Profiler::get_instance() {
        static Profiler profiler;
        return profiler;
    }
}

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

#include "../types.h"

namespace bebone::core {
    // Debug profile class
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

            /*!
            * Default profile constructor
            * @param label - Profile label
            */
            explicit Profile(std::string label);

            /*!
            * Default profile constructor
            * @param label - Profile label
            */
            explicit Profile(const char* label);

            // Start profile record
            void record();

            // Stop profile record
            void stop();

            /*!
            * Pushes child profile
            * @param label - Pointer to child profile
            */
            void push_child_profile(Profile *profile);

            // Getter for child profile count
            u32 count_child_profiles();

            /*!
            * Reference childs container
            * @return childs container
            */
            std::vector<Profile*>& get_childs();
    };

    class Profiler {
        private:
            // Hidden constructor
            Profiler();

            std::array<Profile*, 1024> stack;
            unsigned int stackIndex;

            std::vector<Profile*> entryPoints;

        public:
            /*!
            * Pushes profile to profiler
            * @param profile - Pointer to profile
            */
            void push_profile(Profile* profile);

            /*!
            * Binds top level profile
            * @param profile - Pointer to profile
            */
            void bind_top_profile(Profile *profile);

            // Unbinds top level profile
            void unbind_top_profile();

            // Getter for current stack index
            const unsigned int& get_stack_index() const;

            // Getter for profile stack
            const std::array<Profile*, 1024>& get_stack() const;

            // Getter for profiler entry points profiles
            const std::vector<Profile*>& get_entry_points() const;

            /*!
            * Sum ups all profile data, creates single string representation of program performance
            * @param profile - Result string
            */
            std::string result() const;

            // Returns a reference to a single top instance
            static Profiler& get_instance();
    };

    /*!
    * Function that can be used to trace profile tree
    * @param profile - Profile
    * @param parent - Parent profile
    * @param depth - Profile tree depth
    * @param lamda - Function lambda, that will be used for every profile in a tree
    */
    void trace_profiles(
        Profile *profile,
        Profile *parent,
        unsigned long depth,
        const std::function<void(Profile* profile, Profile* parent, unsigned int depth)>& lamda
    );
}

#ifdef DEBUG
    #define BEBONE_PROFILE_RECORD(LABEL) static bebone::core::Profile LABEL(#LABEL); LABEL.record();
    #define BEBONE_PROFILE_STOP(LABEL) LABEL.stop();
    #define BEBONE_PROFILER_SUM_UP() Profiler::get_instance().result()
#else
    #define BEBONE_PROFILE_RECORD(LABEL)
    #define BEBONE_PROFILE_STOP(LABEL)
    #define BEBONE_PROFILER_SUM_UP() ""
#endif

#endif
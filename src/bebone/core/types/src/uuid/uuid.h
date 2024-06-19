/**
 * @file 
 * uuid.tpp
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _OMNI_TYPES_UUID_TYPE_H_
#define _OMNI_TYPES_UUID_TYPE_H_

#include "../primitive_types.h"

#include <sstream>
#include <string>
#include <iomanip>
#include <random>
#include <cmath>

namespace omni::types {
    class UUID {
        private:
            u64 _data[2];
        
            UUID(const u64& data1, const u64& data2);

        public:
            UUID();
            
            bool operator==(const UUID& other) const;
            bool operator!=(const UUID& other) const;

            std::string to_string() const;

            static UUID gen();
    };
}

#endif

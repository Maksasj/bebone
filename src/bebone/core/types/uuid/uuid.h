#ifndef _BEBONE_CORE_TYPES_UUID_TYPE_H_
#define _BEBONE_CORE_TYPES_UUID_TYPE_H_

#include "../primitive_types.h"

#include <sstream>
#include <string>
#include <iomanip>
#include <random>
#include <cmath>

namespace bebone::core {
    class UUID {
        private:
            u64 data[2];
        
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

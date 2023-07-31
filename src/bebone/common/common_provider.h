#ifndef _BEBONE_COMMON_PROVIDER_H_
#define _BEBONE_COMMON_PROVIDER_H_

namespace bebone::common {
    template<class RequiredClass>
    class CommonProvider {

        static RequiredClass provide() {
            
            
            return RequiredClass();
        }
    };
}

#endif

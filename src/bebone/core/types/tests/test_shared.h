#ifndef _OMNI_TYPES_TESTING_TEST_SHARED_H_
#define _OMNI_TYPES_TESTING_TEST_SHARED_H_

#include "omni_types.tpp"

#define ensure(EXP) if(!(EXP)) return 1;
#define ensure_const(EXP) if constexpr (!(EXP)) return 1;
#define TEST_CASE

#endif
#ifndef _BEBONE_TESTING_TEST_SHARED_H_
#define _BEBONE_TESTING_TEST_SHARED_H_

#define ensure(EXP) if(!(EXP)) return 1;
#define ensure_const(EXP) if constexpr (!(EXP)) return 1;
#define TEST_CASE

#endif
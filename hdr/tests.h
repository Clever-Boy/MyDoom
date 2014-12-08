#ifndef __TESTS_H
#define __TESTS_H

#include <stdio.h>

#define TEST_ASSERT(x) if(!(x)) { printf("TEST FAILED in %s (%s:%d)\n", __PRETTY_FUNCTION__, __FILE__, __LINE__); tests_inc_failures(); } else { tests_inc_successes(); }

void tests_run(void);
void tests_inc_failures(void);
void tests_inc_successes(void);

#endif
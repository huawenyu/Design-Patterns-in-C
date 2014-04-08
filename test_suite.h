
#ifndef TEST_SUITE_H_
#define TEST_SUITE_H_

#include <stddef.h> /* size_t */

/**test suite:
     - define MACRO (as the follow)
     - add testcase to my_test_suite_open()

#define MY_RUN_TEST_FROM_CLI
*/
#define MY_RUN_TEST_FROM_CLI

#define MY_DEBUG printf
#define MY_DEBUG_TEST 

enum my_test_suite_flag {
	MY_TEST_SUITE_FLAG_DRYRUN    = 1<<0, /* dry-run */
	MY_TEST_SUITE_FLAG_VERBOSE   = 1<<1, /* show succ + fail */
	MY_TEST_SUITE_FLAG_FAIL_CONT = 1<<2, /* continue if fail */
	MY_TEST_SUITE_FLAG_RESTART   = 1<<3, /* run test from begin */
};

/* test case function
 * @return 0-succ, other-fail with _outmsg_ reason */
typedef int (*test_case_fp)(char *outmsg, size_t sz);
void my_test_suite_open(void);
void my_test_suite_close(void);
void my_test_suite_add(test_case_fp, const char *note);
void my_test_suite_run_all(unsigned int flags); /* default 0, my_test_suite_flag */

#endif /* TEST_SUITE_H_ */

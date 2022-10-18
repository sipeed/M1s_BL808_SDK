#ifndef __TEST_QUEUE_H__
#define __TEST_QUEUE_H__

#ifdef __cplusplus
extern "C"
{
#endif

void test_queue_within_two_tasks_main(void);
void test_queue_full_main(void);
void test_queue_empty_main(void);
void test_queue_put_fromISR_main(void);
void test_queue_get_fromISR_main(void);

#ifdef __cplusplus
}
#endif

#endif // __TEST_QUEUE_H__

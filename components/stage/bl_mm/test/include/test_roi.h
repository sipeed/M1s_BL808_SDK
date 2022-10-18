#ifndef __TEST_ROI_H__
#define __TEST_ROI_H__

#ifdef __cplusplus
extern "C"
{
#endif

int test_mono_roi_main(int id);
int test_multi_roi_main(int id);
int test_roi_main(int stream_id);
int test_roi_running_main(int stream_id, int frame_cnt);

#ifdef __cplusplus
}
#endif

#endif // __TEST_ROI_H__

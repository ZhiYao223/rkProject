#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_save_sample_setting(lv_event_t * e);
extern void action_save_shift_setting(lv_event_t * e);
extern void action_save_communicate_setting(lv_event_t * e);
extern void action_btn_motor_stop(lv_event_t * e);
extern void thread_auto_take(void);
#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/
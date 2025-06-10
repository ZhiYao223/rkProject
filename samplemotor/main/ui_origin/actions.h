#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_save_setting_func(lv_event_t * e);
extern void action_manual_take(lv_event_t * e);
extern void action_took_mark(lv_event_t * e);
extern void action_manual_take_ccw(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/

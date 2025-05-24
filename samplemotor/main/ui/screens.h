#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *setting;
    lv_obj_t *btn_setting;
    lv_obj_t *btn_mark_took;
    lv_obj_t *btn_manual_take;
    lv_obj_t *btn_manual_take_ccw;
    lv_obj_t *input_cw;
    lv_obj_t *input_ccw;
    lv_obj_t *btn_save_setting;
    lv_obj_t *input_hour;
    lv_obj_t *input_cw_manual_time;
    lv_obj_t *input_ccw_manual_time;
    lv_obj_t *input_motor_stop;
    lv_obj_t *main_label;
    lv_obj_t *label_btn_sample_setting;
    lv_obj_t *label_btn_mark_took;
    lv_obj_t *label_btn_manual_take;
    lv_obj_t *label_btn_manual_take_ccw;
    lv_obj_t *number_input_keyboard;
    lv_obj_t *label_interval;
    lv_obj_t *label_rotate_cw;
    lv_obj_t *label_rotate_cw_unit;
    lv_obj_t *label_rotate_ccw;
    lv_obj_t *label_rotate_ccw_unit;
    lv_obj_t *label_btn_save_setting;
    lv_obj_t *label_interval_unit;
    lv_obj_t *label_rotate_cw_manual;
    lv_obj_t *label_rotate_cw_manual_unit;
    lv_obj_t *label_rotate_cww_manual;
    lv_obj_t *label_rotate_ccw_manual_unit;
    lv_obj_t *label_motor_stop;
    lv_obj_t *label_stop_time_unit;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_SETTING = 2,
};

void create_screen_main();
void tick_screen_main();

void create_screen_setting();
void tick_screen_setting();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/

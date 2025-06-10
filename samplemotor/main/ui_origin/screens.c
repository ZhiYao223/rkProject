#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_btn_setting(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;

    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 2, 0, e);
    }
}

static void event_handler_cb_main_btn_mark_took(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;

    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_took_mark(e);
    }
}

static void event_handler_cb_main_btn_manual_take(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;

    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_manual_take(e);
    }
}

static void event_handler_cb_main_btn_manual_take_ccw(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;

    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_manual_take_ccw(e);
    }
}

static void event_handler_cb_setting_input_cw(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;

    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            const char *value = lv_textarea_get_text(ta);
            assignStringProperty(flowState, 4, 3, value, "Failed to assign Text in Textarea widget");
        }
    }

    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 4, 0, e);
    }
}

static void event_handler_cb_setting_input_ccw(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;

    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            const char *value = lv_textarea_get_text(ta);
            assignStringProperty(flowState, 7, 3, value, "Failed to assign Text in Textarea widget");
        }
    }

    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 7, 0, e);
    }
}

static void event_handler_cb_setting_btn_save_setting(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;

    if (event == LV_EVENT_PRESSING) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 9, 0, e);
    }
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_save_setting_func(e);
    }
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 9, 1, e);
    }
}

static void event_handler_cb_setting_input_hour(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;

    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            const char *value = lv_textarea_get_text(ta);
            assignStringProperty(flowState, 11, 3, value, "Failed to assign Text in Textarea widget");
        }
    }

    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 11, 0, e);
    }
}

static void event_handler_cb_setting_input_cw_manual_time(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;

    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            const char *value = lv_textarea_get_text(ta);
            assignStringProperty(flowState, 14, 3, value, "Failed to assign Text in Textarea widget");
        }
    }

    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 14, 0, e);
    }
}

static void event_handler_cb_setting_input_ccw_manual_time(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;

    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            const char *value = lv_textarea_get_text(ta);
            assignStringProperty(flowState, 17, 3, value, "Failed to assign Text in Textarea widget");
        }
    }

    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 17, 0, e);
    }
}

static void event_handler_cb_setting_input_motor_stop(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;

    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            const char *value = lv_textarea_get_text(ta);
            assignStringProperty(flowState, 20, 3, value, "Failed to assign Text in Textarea widget");
        }
    }

    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 20, 0, e);
    }
}

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 768);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3631db), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // main_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.main_label = obj;
            lv_obj_set_pos(obj, 0, 280);
            lv_obj_set_size(obj, 1024, 80);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfff9f6f6), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "China");
        }
        {
            // btn_setting
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.btn_setting = obj;
            lv_obj_set_pos(obj, 780, 675);
            lv_obj_set_size(obj, 204, 71);
            lv_obj_add_event_cb(obj, event_handler_cb_main_btn_setting, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_sample_setting
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_sample_setting = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Setting");
                }
            }
        }
        {
            // btn_mark_took
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.btn_mark_took = obj;
            lv_obj_set_pos(obj, 536, 675);
            lv_obj_set_size(obj, 216, 71);
            lv_obj_add_event_cb(obj, event_handler_cb_main_btn_mark_took, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_mark_took
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_mark_took = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Take");
                }
            }
        }
        {
            // btn_manual_take
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.btn_manual_take = obj;
            lv_obj_set_pos(obj, 40, 675);
            lv_obj_set_size(obj, 214, 71);
            lv_obj_add_event_cb(obj, event_handler_cb_main_btn_manual_take, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_manual_take
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_manual_take = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Manual take");
                }
            }
        }
        {
            // btn_manual_take_ccw
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.btn_manual_take_ccw = obj;
            lv_obj_set_pos(obj, 288, 676);
            lv_obj_set_size(obj, 214, 71);
            lv_obj_add_event_cb(obj, event_handler_cb_main_btn_manual_take_ccw, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_manual_take_ccw
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_manual_take_ccw = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Manual take");
                }
            }
        }
    }

    tick_screen_main();
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
}

void create_screen_setting() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.setting = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 768);
    {
        lv_obj_t *parent_obj = obj;
        {
            // number_input_keyboard
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.number_input_keyboard = obj;
            lv_obj_set_pos(obj, 0, 424);
            lv_obj_set_size(obj, 1024, 239);
            lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // label_interval
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_interval = obj;
            lv_obj_set_pos(obj, 189, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Interval:");
        }
        {
            // label_rotate_cw
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_rotate_cw = obj;
            lv_obj_set_pos(obj, 190, 170);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "CW:");
        }
        {
            // input_cw
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.input_cw = obj;
            lv_obj_set_pos(obj, 513, 160);
            lv_obj_set_size(obj, 276, 50);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, event_handler_cb_setting_input_cw, LV_EVENT_ALL, flowState);
        }
        {
            // label_rotate_cw_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_rotate_cw_unit = obj;
            lv_obj_set_pos(obj, 818, 170);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "S");
        }
        {
            // label_rotate_ccw
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_rotate_ccw = obj;
            lv_obj_set_pos(obj, 191, 231);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "CCW:");
        }
        {
            // input_ccw
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.input_ccw = obj;
            lv_obj_set_pos(obj, 514, 221);
            lv_obj_set_size(obj, 276, 50);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, event_handler_cb_setting_input_ccw, LV_EVENT_ALL, flowState);
        }
        {
            // label_rotate_ccw_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_rotate_ccw_unit = obj;
            lv_obj_set_pos(obj, 817, 223);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "S");
        }
        {
            // btn_save_setting
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.btn_save_setting = obj;
            lv_obj_set_pos(obj, 739, 664);
            lv_obj_set_size(obj, 258, 79);
            lv_obj_add_event_cb(obj, event_handler_cb_setting_btn_save_setting, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_save_setting
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_save_setting = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Save");
                }
            }
        }
        {
            // input_hour
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.input_hour = obj;
            lv_obj_set_pos(obj, 512, 39);
            lv_obj_set_size(obj, 276, 50);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, event_handler_cb_setting_input_hour, LV_EVENT_ALL, flowState);
        }
        {
            // label_interval_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_interval_unit = obj;
            lv_obj_set_pos(obj, 813, 41);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "M");
        }
        {
            // label_rotate_cw_manual
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_rotate_cw_manual = obj;
            lv_obj_set_pos(obj, 190, 289);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "manual_take");
        }
        {
            // input_cw_manual_time
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.input_cw_manual_time = obj;
            lv_obj_set_pos(obj, 513, 279);
            lv_obj_set_size(obj, 276, 50);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, event_handler_cb_setting_input_cw_manual_time, LV_EVENT_ALL, flowState);
        }
        {
            // label_rotate_cw_manual_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_rotate_cw_manual_unit = obj;
            lv_obj_set_pos(obj, 816, 281);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "S");
        }
        {
            // label_rotate_cww_manual
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_rotate_cww_manual = obj;
            lv_obj_set_pos(obj, 189, 351);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "manual_push");
        }
        {
            // input_ccw_manual_time
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.input_ccw_manual_time = obj;
            lv_obj_set_pos(obj, 512, 341);
            lv_obj_set_size(obj, 276, 50);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, event_handler_cb_setting_input_ccw_manual_time, LV_EVENT_ALL, flowState);
        }
        {
            // label_rotate_ccw_manual_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_rotate_ccw_manual_unit = obj;
            lv_obj_set_pos(obj, 815, 343);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "S");
        }
        {
            // label_motor_stop
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_motor_stop = obj;
            lv_obj_set_pos(obj, 190, 109);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "stop_interval");
        }
        {
            // input_motor_stop
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.input_motor_stop = obj;
            lv_obj_set_pos(obj, 513, 99);
            lv_obj_set_size(obj, 276, 50);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, event_handler_cb_setting_input_motor_stop, LV_EVENT_ALL, flowState);
        }
        {
            // label_stop_time_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_stop_time_unit = obj;
            lv_obj_set_pos(obj, 818, 109);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "S");
        }
    }

    tick_screen_setting();
}

void tick_screen_setting() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 4, 3, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.input_cw);
        uint32_t max_length = lv_textarea_get_max_length(objects.input_cw);
        if (strncmp(new_val, cur_val, max_length) != 0) {
            tick_value_change_obj = objects.input_cw;
            lv_textarea_set_text(objects.input_cw, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 7, 3, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.input_ccw);
        uint32_t max_length = lv_textarea_get_max_length(objects.input_ccw);
        if (strncmp(new_val, cur_val, max_length) != 0) {
            tick_value_change_obj = objects.input_ccw;
            lv_textarea_set_text(objects.input_ccw, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 11, 3, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.input_hour);
        uint32_t max_length = lv_textarea_get_max_length(objects.input_hour);
        if (strncmp(new_val, cur_val, max_length) != 0) {
            tick_value_change_obj = objects.input_hour;
            lv_textarea_set_text(objects.input_hour, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 14, 3, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.input_cw_manual_time);
        uint32_t max_length = lv_textarea_get_max_length(objects.input_cw_manual_time);
        if (strncmp(new_val, cur_val, max_length) != 0) {
            tick_value_change_obj = objects.input_cw_manual_time;
            lv_textarea_set_text(objects.input_cw_manual_time, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 17, 3, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.input_ccw_manual_time);
        uint32_t max_length = lv_textarea_get_max_length(objects.input_ccw_manual_time);
        if (strncmp(new_val, cur_val, max_length) != 0) {
            tick_value_change_obj = objects.input_ccw_manual_time;
            lv_textarea_set_text(objects.input_ccw_manual_time, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.input_motor_stop);
        uint32_t max_length = lv_textarea_get_max_length(objects.input_motor_stop);
        if (strncmp(new_val, cur_val, max_length) != 0) {
            tick_value_change_obj = objects.input_motor_stop;
            lv_textarea_set_text(objects.input_motor_stop, new_val);
            tick_value_change_obj = NULL;
        }
    }
}


static const char *screen_names[] = { "Main", "Setting" };
static const char *object_names[] = { "main", "setting", "btn_setting", "btn_mark_took", "btn_manual_take", "btn_manual_take_ccw", "input_cw", "input_ccw", "btn_save_setting", "input_hour", "input_cw_manual_time", "input_ccw_manual_time", "input_motor_stop", "main_label", "label_btn_sample_setting", "label_btn_mark_took", "label_btn_manual_take", "label_btn_manual_take_ccw", "number_input_keyboard", "label_interval", "label_rotate_cw", "label_rotate_cw_unit", "label_rotate_ccw", "label_rotate_ccw_unit", "label_btn_save_setting", "label_interval_unit", "label_rotate_cw_manual", "label_rotate_cw_manual_unit", "label_rotate_cww_manual", "label_rotate_ccw_manual_unit", "label_motor_stop", "label_stop_time_unit" };


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_setting,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));

    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    create_screen_main();
    create_screen_setting();
}

#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

groups_t groups;
static bool groups_created = false;

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_page_main_page(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: left_button
        lv_group_remove_all_objs(groups.left_button);
    }
}

static void event_handler_cb_main_page_setting8(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 3, 0, e);
    }
}

static void event_handler_cb_shift_setting_page_shift_setting_page(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: left_button
        lv_group_remove_all_objs(groups.left_button);
    }
}

static void event_handler_cb_shift_setting_page_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 2, 0, e);
    }
}

static void event_handler_cb_shift_setting_page_btn_save_shift_setting(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_save_shift_setting(e);
    }
}

static void event_handler_cb_shift_setting_page_obj1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 7, 0, e);
    }
}

static void event_handler_cb_shift_setting_page_obj2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 9, 0, e);
    }
}

static void event_handler_cb_shift_setting_page_obj3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 11, 0, e);
    }
}

static void event_handler_cb_shift_setting_page_obj4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 13, 0, e);
    }
}

static void event_handler_cb_sample_setting_page_sample_setting_page(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: left_button
        lv_group_remove_all_objs(groups.left_button);
    }
}

static void event_handler_cb_sample_setting_page_obj5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 0, 0, e);
    }
}

static void event_handler_cb_sample_setting_page_obj6(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 2, 0, e);
    }
}

static void event_handler_cb_sample_setting_page_obj7(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 7, 0, e);
    }
}

static void event_handler_cb_sample_setting_page_obj8(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 9, 0, e);
    }
}

static void event_handler_cb_sample_setting_page_obj9(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 11, 0, e);
    }
}

static void event_handler_cb_sample_setting_page_obj10(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 13, 0, e);
    }
}

static void event_handler_cb_sample_setting_page_motor_ccw_seconds(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 19, 0, e);
    }
}

static void event_handler_cb_sample_setting_page_motor_cw_seconds(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 20, 0, e);
    }
}

static void event_handler_cb_sample_setting_page_motor_stop_seconds(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 21, 0, e);
    }
}

static void event_handler_cb_sample_setting_page_btn_save_sample_setting(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_save_sample_setting(e);
    }
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 26, 0, e);
    }
}

static void event_handler_cb_sample_setting_page_btn_auto_take_cw(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 32, 0, e);
    }
}

static void event_handler_cb_sample_setting_page_obj11(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 35, 0, e);
    }
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_motor_stop(e);
    }
}

static void event_handler_cb_communicate_setting_page_communicate_setting_page(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: left_button
        lv_group_remove_all_objs(groups.left_button);
    }
}

static void event_handler_cb_communicate_setting_page_obj12(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 0, 0, e);
    }
}

static void event_handler_cb_communicate_setting_page_obj13(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 2, 0, e);
    }
}

static void event_handler_cb_communicate_setting_page_obj14(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 5, 0, e);
    }
}

static void event_handler_cb_communicate_setting_page_obj15(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 7, 0, e);
    }
}

static void event_handler_cb_communicate_setting_page_obj16(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 9, 0, e);
    }
}

static void event_handler_cb_communicate_setting_page_obj17(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 11, 0, e);
    }
}

static void event_handler_cb_communicate_setting_page_input_address(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 17, 0, e);
    }
}

static void event_handler_cb_communicate_setting_page_input_gateway(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 18, 0, e);
    }
}

static void event_handler_cb_communicate_setting_page_input_dns(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 19, 0, e);
    }
}

static void event_handler_cb_communicate_setting_page_btn_save_communicate_setting(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_save_communicate_setting(e);
    }
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 21, 0, e);
    }
}

static void event_handler_cb_motor_test_setting_page_motor_test_setting_page(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: left_button
        lv_group_remove_all_objs(groups.left_button);
    }
}

static void event_handler_cb_motor_test_setting_page_obj18(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 0, 0, e);
    }
}

static void event_handler_cb_motor_test_setting_page_obj19(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 2, 0, e);
    }
}

static void event_handler_cb_motor_test_setting_page_obj20(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 5, 0, e);
    }
}

static void event_handler_cb_motor_test_setting_page_obj21(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 7, 0, e);
    }
}

static void event_handler_cb_motor_test_setting_page_obj22(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 9, 0, e);
    }
}

static void event_handler_cb_motor_test_setting_page_obj23(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 11, 0, e);
    }
}

static void event_handler_cb_motor_test_setting_page_btn_sample_motor_cw(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_LONG_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 17, 0, e);
    }
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 17, 1, e);
    }
}

static void event_handler_cb_motor_test_setting_page_btn_sample_motor_ccw(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_LONG_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 19, 0, e);
    }
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 19, 1, e);
    }
}

static void event_handler_cb_motor_test_setting_page_btn_rotate_motor_ccw(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_LONG_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 21, 0, e);
    }
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 21, 1, e);
    }
}

static void event_handler_cb_motor_test_setting_page_btn_rotate_motor_cw(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_LONG_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 23, 0, e);
    }
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 23, 1, e);
    }
}

static void event_handler_cb_motor_test_setting_page_input_rotational_speed(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 25, 0, e);
    }
}

static void event_handler_cb_motor_test_setting_page_btn_save_motor_test_setting(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 27, 0, e);
    }
}

static void event_handler_cb_warning_page_warning_page(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: left_button
        lv_group_remove_all_objs(groups.left_button);
    }
}

static void event_handler_cb_warning_page_btn_warning_ok(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 3, 0, e);
    }
}

void create_screen_main_page() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.main_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 768);
    lv_obj_add_event_cb(obj, event_handler_cb_main_page_main_page, LV_EVENT_ALL, flowState);
    {
        lv_obj_t *parent_obj = obj;
        {
            // main1
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.main1 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_backgraound);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj24 = obj;
            lv_obj_set_pos(obj, 342, 16);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "AI煤灰自动取样系统");
        }
        {
            // setting8
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.setting8 = obj;
            lv_obj_set_pos(obj, 947, 12);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_setting7);
            lv_obj_add_event_cb(obj, event_handler_cb_main_page_setting8, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_state(obj, LV_STATE_PRESSED);
        }
        {
            // information
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.information = obj;
            lv_obj_set_pos(obj, 695, 95);
            lv_obj_set_size(obj, 329, 211);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj25 = obj;
                    lv_obj_set_pos(obj, 22, 14);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "工作温度：");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj26 = obj;
                    lv_obj_set_pos(obj, 233, 14);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "℃");
                }
                {
                    // Temperature
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.temperature = obj;
                    lv_obj_set_pos(obj, 172, 14);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj27 = obj;
                    lv_obj_set_pos(obj, 22, 86);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "日期：");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj28 = obj;
                    lv_obj_set_pos(obj, 22, 166);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "时间：");
                }
                {
                    // TIME_h
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_h = obj;
                    lv_obj_set_pos(obj, 149, 166);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // DATE_y
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.date_y = obj;
                    lv_obj_set_pos(obj, 142, 86);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // TIME_m
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_m = obj;
                    lv_obj_set_pos(obj, 219, 166);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj29 = obj;
                    lv_obj_set_pos(obj, 180, 166);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "：");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj30 = obj;
                    lv_obj_set_pos(obj, 206, 86);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, ".");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj31 = obj;
                    lv_obj_set_pos(obj, 253, 86);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, ".");
                }
                {
                    // DATE_m
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.date_m = obj;
                    lv_obj_set_pos(obj, 228, 86);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // DATE_d
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.date_d = obj;
                    lv_obj_set_pos(obj, 279, 86);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // btn_factory_reset
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.btn_factory_reset = obj;
            lv_obj_set_pos(obj, 821, 652);
            lv_obj_set_size(obj, 156, 72);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff009ea2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "恢复出厂设置");
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 20, 80);
            lv_obj_set_size(obj, 650, 290);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Barrel_1
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.barrel_1 = obj;
                    lv_obj_set_pos(obj, 0, -4);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_barrel_empty);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj32 = obj;
                            lv_obj_set_pos(obj, 104, 233);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "桶1 ");
                        }
                    }
                }
                {
                    // Barrel_2
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.barrel_2 = obj;
                    lv_obj_set_pos(obj, 200, -4);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_barrel_empty);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj33 = obj;
                            lv_obj_set_pos(obj, 107, 233);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "桶2");
                        }
                    }
                }
                {
                    // Barrel_3
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.barrel_3 = obj;
                    lv_obj_set_pos(obj, 400, -4);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_barrel_empty);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj34 = obj;
                            lv_obj_set_pos(obj, 107, 233);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "桶3");
                        }
                    }
                }
            }
        }
        {
            // main_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.main_label = obj;
            lv_obj_set_pos(obj, 303, 441);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_38, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Main_label");
        }
    }
    
    tick_screen_main_page();
}

void tick_screen_main_page() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 7, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.temperature);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.temperature;
            lv_label_set_text(objects.temperature, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 10, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.time_h);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.time_h;
            lv_label_set_text(objects.time_h, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 11, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.date_y);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.date_y;
            lv_label_set_text(objects.date_y, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.time_m);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.time_m;
            lv_label_set_text(objects.time_m, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 16, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.date_m);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.date_m;
            lv_label_set_text(objects.date_m, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 17, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.date_d);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.date_d;
            lv_label_set_text(objects.date_d, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_shift_setting_page() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.shift_setting_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 768);
    lv_obj_add_event_cb(obj, event_handler_cb_shift_setting_page_shift_setting_page, LV_EVENT_ALL, flowState);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 768);
            lv_image_set_src(obj, &img_backgraound1);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 947, 12);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_home);
            lv_obj_add_event_cb(obj, event_handler_cb_shift_setting_page_obj0, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // title_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.title_2 = obj;
            lv_obj_set_pos(obj, 342, 16);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "AI煤灰自动取样系统");
        }
        {
            // btn_save_shift_setting
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.btn_save_shift_setting = obj;
            lv_obj_set_pos(obj, 903, 686);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_shift_setting_page_btn_save_shift_setting, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff009ea2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "保存");
                }
            }
        }
        {
            // Button_left_Shift
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.button_left_shift = obj;
            lv_obj_set_pos(obj, 0, 58);
            lv_obj_set_size(obj, 93, 525);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0ddfcd), LV_PART_MAIN | LV_STATE_PRESSED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj1 = obj;
                    lv_obj_set_pos(obj, 19, 318);
                    lv_obj_set_size(obj, 71, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_shift_setting_page_obj1, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3195e4), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "测试");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj2 = obj;
                    lv_obj_set_pos(obj, 19, 122);
                    lv_obj_set_size(obj, 71, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_shift_setting_page_obj2, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "取样\n设置");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj3 = obj;
                    lv_obj_set_pos(obj, 19, 220);
                    lv_obj_set_size(obj, 71, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_shift_setting_page_obj3, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "通讯\n设置");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj4 = obj;
                    lv_obj_set_pos(obj, 19, 27);
                    lv_obj_set_size(obj, 71, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_shift_setting_page_obj4, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "班次\n设置");
                        }
                    }
                }
            }
        }
        {
            // input_main_Shift
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.input_main_shift = obj;
            lv_obj_set_pos(obj, 108, 80);
            lv_obj_set_size(obj, 568, 435);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj35 = obj;
                    lv_obj_set_pos(obj, 32, 103);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffff8f8), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "第一班：");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 186, 18);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_font2(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "开始时间");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj36 = obj;
                    lv_obj_set_pos(obj, 32, 201);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffff8f8), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "第二班：");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj37 = obj;
                    lv_obj_set_pos(obj, 32, 299);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffff8f8), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "第三班：");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 412, 18);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_font2(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "结束时间");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj38 = obj;
                    lv_obj_set_pos(obj, 32, 368);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffff8f8), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "自动取\n样次数：");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj39 = obj;
                    lv_obj_set_pos(obj, 322, 382);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffff8f8), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "次/班");
                }
                {
                    // input_start_time1
                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                    objects.input_start_time1 = obj;
                    lv_obj_set_pos(obj, 170, 91);
                    lv_obj_set_size(obj, 128, LV_SIZE_CONTENT);
                    lv_dropdown_set_options(obj, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n20\n21\n22\n23\n24");
                    lv_dropdown_set_selected(obj, 0, LV_ANIM_OFF);
                }
                {
                    // input_start_time2
                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                    objects.input_start_time2 = obj;
                    lv_obj_set_pos(obj, 170, 192);
                    lv_obj_set_size(obj, 128, LV_SIZE_CONTENT);
                    lv_dropdown_set_options(obj, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n20\n21\n22\n23\n24");
                    lv_dropdown_set_selected(obj, 0, LV_ANIM_OFF);
                }
                {
                    // input_stop_time3
                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                    objects.input_stop_time3 = obj;
                    lv_obj_set_pos(obj, 396, 292);
                    lv_obj_set_size(obj, 128, LV_SIZE_CONTENT);
                    lv_dropdown_set_options(obj, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n20\n21\n22\n23\n24");
                    lv_dropdown_set_selected(obj, 0, LV_ANIM_OFF);
                }
                {
                    // input_start_time3
                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                    objects.input_start_time3 = obj;
                    lv_obj_set_pos(obj, 170, 292);
                    lv_obj_set_size(obj, 128, LV_SIZE_CONTENT);
                    lv_dropdown_set_options(obj, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n20\n21\n22\n23\n24");
                    lv_dropdown_set_selected(obj, 0,LV_ANIM_OFF);
                }
                {
                    // input_stop_time2
                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                    objects.input_stop_time2 = obj;
                    lv_obj_set_pos(obj, 396, 192);
                    lv_obj_set_size(obj, 128, LV_SIZE_CONTENT);
                    lv_dropdown_set_options(obj, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n20\n21\n22\n23\n24");
                    lv_dropdown_set_selected(obj, 0,LV_ANIM_OFF);
                }
                {
                    // input_stop_time1
                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                    objects.input_stop_time1 = obj;
                    lv_obj_set_pos(obj, 396, 91);
                    lv_obj_set_size(obj, 128, LV_SIZE_CONTENT);
                    lv_dropdown_set_options(obj, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n20\n21\n22\n23\n24");
                    lv_dropdown_set_selected(obj, 0,LV_ANIM_OFF);
                }
                {
                    // input_auto_sample_time
                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                    objects.input_auto_sample_time = obj;
                    lv_obj_set_pos(obj, 170, 375);
                    lv_obj_set_size(obj, 128, LV_SIZE_CONTENT);
                    lv_dropdown_set_options(obj, "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40");
                    lv_dropdown_set_selected(obj, 0,LV_ANIM_OFF);
                }
            }
        }
    }
    
    tick_screen_shift_setting_page();
}

void tick_screen_shift_setting_page() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
}

void create_screen_sample_setting_page() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.sample_setting_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 768);
    lv_obj_add_event_cb(obj, event_handler_cb_sample_setting_page_sample_setting_page, LV_EVENT_ALL, flowState);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.obj5 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_backgraound1);
            lv_obj_add_event_cb(obj, event_handler_cb_sample_setting_page_obj5, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_state(obj, LV_STATE_PRESSED);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 947, 12);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_home);
            lv_obj_add_event_cb(obj, event_handler_cb_sample_setting_page_obj6, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // Keyboard_Auto
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.keyboard_auto = obj;
            lv_obj_set_pos(obj, 104, 506);
            lv_obj_set_size(obj, 909, 262);
            lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // title_4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.title_4 = obj;
            lv_obj_set_pos(obj, 342, 16);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "AI煤灰自动取样系统");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 132, 376);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_font2(obj);
            lv_obj_set_style_text_font(obj, &ui_font_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "手动取样");
        }
        {
            // Button_left_Auto
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.button_left_auto = obj;
            lv_obj_set_pos(obj, 0, 58);
            lv_obj_set_size(obj, 93, 520);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0ddfcd), LV_PART_MAIN | LV_STATE_PRESSED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj7 = obj;
                    lv_obj_set_pos(obj, 19, 318);
                    lv_obj_set_size(obj, 71, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_sample_setting_page_obj7, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3195e4), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "测试");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj8 = obj;
                    lv_obj_set_pos(obj, 19, 122);
                    lv_obj_set_size(obj, 71, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_sample_setting_page_obj8, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "取样\n设置");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj9 = obj;
                    lv_obj_set_pos(obj, 19, 220);
                    lv_obj_set_size(obj, 71, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_sample_setting_page_obj9, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "通讯\n设置");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj10 = obj;
                    lv_obj_set_pos(obj, 19, 27);
                    lv_obj_set_size(obj, 71, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_sample_setting_page_obj10, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "班次\n设置");
                        }
                    }
                }
            }
        }
        {
            // input_Auto_ssampling手
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.input_auto_ssampling_ = obj;
            lv_obj_set_pos(obj, 109, 90);
            lv_obj_set_size(obj, 572, 260);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 52, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_font2(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "清灰时间：");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 52, 147);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_font2(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "取灰时间：");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 52, 214);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_font2(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "等待时间：");
                }
                {
                    // motor_ccw_seconds
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.motor_ccw_seconds = obj;
                    lv_obj_set_pos(obj, 191, 70);
                    lv_obj_set_size(obj, 313, 46);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_add_event_cb(obj, event_handler_cb_sample_setting_page_motor_ccw_seconds, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                }
                {
                    // motor_cw_seconds
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.motor_cw_seconds = obj;
                    lv_obj_set_pos(obj, 191, 136);
                    lv_obj_set_size(obj, 313, 46);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_add_event_cb(obj, event_handler_cb_sample_setting_page_motor_cw_seconds, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                }
                {
                    // motor_stop_seconds
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.motor_stop_seconds = obj;
                    lv_obj_set_pos(obj, 191, 204);
                    lv_obj_set_size(obj, 313, 46);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_add_event_cb(obj, event_handler_cb_sample_setting_page_motor_stop_seconds, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 529, 78);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_font2(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "秒");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 529, 213);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_font2(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "秒");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 529, 142);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_font2(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "秒");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 23, 23);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_font2(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "自动取样");
                }
            }
        }
        {
            // btn_save_sample_setting
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.btn_save_sample_setting = obj;
            lv_obj_set_pos(obj, 772, 160);
            lv_obj_set_size(obj, 175, 72);
            lv_obj_add_event_cb(obj, event_handler_cb_sample_setting_page_btn_save_sample_setting, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff009ea2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "保存当前配置");
                }
            }
        }
        {
            // btn_manual_take_ccw
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.btn_manual_take_ccw = obj;
            lv_obj_set_pos(obj, 282, 398);
            lv_obj_set_size(obj, 175, 73);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff009ea2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "手动清灰");
                }
            }
        }
        {
            // btn_manual_take_cw
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.btn_manual_take_cw = obj;
            lv_obj_set_pos(obj, 487, 398);
            lv_obj_set_size(obj, 175, 73);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff009ea2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "手动取灰");
                }
            }
        }
        {
            // btn_auto_take_cw
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.btn_auto_take_cw = obj;
            lv_obj_set_pos(obj, 772, 267);
            lv_obj_set_size(obj, 175, 73);
            lv_obj_add_event_cb(obj, event_handler_cb_sample_setting_page_btn_auto_take_cw, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff009ea2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj40 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "开始自动取灰");
                }
            }
        }
        {
            // keyboard_sample
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.keyboard_sample = obj;
            lv_obj_set_pos(obj, 110, 483);
            lv_obj_set_size(obj, 903, 283);
            lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj11 = obj;
            lv_obj_set_pos(obj, 772, 398);
            lv_obj_set_size(obj, 175, 73);
            lv_obj_add_event_cb(obj, event_handler_cb_sample_setting_page_obj11, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff009ea2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj41 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "停止");
                }
            }
        }
    }
    
    tick_screen_sample_setting_page();
}

void tick_screen_sample_setting_page() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
}

void create_screen_communicate_setting_page() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.communicate_setting_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 768);
    lv_obj_add_event_cb(obj, event_handler_cb_communicate_setting_page_communicate_setting_page, LV_EVENT_ALL, flowState);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.obj12 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_backgraound1);
            lv_obj_add_event_cb(obj, event_handler_cb_communicate_setting_page_obj12, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_state(obj, LV_STATE_PRESSED);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.obj13 = obj;
            lv_obj_set_pos(obj, 947, 12);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_home);
            lv_obj_add_event_cb(obj, event_handler_cb_communicate_setting_page_obj13, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // title_3
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.title_3 = obj;
            lv_obj_set_pos(obj, 342, 16);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "AI煤灰自动取样系统");
        }
        {
            // Button_left_Communication
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.button_left_communication = obj;
            lv_obj_set_pos(obj, 0, 58);
            lv_obj_set_size(obj, 93, 520);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0ddfcd), LV_PART_MAIN | LV_STATE_PRESSED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj14 = obj;
                    lv_obj_set_pos(obj, 0, 318);
                    lv_obj_set_size(obj, 90, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_communicate_setting_page_obj14, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3195e4), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "测试");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj15 = obj;
                    lv_obj_set_pos(obj, 0, 122);
                    lv_obj_set_size(obj, 90, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_communicate_setting_page_obj15, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "取样\n设置");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj16 = obj;
                    lv_obj_set_pos(obj, 0, 220);
                    lv_obj_set_size(obj, 90, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_communicate_setting_page_obj16, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "通讯\n设置");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj17 = obj;
                    lv_obj_set_pos(obj, 0, 27);
                    lv_obj_set_size(obj, 90, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_communicate_setting_page_obj17, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "班次\n设置");
                        }
                    }
                }
            }
        }
        {
            // input_main_Communication
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.input_main_communication = obj;
            lv_obj_set_pos(obj, 110, 88);
            lv_obj_set_size(obj, 502, 262);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 16, 19);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_font2(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "地址：");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 16, 118);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_font2(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "默认网关：");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 16, 208);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_font2(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "DNS服务器：");
                }
                {
                    // input_Address
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.input_address = obj;
                    lv_obj_set_pos(obj, 192, 9);
                    lv_obj_set_size(obj, 176, 46);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_add_event_cb(obj, event_handler_cb_communicate_setting_page_input_address, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                }
                {
                    // input_Gateway
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.input_gateway = obj;
                    lv_obj_set_pos(obj, 192, 110);
                    lv_obj_set_size(obj, 176, 46);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_add_event_cb(obj, event_handler_cb_communicate_setting_page_input_gateway, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                }
                {
                    // input_DNS
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.input_dns = obj;
                    lv_obj_set_pos(obj, 192, 202);
                    lv_obj_set_size(obj, 176, 46);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_add_event_cb(obj, event_handler_cb_communicate_setting_page_input_dns, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                }
            }
        }
        {
            // Keyboard_communication
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.keyboard_communication = obj;
            lv_obj_set_pos(obj, 109, 393);
            lv_obj_set_size(obj, 582, 292);
            lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // btn_save_communicate_setting
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.btn_save_communicate_setting = obj;
            lv_obj_set_pos(obj, 903, 686);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_communicate_setting_page_btn_save_communicate_setting, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff009ea2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "保存");
                }
            }
        }
    }
    
    tick_screen_communicate_setting_page();
}

void tick_screen_communicate_setting_page() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
}

void create_screen_motor_test_setting_page() {
    void *flowState = getFlowState(0, 4);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.motor_test_setting_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 768);
    lv_obj_add_event_cb(obj, event_handler_cb_motor_test_setting_page_motor_test_setting_page, LV_EVENT_ALL, flowState);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.obj18 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_backgraound1);
            lv_obj_add_event_cb(obj, event_handler_cb_motor_test_setting_page_obj18, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_state(obj, LV_STATE_PRESSED);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.obj19 = obj;
            lv_obj_set_pos(obj, 947, 12);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_home);
            lv_obj_add_event_cb(obj, event_handler_cb_motor_test_setting_page_obj19, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // title_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.title_1 = obj;
            lv_obj_set_pos(obj, 342, 16);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "AI煤灰自动取样系统");
        }
        {
            // Button_left_Test
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.button_left_test = obj;
            lv_obj_set_pos(obj, 0, 58);
            lv_obj_set_size(obj, 93, 510);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0ddfcd), LV_PART_MAIN | LV_STATE_PRESSED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj20 = obj;
                    lv_obj_set_pos(obj, 19, 318);
                    lv_obj_set_size(obj, 71, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_motor_test_setting_page_obj20, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3195e4), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "测试");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj21 = obj;
                    lv_obj_set_pos(obj, 19, 122);
                    lv_obj_set_size(obj, 71, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_motor_test_setting_page_obj21, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "取样\n设置");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj22 = obj;
                    lv_obj_set_pos(obj, 19, 220);
                    lv_obj_set_size(obj, 71, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_motor_test_setting_page_obj22, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "通讯\n设置");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj23 = obj;
                    lv_obj_set_pos(obj, 19, 27);
                    lv_obj_set_size(obj, 71, 72);
                    lv_obj_add_event_cb(obj, event_handler_cb_motor_test_setting_page_obj23, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9e7ff), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "班次\n设置");
                        }
                    }
                }
            }
        }
        {
            // input_main_Test
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.input_main_test = obj;
            lv_obj_set_pos(obj, 135, 107);
            lv_obj_set_size(obj, 538, 293);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 23, 40);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_font2(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "取样电机：");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 23, 140);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_font2(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "旋转电机：");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 23, 241);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_font2(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "旋转速度：");
                }
                {
                    // btn_sample_motor_cw
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_sample_motor_cw = obj;
                    lv_obj_set_pos(obj, 204, 29);
                    lv_obj_set_size(obj, 100, 50);
                    lv_obj_add_event_cb(obj, event_handler_cb_motor_test_setting_page_btn_sample_motor_cw, LV_EVENT_ALL, flowState);
                    lv_obj_add_state(obj, LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "正转");
                        }
                    }
                }
                {
                    // btn_sample_motor_ccw
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_sample_motor_ccw = obj;
                    lv_obj_set_pos(obj, 379, 29);
                    lv_obj_set_size(obj, 100, 50);
                    lv_obj_add_event_cb(obj, event_handler_cb_motor_test_setting_page_btn_sample_motor_ccw, LV_EVENT_ALL, flowState);
                    lv_obj_add_state(obj, LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "反转");
                        }
                    }
                }
                {
                    // btn_rotate_motor_ccw
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_rotate_motor_ccw = obj;
                    lv_obj_set_pos(obj, 379, 129);
                    lv_obj_set_size(obj, 100, 50);
                    lv_obj_add_event_cb(obj, event_handler_cb_motor_test_setting_page_btn_rotate_motor_ccw, LV_EVENT_ALL, flowState);
                    lv_obj_add_state(obj, LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "反转");
                        }
                    }
                }
                {
                    // btn_rotate_motor_cw
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_rotate_motor_cw = obj;
                    lv_obj_set_pos(obj, 205, 129);
                    lv_obj_set_size(obj, 100, 50);
                    lv_obj_add_event_cb(obj, event_handler_cb_motor_test_setting_page_btn_rotate_motor_cw, LV_EVENT_ALL, flowState);
                    lv_obj_add_state(obj, LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "正转");
                        }
                    }
                }
            }
        }
        {
            // input_Rotational_speed
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.input_rotational_speed = obj;
            lv_obj_set_pos(obj, 338, 327);
            lv_obj_set_size(obj, 150, 57);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, event_handler_cb_motor_test_setting_page_input_rotational_speed, LV_EVENT_ALL, flowState);
            lv_obj_add_state(obj, LV_STATE_PRESSED);
        }
        {
            // Keyboard_Test
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.keyboard_test = obj;
            lv_obj_set_pos(obj, 113, 448);
            lv_obj_set_size(obj, 560, 262);
            lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // btn_save_motor_test_setting
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.btn_save_motor_test_setting = obj;
            lv_obj_set_pos(obj, 903, 686);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_motor_test_setting_page_btn_save_motor_test_setting, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff009ea2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "保存");
                }
            }
        }
    }
    
    tick_screen_motor_test_setting_page();
}

void tick_screen_motor_test_setting_page() {
    void *flowState = getFlowState(0, 4);
    (void)flowState;
}

void create_screen_warning_page() {
    void *flowState = getFlowState(0, 5);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.warning_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 768);
    lv_obj_add_event_cb(obj, event_handler_cb_warning_page_warning_page, LV_EVENT_ALL, flowState);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 768);
            lv_image_set_src(obj, &img_backgraound1);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // title_5
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.title_5 = obj;
            lv_obj_set_pos(obj, 342, 16);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "AI煤灰自动取样系统");
        }
        {
            // btn_warning_ok
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.btn_warning_ok = obj;
            lv_obj_set_pos(obj, 745, 624);
            lv_obj_set_size(obj, 219, 104);
            lv_obj_add_event_cb(obj, event_handler_cb_warning_page_btn_warning_ok, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff009ea2), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "确认");
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 250, 221);
            lv_obj_set_size(obj, 525, 207);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, -17, 1);
                    lv_obj_set_size(obj, 534, 187);
                    lv_image_set_src(obj, &img_warning_background);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj42 = obj;
                    lv_obj_set_pos(obj, 126, 60);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff080303), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "警告：结束时间必须早于\n下一班开始时间！");
                }
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 26, 45);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_warning_icon);
                }
            }
        }
    }
    
    tick_screen_warning_page();
}

void tick_screen_warning_page() {
    void *flowState = getFlowState(0, 5);
    (void)flowState;
}


extern void add_style(lv_obj_t *obj, int32_t styleIndex);
extern void remove_style(lv_obj_t *obj, int32_t styleIndex);

void ui_create_groups() {
    if (!groups_created) {
        groups.left_button = lv_group_create();
        eez_flow_init_groups((lv_group_t **)&groups, sizeof(groups) / sizeof(lv_group_t *));
        groups_created = true;
    }
}

static const char *screen_names[] = { "Main_page", "Shift_setting_page", "Sample_setting_page", "Communicate_setting_page", "Motor_Test_setting_page", "warning_page" };
static const char *object_names[] = { "main_page", "shift_setting_page", "sample_setting_page", "communicate_setting_page", "motor_test_setting_page", "warning_page", "setting8", "obj0", "btn_save_shift_setting", "obj1", "obj2", "obj3", "obj4", "obj5", "obj6", "obj7", "obj8", "obj9", "obj10", "motor_ccw_seconds", "motor_cw_seconds", "motor_stop_seconds", "btn_save_sample_setting", "btn_auto_take_cw", "obj11", "obj12", "obj13", "obj14", "obj15", "obj16", "obj17", "input_address", "input_gateway", "input_dns", "btn_save_communicate_setting", "obj18", "obj19", "obj20", "obj21", "obj22", "obj23", "btn_sample_motor_cw", "btn_sample_motor_ccw", "btn_rotate_motor_ccw", "btn_rotate_motor_cw", "input_rotational_speed", "btn_save_motor_test_setting", "btn_warning_ok", "main1", "obj24", "information", "obj25", "obj26", "temperature", "obj27", "obj28", "time_h", "date_y", "time_m", "obj29", "obj30", "obj31", "date_m", "date_d", "btn_factory_reset", "barrel_1", "obj32", "barrel_2", "obj33", "barrel_3", "obj34", "main_label", "title_2", "button_left_shift", "input_main_shift", "obj35", "obj36", "obj37", "obj38", "obj39", "input_start_time1", "input_start_time2", "input_stop_time3", "input_start_time3", "input_stop_time2", "input_stop_time1", "input_auto_sample_time", "keyboard_auto", "title_4", "button_left_auto", "input_auto_ssampling_", "btn_manual_take_ccw", "btn_manual_take_cw", "obj40", "keyboard_sample", "obj41", "title_3", "button_left_communication", "input_main_communication", "keyboard_communication", "title_1", "button_left_test", "input_main_test", "keyboard_test", "title_5", "obj42" };
static const char *group_names[] = { "left_button" };
static const char *style_names[] = { "font2" };


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main_page,
    tick_screen_shift_setting_page,
    tick_screen_sample_setting_page,
    tick_screen_communicate_setting_page,
    tick_screen_motor_test_setting_page,
    tick_screen_warning_page,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    ui_create_groups();
    
    eez_flow_init_styles(add_style, remove_style);
    
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    eez_flow_init_group_names(group_names, sizeof(group_names) / sizeof(const char *));
    eez_flow_init_style_names(style_names, sizeof(style_names) / sizeof(const char *));
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main_page();
    create_screen_shift_setting_page();
    create_screen_sample_setting_page();
    create_screen_communicate_setting_page();
    create_screen_motor_test_setting_page();
    create_screen_warning_page();
}

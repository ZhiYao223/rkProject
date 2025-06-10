#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_NONE
};

// Native global variables
extern int32_t get_var_sample_interval_minutes();
extern void set_var_sample_interval_minutes(int32_t value);
extern int32_t get_var_cw_rotate_seconds();
extern void set_var_cw_rotate_seconds(int32_t value);
extern int32_t get_var_ccw_rotate_seconds();
extern void set_var_ccw_rotate_seconds(int32_t value);
extern int32_t get_var_motor_stop_time();
extern void set_var_motor_stop_time(int32_t value);
extern int32_t get_var_manual_take_time_cw();
extern void set_var_manual_take_time_cw(int32_t value);
extern int32_t get_var_manual_take_time_ccw();
extern void set_var_manual_take_time_ccw(int32_t value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/

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

extern int32_t get_var_start_time_1();
extern void set_var_start_time_1(int32_t value);
extern int32_t get_var_stop_time_1();
extern void set_var_stop_time_1(int32_t value);
extern int32_t get_var_start_time_2();
extern void set_var_start_time_2(int32_t value);
extern int32_t get_var_stop_time_2();
extern void set_var_stop_time_2(int32_t value);
extern int32_t get_var_tem();
extern void set_var_tem(int32_t value);
extern int32_t get_var_start_time_3();
extern void set_var_start_time_3(int32_t value);
extern int32_t get_var_stop_time_3();
extern void set_var_stop_time_3(int32_t value);
extern int32_t get_var_ccw_time();
extern void set_var_ccw_time(int32_t value);
extern int32_t get_var_cw_time();
extern void set_var_cw_time(int32_t value);
extern int32_t get_var_stop_time();
extern void set_var_stop_time(int32_t value);
extern int32_t get_var_address();
extern void set_var_address(int32_t value);
extern int32_t get_var_gateway();
extern void set_var_gateway(int32_t value);
extern int32_t get_var_dns();
extern void set_var_dns(int32_t value);
extern int32_t get_var_rotational_speed();
extern void set_var_rotational_speed(int32_t value);
extern int32_t get_var_date_year();
extern void set_var_date_year(int32_t value);
extern int32_t get_var_time_hour();
extern void set_var_time_hour(int32_t value);
extern int32_t get_var_time_min();
extern void set_var_time_min(int32_t value);
extern int32_t get_var_date_month();
extern void set_var_date_month(int32_t value);
extern int32_t get_var_date_day();
extern void set_var_date_day(int32_t value);
extern int32_t get_var_sample_interval_minutes();
extern void set_var_sample_interval_minutes(int32_t value);
extern int32_t get_var_motor_ccw_seconds();
extern void set_var_motor_ccw_seconds(int32_t value);
extern int32_t get_var_motor_cw_seconds();
extern void set_var_motor_cw_seconds(int32_t value);
extern int32_t get_var_motor_stop_seconds();
extern void set_var_motor_stop_seconds(int32_t value);
extern int32_t get_var_manual_take_time_cw();
extern void set_var_manual_take_time_cw(int32_t value);
extern int32_t get_var_manual_take_time_ccw();
extern void set_var_manual_take_time_ccw(int32_t value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/
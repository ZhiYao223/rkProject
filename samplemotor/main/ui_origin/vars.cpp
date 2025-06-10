#include "vars.h"

int32_t sample_interval_minutes;

extern "C" int32_t get_var_sample_interval_minutes() {
    return sample_interval_minutes;
}

extern "C" void set_var_sample_interval_minutes(int32_t value) {
    sample_interval_minutes = value;
}

int32_t cw_rotate_seconds;

extern "C" int32_t get_var_cw_rotate_seconds() {
    return cw_rotate_seconds;
}

extern "C" void set_var_cw_rotate_seconds(int32_t value) {
    cw_rotate_seconds = value;
}

// 电机反转时间
int32_t ccw_rotate_seconds;

extern "C" int32_t get_var_ccw_rotate_seconds() {
    return ccw_rotate_seconds;
}

extern "C" void set_var_ccw_rotate_seconds(int32_t value) {
    ccw_rotate_seconds = value;
}

int32_t motor_stop_time;

extern "C" int32_t get_var_motor_stop_time() {
    return motor_stop_time;
}

extern "C" void set_var_motor_stop_time(int32_t value) {
    motor_stop_time = value;
}


int32_t manual_take_time_cw;

extern "C" int32_t get_var_manual_take_time_cw() {
    return manual_take_time_cw;
}

extern "C" void set_var_manual_take_time_cw(int32_t value) {
    manual_take_time_cw = value;
}


int32_t manual_take_time_ccw;

extern "C" int32_t get_var_manual_take_time_ccw() {
    return manual_take_time_ccw;
}

extern "C" void set_var_manual_take_time_ccw(int32_t value) {
    manual_take_time_ccw = value;
}

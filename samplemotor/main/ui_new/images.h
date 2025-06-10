#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_home;
extern const lv_img_dsc_t img_barrel;
extern const lv_img_dsc_t img_setting7;
extern const lv_img_dsc_t img_backgraound1;
extern const lv_img_dsc_t img_backgraound;
extern const lv_img_dsc_t img_net;
extern const lv_img_dsc_t img_calendar_symbol;
extern const lv_img_dsc_t img_warning_background;
extern const lv_img_dsc_t img_warning_icon;
extern const lv_img_dsc_t img_barrel_empty;
extern const lv_img_dsc_t img_barrel_full;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[11];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/
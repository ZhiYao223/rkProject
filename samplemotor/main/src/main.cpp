
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "lvgl/lvgl.h"
// #include "lvgl/examples/lv_examples.h"
// #include "lvgl/demos/lv_demos.h"
#include "glob.h"

#include <list>
#include <memory>
#include <thread>
#include <chrono>
#include <SDL2/SDL.h>
#include "../../lvgl/src/libs/freetype/lv_freetype.h"
#include "../../lvgl/src/drivers/sdl/lv_sdl_window.h"
#include "../../eez_rk3566/ui/ui.h"
#include "../../eez_rk3566/ui/screens.h"
#include "../../eez_rk3566/ui/vars.h"
#include "../../eez_rk3566/ui/actions.h"
#include "gpio.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_display_t * hal_init(int32_t w, int32_t h);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

extern void freertos_main(void);
extern void load_configs();
extern void init_main_label();
static void lv_font_style_init();
static void screen_communicate_init();
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/
static std::list<lv_font_t*> _g_fonts;
static std::list<lv_style_t*> _g_styles;

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
#if LV_FREETYPE_USE_LVGL_PORT
    #define PATH_PREFIX "A"
#else
    #define PATH_PREFIX "../"
#endif
// 要使用该函数，必须在项目中启用 LV_USE_FREETYPE = 1，并配置好 lv_freetype.h
static lv_font_t* load_chinese_font(const char* path, uint32_t font_size){
  lv_font_t* font = lv_freetype_font_create(path,LV_FREETYPE_FONT_RENDER_MODE_BITMAP,font_size,LV_FREETYPE_FONT_STYLE_NORMAL);
  if (font){
    printf("load font %s success\n", path);
  } else {
    printf("load font %s failed\n", path);
  }
  return font;
}

// char main_label_text[128] = "电机停止状态";
// static void update_label_cb(void *param) {
//   lv_label_set_text((lv_obj_t *)param, main_label_text);
// }

// static void sample_thread(){
//   printf("sample thread started\n");
//   while(1){
//     uint32_t interval_mintues = get_var_sample_interval_minutes();

//     if (interval_mintues == 0){
//       std::this_thread::sleep_for(std::chrono::seconds(1));
//       continue;
//     }
//     uint32_t cw_seconds = get_var_cw_rotate_seconds();
//     uint32_t ccw_seconds = get_var_ccw_rotate_seconds();

//     if (cw_seconds == 0 && ccw_seconds == 0){
//       std::this_thread::sleep_for(std::chrono::seconds(1));
//       continue;
//     }
//     memset(main_label_text, 0, sizeof(main_label_text));
//     strcpy(main_label_text, "电机转动中(正转)");
//     lv_async_call(update_label_cb, objects.main_label);
//     // lv_label_set_text(objects.main_label, "电机转动中(正转)");
//     ACES::GPIO::GetInstance().SetMotorDirection(ACES::MotorDirection::CW);
//     ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::ON);
//     std::this_thread::sleep_for(std::chrono::seconds(cw_seconds));
//     // lv_label_set_text(objects.main_label, "电机转动中(反转)");
//     memset(main_label_text, 0, sizeof(main_label_text));
//     strcpy(main_label_text, "电机转动中(反转)");
//     lv_async_call(update_label_cb, objects.main_label);
//     ACES::GPIO::GetInstance().SetMotorDirection(ACES::MotorDirection::CCW);
//     std::this_thread::sleep_for(std::chrono::seconds(ccw_seconds));
//     ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::OFF);
//     // lv_label_set_text(objects.main_label, "电机停止状态");
//     memset(main_label_text, 0, sizeof(main_label_text));
//     strcpy(main_label_text, "电机停止状态");
//     lv_async_call(update_label_cb, objects.main_label);

//     std::this_thread::sleep_for(std::chrono::minutes(interval_mintues));
//   }
// }
void Label_text_setting(){
#if 0
  lv_obj_add_style(objects.label_btn_left1, style28, 0);
  lv_label_set_text(objects.label_btn_left1, "环境");

  lv_obj_add_style(objects.label_btn_left2, style28, 0);
  lv_label_set_text(objects.label_btn_left2, "温度");

  lv_obj_add_style(objects.label_btn_left3, style28, 0);
  lv_label_set_text(objects.label_btn_left3, "湿度");

  lv_obj_add_style(objects.label_btn_left4, style28, 0);
  lv_label_set_text(objects.label_btn_left4, "气压");

  lv_obj_add_style(objects.label_manual_take_time_cw, style28, 0);
  lv_label_set_text(objects.label_manual_take_time_cw, "手动取灰(正转)");

  lv_obj_add_style(objects.label_btn_mark_take_cw, style28, 0);
  lv_label_set_text(objects.label_btn_mark_take_cw, "自动取灰");

  lv_obj_add_style(objects.label_btn_save_setting, style28, 0);
  lv_label_set_text(objects.label_btn_save_setting, "保存配置");
  lv_obj_add_style(objects.main_label, style56, 0);
  lv_label_set_text(objects.main_label, "电机停止状态(RK3566控制)");

  lv_obj_add_style(objects.label_btn_manual_take, style28, 0);
  lv_label_set_text(objects.label_btn_manual_take, "手动取灰(正转)");

  lv_obj_add_style(objects.label_btn_manual_take_ccw, style28, 0);
  lv_label_set_text(objects.label_btn_manual_take_ccw, "手动排灰(反转)");

  lv_obj_add_style(objects.label_btn_mark_took, style28, 0);
  lv_label_set_text(objects.label_btn_mark_took, "自动取灰");

  lv_obj_add_style(objects.label_btn_sample_setting, style28, 0);
  lv_label_set_text(objects.label_btn_sample_setting, "取样配置");

  lv_obj_add_style(objects.label_btn_save_setting, style28, 0);
  lv_label_set_text(objects.label_btn_save_setting, "保存配置");

  lv_obj_add_style(objects.label_interval, style28, 0);
  lv_label_set_text(objects.label_interval, "自动取灰间隔时间：");

  lv_obj_add_style(objects.label_interval_unit, style28, 0);
  lv_label_set_text(objects.label_interval_unit, "分");

  lv_obj_add_style(objects.label_rotate_cw, style28, 0);
  lv_label_set_text(objects.label_rotate_cw, "正转时间：");

  lv_obj_add_style(objects.label_rotate_cw_unit, style28, 0);
  lv_label_set_text(objects.label_rotate_cw_unit, "秒");

  lv_obj_add_style(objects.label_rotate_ccw, style28, 0);
  lv_label_set_text(objects.label_rotate_ccw, "反转时间：");

  lv_obj_add_style(objects.label_rotate_ccw_unit, style28, 0);
  lv_label_set_text(objects.label_rotate_ccw_unit, "秒");

  lv_obj_add_style(objects.label_stop_time_unit, style28, 0);
  lv_label_set_text(objects.label_stop_time_unit, "秒");

  lv_obj_add_style(objects.label_rotate_cw_manual_unit, style28, 0);
  lv_label_set_text(objects.label_rotate_cw_manual_unit, "秒");

  lv_obj_add_style(objects.label_rotate_ccw_manual_unit, style28, 0);
  lv_label_set_text(objects.label_rotate_ccw_manual_unit, "秒");

  lv_obj_add_style(objects.label_rotate_cw_manual, style28, 0);
  lv_label_set_text(objects.label_rotate_cw_manual, "手动取灰时间：");

  lv_obj_add_style(objects.label_rotate_cww_manual, style28, 0);
  lv_label_set_text(objects.label_rotate_cww_manual, "手动排灰时间：");

  lv_obj_add_style(objects.label_motor_stop, style28, 0);
  lv_label_set_text(objects.label_motor_stop, "电机停止时间：");

  // Auto Take is DISABLED
  lv_obj_set_style_bg_color(objects.btn_mark_took, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);

  load_configs();
  init_main_label();
  action_save_setting_func(NULL);
#endif
}

int main(int argc, char **argv)
{
  (void)argc; /*Unused*/
  (void)argv; /*Unused*/

  /*Initialize LVGL*/
  lv_init();                 // 初始化 LVGL 库
  lv_font_style_init();      // 初始化字体样式
  load_configs();            // 加载配置文件，设置界面上的默认值为最近一次设置的参数
  hal_init(1024, 768);  // 初始化硬件抽象层HAL,设置显示器和输入设备等，1024 和 768 是屏幕的宽度和高度，单位是像素。
  // 只有当 LVGL 配置为不使用操作系统（裸机环境）时，下面的代码才会被编译进来。
  #if LV_USE_OS == LV_OS_NONE
  // lv_demo_widgets();
  ui_init();
  //screen_communicate_init(); // 初始化通信设置页面

  ACES::GPIO::GetInstance().Init(); // 初始化GPIO功能
  ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::OFF); //初始化关闭电机电源

  // std::thread t1(sample_thread);
  // t1.detach();
  while(1) {
    lv_timer_handler();
    ui_tick();
    usleep(5 * 1000);
  }

  for(auto i = _g_styles.begin(); i != _g_styles.end(); i++){
    lv_style_reset(*i);
    //delete *i;
  }
  for(auto i = _g_fonts.begin(); i != _g_fonts.end(); i++){
    lv_freetype_font_delete(*i);
  }

  // lv_freetype_uninit();

#elif LV_USE_OS == LV_OS_FREERTOS
/* Run FreeRTOS and create lvgl task */
freertos_main();
#endif

  return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static lv_display_t * hal_init(int32_t w, int32_t h)
{
  //设置 SDL 窗口为“非全屏 + 有边框 + 允许被窗口管理器控制”
  SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
  SDL_SetHint(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, "1");

  // 创建一个默认的输入组，用于键盘/鼠标聚焦管理
  lv_group_set_default(lv_group_create());
  // 使用 SDL 创建一个 LVGL 显示窗口，分辨率为 w * h, 1024 * 768
  lv_display_t * disp = lv_sdl_window_create(w, h);   //  创建 LVGL 显示窗口（此时是窗口模式，而不是霸屏）
  // 创建鼠标输入设备
  lv_indev_t * mouse = lv_sdl_mouse_create();
  // 将鼠标设备绑定到默认输入组
  lv_indev_set_group(mouse, lv_group_get_default());
  // 将鼠标设备绑定到显示设备
  lv_indev_set_display(mouse, disp);
  /// 设置该 SDL 显示窗口为 LVGL 的默认显示器
  lv_display_set_default(disp);

  // （可选）创建自定义鼠标图标
  // LV_IMAGE_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  // lv_obj_t * cursor_obj;
  // cursor_obj = lv_image_create(lv_screen_active()); /*Create an image object for the cursor */
  // lv_image_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
  // lv_indev_set_cursor(mouse, cursor_obj);             /*Connect the image  object to the driver*/

  // 创建鼠标滚轮输入设备（模拟滚动操作）
  lv_indev_t * mousewheel = lv_sdl_mousewheel_create();
  lv_indev_set_display(mousewheel, disp);
  lv_indev_set_group(mousewheel, lv_group_get_default());

  // 创建键盘输入设备（用于输入焦点控件）
  lv_indev_t * kb = lv_sdl_keyboard_create();
  lv_indev_set_display(kb, disp);
  lv_indev_set_group(kb, lv_group_get_default());
  // 返回显示器对象

  return disp;
}

void lv_font_style_init(){
  lv_font_t* font28 = load_chinese_font("/opt/sample/font/SourceHanSerifSC-VF.ttf", 28);
  if (font28) _g_fonts.push_back(font28);
  lv_font_t* font56 = load_chinese_font("/opt/sample/font/SourceHanSerifSC-VF.ttf", 56);
  if (font56) _g_fonts.push_back(font56);

  // 创建一个自定义字体样式并保存到全局样式列表 _g_styles 中
  lv_style_t* style28 = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(style28);
  lv_style_set_text_font(style28, font28);
  lv_style_set_text_align(style28, LV_TEXT_ALIGN_LEFT);
  _g_styles.push_back(style28);

  // 创建一个自定义字体样式并保存到全局样式列表 _g_styles 中
  lv_style_t* style56 = (lv_style_t*)malloc(sizeof(lv_style_t));
  lv_style_init(style56);
  lv_style_set_text_font(style56, font56);
  lv_style_set_text_align(style56, LV_TEXT_ALIGN_LEFT);
  _g_styles.push_back(style56);
}

void screen_communicate_init(){
    lv_textarea_set_text(objects.input_address, get_var_address()); // 设置输入框的默认值为最近一次的ip地址
    lv_textarea_set_text(objects.input_gateway, get_var_gateway()); // 设置输入框的默认值为最近一次的网关地址
    lv_textarea_set_text(objects.input_dns,     get_var_dns());     // 设置输入框的默认值为最近一次的DNS服务器地址
}
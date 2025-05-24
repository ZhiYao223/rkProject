#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include <thread>

#include "actions.h"
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
#include "../ui/vars.h"
#include "../ui/screens.h"

#include "../src/gpio.h"

// 全局标志位，表示不退出线程（线程运行中）。
static bool bQuitAutoTakeThread = false;

// #define CONFIG_PATH     "/opt/sample/config.json"
#define CONFIG_PATH     "../main/ui/config.json"
// 保存设置按钮的回调函数
void action_save_setting_func(lv_event_t * e)
{
    rapidjson::Document doc;                                    // 表示 JSON 的根文档对象
    rapidjson::StringBuffer buffer;                             // 字符串缓冲区，用于临时存放 JSON 文本。
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);  // 将 doc 序列化为 JSON 字符串，写入 buffer。

    doc.SetObject();                                            //将文档设置为 JSON 对象（即键值对形式的结构）。
    //  添加字段：采样时间间隔（单位：分钟）
    rapidjson::Value elInterval(rapidjson::kNumberType);        // 创建一个 JSON 数值类型的字段 elInterval。
    elInterval.SetInt(get_var_sample_interval_minutes());       // 将其值设为当前系统变量 get_var_sample_interval_minutes()
    doc.AddMember("sample_interval_minutes", elInterval, doc.GetAllocator());   // 添加到 JSON 文档中，字段名为 "sample_interval_minutes"
    // 添加字段：正向旋转时间（单位：秒）,  以同样方式添加字段 "cw_rotate_seconds"，表示电机顺时针旋转时间。
    rapidjson::Value elCwRotate(rapidjson::kNumberType);
    elCwRotate.SetInt(get_var_cw_rotate_seconds());
    doc.AddMember("cw_rotate_seconds", elCwRotate, doc.GetAllocator());

    // 添加字段：反向旋转时间（单位：秒）,  以同样方式添加字段 "ccw_rotate_seconds"，表示电机逆时针旋转时间。
    rapidjson::Value elCcwRotate(rapidjson::kNumberType);
    elCcwRotate.SetInt(get_var_ccw_rotate_seconds());
    doc.AddMember("ccw_rotate_seconds", elCcwRotate, doc.GetAllocator());

    // 添加字段：电机停止时间（单位：秒）,  以同样方式添加字段 "input_motor_stop"，表示电机停止时间。
    rapidjson::Value elMotorStop(rapidjson::kNumberType);
    elMotorStop.SetInt(get_var_motor_stop_time());
    doc.AddMember("input_motor_stop", elMotorStop, doc.GetAllocator());

    // 添加字段：手动正转取样时间, 以同样方式添加字段 "input_cw_manual_time"，表示手动正转取样时间。
    rapidjson::Value elManualTakeCW(rapidjson::kNumberType);
    elManualTakeCW.SetInt(get_var_manual_take_time_cw());
    doc.AddMember("input_cw_manual_time", elManualTakeCW, doc.GetAllocator());

    // 添加字段：手动反转取样时间, 以同样方式添加字段 "input_ccw_manual_time"，表示手动反转取样时间。
    rapidjson::Value elManualTakeCCW(rapidjson::kNumberType);
    elManualTakeCCW.SetInt(get_var_manual_take_time_ccw());
    doc.AddMember("input_ccw_manual_time", elManualTakeCCW, doc.GetAllocator());

    // 将 JSON 写入字符串并输出到文件
    doc.Accept(writer);                     // 将JSON 文档序列化成字符串。
    const char* json = buffer.GetString();  // 获取最终的 JSON 字符串内容。
    // 保存到文件
    FILE *fp = fopen(CONFIG_PATH, "wb+");   // 尝试以可读写模式打开（或创建）配置文件。
    // 如果失败，输出错误信息并提前返回。
    if (NULL == fp){
        printf("open file %s failed\n", CONFIG_PATH);
        return;
    }
    fwrite(json, strlen(json), 1, fp);      // 将 JSON 字符串写入文件。
    fclose(fp);                             // 关闭文件，完成保存操作
}

// 从 JSON 配置文件 "/opt/sample/config.json" 中读取参数并加载到程序中。
void load_configs(){
    // 打开文件
    FILE *fp = fopen(CONFIG_PATH, "rb");                // 以二进制只读模式 "rb" 打开配置文件。
    if (NULL == fp){                                    // 如果打开失败，打印错误信息并返回。
        printf("open file %s failed\n", CONFIG_PATH);
        return;
    }
    // 获取文件大小，并分配内存
    fseek(fp, 0, SEEK_END);                             // 移动文件指针到末尾
    int size = ftell(fp);                               // 获取当前文件大小（单位：字节）。
    fseek(fp, 0, SEEK_SET);                             // 回到文件开头准备读取。
    char *buffer = (char *)malloc(size + 1);            // 分配一个多出1字节的缓冲区（用于末尾加 \0）,以存放文件内容
    if (NULL == buffer){                                // 如果分配失败，打印错误信息并返回。
        printf("malloc buffer failed\n");               
        fclose(fp);                                     // 关闭文件指针
        return;
    }
    // 读取文件内容到缓冲区
    fread(buffer, size, 1, fp);                         // 一次性读取整个文件到 buffer               
    fclose(fp);                                         // 关闭文件指针 fp。

    buffer[size] = '\0';                                // 手动添加 C 字符串结束符，确保 buffer 是合法的字符串（JSON 格式字符串）。
    rapidjson::Document doc;                            // 
    doc.Parse(buffer);                                  // 解析 JSON 字符串。
    if (doc.HasParseError())                            // 若解析失败，释放内存并输出错误信息。
    {
        free(buffer);
        printf("parse json failed\n");
        return;
    }
    // 读取字段并赋值给系统变量, 检查是否存在 "sample_interval_minutes" 字段且是整数。
    if (doc.HasMember("sample_interval_minutes") && doc["sample_interval_minutes"].IsInt()) 
    {
        // 调用 set_var_sample_interval_minutes() 设置该值。
        int sample_interval_minutes = doc["sample_interval_minutes"].GetInt();      
        set_var_sample_interval_minutes(sample_interval_minutes);   // 设置电机采样间隔时间
    }
    // 检查是否存在 "cw_rotate_seconds" 字段且是整数。
    if (doc.HasMember("cw_rotate_seconds") && doc["cw_rotate_seconds"].IsInt())
    {
        // 调用 set_var_cw_rotate_seconds() 设置该值。
        int cw_rotate_seconds = doc["cw_rotate_seconds"].GetInt();
        set_var_cw_rotate_seconds(cw_rotate_seconds);
    } else { // 若不存在
        set_var_cw_rotate_seconds(300); // 设置电机顺时针旋转时间，默认值为 300。
    }
    // 检查是否存在 "ccw_rotate_seconds" 字段且是整数。
    if (doc.HasMember("ccw_rotate_seconds") && doc["ccw_rotate_seconds"].IsInt())
    {
        // 调用 set_var_ccw_rotate_seconds() 设置该值。
        int ccw_rotate_seconds = doc["ccw_rotate_seconds"].GetInt();
        set_var_ccw_rotate_seconds(ccw_rotate_seconds);
    } else { // 若不存在
        set_var_ccw_rotate_seconds(240); // 设置电机逆时针旋转时间，默认值为 240。
    }
    // 检查是否存在 "input_motor_stop" 字段且是整数。
    if (doc.HasMember("input_motor_stop") && doc["input_motor_stop"].IsInt())
    {
        int input_motor_stop = doc["input_motor_stop"].GetInt();
        set_var_motor_stop_time(input_motor_stop);
    } else {
        set_var_motor_stop_time(240);   // 设置电机停止延迟时间，默认值为 240。
    }
    // 检查是否存在 "input_cw_manual_time" 字段且是整数。
    if (doc.HasMember("input_cw_manual_time") && doc["input_cw_manual_time"].IsInt())
    {
        int input_cw_manual_time = doc["input_cw_manual_time"].GetInt();
        set_var_manual_take_time_cw(input_cw_manual_time);
    } else {
        set_var_manual_take_time_cw(300); // 设置手动顺时针取样时间，默认 300 秒。
    }
    // 检查是否存在 "input_ccw_manual_time" 字段且是整数。
    if (doc.HasMember("input_ccw_manual_time") && doc["input_ccw_manual_time"].IsInt())
    {
        int input_ccw_manual_time = doc["input_ccw_manual_time"].GetInt();
        set_var_manual_take_time_ccw(input_ccw_manual_time);
    } else {
        set_var_manual_take_time_ccw(240); // 置手动逆时针取样时间，默认 240 秒。
    }
    free(buffer); //最后释放之前分配的 JSON 缓冲区内存。
}


void init_main_label(){
    // lv_obj_add_event_cb(objects.main_label, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
}

/*
*/
char main_label_text[128] = "电机停止状态";
static void update_label_cb(void *param) {
  lv_label_set_text((lv_obj_t *)param, main_label_text);
}

typedef  struct btn_bg_param {
    lv_obj_t *btn;
    lv_color_t color;
}BG_COLOR_PARAM;

static BG_COLOR_PARAM btnBgParam;
static void update_btn_bg_async_cb(void *param) {
    BG_COLOR_PARAM  *btn_param = (BG_COLOR_PARAM *)param;
    lv_obj_set_style_bg_color(btn_param->btn, btn_param->color, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_color((lv_obj_t *)param, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
}

static void SetBtnBgColor(lv_obj_t *btn, lv_color_t color){
    btnBgParam.btn = btn;
    btnBgParam.color = color;
    lv_async_call(update_btn_bg_async_cb, &btnBgParam);
}

// 电机是否在使用标志
static bool bMotoInUse = false;

#define   SET_MOTOR_IN_USE(use) do{if(use) printf("line:%d, set motor in use\n", __LINE__); else printf("line:%d set motor not use\n", __LINE__); bMotoInUse = use;}while(0)

static bool bInTakeCW = false;
static bool bQuitThreadCW = false;
void action_manual_take(lv_event_t * e){
    if (!bInTakeCW){

        if (bMotoInUse){
            printf("Motor in use!\n");
            return;
        }
        bInTakeCW = true;
        SET_MOTOR_IN_USE(true);

        SetBtnBgColor(objects.btn_manual_take, lv_palette_main(LV_PALETTE_RED));
        // lv_obj_set_style_bg_color(objects.btn_manual_take, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
        bQuitThreadCW = false;
        std::thread t1([](){
            printf("manual take  start cw\n");
            int s2 = get_var_manual_take_time_cw();
            memset(main_label_text, 0, sizeof(main_label_text));
            strcpy(main_label_text, "电机转动中(正转)");
            lv_async_call(update_label_cb, objects.main_label);
            ACES::GPIO::GetInstance().SetMotorDirection(ACES::MotorDirection::CW);
            ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::ON);
            int secondCount = 0;
            while((secondCount / 10) < s2){
                if (bQuitThreadCW){
                    printf("smanual take  exited\n");
                    memset(main_label_text, 0, sizeof(main_label_text));
                    strcpy(main_label_text, "电机停止状态");
                    lv_async_call(update_label_cb, objects.main_label);
                    // lv_label_set_text(objects.main_label, "电机停止状态");
                    ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::OFF);
                    // bMotoInUse = false;
                    SET_MOTOR_IN_USE(false);
                    bInTakeCW = false;
                    SetBtnBgColor(objects.btn_manual_take, lv_palette_main(LV_PALETTE_BLUE));
                    // lv_obj_set_style_bg_color(objects.btn_manual_take, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
                    return;     // Quit Thread
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                secondCount++;
            }
            ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::OFF);
            memset(main_label_text, 0, sizeof(main_label_text));
            strcpy(main_label_text, "电机停止状态");
            lv_async_call(update_label_cb, objects.main_label);
            // bMotoInUse = false;
            SET_MOTOR_IN_USE(false);
            // LV_PALETTE_BLUE
            // lv_obj_set_style_bg_color(objects.btn_manual_take, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
            SetBtnBgColor(objects.btn_manual_take, lv_palette_main(LV_PALETTE_BLUE));
            bInTakeCW = false;
        });
        t1.detach();

    } else
    {
        // lv_obj_set_style_bg_color(objects.btn_manual_take, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
        bQuitThreadCW = true;
    }
}

static bool bInTakeCCW = false;
static bool bQuitCCWThread = false;
void action_manual_take_ccw(lv_event_t * e)
{
    if (!bInTakeCCW){

        if (bMotoInUse){
            printf("Motor in use!\n");
            return;
        }
        bInTakeCCW = true;
        SET_MOTOR_IN_USE(true);

        SetBtnBgColor(objects.btn_manual_take_ccw, lv_palette_main(LV_PALETTE_RED));
        // lv_obj_set_style_bg_color(objects.btn_manual_take_ccw, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
        bQuitCCWThread = false;
        std::thread t1([](){
            printf("manual take  start cw\n");
            int s2 = get_var_manual_take_time_ccw();
            memset(main_label_text, 0, sizeof(main_label_text));
            strcpy(main_label_text, "电机转动中(反转)");
            lv_async_call(update_label_cb, objects.main_label);
            ACES::GPIO::GetInstance().SetMotorDirection(ACES::MotorDirection::CCW);
            ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::ON);
            int secondCount = 0;
            while((secondCount / 10) < s2){
                if (bQuitCCWThread){
                    printf("smanual take  exited\n");
                    memset(main_label_text, 0, sizeof(main_label_text));
                    strcpy(main_label_text, "电机停止状态");
                    lv_async_call(update_label_cb, objects.main_label);
                    // lv_label_set_text(objects.main_label, "电机停止状态");
                    ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::OFF);
                    // bMotoInUse = false;
                    SET_MOTOR_IN_USE(false);
                    bInTakeCCW = false;
                    SetBtnBgColor(objects.btn_manual_take_ccw, lv_palette_main(LV_PALETTE_BLUE));
                    // lv_obj_set_style_bg_color(objects.btn_manual_take_ccw, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
                    return;     // Quit Thread
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                secondCount++;
            }
            ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::OFF);
            memset(main_label_text, 0, sizeof(main_label_text));
            strcpy(main_label_text, "电机停止状态");
            lv_async_call(update_label_cb, objects.main_label);
            // bMotoInUse = false;
            SET_MOTOR_IN_USE(false);
            SetBtnBgColor(objects.btn_manual_take_ccw, lv_palette_main(LV_PALETTE_BLUE));
            // lv_obj_set_style_bg_color(objects.btn_manual_take_ccw, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
            bInTakeCCW = false;
        });
        t1.detach();

    } else
    {
        // lv_obj_set_style_bg_color(objects.btn_manual_take_ccw, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
        bQuitCCWThread = true;
    }
}




void thread_auto_take(){
    printf("sample thread started\n");
    int secondCount = 0;
    while(!bQuitAutoTakeThread){
        if (bMotoInUse) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        int cwSeconds = get_var_cw_rotate_seconds();
        bMotoInUse = true;
        memset(main_label_text, 0, sizeof(main_label_text));
        strcpy(main_label_text, "电机转动中(正转)");
        lv_async_call(update_label_cb, objects.main_label);
        // lv_label_set_text(objects.main_label, "电机转动中(正转)");
        ACES::GPIO::GetInstance().SetMotorDirection(ACES::MotorDirection::CW);
        ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::ON);
        secondCount = 0;
        while((secondCount / 10) < cwSeconds){
            if (bQuitAutoTakeThread){
                ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::OFF);
                bMotoInUse = false;
                memset(main_label_text, 0, sizeof(main_label_text));
                strcpy(main_label_text, "电机停止状态");
                lv_async_call(update_label_cb, objects.main_label);
                printf("sample thread exited\n");
                return;     // Quit Thread
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            secondCount++;
        }

        // Stop Motor
        ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::OFF);
        ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::OFF);
        memset(main_label_text, 0, sizeof(main_label_text));
        strcpy(main_label_text, "电机冷却状态,禁止操作");
        lv_async_call(update_label_cb, objects.main_label);
        // lv_label_set_text(objects.main_label, "电机冷却状态,禁止操作");
        secondCount = 0;
        int stopTime = get_var_motor_stop_time();
        while((secondCount / 10) < stopTime){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            secondCount++;
        }

        // Push
        int ccwSeconds = get_var_ccw_rotate_seconds();
        memset(main_label_text, 0, sizeof(main_label_text));
        strcpy(main_label_text, "电机转动中(反转)");
        lv_async_call(update_label_cb, objects.main_label);
        // lv_label_set_text(objects.main_label, "电机转动中(反转)");
        ACES::GPIO::GetInstance().SetMotorDirection(ACES::MotorDirection::CCW);
        ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::ON);
        secondCount = 0;
        while((secondCount / 10) < ccwSeconds){
            if (bQuitAutoTakeThread){
                ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::OFF);
                bMotoInUse = false;
                printf("sample thread exited\n");
                memset(main_label_text, 0, sizeof(main_label_text));
                strcpy(main_label_text, "电机停止状态");
                lv_async_call(update_label_cb, objects.main_label);
                return;     // Quit Thread
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            secondCount++;
        }

        ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::OFF);
        bMotoInUse = false;
        memset(main_label_text, 0, sizeof(main_label_text));
        strcpy(main_label_text, "电机停止状态");
        lv_async_call(update_label_cb, objects.main_label);

        int sampleIntervalMinutes = get_var_sample_interval_minutes();

        secondCount = 0;
        while((secondCount / 600) < sampleIntervalMinutes){
            if (bQuitAutoTakeThread){
                printf("sample thread exited\n");
                return;     // Quit Thread
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            secondCount++;
        }
    }

    printf("sample thread exited\n");
}

/*
* 用作自动取灰控制按钮
*/
static bool bInAutoTake = false; //静态变量，记录是否处于自动取灰状态，初始为 false（未启动）。
void action_took_mark(lv_event_t * e)
{
    // 如果当前不在自动取灰状态，说明这是第一次按下，要开启功能。
    if (!bInAutoTake){
        //  将按钮背景色改为红色（表示“工作中”状态）。
        lv_obj_set_style_bg_color(objects.btn_mark_took, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
        bQuitAutoTakeThread = false;    //全局标志位，表示不退出线程（线程运行中）。
        std::thread t1(thread_auto_take); // 创建并启动新线程 thread_auto_take，并使用 detach() 让其后台运行，不阻塞主线程。
        t1.detach();

    } else  //如果已经在自动取灰状态：
    {
        // 将按钮背景色改为蓝色（表示“停止中”状态）。
        lv_obj_set_style_bg_color(objects.btn_mark_took, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
        bQuitAutoTakeThread = true; //切换状态变量，以便下次按钮点击时执行相反操作。
    }
    bInAutoTake = !bInAutoTake;

}

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
#define CONFIG_PATH     "../ui/config.json" // 配置文件路径，存储在项目目录下的 ui 文件夹中。


// 该函数用于在主界面上显示当前电机状态的标签，并根据传入的状态字符串设置标签的颜色。
void show_motor_status_with_color(lv_obj_t * parent, const char * status, lv_color_t color)
{
    lv_obj_t * label = lv_label_create(parent);  // 创建一个标签对象
    lv_label_set_text(label, status);             // 设置标签文本为传入的状态字符串
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);  // 将标签居中对齐到父对象
    lv_obj_set_style_text_color(label, color, LV_PART_MAIN | LV_STATE_DEFAULT); // 设置标签文本颜色
}

// 保存设置按钮的回调函数 原来：action_save_setting_func
void action_save_setting_func(lv_event_t * e)
{
    rapidjson::Document doc;                                    // 表示 JSON 的根文档对象
    rapidjson::StringBuffer buffer;                             // 字符串缓冲区，用于临时存放 JSON 文本。
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);  // 将 doc 序列化为 JSON 字符串，写入 buffer。
    doc.SetObject();                                            //将文档设置为 JSON 对象（即键值对形式的结构）。

    // 获取分配器，用于后续添加成员。
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator(); 
    // 添加字段：采样时间间隔（单位：分钟）, 以 JSON 数值类型添加字段 "sample_interval_minutes"，表示采样时间间隔。
    rapidjson::Value elInterval(rapidjson::kNumberType);        // 创建一个 JSON 数值类型的字段 elInterval。
    // 将其值设为当前系统变量 get_var_sample_interval_minutes()
    elInterval.SetInt(get_var_sample_interval_minutes());       
    // 添加到 JSON 文档中，字段名为 "sample_interval_minutes"
    doc.AddMember("sample_interval_minutes", elInterval, doc.GetAllocator());   

    // 添加字段：正向旋转时间（单位：秒）,  以同样方式添加字段 "motor_cw_seconds"，表示电机顺时针旋转时间。
    rapidjson::Value elCwRotate(rapidjson::kNumberType);
    elCwRotate.SetInt(get_var_motor_cw_seconds());
    doc.AddMember("motor_cw_seconds", elCwRotate, doc.GetAllocator());

    // 添加字段：反向旋转时间（单位：秒）,  以同样方式添加字段 "motor_ccw_seconds"，表示电机逆时针旋转时间。
    rapidjson::Value elCcwRotate(rapidjson::kNumberType);
    elCcwRotate.SetInt(get_var_motor_ccw_seconds());
    doc.AddMember("motor_ccw_seconds", elCcwRotate, doc.GetAllocator());

    // 添加字段：电机停止时间（单位：秒）,  以同样方式添加字段 "input_motor_stop"，表示电机停止时间。
    rapidjson::Value elMotorStop(rapidjson::kNumberType);
    elMotorStop.SetInt(get_var_motor_stop_seconds());
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
    // 检查是否存在 "motor_cw_seconds" 字段且是整数。
    if (doc.HasMember("motor_cw_seconds") && doc["motor_cw_seconds"].IsInt())
    {
        // 调用 set_var_motor_cw_seconds() 设置该值。
        int motor_cw_seconds = doc["motor_cw_seconds"].GetInt();
        set_var_motor_cw_seconds(motor_cw_seconds);
    } else { // 若不存在
        set_var_motor_cw_seconds(300); // 设置电机顺时针旋转时间，默认值为 300。
    }
    // 检查是否存在 "motor_ccw_seconds" 字段且是整数。
    if (doc.HasMember("motor_ccw_seconds") && doc["motor_ccw_seconds"].IsInt())
    {
        // 调用 set_var_motor_ccw_seconds() 设置该值。
        int motor_ccw_seconds = doc["motor_ccw_seconds"].GetInt();
        set_var_motor_ccw_seconds(motor_ccw_seconds);
    } else { // 若不存在
        set_var_motor_ccw_seconds(240); // 设置电机逆时针旋转时间，默认值为 240。
    }
    // 检查是否存在 "input_motor_stop" 字段且是整数。
    if (doc.HasMember("input_motor_stop") && doc["input_motor_stop"].IsInt())
    {
        int input_motor_stop = doc["input_motor_stop"].GetInt();
        set_var_motor_stop_seconds(input_motor_stop);
    } else {
        set_var_motor_stop_seconds(240);   // 设置电机停止延迟时间，默认值为 240。
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
// 设置电机使用状态的宏定义
#define   SET_MOTOR_IN_USE(use) do{if(use) printf("line:%d, set motor in use\n", __LINE__); else printf("line:%d set motor not use\n", __LINE__); bMotoInUse = use;}while(0)

static bool bInTakeCW = false;      
static bool bQuitThreadCW = false;  
// 手动取样按钮的回调函数 
void action_manual_collect(lv_event_t * e){
    if (!bInTakeCW){
        if (bMotoInUse){
            printf("Motor in use!\n");
            return;
        }
        bInTakeCW = true;       // 设置手动取样状态为 true，表示正在进行手动取样操作。
        // 设置电机使用状态为 true，表示电机正在被使用。
        SET_MOTOR_IN_USE(true);
        // 设置按钮背景颜色为红色，表示正在进行手动取样操作。
        SetBtnBgColor(objects.btn_manual_take_cw, lv_palette_main(LV_PALETTE_RED));
        // lv_obj_set_style_bg_color(objects.btn_manual_take, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
        bQuitThreadCW = false;  // 设置退出标志为 false，表示线程可以继续运行。
        // 创建一个新的线程来执行手动取样操作
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
                    SetBtnBgColor(objects.btn_manual_take_cw, lv_palette_main(LV_PALETTE_BLUE));
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
            SetBtnBgColor(objects.btn_manual_take_cw, lv_palette_main(LV_PALETTE_BLUE));
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

// 手动排灰按钮的回调函数
void action_manual_pour(lv_event_t * e)
{
    if (!bInTakeCCW){
        // 如果电机正在使用中，打印提示信息并返回。
        if (bMotoInUse){
            printf("Motor in use!\n");
            return;
        }
        bInTakeCCW = true;          // 设置手动排灰状态为 true，表示正在进行手动排灰操作。
        // 设置电机使用状态为 true，表示电机正在被使用。
        SET_MOTOR_IN_USE(true);
        // 设置按钮背景颜色为红色，表示正在进行手动排灰操作。
        SetBtnBgColor(objects.btn_manual_take_ccw, lv_palette_main(LV_PALETTE_RED));
        // lv_obj_set_style_bg_color(objects.btn_manual_take_ccw, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
        bQuitCCWThread = false;     // 设置退出标志为 false，表示线程可以继续运行。
        // 创建一个新的线程来执行手动排灰操作
        std::thread t1([](){
            printf("manual take  start cw\n");                      // 打印调试信息，表示手动排灰操作开始。
            int s2 = get_var_manual_take_time_ccw();                // 获取手动排灰时间（逆时针旋转时间）。
            memset(main_label_text, 0, sizeof(main_label_text));    // 清空主标签文本缓冲区。
            strcpy(main_label_text, "电机转动中(反转)");    // 设置主标签文本为 "电机转动中(反转)"，表示电机正在逆时针旋转。
            lv_async_call(update_label_cb, objects.main_label);     // 异步更新主标签文本显示。
            ACES::GPIO::GetInstance().SetMotorDirection(ACES::MotorDirection::CCW);// 设置电机方向为逆时针旋转。
            ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::ON);  // 设置电机供电状态为 ON，开始电机工作。
            int secondCount = 0;    // 初始化计时器变量 secondCount，用于记录电机运行时间。
            
            /* 进入循环，直到手动排灰时间达到或退出标志被设置为 true。这里的 s2 是手动排灰时间，单位为秒。循环条件是 secondCount 除以 10 小于 s2，表示每 10 毫秒计数一次。例如，如果 s2 为 30，则循环将持续 300 秒（30 秒）。注意：secondCount 是以 10 毫秒为单位计数的，所以需要除以 10 来转换为秒。*/
            while((secondCount / 10) < s2){
                if (bQuitCCWThread){
                    printf("smanual take  exited\n");
                    memset(main_label_text, 0, sizeof(main_label_text)); // 清空主标签文本缓冲区。
                    strcpy(main_label_text, "电机停止状态");    // 设置主标签文本为 "电机停止状态"，表示电机已停止工作。
                    lv_async_call(update_label_cb, objects.main_label);// 异步更新主标签文本显示。
                    // lv_label_set_text(objects.main_label, "电机停止状态");
                    ACES::GPIO::GetInstance().SetMotorPower(ACES::MotoPowerState::OFF);// 停止电机供电。
                    // bMotoInUse = false; 
                    SET_MOTOR_IN_USE(false); // 设置电机使用状态为 false，表示电机不再被使用。
                    bInTakeCCW = false;
                    SetBtnBgColor(objects.btn_manual_take_ccw, lv_palette_main(LV_PALETTE_BLUE));
                    // lv_obj_set_style_bg_color(objects.btn_manual_take_ccw, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
                    return;     // Quit Thread
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                secondCount++;
            }
            // 
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


// 自动取灰
void thread_auto_take(){
    printf("sample thread started\n");
    int secondCount = 0;
    while(!bQuitAutoTakeThread){
        if (bMotoInUse) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        int cwSeconds = get_var_motor_cw_seconds(); // 获取正转时间
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
        int stopTime = get_var_motor_stop_seconds();
        while((secondCount / 10) < stopTime){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            secondCount++;
        }

        // Push
        int ccwSeconds = get_var_motor_ccw_seconds();
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

void action_auto_collect(lv_event_t * e)
{
    // 如果当前不在自动取灰状态，说明这是第一次按下，要开启功能。
    if (!bInAutoTake){
        //  将按钮背景色改为红色（表示“工作中”状态）。
        lv_obj_set_style_bg_color(objects.btn_auto_take_cw, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
        bQuitAutoTakeThread = false;    //全局标志位，表示不退出线程（线程运行中）。
        std::thread t1(thread_auto_take); // 创建并启动新线程 thread_auto_take，并使用 detach() 让其后台运行，不阻塞主线程。
        t1.detach();

    } else  //如果已经在自动取灰状态：
    {
        // 将按钮背景色改为蓝色（表示“停止中”状态）。
        lv_obj_set_style_bg_color(objects.btn_auto_take_cw, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
        bQuitAutoTakeThread = true; //切换状态变量，以便下次按钮点击时执行相反操作。
    }
    bInAutoTake = !bInAutoTake;

}
// 保存采样设置按钮的回调函数
extern void action_save_sample_setting(lv_event_t * e){
    // 调用保存设置函数，将当前采样设置保存到配置文件中。
    action_save_setting_func(e);
    // 显示保存成功的提示信息
    show_motor_status_with_color(objects.main_label, "采样设置已保存", lv_palette_main(LV_PALETTE_GREEN));
    // lv_label_set_text(objects.main_label, "采样设置已保存");
    // 延时 2 秒后清除提示信息
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // 清除主界面标签文本
    memset(main_label_text, 0, sizeof(main_label_text));
    strcpy(main_label_text, "电机停止状态");
    lv_async_call(update_label_cb, objects.main_label);
    // lv_label_set_text(objects.main_label, "电机停止状态");
    // 重新加载配置文件
    load_configs(); // 重新加载配置文件，以确保界面显示最新的设置。
    // 更新界面上的采样设置显示
    //lv_label_set_text(objects.label_sample_interval, std::to_string(get_var_sample_interval_minutes()).c_str());
    //lv_label_set_text(objects.label_motor_cw_seconds, std::to_string(get_var_motor_cw_seconds()).c_str());  
}
// 保存移位设置按钮的回调函数
extern void action_save_shift_setting(lv_event_t * e){

}
// 保存通信设置按钮的回调函数
extern void action_save_communicate_setting(lv_event_t * e){

}
// 电机停止按钮的回调函数
extern void action_btn_motor_stop(lv_event_t * e){

}
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

static bool bQuitAutoTakeThread = false;

#define CONFIG_PATH     "/opt/sample/config.json"
void action_save_setting_func(lv_event_t * e)
{
    rapidjson::Document doc;
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    doc.SetObject();

    rapidjson::Value elInterval(rapidjson::kNumberType);
    elInterval.SetInt(get_var_sample_interval_minutes());
    doc.AddMember("sample_interval_minutes", elInterval, doc.GetAllocator());

    rapidjson::Value elCwRotate(rapidjson::kNumberType);
    elCwRotate.SetInt(get_var_cw_rotate_seconds());
    doc.AddMember("cw_rotate_seconds", elCwRotate, doc.GetAllocator());


    rapidjson::Value elCcwRotate(rapidjson::kNumberType);
    elCcwRotate.SetInt(get_var_ccw_rotate_seconds());
    doc.AddMember("ccw_rotate_seconds", elCcwRotate, doc.GetAllocator());

    rapidjson::Value elMotorStop(rapidjson::kNumberType);
    elMotorStop.SetInt(get_var_motor_stop_time());
    doc.AddMember("input_motor_stop", elMotorStop, doc.GetAllocator());

    rapidjson::Value elManualTakeCW(rapidjson::kNumberType);
    elManualTakeCW.SetInt(get_var_manual_take_time_cw());
    doc.AddMember("input_cw_manual_time", elManualTakeCW, doc.GetAllocator());

    rapidjson::Value elManualTakeCCW(rapidjson::kNumberType);
    elManualTakeCCW.SetInt(get_var_manual_take_time_ccw());
    doc.AddMember("input_ccw_manual_time", elManualTakeCCW, doc.GetAllocator());

    doc.Accept(writer);
    const char* json = buffer.GetString();

    FILE *fp = fopen(CONFIG_PATH, "wb+");
    if (NULL == fp){
        printf("open file %s failed\n", CONFIG_PATH);
        return;
    }
    fwrite(json, strlen(json), 1, fp);
    fclose(fp);
}

void load_configs(){
    FILE *fp = fopen(CONFIG_PATH, "rb");
    if (NULL == fp){
        printf("open file %s failed\n", CONFIG_PATH);
        return;
    }

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buffer = (char *)malloc(size + 1);
    if (NULL == buffer){
        printf("malloc buffer failed\n");
        fclose(fp);
        return;
    }
    fread(buffer, size, 1, fp);
    fclose(fp);

    buffer[size] = '\0';
    rapidjson::Document doc;
    doc.Parse(buffer);
    if (doc.HasParseError())
    {
        free(buffer);
        printf("parse json failed\n");
        return;
    }

    if (doc.HasMember("sample_interval_minutes") && doc["sample_interval_minutes"].IsInt())
    {
        int sample_interval_minutes = doc["sample_interval_minutes"].GetInt();
        set_var_sample_interval_minutes(sample_interval_minutes);
    }

    if (doc.HasMember("cw_rotate_seconds") && doc["cw_rotate_seconds"].IsInt())
    {
        int cw_rotate_seconds = doc["cw_rotate_seconds"].GetInt();
        set_var_cw_rotate_seconds(cw_rotate_seconds);
    } else {
        set_var_cw_rotate_seconds(300);
    }

    if (doc.HasMember("ccw_rotate_seconds") && doc["ccw_rotate_seconds"].IsInt())
    {
        int ccw_rotate_seconds = doc["ccw_rotate_seconds"].GetInt();
        set_var_ccw_rotate_seconds(ccw_rotate_seconds);
    } else {
        set_var_ccw_rotate_seconds(240);
    }

    if (doc.HasMember("input_motor_stop") && doc["input_motor_stop"].IsInt())
    {
        int input_motor_stop = doc["input_motor_stop"].GetInt();
        set_var_motor_stop_time(input_motor_stop);
    } else {
        set_var_motor_stop_time(240);
    }

    if (doc.HasMember("input_cw_manual_time") && doc["input_cw_manual_time"].IsInt())
    {
        int input_cw_manual_time = doc["input_cw_manual_time"].GetInt();
        set_var_manual_take_time_cw(input_cw_manual_time);
    } else {
        set_var_manual_take_time_cw(300);
    }

    if (doc.HasMember("input_ccw_manual_time") && doc["input_ccw_manual_time"].IsInt())
    {
        int input_ccw_manual_time = doc["input_ccw_manual_time"].GetInt();
        set_var_manual_take_time_ccw(input_ccw_manual_time);
    } else {
        set_var_manual_take_time_ccw(240);
    }

    free(buffer);
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
static bool bInAutoTake = false;
void action_took_mark(lv_event_t * e)
{
    if (!bInAutoTake){
        lv_obj_set_style_bg_color(objects.btn_mark_took, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
        bQuitAutoTakeThread = false;
        std::thread t1(thread_auto_take);
        t1.detach();

    } else
    {
        lv_obj_set_style_bg_color(objects.btn_mark_took, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
        bQuitAutoTakeThread = true;
    }
    bInAutoTake = !bInAutoTake;

}

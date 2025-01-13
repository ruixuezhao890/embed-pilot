/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_desk_ui.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2025/1/3
*********************************************************************
*********
*/
#include "embed_pilot/app_sys/app_desk/app_desk.h"
#include "embed_pilot/app_sys/app_desk/app_desk_ui/square_line/ui.h"
#include "ep_lib.h"

#define LOG_TAG "app_desk_ui"

LV_FONT_DECLARE(Font_500w);//引入字库

static const std::string week[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat","Sun"};

static ep_hw_abstract::rtc_data_time time_static={0,0,0,0,0,0};

static bool first_init= false;

static int calculateDayOfWeek(int year, int month, int day) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    int k = year % 100;
    int j = year / 100;
    int h = day + 13 * (month + 1) / 5 + k + k / 4 + j / 4 + 5 * j;
    h = h % 7;
    return ((h + 5) % 7) + 1; // Returns 1 (Sunday) to 7 (Saturday)
}

static void scroll_end_event(lv_event_t * e)
{
    lv_obj_t * cont = lv_event_get_target(e); // 获取事件的初始对象

    /* 获取事件的事件代码 */
    if(lv_event_get_code(e) == LV_EVENT_SCROLL_END)
    {
        /* 判断是否在滚动中 */
        if (lv_obj_is_scrolling(cont))
        {
            return;
        }
        auto desk_ui = (app_desk_ui *)lv_event_get_user_data(e);
        lv_coord_t child_cnt = lv_obj_get_child_cnt(cont); // 获取子界面的数量

        /* 获取父对象y轴的中心坐标值 */
        lv_area_t cont_a;
        lv_obj_get_coords(cont, &cont_a); // 将cont对象的坐标复制到cont_a
        lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2; // 获取界面的高像素大小/2

        /* 遍历子界面 */
        for (lv_coord_t i = 0; i < child_cnt; i++) {
            lv_obj_t* child = lv_obj_get_child(cont, i); // 通过索引获取子对象

            /* 获取子对象y轴的中心坐标值 */
            lv_area_t child_a;
            lv_obj_get_coords(child, &child_a);
            lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2; // 获取界面中按钮高像素值的大小/2

            /* 判断子类是否位于父类的y轴的正中心 */
            if (child_y_center == cont_y_center)
            {
                //绘制图标
                auto child_package=(app_desk_packager *)lv_obj_get_user_data(child);
                if (child_package->get_icon()){//存在图标
                    lv_img_set_src(ui_AppImage1,child_package->get_icon());
                } else{
                    lv_img_set_src(ui_AppImage1,&ui_img_defaut_png);
                }
                desk_ui->get_screen_widget_child().app_index=child_package->get_app_package_id();
                desk_ui->get_screen_widget_child().app_click_enable=1;
                //添加动画
                //1.控制宽度
                lv_anim_t a_width;
                lv_anim_init(&a_width);
                lv_anim_set_var(&a_width, ui_AppImage1);
                lv_anim_set_values(&a_width, 0, 60);
                lv_anim_set_exec_cb(&a_width, [](void *var,int32_t v){
                    lv_obj_set_width((lv_obj_t *)var,v);
                });
                lv_anim_set_time(&a_width, 1000);
                lv_anim_set_path_cb(&a_width, lv_anim_path_ease_in_out);
                lv_anim_start(&a_width);
                //2.控制高度
                lv_anim_t a_height;
                lv_anim_init(&a_height);
                lv_anim_set_var(&a_height, ui_AppImage1);
                lv_anim_set_values(&a_height, 0, 60); // 假设高度也变化到60
                lv_anim_set_exec_cb(&a_height, [](void *var,int32_t v){
                    lv_obj_set_height((lv_obj_t *)var,v);
                });
                lv_anim_set_time(&a_height, 1000);
                lv_anim_set_path_cb(&a_height, lv_anim_path_ease_in_out);
                lv_anim_start(&a_height);
            }
        }
    }
}

static void change_query_city(lv_event_t * e){
    auto code =lv_event_get_code(e);
    if(code==LV_EVENT_CLICKED){
        auto desk_app =(app_desk *)lv_event_get_user_data(e);

    }
}

static void wireless_img_update(lv_timer_t * timer){
    int flag; ep_hw_abstract::hardware_abstract::is_connect_wifi(flag);// todo只有WiFi，蓝牙还在规划
    if(flag){
        timer->period=300000;
        lv_obj_clear_flag(ui_WifiLabel4,LV_OBJ_FLAG_HIDDEN);
    }else{
        lv_obj_add_flag(ui_WifiLabel4,LV_OBJ_FLAG_HIDDEN);
    }
}

void app_desk_ui::desk_ui_init() {
    // 合并初始化和赋值操作，减少代码行数
    ui_init(this->screen_obj_t);
    first_init = true;

// 使用结构体初始化列表来简化代码
    widget.time_label0=ui_TimeLabel1;
    widget.time_label1=ui_TimeLabel2;
    widget.app_install_panel=ui_AppPanel3;
    widget.app_icon_img=ui_AppImage1;

// 将事件回调函数添加到面板中
    lv_obj_add_event_cb(widget.app_install_panel, scroll_end_event, LV_EVENT_SCROLL_END, this);

// 获取RTC数据并计算星期
    ep_hw_abstract::hardware_abstract::get_rtc_data_time(time_static);
    int i = calculateDayOfWeek(time_static.year, time_static.month, time_static.day);

// 使用三元运算符简化字符串格式化
    std::string str0 = ep_string_control::format("{}", time_static.hour);
    std::string str1 = ep_string_control::format("{}", time_static.minute > 9 ? std::to_string(time_static.minute) : "0" + std::to_string(time_static.minute));

// 优化日期字符串的格式化
    std::string str2 = ep_string_control::format("{}-{}-{}-{}", time_static.year, time_static.month, time_static.day, week[i]);

// 设置标签文本
    lv_label_set_text(widget.time_label0, str0.c_str());
    lv_label_set_text(widget.time_label1, str1.c_str());
    lv_label_set_text(ui_DataLabel2, str2.c_str());

// 创建定时器更新无线图像
    lv_timer_create(wireless_img_update, 1000, nullptr);

}

static void time_label_update(){
    ep_hw_abstract::rtc_data_time time;
    ep_hw_abstract::hardware_abstract::get_rtc_data_time(time);

// 只有当秒变化超过30或者分钟变化时，才更新时间和日期标签
    if (time.second - time_static.second > 30 || time.minute != time_static.minute) {
        // 格式化小时
        auto str0 = ep_string_control::format("{}", time.hour);
        // 格式化分钟，确保两位数字
        std::string str1 = (time.minute > 9) ?
                           ep_string_control::format("{}", time.minute) :
                           ep_string_control::format("0{}", time.minute);

        // 更新静态时间变量
        time_static = time;

        // 更新标签文本
        lv_label_set_text(ui_TimeLabel1, str0.c_str());
        lv_label_set_text(ui_TimeLabel2, str1.c_str());

        // 如果日期变化，则更新日期标签
        if (time.day != time_static.day||first_init) {
            first_init= false;
            int i = calculateDayOfWeek(time.year, time.month, time.day);
            auto str2 = ep_string_control::format("{}-{}-{}-{}", time.year, time.month, time.day, week[i]);
            lv_label_set_text(ui_DataLabel2, str2.c_str());
        }
    }

}




void app_desk_ui::monitor_weather_change(const std::string Weather) {
    std::string pic_path = "A:/weather_pic/{}.png";
    std::string weather_condition = Weather;

// 特殊处理多云天气，根据时间判断是白天还是夜间
    if (weather_condition == "多云") {
        ep_hw_abstract::rtc_data_time time;
        ep_hw_abstract::hardware_abstract::get_rtc_data_time(time);
        weather_condition = (time.hour >= 8 && time.hour <= 18) ? "白天-多云" : "夜间-多云";
    }

// 格式化路径
    pic_path = ep_string_control::format(pic_path, weather_condition);

//    ep_info_log(pic_path);
    lv_img_set_src(ui_WeatherImage2, pic_path.c_str());
}

void app_desk_ui::on_foreground() {
    time_label_update();
}

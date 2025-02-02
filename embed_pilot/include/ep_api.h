/**
*********************************************************************
*********
* @project_name :embed_pilot
* @file : ep_api.hpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/24 
*********************************************************************
*********
*/


#ifndef EMBED_PILOT_EP_API_HPP
#define EMBED_PILOT_EP_API_HPP

#include "ep_def.h"
#ifdef EP_USE_FMT_LIB
#define FMT_HEADER_ONLY
#include "components/libraries/fmt_lib/fmt/core.h"
#endif
#include "components/libraries/easy_logger/elog.h"

#ifdef ELOG_OUTPUT_ENABLE
#define ep_debug_log(...)  do{ \
    std::string string_define = ep_string_control::format(__VA_ARGS__); \
    ep_log_d(string_define.c_str()); \
}while(0);
#else
#define ep_debug_log(...)  do{}while(0);
#endif

#ifdef ELOG_OUTPUT_ENABLE
#define ep_assert_log(...)  do{ \
        std::string string_define = ep_string_control::format(__VA_ARGS__); \
        ep_log_a(string_define.c_str()); \
    }while(0);
#else
#define ep_assert_log(...)  do{}while(0);
#endif

#ifdef ELOG_OUTPUT_ENABLE
#define ep_error_log(...)  do{ \
        std::string string_define = ep_string_control::format(__VA_ARGS__); \
        ep_log_e(string_define.c_str()); \
    }while(0);
#else
#define ep_error_log(...)  do{}while(0);
#endif

#ifdef ELOG_OUTPUT_ENABLE
#define ep_warn_log(...)  do{ \
        std::string string_define = ep_string_control::format(__VA_ARGS__); \
        ep_log_w(string_define.c_str()); \
    }while(0);
#else
#define ep_warn_log(...)  do{}while(0);
#endif

#ifdef ELOG_OUTPUT_ENABLE
#define ep_info_log(...)  do{ \
        std::string string_define = ep_string_control::format(__VA_ARGS__); \
        ep_log_i(string_define.c_str()); \
    }while(0);
#else
#define ep_info_log(...)  do{}while(0);
#endif

#ifdef ELOG_OUTPUT_ENABLE
#define ep_verbose_log(...)  do{ \
        std::string string_define = ep_string_control::format(__VA_ARGS__); \
        ep_log_v(string_define.c_str()); \
    }while(0);
#else
#define ep_verbose_log(...)  do{}while(0);
#endif




namespace ep_auto_init_control{
    void ep_auto_init();
};

namespace ep_data_up_control{
    void ep_data_up();
};
namespace ep_memory_control{
    //todo 先这样子写着，有没有内存管理另说
    void * ep_malloc(size_t size);
    void   ep_free(void * memory);
    size_t ep_malloc_usable_size(void * memory);
    void * ep_init_alloc(size_t num,size_t size);
    void * ep_realloc(void * memory,size_t size);

}
namespace ep_string_control{
    template<typename... Args>
    std::string format(const std::string& format, Args &&...args){
#ifdef EP_USE_FMT_LIB
        return fmt::format(format, std::forward<Args>(args)...);
#else

        return "no lib";
#endif
    }

    template<typename... Args>
    int ep_printf(const char *format, Args &&...args){
#ifdef EP_USE_DEBUG

        auto string=ep_string_control::format(format, std::forward<Args>(args)...);

#ifdef HW_ESP32
        return Serial.print(string.c_str());
#endif
#else
        return 0;
#endif
    }

    template<typename... Args>
    int ep_new_line_printf(const char *format, Args &&...args){
        int num=0;
        num=ep_printf(format, std::forward<Args>(args)...);
        num+=ep_printf("\r\n");
        return num;
    }


};


namespace ep_interrupt_control{
     void ep_interrupt_enable();
     bool ep_interrupt_disable();
};

namespace ep_delay_control{
     void ep_delay_us(uint32_t nums);
     void ep_delay_ms(uint32_t nums);
     void ep_delay_os(uint32_t nums);
};


#endif //EMBED_PILOT_EP_API_HPP

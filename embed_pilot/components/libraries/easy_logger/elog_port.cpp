/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2015-04-28
 */

#include "ep_lib.h"
#include <components/libraries/easy_logger/elog.h>

/**
 * EasyLogger port initialize
 *
 * @return result
 */
ElogErrCode elog_port_init(void) {
    ElogErrCode result = ELOG_NO_ERR;

    /* add your code here */
    
    return result;
}

/**
 * EasyLogger port deinitialize
 *
 */
void elog_port_deinit(void) {

    /* add your code here */

}

/**
 * output log port interface
 *
 * @param log output of log
 * @param size log size
 */
void elog_port_output(const char *log, size_t size) {
    
    /* add your code here */
    auto temp_string=ep_string_control::format("{:.{}s}",log,size);
    ep_string_control::ep_printf(temp_string.c_str());
}

/**
 * output lock
 */
void elog_port_output_lock(void) {
    
    /* add your code here */
    ep_interrupt_control::ep_interrupt_disable();
}

/**
 * output unlock
 */
void elog_port_output_unlock(void) {
    
    /* add your code here */
    ep_interrupt_control::ep_interrupt_enable();
}

/**
 * get current time interface
 *
 * @return current time
 */
const char *elog_port_get_time(void) {

    /* add your code here */
    static char cur_system_time[16] = { 0 };

#if (INCLUDE_xTaskGetSchedulerState  == 1 )
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
#endif
    TickType_t tick = xTaskGetTickCount();
    snprintf(cur_system_time, 16, "%d.%.3d", (tick / configTICK_RATE_HZ), tick % configTICK_RATE_HZ);
#if (INCLUDE_xTaskGetSchedulerState  == 1 )
    }
#endif

    return cur_system_time;
    
}

/**
 * get current process name interface
 *
 * @return current process name
 */
const char *elog_port_get_p_info(void) {
    
    /* add your code here */
    return " ";
}

/**
 * get current thread name interface
 *
 * @return current thread name
 */
const char *elog_port_get_t_info(void) {

    /* add your code here */
#if (INCLUDE_xTaskGetSchedulerState  == 1 )
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
#endif
    return pcTaskGetName(xTaskGetCurrentTaskHandle());
#if (INCLUDE_xTaskGetSchedulerState  == 1 )
    }
#endif

    return "";
    
}
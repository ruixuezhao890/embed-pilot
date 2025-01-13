/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_mange.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/24 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_APP_MANGER_H
#define MICRO_SNOW_APP_MANGER_H
#include <list>
#include <vector>
#include "application/app_blueprint/app.h"

namespace ep_application{
    class app_manager{
    private:

    public:
        enum class app_lifecycle_state:uint8_t {
            ON_CREATE=0,
            ON_RESUME,
            ON_RUNNING,
            ON_RUNNING_BACKGROUND,
            ON_PAUSE,
            ON_DESTROY
        };
        struct app_lifecycle_t{
            app_base * app{};
            app_lifecycle_state state=app_lifecycle_state::ON_CREATE;
        };
    private:
        /* A list of apps' lifecycle */
        std::vector<app_lifecycle_t> app_lifecycle_list_;
        int _search_app_lifecycle_list(app_base * app);

        /* A buffer of apps that about to add in lifecycle */
        /* To avoid push_back method while lifecycle list's iterating */
        std::vector<app_lifecycle_t> app_create_buffer_;
        int _search_app_create_buffer(app_base * app);

    public:
        ~app_manager()=default;

        app_base * create_app(app_package_base * app_package);

        bool start_app(app_base* app);

        bool close_app(app_base* app);

        void update();

        bool destroy_app(app_base* app);

        void destroy_all_apps();

        inline size_t get_created_app_num(){return app_lifecycle_list_.size();}

        inline const std::vector<app_lifecycle_t>* getAppLifecycleList() { return &app_lifecycle_list_; }
    };


}
#endif //MICRO_SNOW_APP_MANGER_H

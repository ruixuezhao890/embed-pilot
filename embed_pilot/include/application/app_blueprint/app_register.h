/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_register.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/24 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_APP_REGISTER_H
#define MICRO_SNOW_APP_REGISTER_H
#include "app.h"
#include <vector>
namespace ep_application{
    class app_register{
    private:
        std::vector<app_package_base*> app_packer_vector_;
    public:
        ~app_register();

        inline app_package_base * get_install_app_package(uint8_t id){return app_packer_vector_[id];}

        inline app_package_base * get_install_app_package(const char * name){
            for (auto &item: app_packer_vector_) {
                if(name==item->get_app_name()){
                    return item;
                }
            }
            return nullptr;
        }

        inline std::size_t get_install_app_num(){return app_packer_vector_.size();}

        bool install(app_package_base *,void* user_data= nullptr);

        bool uninstall(app_package_base *,bool free_memory= true);

        void uninstall_all_apps(bool free_memory= true);

        bool is_app_installed(app_package_base *);
    };
}
#endif //MICRO_SNOW_APP_REGISTER_H

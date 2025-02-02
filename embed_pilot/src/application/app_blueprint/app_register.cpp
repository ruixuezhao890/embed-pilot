/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_register.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/25 
*********************************************************************
*********
*/

#include "application/app_blueprint/app_register.h"

using namespace ep_application;

app_register::~app_register() {
    uninstall_all_apps();
}

bool app_register::install(app_package_base *app_packager, void *user_data) {
    if (app_packager== nullptr){
        return false;
    }
    if (is_app_installed(app_packager)){
        return false;
    }

    app_packager->set_user_data(user_data);
    app_packager->set_app_package_id(app_packer_vector_.size());
    app_packer_vector_.push_back(app_packager);

    return true;
}

bool app_register::uninstall(app_package_base *app_packager, bool free_memory) {
    if (app_packager== nullptr){
        return false;
    }
    for (auto item = app_packer_vector_.begin(); item != app_packer_vector_.end(); item++) {
        if (*item==app_packager){
            if (free_memory){
                delete (*item);
            }
            app_packer_vector_.erase(item);
            return true;
        }
    }
    return false;
}

void app_register::uninstall_all_apps(bool free_memory) {
    if (free_memory){
        for (const auto & item:app_packer_vector_) {
            delete item;
        }
    }
    app_packer_vector_.clear();
}

bool app_register::is_app_installed(app_package_base * app_packager) {
    if (app_packager== nullptr){
        return false;
    }
    for (const auto & item:app_packer_vector_) {
        if (item==app_packager){
            return true;
        }
    }
    return false;
}

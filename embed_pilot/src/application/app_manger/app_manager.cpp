/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_manager.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/25 
*********************************************************************
*********
*/
#include "application/app_manager/app_manger.h"
#include "ep_lib.h"
namespace ep_application{
    /**
  * Searches for an app in the lifecycle list.
  * @param app The app_base pointer to search for.
  * @return The index of the app in the lifecycle list or EP_EINVAL if not found.
  */
    int app_manager::_search_app_lifecycle_list(app_base *app) {
        if (app == nullptr) {
            return EP_EINVAL;
        }

        for (int i = 0; i < app_lifecycle_list_.size(); ++i) {
            if (app_lifecycle_list_[i].app == app) {
                return i;
            }
        }
        return EP_EINVAL;
    }

    /**
     * Searches for an app in the create buffer.
     * @param app The app_base pointer to search for.
     * @return The index of the app in the create buffer or EP_EINVAL if not found.
     */
    int app_manager::_search_app_create_buffer(app_base *app) {
        if (app == nullptr) {
            return EP_EINVAL;
        }

        for (int i = 0; i < app_create_buffer_.size(); ++i) {
            if (app_create_buffer_[i].app == app) {
                return i;
            }
        }
        return EP_EINVAL;
    }

    /**
   * Creates a new application from a given package.
   *
   * This method instantiates a new application based on the provided app package.
   * It sets up the application's UI and lifecycle state, and adds it to the creation buffer.
   *
   * @param app_package Pointer to the app_package_base containing the app to create.
   * @return Pointer to the newly created app_base instance, or nullptr if creation failed.
   */
    app_base *app_manager::create_app(app_package_base *app_package) {
        // Check if the provided app package is valid
        if (app_package == nullptr) {
            return nullptr;
        }
        // Attempt to create a new app instance using the app package
        auto new_app = (app_base *)app_package->new_app();
        if (!new_app) {
            return nullptr;
        }
        // Set the app packager for the new app
        new_app->set_app_packager(app_package);

        // Create and set the UI for the new app
        auto app_ui_ = (app_ui_base *)new_app->ui_create();
        new_app->set_app_ui(app_ui_);
        // Initialize the UI and the app itself
        new_app->ui_on_create();
        new_app->on_create();
        // Create a new lifecycle entry for the app and add it to the creation buffer
        app_lifecycle_t new_lifecycle;
        new_lifecycle.app = new_app;
        new_lifecycle.state = app_lifecycle_state::ON_CREATE;
//        for (auto & item:app_create_buffer_) {//检查是否已经存在该app，不再重新加入
//            if (item.app->get_app_name()==new_app->get_app_name()){
//                return item.app;
//            }
//        }
        app_create_buffer_.push_back(new_lifecycle);
        // Set the app package ID based on the size of the creation buffer
        app_package->set_app_package_id(app_create_buffer_.size());
        // Return the pointer to the newly created app
        return new_app;
    }

    /**
 * Starts an application.
 *
 * This method starts the specified application by updating its lifecycle state.
 * It searches for the application in the creation buffer and the lifecycle list
 * to determine its current state and then updates it accordingly.
 *
 * @param app Pointer to the app_base instance of the application to start.
 * @return True if the application was started successfully, false otherwise.
 */
    bool app_manager::start_app(app_base *app) {
        // Search for the app in the creation buffer
        int index = _search_app_create_buffer(app);
        if (index >= 0) {
            // If found, update the state to ON_RESUME
            app_create_buffer_[index].state = app_lifecycle_state::ON_RESUME;
            return true;
        }
        // If not found in the creation buffer, search in the lifecycle list
        index = _search_app_lifecycle_list(app);
        if (index < 0) {
            // If not found in either, return false
            return false;
        }
        // Update the state of the app based on its current lifecycle state
        switch (app_lifecycle_list_[index].state) {
            case app_lifecycle_state::ON_CREATE:
                // Transition from ON_CREATE to ON_RESUME
                app_lifecycle_list_[index].state = app_lifecycle_state::ON_RESUME;
                break;
            case app_lifecycle_state::ON_RESUME:
                // Already in ON_RESUME, do nothing
                break;
            case app_lifecycle_state::ON_RUNNING:
                // Already running, do nothing
                break;
            case app_lifecycle_state::ON_RUNNING_BACKGROUND:
                // Transition from background to ON_RESUME
                app_lifecycle_list_[index].state = app_lifecycle_state::ON_RESUME;
                break;
            case app_lifecycle_state::ON_PAUSE:
                // Transition from ON_PAUSE to ON_RESUME
                app_lifecycle_list_[index].state = app_lifecycle_state::ON_RESUME;
                break;
            case app_lifecycle_state::ON_DESTROY:
                // The app is being destroyed, cannot start
                break;
            default:
                // Handle any other unspecified states
                break;
        }
        // Return true to indicate the app has started successfully
        return true;
    }
    /**
   * Closes the specified application if it is currently managed by the app manager.
   *
   * This function attempts to close an application by updating its lifecycle state.
   * If the application is not yet fully initialized (i.e., it has been created but
   * not yet pushed into the active lifecycle list), it will be marked as paused.
   * If the application is already in the lifecycle list, its state will be updated
   * accordingly before closing.
   *
   * @param app Pointer to the app_base object representing the application to close.
   * @return true if the application was successfully closed or marked for closure, false otherwise.
   */
    bool app_manager::close_app(app_base *app) {
        // Check if the app is in the creation buffer and not yet in the lifecycle list
        int index = _search_app_create_buffer(app);
        if (index >= 0)
        {
            // Mark the app as paused in the creation buffer
            app_create_buffer_[index].state = app_lifecycle_state::ON_PAUSE;
            return true;
        }
        // Search for the app in the lifecycle list
        index = _search_app_lifecycle_list(app);
        if (index < 0)
            return false; // App not found in the lifecycle list
        // Update the state of the app based on its current lifecycle state
        switch (app_lifecycle_list_[index].state)
        {
            case app_lifecycle_state::ON_CREATE:
                // No action needed if the app is in the creation state
                break;
            case app_lifecycle_state::ON_RESUME:
                // Pause the app if it is currently resumed
                app_lifecycle_list_[index].state = app_lifecycle_state::ON_PAUSE;
                break;
            case app_lifecycle_state::ON_RUNNING:
                // Pause the app if it is currently running
                app_lifecycle_list_[index].state = app_lifecycle_state::ON_PAUSE;
                break;
            case app_lifecycle_state::ON_RUNNING_BACKGROUND:
                // No action needed if the app is running in the background
                break;
            case app_lifecycle_state::ON_PAUSE:
                // No action needed if the app is already paused
                break;
            case app_lifecycle_state::ON_DESTROY:
                // This case should not occur as the app is already marked for destruction
                break;
            default:
                // Handle any other unspecified states
                break;
        }
        // Return true to indicate that the app closure process has started
        return true;
    }

    /**
 * Updates the state of all managed applications based on their lifecycle events.
 *
 * This function iterates through the list of applications and updates their
 * lifecycle state according to their current flags and conditions. It also
 * handles the transition between different lifecycle states and performs
 * the necessary actions for each state change.
 */
    void app_manager::update() {
        // Iterate over the lifecycle list of applications
        for (auto iter = app_lifecycle_list_.begin(); iter != app_lifecycle_list_.end();) {
            // Check if the application is about to start
            if (iter->app->is_going_start()) {
                iter->app->ui_on_show();
                iter->app->reset_going_start_flag(); // Reset the start flag
                iter->state = app_lifecycle_state::ON_RESUME; // Transition to the resume state
            }
            // Check if the application is about to close
            if (iter->app->is_going_close()) {
                iter->app->reset_going_close_flag(); // Reset the close flag
                // Determine the next state based on whether background running is allowed
                if (iter->app->is_allow_background_running()) {
                    iter->app->ui_on_hide();
                    iter->state = app_lifecycle_state::ON_PAUSE;
                } else {
                    iter->state = app_lifecycle_state::ON_DESTROY;
                }
            }
            // Check if the application is about to be destroyed
            if (iter->app->is_going_destroy()) {
                iter->app->reset_going_destroy_flag(); // Reset the destroy flag
                iter->state = app_lifecycle_state::ON_DESTROY; // Transition to the destroy state
            }
//            ep_string_control::ep_new_line_printf("name:{},state:{}",iter->app->get_app_name(),(int)iter->state);
            // Finite State Machine (FSM) for application lifecycle
            switch (iter->state) {
                case app_lifecycle_state::ON_CREATE:
                    // No action needed for the create state
                    break;
                case app_lifecycle_state::ON_RESUME:
                    iter->app->on_resume(); // Call the resume method
                    iter->state = app_lifecycle_state::ON_RUNNING; // Transition to the running state
                    break;
                case app_lifecycle_state::ON_RUNNING:
                    iter->app->ui_on_foreground();
                    iter->app->on_running(); // Call the running method
                    break;
                case app_lifecycle_state::ON_RUNNING_BACKGROUND:
                    iter->app->on_running_background_running(); // Call the background running method
                    break;
                case app_lifecycle_state::ON_PAUSE:
                    iter->app->on_pause(); // Call the pause method
                    iter->state = app_lifecycle_state::ON_RUNNING_BACKGROUND; // Transition to the background running state
                    break;
                case app_lifecycle_state::ON_DESTROY:
                    // Perform actions equivalent to destroyApp()
                    iter->app->on_pause(); // Call the pause method
                    iter->app->on_destroy(); // Call the destroy method
                    iter->app->delete_app_pointer(iter->app); // Delete the application pointer
                    // Remove the application from the list and update the iterator
                    iter = app_lifecycle_list_.erase(iter);
                    continue; // Skip the increment to avoid invalidating the iterator
                default:
                    // Handle any other unspecified states
                    break;
            }
            // Move to the next application in the list
            iter++;
        }
        // Move applications from the creation buffer to the lifecycle list
        if (!app_create_buffer_.empty()) {
            for (const auto& app : app_create_buffer_) {
                app_lifecycle_list_.push_back(app); // Add the application to the lifecycle list
            }
            app_create_buffer_.clear(); // Clear the creation buffer
        }
    }

    /**
    * Destroys the specified application and removes it from management.
    *
    * This function attempts to find and destroy the given application by
    * removing it from the lifecycle list or creation buffer and calling
    * its onPause and onDestroy methods. If the application is found and
    * successfully destroyed, the function returns true; otherwise, it returns false.
    *
    * @param app Pointer to the application to be destroyed.
    * @return bool True if the application was destroyed, false otherwise.
    */
    bool app_manager::destroy_app(app_base *app) {
        // Check if the application pointer is valid
        if (!app) {
            return false;
        }
        // Search for the application in the creation buffer
        for (auto iter = app_create_buffer_.begin(); iter != app_create_buffer_.end(); ++iter) {
            if (iter->app == app) {
                // Remove the application from the creation buffer
                app_create_buffer_.erase(iter);
                return true;
            }
        }
        // Search for the application in the lifecycle list
        for (auto iter = app_lifecycle_list_.begin(); iter != app_lifecycle_list_.end(); ++iter) {
            if (iter->app == app) {
                // Call the application's onPause method
                iter->app->on_pause();
                // Call the application's onDestroy method
                iter->app->on_destroy();
                // Delete the application using its app pointer
                iter->app->delete_app_pointer(iter->app);
                // Remove the application from the lifecycle list
                app_lifecycle_list_.erase(iter);
                return true;
            }
        }
        // If the application was not found in either list, return false
        return false;
    }

    /**
 * Destroys all managed applications and clears all lists.
 *
 * This function iterates through the lifecycle list and creation buffer,
 * calling onPause and onDestroy methods for each application, and then
 * deleting the application pointers. After all applications are destroyed,
 * both the lifecycle list and creation buffer are cleared.
 */
    void app_manager::destroy_all_apps() {
        // Iterate through the lifecycle list and destroy each application
        for (auto& i : app_lifecycle_list_) {
            // Call the application's onPause method
            i.app->on_pause();
            // Call the application's onDestroy method
            i.app->on_destroy();
            // Delete the application using its app pointer
            i.app->delete_app_pointer(i.app);
        }
        // Clear the lifecycle list
        app_lifecycle_list_.clear();
        // Clear the creation buffer
        app_create_buffer_.clear();
    }
}
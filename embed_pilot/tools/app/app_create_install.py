import os
import re

app_name = " "
base_path = 'D:/CODE/esp32/micro_snow/src/'
relative_path = base_path + 'embed_pilot/app_sys/app_template'
sys_path = base_path + 'embed_pilot/app_sys'
user_path = base_path + 'embed_pilot/app_user'
install_path = base_path + 'embed_pilot/include/application/app_blueprint/app_install.h'
old_head_string = "/* Header files locator(Don't remove) */"
old_src_string = "/* Install app locator(Don't remove) */"


def get_app_name():
    global app_name
    app_name = input("Enter the name of the app you want to create:").lower()


def check_app_name():
    global app_name
    special_chars = "-#@%^&*"
    return not any(char in special_chars for char in app_name)


def create_app(path):
    global app_name
    for item in os.listdir(relative_path):
        if item == 'app_template.cpp' or item == 'app_template.h':
            with open(os.path.join(relative_path, item), 'r', encoding='utf-8') as f:
                content = f.read()

            new_content = content.replace('template', app_name)
            new_content = new_content.replace('template'.upper(), app_name.upper())
            full_app_path = path + "/app_" + app_name
            full_app_path_ui = full_app_path + "/app_" + app_name + "_ui_src"
            full_app_path_res = full_app_path + "/app_" + app_name + "__res"
            if not os.path.exists(full_app_path):
                os.makedirs(full_app_path)
                os.makedirs(full_app_path_ui)
                os.makedirs(full_app_path_res)

            if item == 'app_template.cpp':
                file = open(full_app_path + "/app_" + app_name + ".cpp", "w")
                file.write(new_content)
                file.close()
            elif item == 'app_template.h':
                file = open(full_app_path + "/app_" + app_name + ".h", "w")
                file.write(new_content)
                file.close()


def install_app(path):
    with open(install_path, 'r', encoding='utf-8') as f:
        content = f.read()
        replace_string_h = "#include " + '"../' + path + "/app_" + app_name + "/app_" + app_name + '.h"\n' + old_head_string
        content = content.replace(old_head_string, replace_string_h)
        replace_string_s = "\tret=ep_activate->install_app(new app_" + app_name + "_packager());\n\t" + old_src_string
        content = content.replace(old_src_string, replace_string_s)

    with open(install_path, 'w', encoding='utf-8') as f:
        f.write(content)


print("install done")

if __name__ == "__main__":
    print("embed_pilot app generator")
    print("Invalid characters cannot be entered . like:_-#@%^&*")
    print("choice S or U 'S' mean system application 'U' mean user application")
    path_choice = ''
    while True:
        choice = input("Enter your choice :").upper()
        if choice == "S" or choice == "U":
            break
        else:
            print("Invalid selection. Please choose 'S' or 'U'.")

        if choice == "S":
            choice = "system"
        elif choice == "U":
            choice = "user"
        else:
            choice = "unknown"

        print("now choice is {}".format(choice))

    path_choice = choice

    while True:
        get_app_name()
        if check_app_name():
            break
        else:
            print("bad name ,try again")
    print("app name is {}\n".format(app_name))
    if path_choice == "S":
        create_app(sys_path)
        install_app("app_sys")
    elif path_choice == "U":
        create_app(user_path)
        install_app("app_user")

    print("done\n")

import os
import shutil

app_name = " "
base_path = 'src/'
relative_path = base_path+'embed_pilot/'
sys_path = base_path+'embed_pilot/app_sys'
user_path = base_path+'embed_pilot/app_user'
install_path = base_path+'embed_pilot/include/application/app_blueprint/app_install.h'
old_head_string = "/* Header files locator(Don't remove) */"
old_src_string = "/* Install app locator(Don't remove) */"


def get_app_name():
    global app_name
    app_name = input("Enter the name of the app you want to uninstall:").lower()


def check_app_name():
    global app_name
    special_chars = "-#@%^&*"
    return not any(char in special_chars for char in app_name)


def delete_app(path):
    global app_name
    path_ = path + "/app_" + app_name
    if os.path.exists(path_):
        shutil.rmtree(path_)
    else:
        print("文件夹不存在")


def uninstall_app(path):
    with open(install_path, 'r', encoding='utf-8') as f:
        content = f.read()
        replace_string_h = "#include " + '"../' + path + "/app_" + app_name + "/app_" + app_name + '.h"\n' + old_head_string
        content = content.replace(replace_string_h, old_head_string)
        replace_string_s = "\tret=ep_activate->install_app(new app_" + app_name + "_packager());\n\t" + old_src_string
        content = content.replace(replace_string_s, old_src_string)

    with open(install_path, 'w', encoding='utf-8') as f:
        f.write(content)


print("uninstall done")

if __name__ == "__main__":
    print("embed_pilot app destroy")
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
        delete_app(sys_path)
        uninstall_app("app_sys")
    elif path_choice == "U":
        delete_app(user_path)
        uninstall_app("app_user")

    print("done\n")

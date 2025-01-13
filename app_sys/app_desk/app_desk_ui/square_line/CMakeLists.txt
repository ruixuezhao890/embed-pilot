SET(SOURCES screens/ui_Screen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_2051629593.c
    images/ui_img_defaut_png.c
    ui_temporary_image.cpp)

add_library(ui ${SOURCES})

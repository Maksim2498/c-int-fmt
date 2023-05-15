cmake_minimum_required(VERSION 3.12)

project(intstr
        VERSION      1.0.0
        LANGUAGES    C
        DESCRIPTION  "A small C99 library for integer parsing and formatting"
        HOMEPAGE_URL https://github.com/Maksim2498/c-int-str)

add_library(fominmv-intstr
            src/all.h
            src/case.h   src/case.c
            src/fmt.h    src/fmt.c
            src/parse.h  src/parse.c
            src/plus.h   src/plus.c
            src/pres.h   src/pres.c
            src/radix.h  src/radix.c)

set_target_properties(fominmv-intstr PROPERTIES
                      VERSION             ${PROJECT_VERSION}
                      C_STANDARD          99
                      C_STANDARD_REQUIRED YES
                      C_EXTENSIONS        NO
                      PUBLIC_HEADER       "src/all.h;src/case.h;src/fmt.h;src/parse.h;src/plus.h;src/pres.h;src/radix.h")

include(GNUInstallDirs)

install(TARGETS fominmv-intstr
        LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fominmv/intstr)
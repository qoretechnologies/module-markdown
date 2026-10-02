# Copyright (C) 2026 Qore Technologies, s.r.o.
cmake_minimum_required(VERSION 3.16)

project(qore-markdown-module)

set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)
set (VERSION_PATCH 0)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )


FIND_PACKAGE (Qore REQUIRED)


include_directories( ${CMAKE_SOURCE_DIR}/src/sundown/src )
include_directories( ${CMAKE_SOURCE_DIR}/src/sundown/html )


set(CPP_SRC
)
set(QPP_SRC
    src/markdown.qpp
)

set(SUNDOWN_SRC
    src/sundown/html/houdini_href_e.c
    src/sundown/html/houdini_html_e.c
    src/sundown/html/html.c
    src/sundown/html/html_smartypants.c
    src/sundown/src/autolink.c
    src/sundown/src/buffer.c
    src/sundown/src/markdown.c
    src/sundown/src/stack.c
)


#set(EFSW_QMOD qlib/FilePoller.qm)


#add_definitions(-DUSE_UTF8)

qore_wrap_qpp_value(QPP_SOURCES METALIST QPP_META_SRC ${QPP_SRC})

SET (module_name "markdown")

set(QORE_DOX_TMPL_SRC docs/mainpage.doxygen.tmpl)

add_library(${module_name} MODULE ${CPP_SRC} ${QPP_SOURCES} ${SUNDOWN_SRC})

qore_external_binary_module(${module_name} "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

if (DOXYGEN_FOUND)
    qore_wrap_dox(QORE_DOX_SRC ${QORE_DOX_TMPL_SRC})
    add_custom_target(QORE_MOD_DOX_FILES DEPENDS ${QORE_DOX_SRC})
    add_dependencies(docs-module QORE_MOD_DOX_FILES)
endif()

qore_dist("${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# install qpp metadata files
if (COMMAND qore_install_qpp_metadata)
    qore_install_qpp_metadata(${module_name} ${QPP_META_SRC})
else()
    install(FILES ${QPP_META_SRC}
            DESTINATION ${CMAKE_INSTALL_DATADIR}/qore/metadata)
endif()

qore_config_info()

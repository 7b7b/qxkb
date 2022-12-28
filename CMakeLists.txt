CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

project(qxkb)

set(QXKB_VERSION 0.5.1)
add_definitions(-DQXKB_VERSION="${QXKB_VERSION}")

set(QXKB_TRANSLATION_PATH ${CMAKE_INSTALL_PREFIX}/share/qxkb/i18n)
add_definitions(-DQXKB_TRANSLATION_PATH="${QXKB_TRANSLATION_PATH}")

set(QXKB_PID_PATH /tmp)
add_definitions(-DQXKB_PID_PATH="${QXKB_PID_PATH}")

# find the Qt
find_package(Qt5 REQUIRED COMPONENTS Core Svg Widgets X11Extras LinguistTools)

# find required X11 modules
find_package(X11 REQUIRED)

if (NOT X11_Xkb_FOUND)
	message(STATUS "Xkb includes: ${X11_Xkblib_INCLUDE_PATH}")
	message(FATAL "X11 Xkb libraries or include not found!")
endif()

include_directories(
	${X11_Xkblib_INCLUDE_PATH}
	"${CMAKE_SOURCE_DIR}"
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_BINARY_DIR}"
)

set (QXKB_SOURCES
	src/qxkb.cpp
	src/xkbt.cpp
	src/xkeyboard.cpp
	src/xkbconf.cpp
	src/x11tools.cpp
	src/main.cpp
	src/datamodels.cpp
)

set (QXKB_MOCS
	src/qxkb.h
	src/xkbt.h
	src/xkeyboard.h
	src/xkbconf.h
	src/datamodels.h
)

set (QXKB_FORMS
	src/kswconfig.ui
)

set (LANGUAGES
	language/qxkb_ru.ts
	language/qxkb_sr.ts
)

qt5_add_translation(QM ${LANGUAGES})

QT5_WRAP_UI(QXKB_UI ${QXKB_FORMS})
QT5_WRAP_CPP(QXKB_MOC_SRC ${QXKB_MOCS})

add_executable(${CMAKE_PROJECT_NAME} ${QXKB_SOURCES} ${QXKB_UI} ${QXKB_MOC_SRC} ${QM})

target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Core Qt5::Svg Qt5::Widgets Qt5::X11Extras ${X11_X11_LIB} xkbfile)

# installation
#  binary
install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION bin LIBRARY DESTINATION lib${LIB_SUFFIX})
#  translations (qm)
install(FILES ${QM} DESTINATION ${QXKB_TRANSLATION_PATH})
#  themes
install(DIRECTORY theme/ DESTINATION share/qxkb/theme PATTERN ".git" EXCLUDE)

# "make dist" target
string(TOLOWER ${CMAKE_PROJECT_NAME} CPACK_PACKAGE_NAME)
SET(CPACK_PACKAGE_VERSION "${QXKB_VERSION}")
SET(CPACK_SOURCE_GENERATOR "TBZ2")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
SET(CPACK_IGNORE_FILES "/CVS/;/\\\\.svn/;\\\\.swp$;\\\\.#;/#;\\\\.tar.gz$;/CMakeFiles/;CMakeCache.txt;refresh-copyright-and-license.pl;\\\\.git$;build;release;")
SET(CPACK_SOURCE_IGNORE_FILES ${CPACK_IGNORE_FILES})
INCLUDE(CPack)
# simulate autotools' "make dist"
add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

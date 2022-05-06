

################################# options ############################################
# default fallback options
cc_set_if_undefined(BUILD_XR_NATIVE               OFF)
cc_set_if_undefined(XR_OEM_OCULUS                 OFF)
cc_set_if_undefined(XR_OEM_HUAWEIVR               OFF)
cc_set_if_undefined(XR_OEM_PICO                   OFF)
cc_set_if_undefined(XR_OEM_ROKID                  OFF)
cc_set_if_undefined(XR_USE_GRAPHICS_API_OPENGL_ES ON)
cc_set_if_undefined(XR_USE_GRAPHICS_API_VULKAN    ON)
cc_set_if_undefined(XR_USE_GRAPHICS_API_OPENGL    OFF)
cc_set_if_undefined(XR_USE_GRAPHICS_API_D3D11     OFF)
cc_set_if_undefined(XR_USE_GRAPHICS_API_D3D12     OFF)


# Several files use these compile time platform switches
if(WIN32)
    cc_set_if_undefined(XR_USE_PLATFORM_WIN32     ON)
elseif(ANDROID)
    cc_set_if_undefined(XR_USE_PLATFORM_ANDROID   ON)
elseif(PRESENTATION_BACKEND MATCHES "xlib")
    cc_set_if_undefined(XR_USE_PLATFORM_XLIB      ON)
elseif(PRESENTATION_BACKEND MATCHES "xcb")
    cc_set_if_undefined(XR_USE_PLATFORM_XCB       ON)
elseif(PRESENTATION_BACKEND MATCHES "wayland")
    cc_set_if_undefined(XR_USE_PLATFORM_WAYLAND   ON)
endif()


################################# list all option values ##############################
cc_inspect_values(
    BUILD_XR_NATIVE
    XR_OEM_OCULUS
    XR_OEM_HUAWEIVR
    XR_OEM_PICO
    XR_OEM_ROKID
    XR_USE_GRAPHICS_API_OPENGL_ES
    XR_USE_GRAPHICS_API_VULKAN
    XR_USE_GRAPHICS_API_OPENGL
    XR_USE_GRAPHICS_API_D3D11
    XR_USE_GRAPHICS_API_D3D12
    XR_USE_PLATFORM_WIN32
    XR_USE_PLATFORM_ANDROID
    XR_USE_PLATFORM_XLIB
    XR_USE_PLATFORM_XCB
    XR_USE_PLATFORM_WAYLAND
)


################################# cc_xr_apply_definations ###################################
function(cc_xr_apply_definations target)
    target_compile_definitions(${target} PUBLIC
        $<IF:$<BOOL:${XR_OEM_OCULUS}>,XR_OEM_OCULUS=1,XR_OEM_OCULUS=0>
        $<IF:$<BOOL:${XR_OEM_HUAWEIVR}>,XR_OEM_HUAWEIVR=1,XR_OEM_HUAWEIVR=0>
        $<IF:$<BOOL:${XR_OEM_PICO}>,XR_OEM_PICO=1,XR_OEM_PICO=0>
        $<IF:$<BOOL:${XR_OEM_ROKID}>,XR_OEM_ROKID=1,XR_OEM_ROKID=0>
        $<$<BOOL:${XR_USE_GRAPHICS_API_OPENGL_ES}>:XR_USE_GRAPHICS_API_OPENGL_ES=1>
        $<$<BOOL:${XR_USE_GRAPHICS_API_VULKAN}>:XR_USE_GRAPHICS_API_VULKAN=1>
        $<$<BOOL:${XR_USE_GRAPHICS_API_OPENGL}>:XR_USE_GRAPHICS_API_OPENGL=1>
        $<$<BOOL:${XR_USE_GRAPHICS_API_D3D11}>:XR_USE_GRAPHICS_API_D3D11=1>
        $<$<BOOL:${XR_USE_GRAPHICS_API_D3D12}>:XR_USE_GRAPHICS_API_D3D12=1>
        $<$<BOOL:${XR_USE_PLATFORM_WIN32}>:XR_USE_PLATFORM_WIN32=1>
        $<$<BOOL:${XR_USE_PLATFORM_ANDROID}>:XR_USE_PLATFORM_ANDROID=1>
        $<$<BOOL:${XR_USE_PLATFORM_XLIB}>:XR_USE_PLATFORM_XLIB=1>
        $<$<BOOL:${XR_USE_PLATFORM_XCB}>:XR_USE_PLATFORM_XCB=1>
        $<$<BOOL:${XR_USE_PLATFORM_WAYLAND}>:XR_USE_PLATFORM_WAYLAND=1>
    )
endfunction()

set(XR_EXTERNAL_LIBS)
set(XR_EXTERNAL_INCLUDES)
set(XR_EXTERNAL_SOURCES)

list(APPEND XR_EXTERNAL_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/Xr.h
)

list(APPEND XR_EXTERNAL_INCLUDES
        ${CMAKE_CURRENT_LIST_DIR}
)

set(XR_OEM_LOADER_NAME openxr_loader)
if(XR_OEM_OCULUS)
    set(XR_OEM_FOLDER oculus)
elseif(XR_OEM_HUAWEIVR)
    set(XR_OEM_FOLDER huaweivr)
    set(XR_OEM_LOADER_NAME xr_loader)
elseif(XR_OEM_PICO)
    set(XR_OEM_FOLDER pico)
elseif(XR_OEM_ROKID)
    set(XR_OEM_FOLDER rokid)
else()
    set(XR_OEM_FOLDER mobile)
endif()

add_library(openxr SHARED IMPORTED GLOBAL)
set_target_properties(openxr PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/xr/${XR_OEM_FOLDER}/lib${XR_OEM_LOADER_NAME}.so
)

list(APPEND XR_EXTERNAL_LIBS
    openxr
)

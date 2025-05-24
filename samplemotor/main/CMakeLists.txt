include_directories(${PROJECT_SOURCE_DIR})

aux_source_directory(./ui DIR_LIB_SRCS)
# aux_source_directory(./ui UI_SRCS)
# 生成链接库
add_library (uilib ${DIR_LIB_SRCS})
include_directories(${PROJECT_SOURCE_DIR})
# aux_source_directory(./ui DIR_LIB_SRCS)
# aux_source_directory(./ui UI_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/eez_rk3566/ui DIR_LIB_SRCS)
# 生成链接库
add_library (uilib ${DIR_LIB_SRCS})


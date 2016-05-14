PROJECT (ExportMaps)
# A list of source files
SET(PROJECT_SRCS

  # IDA stuff
  ./cpp/util/ofsub.cpp

  # DF utilities and calling DF code
  ./cpp/df_utils/adjust_coordinates_to_region.cpp
  ./cpp/df_utils/biome_type.cpp
  ./cpp/df_utils/delete_world_region_details.cpp
  ./cpp/df_utils/fill_world_region_details.cpp

  # Proto compiled files
  ./cpp/get_world_region_details_command.pb.cc
  ./cpp/world_region_details_result.pb.cc

  # Plugin interface to DFHack
  ./cpp/get_world_region_details.cpp
)
# A list of headers
SET(PROJECT_HDRS
    ./include/get_world_region_details_command.pb.h
    ./include/world_region_details_result.pb.h
)
SET_SOURCE_FILES_PROPERTIES( ${PROJECT_HDRS} PROPERTIES HEADER_FILE_ONLY TRUE)

# mash them together (headers are marked as headers and nothing will try to compile them)
LIST(APPEND PROJECT_SRCS ${PROJECT_HDRS})

#linux
IF(UNIX)
    add_definitions(-DLINUX_BUILD)
    SET(PROJECT_LIBS
        # add any extra linux libs here
        dfhack-tinythread
        ${PROJECT_LIBS}
    )
# windows
ELSE(UNIX)
    SET(PROJECT_LIBS
        # add any extra windows libs here
        dfhack-tinythread
        ${PROJECT_LIBS}
        $(NOINHERIT)
    )
ENDIF(UNIX)
# this makes sure all the stuff is put in proper places and linked to dfhack
DFHACK_PLUGIN(worldregiondetails ${PROJECT_SRCS} LINK_LIBRARIES ${PROJECT_LIBS} COMPILE_FLAGS_GCC "-O0")

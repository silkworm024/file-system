# -------------------------------
# Add targets for executable code
# -------------------------------
add_executable(studio16 Studio16.cpp)
target_link_libraries(studio16 mockos)

add_executable(studio17 Studio17.cpp)
target_link_libraries(studio17 mockos)

add_executable(studio18 Studio18.cpp)
target_link_libraries(studio18 mockos)

add_executable(studio19 Studio19.cpp)
target_link_libraries(studio19 mockos)

add_executable(studio20 Studio20.cpp)
target_link_libraries(studio20 mockos)

add_executable(studio21 Studio21.cpp)
target_link_libraries(studio21 mockos)

add_executable(lab5 Lab5.cpp
        ../include/mockos/enums.h
        ../include/mockos/EditDisplayParsingStrategy.h
        ../include/mockos/PermissionProxy.h
        ../include/mockos/PermissionCommand.h
)
target_link_libraries(lab5 mockos)

add_executable(run_test_map test_map.cpp)
add_executable(run_test_tree test_tree.cpp)
target_include_directories(run_test_map PRIVATE 
    ../include 
    ../googletest/googletest/include
    ../googletest/googlemock/include
)

target_include_directories(run_test_tree PRIVATE 
    ../include 
    ../googletest/googletest/include
    ../googletest/googlemock/include
)
target_link_libraries(run_test_map PRIVATE gtest_main gtest pthread)
target_link_libraries(run_test_tree PRIVATE gtest_main gtest pthread)

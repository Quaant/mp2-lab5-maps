add_executable(run_tests test.cpp)
target_include_directories(run_tests PRIVATE ../include 
                                             ../googletest/googletest/include
                                             ../googletest/googlemock/include
                                             )
target_link_libraries(run_tests PRIVATE gtest_main)

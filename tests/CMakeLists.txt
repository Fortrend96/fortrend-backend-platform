add_executable(
	fortrend_unit_tests
	unit/core/application_config_test.cpp
	unit/core/error_test.cpp
)

target_link_libraries(
	fortrend_unit_tests
	PRIVATE
		fortrend_core
		GTest::gtest_main
)

set_target_properties(
	fortrend_unit_tests
	PROPERTIES
		CXX_EXTENSIONS OFF
)

fortrend_enable_warnings(fortrend_unit_tests)
fortrend_enable_sanitizers(fortrend_unit_tests)

include(GoogleTest)

gtest_discover_tests(fortrend_unit_tests)
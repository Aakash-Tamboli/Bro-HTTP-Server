cmake_minimum_required (VERSION 3.22 FATAL_ERROR)
project (bro)
include_directories ("../include")
add_library (bro bro_global.cpp bro_string_utility.cpp bro_file_system_utility.cpp bro_utilities.cpp bro_gmt_date_time.cpp bro_validator.cpp bro_http_error_status_utility.cpp bro_error.cpp bro_cookie.cpp bro_header_utility.cpp bro_request.cpp bro_response.cpp bro_http_response_utility.cpp bro_simple_function.cpp bro_application_level_container_dependent_function.cpp bro_simple_startup_function.cpp bro_application_level_container_dependent_startup_function.cpp bro_startup_function_comparator.cpp bro_template_engine.cpp bro.cpp bro_container.cpp bro_request_processor.cpp)


if(NOT DEFINED API_IS_SDK)
	include(API)
	cmsdk_include_target(DesignAPI "${API_CONFIG_LIST}")
endif()

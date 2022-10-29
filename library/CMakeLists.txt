
cmsdk2_check_version(
  NAME LvglAPI
  VERSION ${LvglAPI_VERSION}
  MINIMUM_VERSION 1.0.1)

api2_add_library(
  NAME DesignAPI
  VERSION ${PROJECT_VERSION}
  DEPENDENCIES LvglAPI JsonAPI)

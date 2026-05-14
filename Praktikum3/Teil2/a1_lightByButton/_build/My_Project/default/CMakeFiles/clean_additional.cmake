# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "C:\\Users\\khush\\MPLABProjects\\My_Project2\\out\\My_Project\\default.cmf"
  "C:\\Users\\khush\\MPLABProjects\\My_Project2\\out\\My_Project\\default.hex"
  "C:\\Users\\khush\\MPLABProjects\\My_Project2\\out\\My_Project\\default.hxl"
  "C:\\Users\\khush\\MPLABProjects\\My_Project2\\out\\My_Project\\default.mum"
  "C:\\Users\\khush\\MPLABProjects\\My_Project2\\out\\My_Project\\default.o"
  "C:\\Users\\khush\\MPLABProjects\\My_Project2\\out\\My_Project\\default.sdb"
  "C:\\Users\\khush\\MPLABProjects\\My_Project2\\out\\My_Project\\default.sym"
  )
endif()

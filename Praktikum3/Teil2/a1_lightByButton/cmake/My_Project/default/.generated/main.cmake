include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(My_Project_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(My_Project_default_default_XC8_FILE_TYPE_assemble)
add_library(My_Project_default_default_XC8_assemble OBJECT ${My_Project_default_default_XC8_FILE_TYPE_assemble})
    My_Project_default_default_XC8_assemble_rule(My_Project_default_default_XC8_assemble)
    list(APPEND My_Project_default_library_list "$<TARGET_OBJECTS:My_Project_default_default_XC8_assemble>")

endif()

# Handle files with suffix S, for group default-XC8
if(My_Project_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(My_Project_default_default_XC8_assemblePreprocess OBJECT ${My_Project_default_default_XC8_FILE_TYPE_assemblePreprocess})
    My_Project_default_default_XC8_assemblePreprocess_rule(My_Project_default_default_XC8_assemblePreprocess)
    list(APPEND My_Project_default_library_list "$<TARGET_OBJECTS:My_Project_default_default_XC8_assemblePreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC8
if(My_Project_default_default_XC8_FILE_TYPE_compile)
add_library(My_Project_default_default_XC8_compile OBJECT ${My_Project_default_default_XC8_FILE_TYPE_compile})
    My_Project_default_default_XC8_compile_rule(My_Project_default_default_XC8_compile)
    list(APPEND My_Project_default_library_list "$<TARGET_OBJECTS:My_Project_default_default_XC8_compile>")

endif()


# Main target for this project
add_executable(My_Project_default_image_XXieOxIW ${My_Project_default_library_list})

set_target_properties(My_Project_default_image_XXieOxIW PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf"
    ADDITIONAL_CLEAN_FILES "${output_extensions}"
    RUNTIME_OUTPUT_DIRECTORY "${My_Project_default_output_dir}")
target_link_libraries(My_Project_default_image_XXieOxIW PRIVATE ${My_Project_default_default_XC8_FILE_TYPE_link})

# Add the link options from the rule file.
My_Project_default_link_rule( My_Project_default_image_XXieOxIW)



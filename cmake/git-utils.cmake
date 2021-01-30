function(git_describe)
    find_program(GIT_EXECUTABLE "git")
    if(NOT GIT_EXECUTABLE)
        message(FATAL_ERROR "git executable not found.")
    endif()

    execute_process(
        COMMAND
            ${GIT_EXECUTABLE} describe --tags --dirty=-dirty
        WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE
            result
        OUTPUT_VARIABLE
            output
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if(NOT result EQUAL 0)
        set(output "v0.0.0-invalid")
        message(WARNING
            "Failed to get git revision of project."
        )
    endif()

    if(NOT "${output}" MATCHES "^v[0-9]+\\.[0-9]+\\.[0-9]+.*")
        set(output "v0.0.0-invalid")
        message(WARNING
            "Failed to get git revision of project."
        )
    endif()

    string(REGEX REPLACE
        "^v([0-9]+\\.[0-9]+\\.[0-9]+.*)" "\\1"
        version
        "${output}"
    )

    string(REGEX REPLACE
        "^v([0-9]+)\\..*" "\\1"
        major
        "${output}"
    )

    string(REGEX REPLACE
        "^v[0-9]+\\.([0-9]+).*" "\\1"
        minor
        "${output}"
    )

    string(REGEX REPLACE
        "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1"
        patch
        "${output}"
    )

    set(GIT_DESCRIBE_VERSION ${version} PARENT_SCOPE)
    set(GIT_DESCRIBE_VERSION_MAJOR ${major} PARENT_SCOPE)
    set(GIT_DESCRIBE_VERSION_MINOR ${minor} PARENT_SCOPE)
    set(GIT_DESCRIBE_VERSION_PATCH ${patch} PARENT_SCOPE)
endfunction()

function(arale_get_git_info)

set(ARALE_BRANCH="no info")
set(ARALE_COMMIT="no info")
set(ARALE_COMMIT_DATE="no info")
set(ARALE_COMMITED=0)

find_program(GIT_PROGRAMM git)
if (GIT_PROGRAMM)
    execute_process(
    COMMAND git rev-parse HEAD
    RESULT_VARIABLE STATUS
    OUTPUT_VARIABLE HAVE_HEAD 
    ERROR_QUIET )

    if(STATUS AND NOT STATUS EQUAL 0)
        message(STATUS "FAILED TO GET COMMIT: ${STATUS}")
        elseif(HAVE_HEAD)
        #commit
        string(STRIP ${HAVE_HEAD} ARALE_COMMIT)
        #commit date
          execute_process(
            COMMAND git show -s --format=%cd
            OUTPUT_VARIABLE ARALE_COMMIT_DATE 
            ERROR_QUIET )   
          string(STRIP ${ARALE_COMMIT_DATE} ARALE_COMMIT_DATE)
        #branch
          execute_process(
            COMMAND git rev-parse --abbrev-ref HEAD
            OUTPUT_VARIABLE ARALE_BRANCH 
            ERROR_QUIET )  
          string(STRIP ${ARALE_BRANCH} ARALE_BRANCH)
        #is commited
          execute_process(
            COMMAND git status -suno
            OUTPUT_VARIABLE ARALE_COMMITED 
            ERROR_QUIET )
          if(ARALE_COMMITED)
            set(ARALE_COMMITED 0)
          else()
            set(ARALE_COMMITED 1)
          endif()
    endif()
else ()
    message(STATUS "Install git to get info")
endif()

endfunction() # arale_get_git_info

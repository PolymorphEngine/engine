if(NOT TARGET myxmlpp)
    include(FetchContent)

    FetchContent_Declare(
            myxmlpp
            GIT_REPOSITORY https://github.com/PolymorphEngine/myxmlpp.git
            GIT_TAG test
    )

    FetchContent_MakeAvailable(myxmlpp)
endif()
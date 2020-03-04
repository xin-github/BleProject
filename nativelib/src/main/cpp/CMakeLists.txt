# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             native-lib.cpp rtwtypes.h tmwtypes.h emxutil.cpp emxutil.h types.h
        filter_all/filter.cpp filter_all/filter_all.cpp
        filter_all/filter_all_initialize.cpp

        fft/fft.cpp fft/fft1.cpp fft/fft_compare.cpp emxAPI.cpp
        fft/fft_compare_initialize.cpp

        mmf/betaincinv.cpp mmf/erfcinv.cpp mmf/filloutliers.cpp mmf/gammaln.cpp mmf/locateoutliers.cpp
        mmf/log.cpp mmf/median_mean_frequency.cpp
        mmf/median_mean_frequency_initialize.cpp
        mmf/median_mean_frequency_rtwutil.cpp mmf/median_mean_frequency_terminate.cpp
        mmf/polyfit.cpp mmf/sqrt.cpp mmf/vvarstd.cpp
        mmf/xgeqp3.cpp mmf/xnrm2.cpp mmf/xscal.cpp

        arv_rms/ARV_RMS.cpp
        arv_rms/ARV_RMS_initialize.cpp arv_rms/ARV_RMS_terminate.cpp

        rt/rt_nonfinite.cpp
        rt/rtGetInf.cpp rt/rtGetNaN.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )

#add_executable(filter_all/*  filter.cpp filter_all.cpp
#        filter_all_emxAPI.cpp filter_all_emxutil.cpp filter_all_initialize.cpp
#        filter_all_terminate.cpp)
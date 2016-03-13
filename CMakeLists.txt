cmake_minimum_required(VERSION 2.8)
project( store_credit )
find_package( OpenCV REQUIRED )
add_executable( app store_credit.cpp )

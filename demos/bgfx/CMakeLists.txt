cmake_minimum_required(VERSION 3.15)

project(bgfx_demo)

add_executable(bgfx_demo
    main.cpp
)

setup_bgfx_target(bgfx_demo)
#!/bin/bash

BUILD_FILE_NAME="build"

mkdir -p ${BUILD_FILE_NAME}
(cd ${BUILD_FILE_NAME} && cmake .. && make)

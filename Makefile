# Project Name
TARGET ?= bluemchen_test_app

DEBUG = 1
OPT = -O0

# Sources
CPP_SOURCES = dependencies/kxmx_bluemchen/kxmx_bluemchen.cpp src/${TARGET}.cpp

USE_FATFS = 1

# Library Locations
LIBDAISY_DIR = dependencies/kxmx_bluemchen/libDaisy

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

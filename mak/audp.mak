TARGET = bin/audp
SRCS = \
src/audp/log.cpp \
src/audp/log_master.cpp \
src/audp/log_port.cpp \
src/audp/log_shop.cpp \
src/audp/main.cpp \

LINK_TYPE = exec
INCLUDE = -Isrc
BUILD_DIR = build
DEPFILE =

LIB = \
-Lbuild \
-Llib  \
-lpthread -lrt \
-ldl \
-lz \

include mak/main.mak

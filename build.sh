set -xe

cd build
[ ! -f Makefile ] && cmake ..
make -j8

if [ "$1" = "--run" ] || [ "$1" = "-r" ]; then
    alacritty -e /bin/bash -c \
        "/home/justcris/Documents/cpp/opengl_conan/build/bin/learn_opengl; read"
fi

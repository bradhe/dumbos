#!/bin/bash

##
# Installs QEmu from source.
#
cc=/usr/bin/gcc-4.2
tmp_dir=/tmp/qemu

mkdir -p $tmp_dir

cd $tmp_dir
curl http://wiki.qemu.org/download/qemu-0.15.1.tar.gz > qemu-0.15.1.tar.gz
tar -xf qemu-0.15.1.tar.gz
cd qemu-0.15.1
./configure --cc=$cc --disable-darwin-user --disable-bsd-user
make
sudo make install

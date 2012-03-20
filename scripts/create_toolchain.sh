#!/bin/bash

##
# Configures a vanilla toolchain for making dumbos. This comes from the osdev wiki!
# http://wiki.osdev.org/Talk:GCC_Cross-Compiler -- Thanks Nokurn
#
# Tested and works on OSX Lion.
#
export PREFIX=/usr/local/cross
export TARGET=i586-elf
export MAKEFLAGS="-j 16"

# Specific for us.
export CC=/usr/bin/gcc-4.2
export CXX=/usr/bin/g++-4.2
export CPP=/usr/bin/cpp-4.2
export LD=/usr/bin/gcc-4.2

tmp_dir=/tmp/toolchain
gcc_version=4.6.3

# Start fresh.
rm -rf $tmp_dir
mkdir -p $tmp_dir
mkdir -p $tmp_dir/build-{binutils,gcc}/

# Fetch all the shit we need.
curl ftp://ftp.gnu.org/gnu/binutils/binutils-2.22.tar.bz2 | tar -x -f - -C $tmp_dir
curl ftp://ftp.gnu.org/gnu/gcc/gcc-$gcc_version/gcc-core-$gcc_version.tar.bz2 | tar -x -f - -C $tmp_dir
curl ftp://ftp.gnu.org/gnu/gmp/gmp-5.0.2.tar.bz2 | tar -x -f - -C $tmp_dir/gcc-$gcc_version/
curl ftp://ftp.gnu.org/gnu/mpfr/mpfr-3.1.0.tar.bz2 | tar -x -f - -C $tmp_dir/gcc-$gcc_version/
curl http://www.multiprecision.org/mpc/download/mpc-0.9.tar.gz | tar -x -f - -C $tmp_dir/gcc-$gcc_version/

# Builds binutils
cd $tmp_dir/build-binutils/
../binutils-2.22/configure --prefix=$PREFIX --target=$TARGET --disable-nls
make all
sudo make install

# Builds GCC
export PATH=$PATH:$PREFIX/bin
cd $tmp_dir/build-gcc/
mv ../gcc-$gcc_version/gmp-5.0.2/ ../gcc-$gcc_version/gmp/
mv ../gcc-$gcc_version/mpfr-3.1.0/ ../gcc-$gcc_version/mpfr/
mv ../gcc-$gcc_version/mpc-0.9/ ../gcc-$gcc_version/mpc/
../gcc-$gcc_version/configure --prefix=$PREFIX --target=$TARGET --disable-nls --without-headers --with-mpfr-include=$tmp_dir/gcc-$gcc_version/mpfr/src/ --with-mpfr-lib=$tmp_dir/build-gcc/mpfr/src/.libs/
make all-gcc
sudo make install-gcc

#!/bin/bash
make floppy
qemu -fda bin/floppy.img

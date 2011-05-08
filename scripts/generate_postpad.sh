#!/bin/bash

kernel_size=`stat -c%s "bin/kernel.bin"`
stage_one_sec=`stat -c%s "lib/grub-0.97-i386-pc/boot/grub/stage1"`
stage_two_size=`stat -c%s "lib/grub-0.97-i386-pc/boot/grub/stage2"`
export total=`expr 1474560 - $kernel_size - $stage_one_sec - $stage_two_size`

if [[ -f "lib/postpad"]] && [[$total -ne `stat -c%s "lib/postpad"` ]]; then
	echo "Post padding size: $total"
	perl -e 'print "\xFF"x$ENV{"total"}' > lib/postpad
elif [ ! -f "lib/postpad" ]; then
	echo "Post padding size: $total"
	perl -e 'print "\xFF"x$ENV{"total"}' > lib/postpad
else
	echo "Post padding size unchanged."
fi

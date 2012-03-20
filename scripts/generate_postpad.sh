#!/bin/bash

kernel_size=`stat -f %z "bin/kernel.bin"`
stage_one_sec=`stat -f %z "lib/grub-0.97-i386-pc/boot/grub/stage1"`
stage_two_size=`stat -f %z "lib/grub-0.97-i386-pc/boot/grub/stage2"`
export total=`expr 1474560 - $kernel_size - $stage_one_sec - $stage_two_size`

echo "Total padding: $total"

# Make sure we aren't doing something crazy...
if [[ -f "lib/postpad"]] && [[$total -ne `stat -f%z "lib/postpad"` ]]; then
	echo "Post padding size: $total"
	perl -e 'print "\xFF"x$ENV{"total"}' > lib/postpad
elif [ ! -f "lib/postpad" ]; then
	echo "Post padding size: $total"
	perl -e 'print "\xFF"x$ENV{"total"}' > lib/postpad
else
	echo "Post padding size unchanged."
fi

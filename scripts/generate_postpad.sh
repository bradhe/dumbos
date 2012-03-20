#!/bin/bash

kernel_size=`stat -f %z "bin/kernel.bin"`
stage_one_sec=`stat -f %z "lib/grub-0.97-i386-pc/boot/grub/stage1"`
stage_two_size=`stat -f %z "lib/grub-0.97-i386-pc/boot/grub/stage2"`
export pre_total=`expr 102400 - $stage_one_sec - $stage_two_size`
export post_total=`expr 1474560 - $kernel_size - $stage_one_sec - $stage_two_size - $pre_total`

if [[ -f "lib/prepad"]] && [[$pre_total -ne `stat -f %z "lib/prepad"` ]]; then
	echo "Pre padding size: $pre_total"
	perl -e 'print "\xFF"x$ENV{"pre_total"}' > lib/prepad
elif [ ! -f "lib/prepad" ]; then
	echo "Pre padding size: $pre_total"
	perl -e 'print "\xFF"x$ENV{"pre_total"}' > lib/prepad
else
	echo "Pre padding size unchanged."
fi

if [[ -f "lib/postpad"]] && [[$post_total -ne `stat -f %z "lib/postpad"` ]]; then
	echo "Post padding size: $post_total"
	perl -e 'print "\xFF"x$ENV{"post_total"}' > lib/postpad
elif [ ! -f "lib/postpad" ]; then
	echo "Post padding size: $post_total"
	perl -e 'print "\xFF"x$ENV{"post_total"}' > lib/postpad
else
	echo "Post padding size unchanged."
fi

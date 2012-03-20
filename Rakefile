require 'rubygems'
require 'rake'

BIN_DIR = 'bin'
OBJ_DIR = 'obj'
SRC_DIR = 'src'
CSRC = %w{kmain.c video.c}
SSRC = %w{loader.s}
LD_CONFIG = 'linker.ld'
BIN_FILE = 'kernel.bin'
CARGS='-Wall -Wextra -Werror -nostdlib -fno-builtin -nostartfiles -nodefaultlibs'

CC='/usr/local/cross/bin/i586-elf-gcc'
LD='/usr/local/cross/bin/i586-elf-ld'

def obj(file)
  File.join(OBJ_DIR, file.sub(/\..{1,4}$/, '.o'))
end

def src(file)
  File.join(SRC_DIR, file)
end

def bin(file)
  File.join(BIN_DIR, file)
end

def cmd(cmd)
  puts cmd
  system cmd
end

def build_file(file)
  cmd_str = begin
          if file.end_with?('.c')
            "#{CC} #{src(file)} -c -o #{obj(file)} #{CARGS}"
          else
            "nasm -s -f elf -o #{obj(file)} #{src(file)}"
          end
        end

  cmd(cmd_str)
  obj(file)
end

task :clean do
  puts "** Cleaning"
  [BIN_DIR, OBJ_DIR].each do |dir|
    cmd("rm -rf #{dir}")
    cmd("mkdir #{dir}")
  end
end

task :build => [:clean] do
  puts "\n** Building (#{SSRC.count} ASM, #{CSRC.count} C)"
  files = SSRC.map do |f|
    build_file(f)
  end

  files += CSRC.map do |f|
    build_file(f)
  end

  cmd("#{LD} -T #{src(LD_CONFIG)} -o #{bin(BIN_FILE)} #{files.join(' ')}")
end

task :floppy => [:build] do
  puts "\n** Generating disk image"
  cmd("scripts/generate_postpad.sh")
  cmd("cat lib/grub-0.97-i386-pc/boot/grub/stage1 lib/grub-0.97-i386-pc/boot/grub/stage2 lib/prepad bin/kernel.bin lib/postpad > bin/floppy.img")
end

task :run => [:floppy] do
  puts "\n** Starting qemu"
  cmd("qemu -fda bin/floppy.img")
end

task :default => :floppy

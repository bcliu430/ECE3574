insmod jprobe_mod.ko
taskset 0x1 cyclictest -a 2 --policy=rr -q -p 95 -l 200
rmmod jprobe_mod.ko
dmesg

echo "bl1-s5p4418 recovery"
rm -rf device/nexell/bl1/bl1-s5p4418
repo sync -l device/nexell/bl1/bl1-s5p4418

echo "bl1-s5p6818 recovery"
rm -rf device/nexell/bl1/bl1-s5p6818
repo sync -l device/nexell/bl1/bl1-s5p6818

echo "u-boot recovery"
rm -rf device/nexell/u-boot/u-boot-2016.01/
repo sync -l device/nexell/u-boot/u-boot-2016.01/

echo "kernel recovery"
rm -rf device/nexell/kernel/kernel-4.4.x/
repo sync -l device/nexell/kernel/kernel-4.4.x/

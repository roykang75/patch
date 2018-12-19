#!/bin/bash

srcDir=$(pwd)
targetDir="../nexell_nougat_r1"

echo ${srcDir}
echo ${targetDir}

echo "uncompress rookie configurations"
cp ./rookie.tar.gz ${targetDir}/device/nexell/
cd ${targetDir}/device/nexell/
tar -xvzf ./rookie.tar.gz
rm ./rookie.tar.gz
cd ${srcDir}

echo "apply patch to bl1-s5p4418"
cp -R ./bl1-s5p4418/* ${targetDir}/device/nexell/bl1/bl1-s5p4418/
cd ${targetDir}/device/nexell/bl1/bl1-s5p4418/
patch -p1 < ./bl1-s5p4418.patch
rm ./bl1-s5p4418.patch
cd ${srcDir}

echo "apply patch to bl1-s5p6818"
cp -R ./bl1-s5p6818/* ${targetDir}/device/nexell/bl1/bl1-s5p6818/
cd ${targetDir}/device/nexell/bl1/bl1-s5p6818/
patch -p1 < ./bl1-s5p6818.patch
rm ./bl1-s5p6818.patch
cd ${srcDir}

echo "apply patch to u-boot"
cp -R ./u-boot/* ${targetDir}/device/nexell/u-boot/u-boot-2016.01/
cd ${targetDir}/device/nexell/u-boot/u-boot-2016.01/
patch -p1 < ./u-boot.patch
rm u-boot.patch
cd ${srcDir}

echo "apply patch to kernel"
cp -R ./kernel/* ${targetDir}/device/nexell/kernel/kernel-4.4.x/
cd ${targetDir}/device/nexell/kernel/kernel-4.4.x/
patch -p1 < ./kernel-4.4.x.patch
rm kernel-4.4.x.patch
cd ${srcDir}


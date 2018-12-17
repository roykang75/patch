#!/bin/bash

srcDir=$(pwd)
targetDir="../patch_nexell_nougat_r1/"

echo ${srcDir}
echo ${targetDir}

echo "uncompress rookie configurations"
cp ./rookie.tar.gz ../patch_nexell_nougat_r1/device/nexell/
cd ../patch_nexell_nougat_r1/device/nexell/
tar -xvzf ./rookie.tar.gz
rm ./rookie.tar.gz
cd ${srcDir}


echo "apply patch to bl1-s5p6818"
cp -R ./bl1-s5p6818/* ../patch_nexell_nougat_r1/device/nexell/bl1/bl1-s5p6818/
cd ../patch_nexell_nougat_r1/device/nexell/bl1/bl1-s5p6818/
patch -p1 < ./bl1-s5p6818.patch
rm ./bl1-s5p6818.patch
cd ${srcDir}

echo "apply patch to u-boot"
cp -R ./u-boot/* ../patch_nexell_nougat_r1/device/nexell/u-boot/u-boot-2016.01/
cd ../patch_nexell_nougat_r1/device/nexell/u-boot/u-boot-2016.01/
patch -p1 < ./u-boot.patch
rm u-boot.patch
cd ${srcDir}

echo "apply patch to kernel"
cp -R ./kernel/* ../patch_nexell_nougat_r1/device/nexell/kernel/kernel-4.4.x/
cd ../patch_nexell_nougat_r1/device/nexell/kernel/kernel-4.4.x/
patch -p1 < ./kernel-4.4.x.patch
rm kernel-4.4.x.patch
cd ${srcDir}


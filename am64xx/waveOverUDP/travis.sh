
# building waveOverUDP 

output=$(rm -rf build build-bin 2>&1)
if [ $? -eq 0 ]; then
   echo "INFO: Removed build and build-bin folders."
else
   echo "$output"
   exit 1
fi

mkdir build
cd build

output=$(cmake .. 2>&1)
if [ $? -eq 0 ]; then
   echo "INFO: Configurations successfully done."
else
   echo "$output"
   exit 1
fi

output=$(make 2>&1)
if [ $? -eq 0 ]; then
   echo "INFO: Build successfully generated all binaries."
else
   echo "$output"
   exit 1
fi


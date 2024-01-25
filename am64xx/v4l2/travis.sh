
# Building v4l2

# remove sender and receiver binaries
echo "INFO: Removing sender and receiver binaries..."
output=$(rm -rf sender receiver 2>&1)
if [ $? -eq 0 ]; then
   echo "INFO: Removed sender and receiver binaries."
else
   echo "$output"
   exit 1
fi

echo "INFO: Building sender and receiver files..."
# Sender:-
output=$(g++ -g -o sender v4LSend2UDP.cpp -o sender -lv4l2 -lopencv_core -lopencv_highgui -lopencv_imgcodecs -std=c++11 2>&1)
if [ $? -eq 0 ]; then
   echo "INFO: successfully compiled v4LSend2UDP.cpp file."
else
   echo "$output"
   exit 1
fi

#Receiver:-
output=$(g++ -g -o receiver final.cpp -I/usr/include/opencv4 -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc 2>&1)
if [ $? -eq 0 ]; then
   echo "INFO: successfully compiled final.cpp file."
else
   echo "$output"
   exit 1
fi

echo "INFO: Build successfully generated sender and receiver binaries."


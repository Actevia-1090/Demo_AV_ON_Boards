
sudo pkill sender
sudo pkill waveSendUDP

# talker video
./Audio_Video/v4l2/sender 10.42.0.224 2308 &

# talker audio
./Audio_Video/waveOverUDP/build-bin/waveSendUDP --chunksize 128 --chunknum 4 --device plughw:0,0 --rate 48000 --channel 2 --port 2306 10.42.0.224

sudo pkill sender
sudo pkill waveSendUDP

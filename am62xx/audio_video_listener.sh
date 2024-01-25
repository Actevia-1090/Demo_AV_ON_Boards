sudo pkill receiver
sudo pkill wavePlayUDP

# talker video
./Audio_Video/v4l2/receiver &

# talker audio
./Audio_Video/waveOverUDP/build-bin/wavePlayUDP

sudo pkill receiver
sudo pkill wavePlayUDP

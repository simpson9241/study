rm -rf ~/ffmpeg  ~/ffmpeg_build ~/ffmpeg_sources ~/bin/{ffmpeg,ffprobe,ffserver,vsyasm,x264,yasm,ytasm};
sudo apt-get autoremove ffmpeg;
sudo apt-get autoremove autoconf automake build-essential libass-dev libfreetype6-dev libgpac-dev libmp3lame-dev libopus-dev libsdl1.2-dev libtheora-dev libtool libva-dev libvdpau-dev libvorbis-dev libvpx-dev libx11-dev libxext-dev libxfixes-dev texi2html zlib1g-dev;
sed -i '/ffmpeg_build/c\' ~/.manpath;
hash -r;
cd ~/;
sudo rm -rf nginx-rtmp-module-master;
sudo rm master.zip;
sudo rm -rf nginx-vod-module;
sudo apt remove nginx nginx-common nginx-full nginx-core;
sudo rm -f -R /usr/local/nginx && sudo rm -f -R /usr/local/sbin/nginx;
sudo rm -f -R /usr/share/nginx;
sudo rm -f -R ~/nginx-1.19.2.tar.gz;

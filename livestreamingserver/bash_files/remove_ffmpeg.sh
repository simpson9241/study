rm -rf ~/ffmpeg_build ~/ffmpeg_sources ~/bin/{ffmpeg,ffprobe,ffserver,vsyasm,x264,yasm,ytasm};
sudo apt-get autoremove autoconf automake build-essential libass-dev libfreetype6-dev libgpac-dev libmp3lame-dev libopus-dev libsdl1.2-dev libtheora-dev libtool libva-dev libvdpau-dev libvorbis-dev libvpx-dev libx11-dev libxext-dev libxfixes-dev texi2html zlib1g-dev;
sed -i '/ffmpeg_build/c\' ~/.manpath;
hash -r;

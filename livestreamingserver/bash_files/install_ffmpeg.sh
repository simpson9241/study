sudo apt-get install ffmpeg;
sudo apt-get update
sudo apt-get -y install autoconf automake build-essential libass-dev libfreetype6-dev libgpac-dev libsdl1.2-dev libtheora-dev libtool libva-dev libvdpau-dev libvorbis-dev libx11-dev libxext-dev libxfixes-dev pkg-config texi2html zlib1g-dev;
mkdir ~/ffmpeg_sources;
cd ~/ffmpeg_sources;
wget http://www.tortall.net/projects/yasm/releases/yasm-1.2.0.tar.gz;
tar xzvf yasm-1.2.0.tar.gz;
cd yasm-1.2.0;
./configure --prefix="$HOME/ffmpeg_build" --bindir="$HOME/bin";
make;
make install;
make distclean;
cd ~/ffmpeg_sources;
wget http://www.nasm.us/pub/nasm/releasebuilds/2.13.01/nasm-2.13.01.tar.xz;
tar -xvf nasm-2.13.01.tar.xz;
cd nasm-2.13.01;
./configure;
make;
sudo make install;
cd ~/ffmpeg_sources;
wget http://download.videolan.org/pub/x264/snapshots/x264-snapshot-20191217-2245-stable.tar.bz2;
tar xjvf x264-snapshot-20191217-2245-stable.tar.bz2;
cd x264-snapshot-20191217-2245-stable;
PATH="$PATH:$HOME/bin" ./configure -- prefix="$HOME/ffmpeg_build" --bindir="$HOME/bin" --enable-static;
make;
make install;
make distclean;
cd ~/ffmpeg_sources;
wget -O fdk-aac.zip https://github.com/mstorsjo/fdk-aac/zipball/master;
unzip fdk-aac.zip;
cd mstorsjo-fdk-aac*;
autoreconf -fiv;
./configure --prefix="$HOME/ffmpeg_build" --disable-shared;
make;
make install;
make distclean;
sudo apt-get install libmp3lame-dev;
cd ~/ffmpeg_sources;
wget http://downloads.xiph.org/releases/opus/opus-1.1.tar.gz;
tar xzvf opus-1.1.tar.gz;
cd opus-1.1;
./configure --prefix="$HOME/ffmpeg_build" --disable-shared;
make;
make install;
make distclean;
cd ~/ffmpeg_sources;
wget http://github.com/webmproject/libvpx/archive/v1.7.0/libvpx-1.7.0.tar.gz;
tar xzvf libvpx-1.7.0.tar.gz;
cd libvpx-1.7.0;
./configure --prefix="$HOME/ffmpeg_build" --disable-examples;
make;
make install;
make clean;
cd ~/ffmpeg_sources;
wget http://ffmpeg.org/releases/ffmpeg-snapshot.tar.bz2;
tar xjvf ffmpeg-shapshot.tar.bz2;
cd ~/ffmpeg;
#PATH: 바이너리 파일을 찾기 위한 경로 설정
#PKG_CONFIG_PATH: 패키지를 찾기 위한 경로 설정
#prefix: configure에 필요한 구성 파일들이 속해있는 경로 설정
#--pkg-config-flags: 
#--extra-cflags: 전처리 명령이 포함된 C 컴파일러가 사용하는 flag
#--extra-ldflags: 커스텀 경로에 설치된 라이브러리를 찾기 위해 링커가 사용
#--extra-libs:
#--bindir: 경로에 있는 바이너리 파일 설치
#--enable-gpl: GPL 코드 사용 허가(Generic Public License)
#--enable-nonfree: nonfree 코드 사용 허가
PATH="$HOME/bin:$PATH" PKG_CONFIG_PATH="$HOME/ffmpeg_build/lib/pkgconfig" ./configure --prefix="$HOME/ffmpeg_build" --pkg-config-flags="--static" --extra-cflags="-I$HOME/ffmpeg_buld/include" --extra-ldflags="-L$HOME/ffmpeg_build/lib" --extra-libs="-lpthread -lm" --bindir="$HOME/bin" --enable-gpl --enable-libass --enable-libfdk-aac --enable-libfreetype --enable-libmp3lame --enable-libmfx --enable-libopus --enable-libtheora --enable-libvorbis --enable-libvpx --enable-libx264 --enable-nonfree;
make;
make install;
make distclean;
#$PATH 와 기억된 경로를 통해 명령어를 찾은 해시 테이블 초기화
hash -r;
#man ffmpeg 으로 ffmpeg을 실행할 수 있게 설정
echo "MANPATH_MAP $HOME/bin $HOME/ffmpeg_build/share/man" >> ~/.manpath;
#ffmpeg 경로를 현재 쉘 세션이 알 수 있게 설정
. ~/.profile;
sudo apt install ffmpeg;

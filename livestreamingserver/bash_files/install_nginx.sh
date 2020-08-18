cd ~/;
sudo apt-get install libperl-dev libpcre3 libpcre3-dev zlib1g zlib1g-dev openssl libssl-dev libxml2-dev libxslt1-dev libgd-dev libgeoip-dev google-perftools libgoogle-perftools-dev gcc g++;

#rtmp 모듈 다운로드
wget https://github.com/arut/nginx-rtmp-module/archive/master.zip;
unzip master.zip;

#nginx 컴파일 소스 다운로드
wget http://nginx.org/download/nginx-1.19.2.tar.gz;
tar -zxf nginx-1.19.2.tar.gz;
cd nginx-1.19.2;

#--sbin-path: nginx 바이너리 파일이 설치되는 경로 설정
#--prefix: nginx가 설치되는 경로 설정
#--conf-path: 환경 설정 파일 경로 설정
#--error-log-path: 에러 로그 파일 경로 설정
#--http-log-path: 접근 로그 경로  설정
#--pid-path: pid 파일 경로 설정
./configure \
	--sbin-path=/usr/local/sbin/nginx \
	--prefix=/usr/share/nginx \
	--conf-path=/etc/nginx/nginx.conf \
	--error-log-path=/var/log/error.log \
	--http-log-path=/var/log/access.log \
	--pid-path=/var/run/nginx.pid \
	--with-http_ssl_module \
	--with-http_v2_module \
	--with-http_realip_module \
	--with-http_addition_module \
	--with-http_xslt_module \
	--with-http_image_filter_module \
	--with-http_geoip_module \
	--with-http_sub_module \
	--with-http_dav_module \
	--with-http_flv_module \
	--with-http_mp4_module \
	--with-http_gunzip_module \
	--with-http_gzip_static_module \
	--with-http_auth_request_module \
	--with-http_random_index_module \
	--with-http_secure_link_module \
	--with-http_slice_module \
	--with-http_degradation_module \
	--with-http_stub_status_module \
	--with-http_perl_module \
	--with-mail \
	--with-mail_ssl_module \
	--with-stream \
	--with-stream_ssl_module \
	--with-google_perftools_module \
	--with-cpp_test_module \
	--with-debug \
	--add-module=../nginx-rtmp-module-master;
sudo make;
sudo make install;

mkdir ~/vod;
sudo chmod 777 ~/vod;

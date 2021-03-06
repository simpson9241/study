Live Streaming Server Using NGINX
=====

[설치]
-----

1. 터미널 실행
2. 다운로드 받은 폴더로 경로 이동
3. livestream.sh 파일이 있는 livestreamingserver 폴더 경로에서 sh livestream.sh 명령어를 실행 후 1번 메뉴를 선택해 ffmpeg과 nginx를 설치
<pre><code>sh livestream.sh</code></pre>

/etc/nginx 폴더에 있는 nginx.conf 파일에서 특정 경로들을 변경해서 설정 필요(hls_path, location /vod/ 의 root)


[실행]
-----

1. sh livestream.sh 명령어를 실행하고 2번 메뉴를 선택하고 각 기능에 해당하는 번호를 입력하면 nginx 서버에 대한 조작 가능
<pre><code>sh livestream.sh</code></pre>
  - Run Server: nginx 서버 가동  
  - Restart Server: nginx 서버 재시작  
  - Stop Server: nginx 서버 중지
2. 3번 메뉴를 선택하면 원본 영상 파일로 스트리밍 시작
3. 4번 메뉴를 선택하면 원본 영상을 m3u8 파일로 변환하여 ~/vod 폴더에 저장
4. 5번 메뉴를 선택하면 ffmpeg과 nginx 삭제
5. 6번 메뉴를 선택하면 프로그램 중지
6. http://[서버 아이피 주소]/vod/[파일 이름] 으로 vlc에서 네트워크 스트림 지정하면 vod 파일 재생
<pre><code>http://192.168.10.179/vod/bunny.m3u8</code></pre>

[OBS 설정]
-----

1. OBS 실행
2. File-> Settings-> Stream 으로 이동
3. Service를 Custom으로 변경
4. Server를 rtmp://[서버 아이피 주소]/[하위주소] 로 변경
<pre><code>rtmp://localhost/live</code></pre>
5. Stream Key를 임의로 설정(e.g. test)


[VLC 설정]
-----

1. VLC 실행
2. Ctrl + N 혹은 미디어-> 네트워크 스트림 열기 로 이동
3. OBS에서 Server에 설정했던 주소 rtmp://[서버 아이피 주소]/[하위 주소]/[Stream Key] 입력
<pre><code>rtmp://192.168.10.179/live/test</code></pre>
4. 재생 버튼 클릭


[프로그램 삭제]
-----

1. 터미널을 실행
2. livestreamingserver 폴더 경로까지 이동
3. sh livestream.sh 명령어를 실행하고 3번 메뉴를 선택하면 자동으로 ffmpeg과 nginx를 삭제
<pre><code>sh livestream.sh</code></pre>

[오류 해결 방법]
-----

1. nginx 서버를 시작할 때 "Address already in use" 라며 제대로 실행되지 않을 경우
- 터미널을 열어 다음과 같이 명령을 실행 "sudo fuser -k 80/tcp"
<pre><code>sudo fuser -k 80/tcp</code></pre>
- 이때 이미 쓰여지고 있는 포트 번호를 기억하고 상황에 따라 변경해서 명령어 실행
- 이후 nginx 서버를 다시 시작

[함수 설명]
-----

- config_nginx
    * /etc/nginx 폴더에 위치한 nginx.conf 환경 설정 파일에 rtmp 프로토콜에 대한 내용을 추가해주는 함수
        + /etc/nginx 폴더에 위치한 nginx.conf 파일의 권한을 777로 설정
        + /etc/nginx 폴더에 위치한 nginx.conf 파일에 bash_files 폴더에 위치한 text.txt의 내용을 덮어써서 저장
- install
    * ffmpeg 을 다운 받고 빌드해 설치하고 nginx 컴파일 소스를 다운 받고 빌드하여 설치하는 함수
        + 의존 관계가 있는 library 다운로드 및 업데이트
        + ffmpeg_sources 폴더 생성
        + ffmpeg은 빌드 시 Yasm을 사용하므로 Yasm을 설치
        + 코덱 설치에 사용되는 Nasm 설치
        + libx264, libfdk-aac, libmp3lame, libopus, libvpx 코덱 설치
        + ffmpeg 설치
        + 환경 변수 설정
        + 코어 및 모듈 동작에 필요한 PCRE, zlib, OpenSSL 라이브러리와 기본 패키지에서 제공하는 모듈을 사용할 수 있게 해주는 개발자 패키지와 컴파일러를 설치
        + nginx 서버에서 rtmp 모듈을 사용할 수 있게 rtmp 모듈을 다운로드
        + nginx 컴파일 소스 다운로드
        + 환경 설정 옵션에서 nginx 패키지에 포함된 모든 모듈을 사용할 수 있게 하고, 다운 받았던 rtmp 모듈을 추가
        + 환경 설정 옵션에서 설정 파일을 /etc/nginx 에 위치할 수 있도록 설정
        + make 명령어로 컴파일 후 make install 명령어 실행
        + ~/vod 파일 생성
- server_control
    * 서버를 시작, 재시작, 정지할 수 있도록 서버를 컨트롤하는 함수
        + 1번 메뉴를 선택한 경우 nginx 서버를 시작
        + 2번 메뉴를 선택한 경우 nginx 서버를 재시작
        + 3번 메뉴를 선택한 경우 nginx 서버를 정지
        + 4번 메뉴를 선택한 경우 함수 종료
        + 1, 2, 3, 4 외 다른 입력을 한 경우 "Invalid Input!"을 출력  
- stream
    * ffmpeg을 이용하여 기존에 있는 소스 파일을 rtmp 프로토콜로 스트리밍하는 함수
        + 소스 파일의 경로와 rtmp 주소를 입력하면 스트리밍 시작
        + -re: input을 기존 frame rate로 읽어들임
        + -i: 뒤에 오는 것이 input 파일임을 명시
        + -vcodec: 비디오 코덱은 원본 파일에 따라가는 것을 명시
        + -loop: 원본 파일이 얼마나 반복될 것인지 명시. (-1은 무한 반복)
        + -c: 코덱 설정(-c:a는 오디오, -c:v는 영상 이미지)
        + -b: 비트레이트 설정 (-b:a는 오디오)
        + -ar: 오디오 샘플링 비율 설정(단위는 Hz)
        + -f: 파일 포맷 지정
- make_vod
    * ffmpeg을 이용하여 원본 파일을 m3u8 파일로 변환하여 ~/vod 폴더에 저장하는 함수
        + /home/{username}/ 에 들어갈 username 입력
        + 원본 파일의 경로 입력
        + 결과물로 나올 m3u8 파일의 이름 입력
        + -i: input 파일이 뒤에 나오는 것을 명시
        + -bsf: bit stream filter를 지정
        + h264_mp4toannexb: bit stream filter의 일종. mp4 파일은 length marker가 있고 h264 데이터의 00 00 01 prefix 데이터가 없으므로 h264 디코더가 제대로 작동하지 않음. 이 filter를 적용해 file header에 명시된 pps/sps를 식별해 이 문제를 해결.
        + -c: 코덱 명시
        + -hls_time: 세그먼트 길이 설정
        + -hls_list_size: playlist 최대 개수, 모든 playlist를 넣기 위해서는 0으로 설정
- uninstall
    * ffmpeg을 삭제하고 nginx를 삭제하는 함수
        + ffmpeg 패키지 및 관련 패키지 삭제
        + ffmpeg을 설치했던 패키지와 생성했던 폴더 및 파일들 삭제
        + 환경변수 설정해줬던 것을 sed 명령어로 삭제
        + $PATH 와 기억된 경로를 통해 명령어를 찾은 이력(해쉬 테이블)을 초기화 
        + nginx를 설치할 때 다운 받았던 rtmp 모듈 관련 파일 삭제
        + nginx, nginx-common, nginx-full, nginx-core 패키지 삭제
        + /usr/lcoal/nginx 와 /usr/local/sbin/nginx 삭제
        + /usr/share/nginx 삭제  

[RTMP 프로토콜 추가 설명]
-----

- text.txt
    * rtmp 프로토콜과 http 프로토콜에 대한 설정이 담긴 텍스트 파일
        + listen: 1935 포트를 쓴다는 것을 명시
        + chunk_size: chunk 크기를 지정
        + live: 라이브 스트리밍 설정
        + record: 녹화 설정
        + /etc/nginx 폴더에 있는 nginx.conf 파일에서 특정 경로들을 변경해서 설정 필요(hls_path, location /vod/ 의 root)

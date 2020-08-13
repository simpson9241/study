Live Streaming Server using NGINX
=====

[설치 및 실행]
-----

1. 터미널 실행
2. 다운로드 받은 폴더로 경로 이동
3. livestreamingserver 폴더 경로에서 sh livestream.sh 명령어를 실행 후 1번 메뉴를 선택해 ffmpeg과 nginx를 설치
4. sh livestream.sh 명령어를 실행하고 2번 메뉴를 선택하면 각 기능에 해당하는 번호를 입력하면 nginx 서버에 대한 조작 가능  
- Run Server: nginx 서버 가동  
- Restart Server: nginx 서버 재시작  
- Stop Server: nginx 서버 중지


[OBS 설정]
-----

1. OBS 실행
2. File-> Settings-> Stream 으로 이동
3. Service를 Custom으로 변경
4. Server를 rtmp://[서버 아이피 주소]/[하위주소] 로 변경 (e.g. rtmp://localhost/live)
5. Stream Key를 임의로 설정(e.g. test)


[VLC 설정]
-----

1. VLC 실행
2. Ctrl + N 혹은 미디어-> 네트워크 스트림 열기 로 이동
3. OBS에서 Server에 설정했던 주소 rtmp://[서버 아이피 주소]/[하위 주소]/[Stream Key] 입력 (e.g. rtmp://192.168.10.179/live/test)
4. 재생 버튼 클릭


[프로그램 삭제]
-----

1. 터미널을 실행
2. livestreamingserver 폴더 경로까지 이동
3. sh livestream.sh 명령어를 실행하고 3번 메뉴를 선택하면 자동으로 ffmpeg과 nginx를 삭제

[오류 해결 방법]
-----

1. nginx 서버를 시작할 때 "Address already in use" 라며 제대로 실행되지 않을 경우
- 터미널을 열어 다음과 같이 명령을 실행 "sudo fuser -k 80/tcp"
- 이때 이미 쓰여지고 있는 포트 번호를 기억하고 상황에 따라 변경해서 명령어 실행
- 이후 nginx 서버를 다시 시작
- 만약 그래도 안된다면 /etc/nginx 폴더에 있는 nginx.conf 파일에 특정 프로토콜에 대한 설정이 중복으로 있는지 확인한 후 중복된 것을 삭제
- 이 프로그램을 통해 두 번 이상 설치하면 nginx.conf 파일에 rtmp 프로토콜에 대한 설정이 중복으로 들어가게 되므로 확인 권장

[쉘 스크립트 설명]
-----

- livestream.sh  
    * bash_files 폴더 안에 있는 bash 파일들을 이용해 전체적인 프로그램 흐름을 제어하는 쉘 스크립트
        + 1, 2, 3, 4, 5를 입력해 메뉴를 선택하여 해당 기능을 이용할 수 있게 구성
        + 1, 2, 3, 4, 5가 아닌 다른 숫자를 입력하면 "Invalid Input!" 을 출력  
- install_ffmpeg.sh
    * ffmpeg 을 다운 받고 빌드해 설치하는 쉘 스크립트
        + 의존 관계가 있는 library 다운로드 및 업데이트
        + ffmpeg_sources 폴더 생성
        + ffmpeg은 빌드 시 Yasm을 사용하므로 Yasm을 설치
        + 코덱 설치에 사용되는 Nasm 설치
        + libx264, libfdk-aac, libmp3lame, libopus, libvpx 코덱 설치
        + ffmpeg 설치
        + 환경 변수 설정
        + ffserver 설치  
- install_nginx.sh
    * nginx 컴파일 소스를 다운 받고 빌드하여 설치하는 쉘 스크립트
        + 코어 및 모듈 동작에 필요한 PCRE, zlib, OpenSSL 라이브러리와 기본 패키지에서 제공하는 모듈을 사용할 수 있게 해주는 개발자 패키지와 컴파일러를 설치
        + nginx 서버에서 rtmp 모듈을 사용할 수 있게 rtmp 모듈을 다운로드
        + nginx 컴파일 소스 다운로드
        + 환경 설정 옵션에서 nginx 패키지에 포함된 모든 모듈을 사용할 수 있게 하고, 다운 받았던 rtmp 모듈을 추가
        + 환경 설정 옵션에서 설정 파일을 /etc/nginx 에 위치할 수 있도록 설정
        + make 명령어로 컴파일 후 make install 명령어 실행  
- config_nginx.sh
    * /etc/nginx 폴더에 위치한 nginx.conf 환경 설정 파일에 rtmp 프로토콜에 대한 내용을 추가해주는 쉘 스크립트
        + /etc/nginx 폴더에 위치한 nginx.conf 파일의 권한을 777로 설정
        + 환경 설정을 잠시 저장할 임시 파일을 생성
        + 생성한 임시 파일의 권한을 777로 설정
        + /etc/nginx 폴더에 위치한 nginx.conf 파일에 bash_files 폴더에 위치한 text.txt의 내용을 이어 붙여서 생성했던 임시 파일에 저장
        + 이후 임시 파일의 내용을 /etc/nginx 폴더의 nginx.conf 파일에 덮어쓰기
        + 생성했던 임시 파일 삭제  
- install.sh
    * ffmpeg과 nginx 모두 설치하는 쉘 스크립트
        + install_ffmpeg.sh 파일과 install_nginx.sh 파일을 실행  
- start_nginx.sh
    * nginx 서버를 시작하는 쉘 스크립트
        + /etc/nginx/ 폴더로 이동하여 nginx를 실행  
- restart_nginx.sh
    * nginx 서버를 재기동하는 쉘 스크립트
        + /etc/nginx/ 폴더로 이동하여 nginx를 재시작
        + 설정 파일을 다시 읽어 서버에 반영  
- stop_nginx.sh
    * nginx 서버를 정지시키는 쉘 스크립트
        + /etc/nginx/ 폴더로 이동하여 nginx를 정지  
- server_control.sh
    * 서버를 시작, 재시작, 정지할 수 있도록 서버를 컨트롤하는 쉘 스크립트
        + 1번 메뉴를 선택한 경우 start_nginx.sh 파일을 실행하여 nginx 서버를 시작
        + 2번 메뉴를 선택한 경우 restart_nginx.sh 파일을 실행하여 nginx 서버를 재시작
        + 3번 메뉴를 선택한 경우 stop_nginx.sh 파일을 실행하여 nginx 서버를 정지
        + 4번 메뉴를 선택한 경우 쉘 스크립트 종료
        + 1, 2, 3, 4 외 다른 입력을 한 경우 "Invalid Input!"을 출력  
- stream.sh
    * ffmpeg을 이용하여 기존에 있는 소스 파일을 rtmp 프로토콜로 스트리밍하는 쉘 스크립트
        + 소스 파일의 경로와 rtmp 주소를 입력하면 스트리밍 시작
        + -re 옵션: input을 기존 frame rate로 읽어들임
        + -i 옵션: 뒤에 오는 것이 input 파일임을 명시
        + -vcodec: 비디오 코덱은 원본 파일에 따라가는 것을 명시
        + -loop: 원본 파일이 얼마나 반복될 것인지 명시. (-1은 무한 반복)
        + -c: 코덱 설정(-c:a는 오디오, -c:v는 영상 이미지)
        + -b: 비트레이트 설정 (-b:a는 오디오)
        + -ar: 오디오 샘플링 비율 설정(단위는 Hz)
        + -f: 파일 포맷 지정
- remove_ffmpeg.sh
    * ffmpeg을 삭제하는 쉘 스크립트
        + ffmpeg 패키지 및 관련 패키지 삭제
        + ffmpeg을 설치했던 패키지와 생성했던 폴더 및 파일들 삭제
        + 환경변수 설정해줬던 것을 sed 명령어로 삭제
        + $PATH 와 기억된 경로를 통해 명령어를 찾은 이력(해쉬 테이블)을 초기화  
- remove_nginx.sh
    * nginx를 삭제하는 쉘 스크립트
        + nginx를 설치할 때 다운 받았던 rtmp 모듈 관련 파일 삭제
        + nginx, nginx-common, nginx-full, nginx-core 패키지 삭제
        + /usr/lcoal/nginx 와 /usr/local/sbin/nginx 삭제
        + /usr/share/nginx 삭제  
- uninstall.sh
    * ffmpeg과 nginx를 삭제하는 쉘 스크립트
        + remove_nginx.sh 와 remove_ffmpeg.sh 를 실행


[RTMP 프로토콜 추가 설명]
-----

- text.txt
    * rtmp 프로토콜에 대한 설정이 담긴 텍스트 파일
        + listen: 1935 포트를 쓴다는 것을 명시
        + chunk_size: chunk 크기를 지정
        + live: 라이브 스트리밍 설정
        + record: 녹화 설정

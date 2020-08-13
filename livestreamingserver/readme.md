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
- 터미널을 열어 다음과 같이 명령을 실행한다. "sudo fuser -k 80/tcp"
- 이후 nginx 서버를 다시 시작한다.

[쉘 스크립트 설명]
-----

- livestream.sh  
    * bash_files 폴더 안에 있는 bash 파일들을 이용해 전체적인 프로그램 흐름을 제어하느 쉘 스크립트
    * 1, 2, 3, 4를 입력해 메뉴를 선택하여 해당 기능을 이용할 수 있게 구성
    * 1, 2, 3, 4가 아닌 다른 숫자를 입력하면 "Invalid Input!" 을 출력
- install_ffmpeg.sh
- install_nginx.sh
- config_nginx.sh
- install.sh
- start_nginx.sh
- restart_nginx.sh
- stop_nginx.sh
- server_control.sh
- remove_ffmpeg.sh
- remove_nginx.sh
- uninstall.sh


[RTMP 프로토콜 추가 설명]
-----

- text.txt

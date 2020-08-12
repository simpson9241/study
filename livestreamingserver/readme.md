#Live Streaming Server using NGINX

[설치 및 실행]

1. 터미널을 실행
2. 다운로드 받은 폴더로 경로 이동
3. livestreamingserver 폴더 경로에서 sh install.sh 명령어를 실행해 ffmpeg과 nginx를 설치
4. 그 후 sh setup.sh 명령어를 실행해 nginx 서버의 설정에 rtmp 프로토콜을 추가
5. sh server_control.sh 명령어를 실행하면 nginx 서버에 대한 조작 가능  
-Run Server: nginx 서버 가동  
-Restart Server: nginx 서버 재시작  
-Stop Server: nginx 서버 중지


[OBS 설정]

1. OBS 실행
2. File-> Settings-> Stream 으로 이동
3. Service를 Custom으로 변경
4. Server를 rtmp://[서버 아이피 주소]/[하위주소] 로 변경 (e.g. rtmp://localhost/live)
5. Stream Key를 임의로 설정(e.g. test)


[VLC 설정]

1. VLC 실행
2. Ctrl + N 혹은 미디어-> 네트워크 스트림 열기 로 이동
3. OBS에서 Server에 설정했던 주소 rtmp://[서버 아이피 주소]/[하위 주소]/[Stream Key] 입력 (e.g. rtmp://localhost/live/test)
4. 재생 버튼 클릭


[프로그램 삭제]

1. 터미널을 실행
2. livestreamingserver 폴더 경로까지 이동
3. sh uninstall.sh 명령어를 실행하면 자동으로 ffmpeg과 nginx를 삭제


[오류 해결 방법]

1. nginx 서버를 시작할 때 "Address already in use" 라며 제대로 실행되지 않을 경우
-> 터미널을 열어 다음과 같이 명령을 실행한다. "sudo fuser -k 80/tcp"
-> 이후 nginx 서버를 다시 시작한다.

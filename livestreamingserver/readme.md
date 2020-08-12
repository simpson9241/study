nginx 시작할 때 Address already in use 라며 제대로 실행되지 않을 경우 터미널에 다음과 같이 명령을 실행한다.
sudo fuser -k 80/tcp

이후 nginx 재시작하면 끝.

nginx.config 설정에 rtmp 프로토콜 추가하기
제일 밑단에 아래 코드를 추가.

rtmp{
  server{
    listen 1935;
    chunk_size 4096;

    application live{
      live on;
      record off;
    }
  }
}

OBS 에서 설정->Streaming Service: Custom -> Server: rtmp://[서버 아이피 주소]/[하위주소]->스트림 키: [임의로 설정]

VLC 미디어 플레이어에서 네트워크 스트림 열기-> 네트워크 주소란 -> rtmp://[서버 아이피 주소]/[하위 주소]/[스트림 키]

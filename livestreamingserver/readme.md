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

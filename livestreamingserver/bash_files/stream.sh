#! /bin/bash

echo "Input the path of the source file : "
read path
echo "Input the address of the server : "
read address
ffmpeg -re -i ${path} -vcodec copy -loop -1 -c:a aac -b:a 160k -ar 44100 -f flv ${address};

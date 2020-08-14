#! /bin/bash
echo "Enter username : "
read name
echo "Enter the path of the source file : "
read path
echo "Enter the name of the output file : "
read output
ffmpeg -i ${path} -bsf:v h264_mp4toannexb -c:v libx264 -c:a aac -hls_time 2 -hls_list_size 0 /home/${name}/vod/${output}.m3u8;

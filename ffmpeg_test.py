import os
import sys

input_path=sys.argv[1]
ffmpeg_cmd="ffmpeg -i {0} -filter_complex:v \"\
            [0] scale=480x270,fps=fps=29.970,format=yuv420p [output_270];\
            [0] scale=852x480,fps=fps=29.970,format=yuv420p [output_480];\
            [0] scale=1280x720,fps=fps=29.970,format=yuv420p [output_720];\
            [0] scale=1920x1080,fps=fps=29.970,format=yuv420p [output_1080] \"\
            -map [output_270] -map 0:a -c:v libx264 -profile:v baseline -level 3.0 -c:a libfdk_aac -b:v 500K -maxrate 500k -bufsize 1000k -ac 2  -ar 48000 -g 60 -bf 0 -refs 1 -keyint_min 60 -coder 0 -f mp4 270p.mp4\
            -map [output_480] -map 0:a -c:v libx264 -profile:v baseline -level 3.0 -c:a libfdk_aac -b:v 1400K -maxrate 1400k -bufsize 2800k -ac 2 -ar 48000 -g 60 -bf 0 -refs 1 -keyint_min 60 -coder 0 -f mp4 480p.mp4\
            -map [output_720] -map 0:a -c:v libx264 -profile:v baseline -level 3.1 -c:a libfdk_aac -b:v 2000K -maxrate 2000k -bufsize 4000k -ac 2 -ar 48000 -g 60 -bf 0 -refs 1 -keyint_min 60 -coder 0 -f mp4 720p.mp4\
            -map [output_1080] -map 0:a -c:v libx264 -profile:v baseline -level 4.0 -c:a libfdk_aac -b:v 5500K -maxrate 5500k -bufsize 11000k -ac 2 -ar 48000 -g 60 -bf 0 -refs 1 -keyint_min 60 -coder 0 -f mp4 1080p.mp4"

exec_cmd=ffmpeg_cmd.format(input_path)
ret_code=os.system(exec_cmd)

if ret_code==0:
    sys.stdout.write("Success")
else:
    sys.stderr.write("Fatal Error")

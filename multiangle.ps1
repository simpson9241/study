ffmpeg.exe -loglevel verbose -init_hw_device d3d11va=qsv:MFX_IMPL_hw_any -hwaccel qsv -filter_hw_device qsv -c:v h264_qsv -re -i 1080p.mp4 `
    -filter_complex:v "
    color=c=black:size=1920x1080,hwupload=extra_hw_frames=10 [main],
    [0] scale_qsv=1152:648 [center],
    [main][center] overlay_qsv=x=384
    " `
    -c:v h264_qsv -profile:v baseline `
    -b:v 5000k -r 60 -g 120 test.mp4
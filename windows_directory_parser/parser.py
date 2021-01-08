import os
import csv
import sys
import glob
import mimetypes

output_name=sys.argv[2]+".csv"
root_dir=sys.argv[1]+"/**"
file_output=open(output_name, 'w',encoding='utf-8')
writer=csv.writer(file_output)

file_list=glob.glob(root_dir,recursive=True)

for file in file_list:
    get_mime_type=mimetypes.guess_type(file)
    mime_type=get_mime_type[0]
    if not mime_type==None:
        video_flag_temp=mime_type.split('/')
        video_flag=video_flag_temp[0]
        if video_flag=='video':
            file_dir=file
            file_temp=file.split('/')
            file_name=file_temp[-1]
            writer.writerow([file_dir,file_name])


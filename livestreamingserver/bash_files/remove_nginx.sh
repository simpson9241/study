cd ~/;
sudo rm -rf nginx-rtmp-module-master;
sudo rm master.zip;
sudo rm -rf nginx-vod-module;
sudo apt remove nginx nginx-common nginx-full nginx-core;
sudo rm -f -R /usr/local/nginx && sudo rm -f -R /usr/local/sbin/nginx;
sudo rm -f -R /usr/share/nginx;
sudo rm -f -R ~/nginx-1.19.2.tar.gz;

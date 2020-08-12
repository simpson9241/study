sudo chmod 777 /etc/nginx/nginx.conf;
sudo touch /etc/nginx/nginx_temp.conf;
sudo chmod 777 /etc/nginx/nginx_temp.conf;
sudo cat /etc/nginx/nginx.conf text.txt >> /etc/nginx/nginx_temp.conf;
sudo cat /etc/nginx/nginx_temp.conf > /etc/nginx/nginx.conf;
sudo rm /etc/nginx/nginx_temp.conf;


#! /bin/bash
i=0

while [ $i -ne 4 ]
do
	echo "1. Run Server  2. Restart Server  3. Stop Server  4. Exit"
	echo "Input: "
	read i
	if [ $i -eq 1 ]
	then
		cd /etc/nginx/;
		sudo nginx;
	elif [ $i -eq 2 ]
	then
		cd /etc/nginx
		sudo nginx -s reload;
	elif [ $i -eq 3 ]
	then
		cd /etc/nginx;
		sudo nginx -s stop;
	elif [ $i -gt 4 -o $i -lt 1 ]
	then
		echo "Invalid Input!"
	else
		echo "Bye!"
	fi
done



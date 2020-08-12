#! /bin/bash
cd bash_files/;
n=0

while [ $n -ne 4 ]
do
	echo "1. Install  2. Control Server  3. Uninstall  4. Exit"
	echo "Input: "
	read n
	if [ $n -eq 1 ]
	then
		sh install.sh;
		sh config_nginx.sh;
		echo "Install and Configuration Complete"
	elif [ $n -eq 2 ]
	then
		sh server_control.sh;
	elif [ $n -eq 3 ]
	then
		sh uninstall.sh;
		echo "Uninstall Complete"
	elif [ $n -gt 4 -o $n -lt 1 ]
	then
		echo "Invalid Input!"
	else
		echo "Exiting Prgram"
	fi
done


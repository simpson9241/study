#! /bin/bash
i=0

while [ $i -ne 4 ]
do
	echo "1. Run Server  2. Restart Server  3. Stop Server  4. Exit"
	echo "Input: "
	read i
	if [ $i -eq 1 ]
	then
		sh start_nginx.sh;
	elif [ $i -eq 2 ]
	then
		sh restart_nginx.sh;
	elif [ $i -eq 3 ]
	then
		sh stop_nginx.sh;
	elif [ $i -gt 4 -o $i -lt 1 ]
	then
		echo "Invalid Input!"
	else
		echo "Bye!"
	fi
done



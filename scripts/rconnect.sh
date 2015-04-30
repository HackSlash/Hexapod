#!/bin/bash

sudo echo
clear

printf "Do you want a graphical user interface? (\e[0;31mG\e[0;37mraphical, \e[0;31mS\e[0;37mSH)\n"
read awnser

if [ "$awnser" == "G" -o "$awnser"  == "g" ]
then
	graphical=true
elif [ "$awnser"  == "S" -o "$awnser"  == "s" ]
then
	graphical=false
else
	echo "Invalid input, press any key to quit"
	read
	exit
fi

clear

printf "Which IP do you want to use? (\e[0;31mS\e[0;37mchool, \e[0;31mC\e[0;37mustom)\n"
read awnser

if [ "$awnser"  == "S" -o "$awnser" == "s" ]
then
	printf "Put in IP: 141.252.219."
	read ip
	ip="141.252.219.$ip"
elif [ "$awnser"  == "C" -o "$awnser" == "c" ]
then
	printf "Put in IP: "
	read ip
else
	echo "Invalid input, press any key to quit"
	read
	exit
fi

clear

if [ $graphical == true ]
then
printf "\e[0;32mRemember to press CTRL+ALT+F7 when you are switched to the other desktop, you still need to login with SSH\e[0;37m\n"
printf "\e[0;32mPress CTRL+ALT+F8 to go to the Raspberry's Desktop,\n\e[0;33mPress CTRL+ALT+F7 to go back to your own\e[0;37m\n"
read
clear
sudo xinit -- :1 2> xServLog.txt &
DISPLAY=:1 ssh -X pi@$ip lxsession 2> displayConnectLog.txt
else
ssh pi@$ip
fi



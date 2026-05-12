stty -F /dev/ttyUSB0 speed 9600 # o 2400 la que necesiten
cat /dev/ttyUSB0 | while read -n 1 tecla; do
	echo $tecla
	if [ "$tecla" = "A" ]; then
		YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key 105:1
	elif [ "$tecla" = "a" ]; then
		YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key 105:0
	elif [ "$tecla" = "D" ]; then
		YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key 106:1
	elif [ "$tecla" = "d" ]; then
		YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key 106:0
	elif [ "$tecla" = "J" ]; then
		YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key 44:1
	elif [ "$tecla" = "j" ]; then
		YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key 44:0
	fi
done

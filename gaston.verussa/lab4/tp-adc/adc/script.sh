stty -F /dev/ttyUSB0 speed 9600 # o 2400 la que necesiten
valor=0
cat /dev/ttyUSB0 | while read -n 1 c; do
	echo "llego esto: "
	echo $c
	if [[ "$c" =~ [0-9] ]]; then
		((valor = valor * 10 + $c))
		echo 'es num'
		echo "valor es: "
		echo $valor
	else
		((valor = valor * 4))
		echo $valor
		sudo brightnessctl set $valor
		((valor = 0))
	fi
done

default:
	arduino-cli compile -u && arduino-cli monitor

pico:
	picocom --baud 9600 --imap lfcrlf --quiet /dev/ttyUSB0

# lnxenv
Programming in Linux environment

1. Run a C application program as a Linux systemd service.
Following is a quick sample for getting started with Systemd based service manager on Linux.

requsites:
	hw.c
	watchdog-test.service

steps:
	0. Compile the hw.c program and point the 'ExecStart' parameter in the watchdog-test.service file to the executable or a.out file. Use absolute path. 
	1. Put watchdog-test.service file in /lib/systemd/system.
	2. Run command 'systemctl daemon-reload' to reload all services or anytime changes are made to service file.
	3. Run command 'service watchdog-test start'. This should start you C application program and you can check that by running 'ps aux | grep <BIN-NAME>' 
	4. Kill you application program using 'killall -9 <BIN-NAME>'. You'll notice that after a few seconds the application program will start automatically.

links:
	1. https://www.man7.org/linux/man-pages/man5/systemd.service.5.html

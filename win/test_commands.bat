REM
REM This is a set of commands to run and verify they work before doing a new release.
REM Eventually they should also use the -J flag to generate JSON output, and a program should 
REM be written to check the output.
REM Be sure to test both client and server on Linux, BSD, and OSX
REM

if not "%1" == "" goto test
	echo "Usage: %0 hostname"
	goto :eof

:test

REM basic testing
iperf3 -c %1 -V -t 5 -T "test1"
iperf3 -c %1 -u -V -t 5
REM omit mode
iperf3 -c %1 -i .3 -O 2 -t 5
REM JSON mode
iperf3 -c %1 -i 1 -J -t 5
REM force V4
iperf3 -c %1 -4 -t 5
iperf3 -c %1 -4 -u -t 5
REM force V6
iperf3 -c %1 -6 -t 5
iperf3 -c %1 -6 -u -t 5
REM parallel streams
iperf3 -c %1 -P 3 -t 5 
REM win32 mutiple UDP streams are broken
REM iperf3 -c %1 -u -P 3 -t 5
REM reverse mode
iperf3 -c %1 -t 5 -R
iperf3 -c %1 -u -t 5 -R
REM reverse mode multiple streams
iperf3 -c %1 -P 2 -t 5 -R
REM win32 mutiple UDP streams are broken
REM iperf3 -c %1 -u -P 2 -t 5 -R
REM zero copy
REM iperf3 -c %1 -Z -t 5 
REM iperf3 -c %1 -Z -t 5 -R
REM window size
iperf3 -c %1 -t 5 -w 8M 
REM -n flag
iperf3 -c %1 -n 5M  
iperf3 -c %1 -n 5M -u -b1G
REM conflicting -n -t flags
iperf3 -c %1 -n 5M -t 5
REM -k mode
iperf3 -c %1 -k 1K  
iperf3 -c %1 -k 1K -u -b1G
REM CPU affinity
REM iperf3 -c %1 -A 2/2
REM iperf3 -c %1 -A 2/2 -u -b1G
REM Burst mode
iperf3 -c %1 -u -b1G/100
REM change MSS
iperf3 -c %1 -M 1000 -V
REM test congestion control option (linux only)
REM iperf3 -c %1 -C reno -V



#########################################################################
# File Name: httpd_ctl.sh
# Author: ZX
# mail: 18829897183@163.com
# Created Time: Sun 09 Apr 2017 09:06:37 PM PDT
#########################################################################
#!/bin/bash

ROOT_PATH=pwd
BIN=${ROOT_PATH}/httpd
CONF=${ROOT_PATH}/conf/httpd.conf
PID=$ROOT_PATH/httpd.pid

proc=`basename $0`
function usage(){
	printf "%s [start(-s) | stop(-t) | restart(-rt)]\n" "$proc"
}

function http_start(){
	[[ -f $PID ]] && {
		printf "http is exist, pid is $(cat $PID)\n"
		return
	}
	ip=$(grep -E '^IP:' $CONF | awk -F: '{printf $2}')
	port=$(grep -E '^PORT:' $CONF | awk -F: '{printf $2}')
	$BIN $ip $port
	pidof $(basename $BIN) > $PID
	printf "start done, pid is: $(cat $PID)..\n"
}

function http_stop(){
	[[ ! -f $PID ]] && {
		printf "http is not exist!\n"
		return
	}
	pid=$(cat $PID)
	kill -9 $pid
	rm -f $PID
	printf "stop done ...\n"
}

[[ $# -ne 1 ]] && {
	usage
	exit 1
}

case $1 in
		start | -s )
			http_start
		;;
		stop | -t )
			http_stop
		;;
		restart | -rt )
			http_stop
			http_start
		;;
		* )
			usage
			exit 2
		;;
esac

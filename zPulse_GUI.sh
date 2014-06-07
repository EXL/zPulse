#!/bin/bash
mypath=${0%/*}
showRadio "zPulse" "" "1. Standard" "2. Helicopter" "3. UFO" "4. Shock" "5. Mosquito" "6. Train" "7. Pulse"
case "$?" in
1)
exec $mypath/zPulse -standard
;;
2)
exec $mypath/zPulse -helicopter
;;
3)
exec $mypath/zPulse -ufo
;;
4)
exec $mypath/zPulse -shock
;;
5)
exec $mypath/zPulse -mosquito
;;
6)
exec $mypath/zPulse -train
;;
7)
exec $mypath/zPulse -pulse
;;
*)
exit 0
;;
esac

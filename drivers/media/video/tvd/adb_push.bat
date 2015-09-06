adb devices
adb shell mount -o remount,rw /dev/block/system /system
adb push tvd.ko /system/vendor/modules/tvd.ko
adb shell chmod 644 /system/vendor/modules/tvd.ko
adb shell sync
echo press any key to reboot
pause
adb shell reboot
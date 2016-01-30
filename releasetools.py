import common
import struct

def FullOTA_PostValidate(info):
	# run e2fsck
	info.script.AppendExtra('run_program("/sbin/e2fsck", "-fy", "/dev/block/mmcblk0p24");');
	# resize2fs: run and delete
	info.script.AppendExtra('run_program("/tmp/install/bin/resize2fs_static", "/dev/block/mmcblk0p24");');
	# run e2fsck
	info.script.AppendExtra('run_program("/sbin/e2fsck", "-fy", "/dev/block/mmcblk0p24");');

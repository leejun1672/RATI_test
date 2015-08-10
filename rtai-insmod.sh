#! /bin/bash
sync
insmod /usr/realtime/modules/rtai_hal.ko
insmod /usr/realtime/modules/rtai_sched.ko
insmod /usr/realtime/modules/rtai_fifos.ko
insmod /usr/realtime/modules/rtai_calibrate.ko
insmod /usr/realtime/modules/rtai_sem.ko
insmod /usr/realtime/modules/rtai_msg.ko
insmod /usr/realtime/modules/rtai_mbx.ko
# insmod /usr/realtime/modules/rtai_netrpc.ko ThisNode="127.0.0.1"
insmod /usr/realtime/modules/rtai_shm.ko
sync

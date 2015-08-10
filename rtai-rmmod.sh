#! /bin/bash
sync
rmmod /usr/realtime/modules/rtai_shm.ko
# rmmod /usr/realtime/modules/rtai_netrpc.ko ThisNode="127.0.0.1"
rmmod /usr/realtime/modules/rtai_mbx.ko
rmmod /usr/realtime/modules/rtai_msg.ko
rmmod /usr/realtime/modules/rtai_sem.ko
rmmod /usr/realtime/modules/rtai_calibrate.ko
rmmod /usr/realtime/modules/rtai_fifos.ko
rmmod /usr/realtime/modules/rtai_sched.ko
rmmod /usr/realtime/modules/rtai_hal.ko
sync

#cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg
#  ssh red-pitaya "LD_LIBRARY_PATH=/opt/redpitaya/lib /root/projects/esther-pulse-gen/src/gen_esther_pulse2"
export LD_LIBRARY_PATH=/opt/redpitaya/lib
/root/bin/gen_esther_pulse2


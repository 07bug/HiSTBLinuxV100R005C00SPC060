#+++++++++++++++++++++++++++++++++++++
menu "PowerManagement Config"
#+++++++++++++++++++++++++++++++++++++

config HI_DVFS_CPU_SUPPORT
    bool "CPU DVFS Support"
    default y
    help
        If this option is 'y', the Dynamic Voltage & Frequency Scaling of CPU will be supported.

config HI_AVS_SUPPORT
    bool "AVS Support"
    depends on HI_DVFS_CPU_SUPPORT
    default y
    help
        If this option is 'y', the Adaptive Voltage Scaling of CPU will be supported.

# for power up standby
config HI_PM_POWERUP_MODE1_SUPPORT
    bool "Power Up Standby Mode1 Support"
    default n
    help
        If this option is 'y', the power-up standby will be supported. The power-up standby refers to a special standby mode
        which enter standby when the board powers up(cold boot), then users can use IR or button to wake up the system to normal.

menu "Temperature Control"
    depends on HI_DVFS_CPU_SUPPORT

config HI_TEMP_CTRL_DOWN_THRESHOLD
    hex "Downclock: The CPU will be downclocked to reduce its power"
    default 0x73
    help
        When the temperature of the tsensor exceeds this threshold, the frequency of the CPU will decrease to the lowest one in frequency table.

config HI_TEMP_CTRL_UP_THRESHOLD
    hex "Quit Control: Below the temperature, Control loop stops operation"
    default 0x64
    help
        When the temperature of the tsensor is under this threshold, the temperature control will stop.

config HI_TEMP_CTRL_REBOOT_THRESHOLD
    hex "Shutdown: Shut the system down to protect your CPU"
    default 0x7d
    help
        When the temperature of the tsensor exceeds this threshold, the system will enter standby.
endmenu

config HI_PM_START_MCU_RUNNING
    bool "Start Mcu When Power Up"
    default n
    help
        If this option is 'y', the MCU using for standby will be started during module initialization instead of in standby process.

#+++++++++++++++++++++++++++++++++++++
endmenu
#+++++++++++++++++++++++++++++++++++++

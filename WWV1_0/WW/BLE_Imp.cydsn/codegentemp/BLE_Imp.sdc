# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Yehuda Ben Chaim\Google Drive\My Projects\WW\FW\WorkingCopy\WWV1_0\WW\BLE_Imp.cydsn\BLE_Imp.cyprj
# Date: Mon, 31 Dec 2018 20:42:03 GMT
#set_units -time ns
create_clock -name {SCB_1_SCBCLK(FFB)} -period 729.16666666666663 -waveform {0 364.583333333333} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyWCO} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/wco}]]
create_clock -name {CyLFClk} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyECO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/eco}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {PWM_CLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 97 193} [list [get_pins {ClockBlock/udb_div_0}]]
create_generated_clock -name {SCB_1_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 35 71} [list]


# Component constraints for C:\Users\Yehuda Ben Chaim\Google Drive\My Projects\WW\FW\WorkingCopy\WWV1_0\WW\BLE_Imp.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Yehuda Ben Chaim\Google Drive\My Projects\WW\FW\WorkingCopy\WWV1_0\WW\BLE_Imp.cydsn\BLE_Imp.cyprj
# Date: Mon, 31 Dec 2018 20:41:58 GMT

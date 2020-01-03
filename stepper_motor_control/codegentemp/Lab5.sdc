# THIS FILE IS AUTOMATICALLY GENERATED
# Project: D:\Lab5.cydsn\Lab5.cyprj
# Date: Thu, 12 Dec 2019 12:14:07 GMT
#set_units -time ns
create_clock -name {Clock_7(FFB)} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/ff_div_11}]]
create_clock -name {Clock_2(FFB)} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/ff_div_12}]]
create_clock -name {Clock_1(FFB)} -period 1000 -waveform {0 500} [list [get_pins {ClockBlock/ff_div_13}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {Clock_7} -source [get_pins {ClockBlock/hfclk}] -edges {1 5 9} [list]
create_generated_clock -name {Clock_2} -source [get_pins {ClockBlock/hfclk}] -edges {1 5 9} [list]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 49 97} [list]
create_generated_clock -name {Clock_5} -source [get_pins {ClockBlock/hfclk}] -edges {1 4001 8001} -nominal_period 83333.333333333328 [list [get_pins {ClockBlock/udb_div_0}]]
create_generated_clock -name {Clock_6} -source [get_pins {ClockBlock/hfclk}] -edges {1 4001 8001} -nominal_period 83333.333333333328 [list [get_pins {ClockBlock/udb_div_1}]]
create_generated_clock -name {Clock_3} -source [get_pins {ClockBlock/hfclk}] -edges {1 4001 8001} -nominal_period 83333.333333333328 [list [get_pins {ClockBlock/udb_div_2}]]
create_generated_clock -name {Clock_4} -source [get_pins {ClockBlock/hfclk}] -edges {1 4001 8001} -nominal_period 83333.333333333328 [list [get_pins {ClockBlock/udb_div_3}]]


# Component constraints for D:\Lab5.cydsn\TopDesign\TopDesign.cysch
# Project: D:\Lab5.cydsn\Lab5.cyprj
# Date: Thu, 12 Dec 2019 12:13:57 GMT

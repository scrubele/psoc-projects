# THIS FILE IS AUTOMATICALLY GENERATED
# Project: D:\Lab4_V.cydsn\Lab4_V.cyprj
# Date: Thu, 12 Dec 2019 15:25:24 GMT
#set_units -time ns
create_clock -name {Clock_2(FFB)} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/ff_div_11}]]
create_clock -name {Clock_1(FFB)} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/ff_div_12}]]
create_clock -name {ADC_intClock(FFB)} -period 187.5 -waveform {0 93.75} [list [get_pins {ClockBlock/ff_div_10}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {Clock_2} -source [get_pins {ClockBlock/hfclk}] -edges {1 5 9} [list]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 5 9} [list]
create_generated_clock -name {ADC_intClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 9 19} [list]


# Component constraints for D:\Lab4_V.cydsn\TopDesign\TopDesign.cysch
# Project: D:\Lab4_V.cydsn\Lab4_V.cyprj
# Date: Thu, 12 Dec 2019 15:25:19 GMT

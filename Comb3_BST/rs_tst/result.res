###
#	compare the timing betweem qsort using lib and qsort using multi-key
###

=================================================================
`symbol describtion`
qsort-lib: qsort with comp
qsort-mk: qsort with multible keys
all using string to compare


`format of data`
data_N_L	N: number of string, L: maxlen of string.
data_N_L*	ordered data


`statics`
				data_1e5_50		dat_1e5_50*
qsort-lib:		50.608			20.706
qsort-mk:		42.389			26.956


#!/bin/bash

. ./ram_info
. ./sys_info
. ./ip_info
. ./root_info
. ./screen_file
. ./check_param
. ./param_color

check_parameters "$@"

bg_name=$1
text_name=$2
bg_value=$3
text_value=$4

bg_name_color=$(get_back_code "$bg_name")
text_name_color=$(get_text_code "$text_name")
bg_value_color=$(get_back_code "$bg_value")
text_value_color=$(get_text_code "$text_value")

screen
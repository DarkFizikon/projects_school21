#!/bin/bash

. ./ram_info
. ./sys_info
. ./ip_info
. ./root_info
. ./screen_file
. ./check_param
. ./param_color
. ./sheme

CONFIG_FILE="config/color.cfg"

DEFAULT_COLUMN1_BACKGROUND=1
DEFAULT_COLUMN1_FONT_COLOR=6
DEFAULT_COLUMN2_BACKGROUND=6
DEFAULT_COLUMN2_FONT_COLOR=1

if [ -f "$CONFIG_FILE" ]; then
    source "$CONFIG_FILE"
fi

bg_name=${column1_backgroud:-$DEFAULT_COLUMN1_BACKGROUND}
text_name=${column1_font_color:-$DEFAULT_COLUMN1_FONT_COLOR}
bg_value=${column2_background:-$DEFAULT_COLUMN2_BACKGROUND}
text_value=${column2_font_color:-$DEFAULT_COLUMN2_FONT_COLOR}

check_parameters "$bg_name" "$text_name" "$bg_value" "$text_value"

bg_name_color=$(get_back_code "$bg_name")
text_name_color=$(get_text_code "$text_name")
bg_value_color=$(get_back_code "$bg_value")
text_value_color=$(get_text_code "$text_value")

color_name_bg=$(color_name "$bg_name")
color_name_text=$(color_name "$text_name")
color_value_bg=$(color_name "$bg_value")
color_value_text=$(color_name "$text_value")

screen

color_plan
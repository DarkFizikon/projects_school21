#!/bin/bash

. ./check_dir

dir_check "$@"

. ./folders_in_dir
. ./files_in_dir

start_time=$(date +%s.%N)

echo "Total number of folders (including all nested ones) = $total_folders"
echo "TOP 5 folders of maximum size arranged in descending order (path and size):"
top_folders
echo "Total number of files = $total_files"
echo "Number of:"
echo "Configuration files (with the .conf extension) = $conf_files"
echo "Text files = $text_files"
echo "Executable files = $exe_files"
echo "Log files (with the extension .log) = $log_files"
echo "Archive files = $arch_files"
echo "Symbolic links = $symb_link"

. ./top_files
echo "TOP 10 files of maximum size arranged in descending order (path, size and type):"
top_files

. ./top_exec_files
echo "TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file):"
top_exec_files

end_time=$(date +%s.%N)
exec_time=$(echo "$end_time - $start_time" | bc -l)
printf "Script execution time (in seconds) = %.1f\n" $exec_time
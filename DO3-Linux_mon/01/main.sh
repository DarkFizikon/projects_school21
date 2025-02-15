#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Error! You need to pass one parameter"
    echo "Use: $0 <string>"
    exit 1
fi

if [[ $1 =~ ^-?[0-9]+(\.[0-9]+)?(\/[0-9]+)?$ ]]; then
    echo "Error! Invalid argument or count of arguments"
    echo "Use: $0 <string>"
else
    echo $1
fi
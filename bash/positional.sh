#!/bin/bash

#------------------------------------------------------------------------------
#
# Source code for MIPT course on informatics
# Page with slides: http://cs.mipt.ru/wp/?page_id=7775
# Licensed after GNU GPL v3
#
#------------------------------------------------------------------------------
#
# Command-line arguments in bash
#
# Try:
# $ ./positional.sh -b 10 -f myfolder
#
#------------------------------------------------------------------------------

unset border
unset folder

while getopts b:f: flag
do
  case "${flag}" in
    b) border=${OPTARG};;    
    f) folder=${OPTARG};;
  esac
done

echo "folder is $folder"
echo "border is $border"

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
# $ ./third.sh -b 10 -f myfolder
#
#------------------------------------------------------------------------------

echo "param 0 is: $0"
echo "param 1 is: $1"
echo "param 2 is: $2"
echo "param 3 is: $3"
echo "param 4 is: $4"

while getopts b:f: flag
do
  case "${flag}" in
    b) border=${OPTARG};;    
    f) folder=${OPTARG};;
  esac
done

echo "folder is $folder"
echo "border is $border"

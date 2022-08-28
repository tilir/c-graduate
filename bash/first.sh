#------------------------------------------------------------------------------
#
# Source code for MIPT course on informatics
# Page with slides: http://cs.mipt.ru/wp/?page_id=7775
# Licensed after GNU GPL v3
#
#------------------------------------------------------------------------------
#
# script to show how env variables working
#
# Try:
#
# $ folder=myfolder
# $ border=10
# $ source first.sh
#
# $ env folder=myfolder border=10 first.sh
#
# $ export folder=myfolder
# $ export border=10
# $ bash first.sh
#
#------------------------------------------------------------------------------

echo "folder is $folder"
echo "border is $border"

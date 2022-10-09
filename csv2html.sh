#!/bin/bash

#first arg is output csv file from C program, 2nd arg is the filename for the output html

#number of arguments should be 2
if [[ $# != 2 ]]
then
	echo "Usage csv2html.sh <inputfile> <opfile>"
	exit 1
fi

inputcsv=$1
output=$2
#convert the csv file input an html using sed
echo "<TABLE>" > $output
sed -e 's/^/<TR><TD>/' -e 's/$/<\/TD><\/TR>/' -e 's/,/<\/TD><TD>/g' < $inputcsv >> $output
echo "</TABLE>" >> $output




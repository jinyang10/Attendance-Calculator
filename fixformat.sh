#!/bin/bash

#number of arguments should be 2
if [[ $# != 2 ]]
then
	echo "Usage fixformat.sh <dirname> <opfile>"
	exit 1
fi

#first argument should be name of an existing directory

dirname=$1
if [[ ! -d $dirname ]]
then
	echo "Error $dirname is not a valid directory"
fi

labletter=""
opfile=$2
echo -e "User Email,Name (Original Name),Lab,Total Duration (Minutes)" > $opfile 

#or each .csv file that Find finds
for csvfile in $(find $dirname -iname 'lab-[a-Z].csv')
do
	labletter=$(basename $csvfile) 
	labletter=$(echo $labletter | cut -c5)
	labletter=$(echo $labletter | tr [:lower:] [:upper:])

	awk -v lablet=$labletter ' BEGIN { FS="," }
	/mcgill/ {

	{ if (NF == 4)
		{ name=$1; email=$2; totalDur=$3; OFS=","; print email,name,lablet,totalDur }
	else
		{ name=$1; email=$2; totalDur=$5; OFS=","; print email,name,lablet,totalDur } }
	
	}' < $csvfile
done >> $opfile   




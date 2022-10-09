# Attendance-Calculator

fixformat.sh:  
  usage example: ./fixformat.sh \<dirname\> \<opfile\>  
  Finds all csv files under a given directory \<dirname\> (recursively) with the naming convention:   
  lab-[a-Z].csv (case insensitive), reformats and consolidates the output into \<opfile\>
  
labapp.c, zoomrecs.c, zoomrecs.h:
  labapp.c contains the main of the program  
  invoke the makefile to build executable  
  usage example: ./labapp /data/labdata.csv /data/attendance.csv  
  1st arg: reformatted + consolidated file obtained from fixformat.sh  
  2nd arg: output filename for the program to write output to  
  Computes the attendance associated for each student, for each lab from /data/labdata.csv obtained from fixformat.sh  
  Writes the output (formatted) to /data/attendance.csv in this case
  
csv2html.sh:  
  usage example: ./csv2html.sh /data/attendence.csv /data/attendance.html  
  1st arg: input attendance csv file to be converted (obtained from executing labapp)  
  2nd arg: desired name of the html file  
  Converts the attendance.csv file into an html file to be viewed on a browser
  
  
  
  
  
  

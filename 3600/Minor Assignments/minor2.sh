#!/bin/bash

#Samuel Njogo
#Minor Assignment 2
#Section 002

trap 'killScript' 2

#Signal handler to trap SIGINT
function killScript ()
{
    echo "  (SIGINT) received"

	while true; 
	do
    	read -r -p "Terminate Program? (Y/N): " answer
	    case $answer in
	        y|Y)
				printf "Terminating program\n\n"
				exit;;

	        n|N)
	        	printf "Continuing Execution\n\n"  
				break;;

	        * ) 
				echo "Please answer Y or N.";;
	    esac
	done
}


#Current date
now=$(date +"%a %b %d %Y %r %Z")

#Checks for number of command line arguments
if [ $# != 0 ]
then
	while true
	do
		#Holds total number of processes in the server
		numOfProcesses=0 

		echo $now

		#Formatting Output
		printf "User ID\t\t\t\tCount\n"

		#Loop iterates through each euid passed as a command line argument
		for euid in $@;
		do
			i=0
			#Displays euid and number of processes per user
			echo $euid$'\t\t\t\t'$( ps -u $euid --no-headers |echo $( wc -l ) )

			#Sum of all processes for these users
			i=$( ps -u $euid --no-headers | wc -l )
			numOfProcesses=$((numOfProcesses + i))

		done

		printf "%d USERS, TOTAL PROCESSES     %d\n\n" $# $numOfProcesses
		sleep 5
	done	
else
	while true
	do
		#Output of who cmd is stored in file. Contents truncated to leave only euids behind
		who > users
		cut -d ' ' -f 1 users > euids
		echo $now

		#Formatting Output
		printf "User ID\t\t\t\tCount\n"

		#Read euids from file and displays euid and number of processes per user
		while read -r euid
		do
			echo $euid$'\t\t\t\t'$( ps -u $euid --no-headers |echo $( wc -l ) )
		done < euids

		#Total number of users
		numOfUsers=$( wc -l < euids )

		#Total number of processes
		numOfProcesses=$( ps -eaho user | wc -l)

		printf "%d USERS, TOTAL PROCESSES    %d\n\n" $numOfUsers $numOfProcesses
		sleep 5
	done
fi


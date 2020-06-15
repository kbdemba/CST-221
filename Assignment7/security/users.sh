#!/bin/bash

fileName=$1
groupName=$2
action=$3
arguments=$#

# check the number of arguments
if ! [[ $arguments -eq 3 ]]; then
	echo fail: You should have 3 arguments
	echo Exiting program ...
	exit 1
fi


if [[ $action == '-a' ]]; then
	echo adding users
	while IFS= read -r line
	do
		IFS=' '
		read -a strarr <<< "$line"
		
		if grep -q $groupName /etc/group; then
			echo "group already exists"
		  exit 2
		else
			groupadd $groupName
			echo "Adding $groupName to group"
		fi

		useradd ${strarr[0]}
		echo "user ${strarr[0]} added successfully!"

		echo ${strarr[1]} | passwd --stdin ${strarr[0]}
		echo "Password for user ${strarr[0]} changed successfully"

		# usermod -aG ${strarr[0] $groupName
		echo "Add user ${strarr[0]} to group $groupName"

	done < $fileName
elif [[ $action == '-a' ]]; then
	echo removing users
	while IFS= read -r line
	do
		IFS=' '
		read -a strarr <<< "$line"
		if grep -q $groupName /etc/group; then
			echo "group found"
		else	
			echo "group $groupName was not found"
		  echo "Exiting ...."
			exit 3
		fi
		userdel -r ${strarr[0]}
		echo "user ${strarr[0]} deleted successfully!"

	done < $fileName
else
	echo provide a correct argument
fi


#!/bin/bash

#variable to check if it password is acceptable 
isPass=true
password=$1

# check if password is 8 characters long
if [[ ${#password} -lt 8 ]]; then
	echo Password Must be atleast 8 characters long
	isPass=false
fi

# check if password contains a number
if ! [[ $password =~ [0-9] ]]; then
   echo Pasword must include a number
	 isPass=false
fi

# check if password contains a non-alphabetic characters
if ! [[ "$password" =~ [^a-zA-Z0-9] ]]; then
	echo Password must include at least one non-alphabetic characters
	 isPass=false
fi

# check if the password passed or failed
if [[ "$isPass" = "true" ]]; then
	echo Passed: Your password is accepted
else
	echo Failed: Your password was not accepted, Try agiain
fi 
#!/bin/bash

: '
   GROUP_17
   270201028 Fatih YELBOĞA
   270201068 Berkay BAYRAK
'

: 'the variable used to print number of queue in the file modification_details.txt'
counter=1

: 'the variable used to return whether the file(s) is found or not'
found=0

: 'find all files of the directory by keyword, copy them to Found directory and return 1 if it found'
find_all_files_of_directory_by_keyword(){

    for f_or_dir in "$1"/*
    do
        if [ -f $f_or_dir ] && grep -q "$2" "$f_or_dir"
        then
            if [ ! -d "$(pwd)/Found" ]
            then
                mkdir "$(pwd)/Found"
            fi

            touch $(pwd)/Found/found_${f_or_dir##*/}
            cat $f_or_dir > $(pwd)/Found/found_${f_or_dir##*/}
            found=1  
            display_modifications_of_original_files $f_or_dir
        elif [ -d $f_or_dir ]
        then
            find_all_files_of_directory_by_keyword $f_or_dir $keyword
        fi
    done

    return $found
}

: 'save the modifications to modification_details.txt and print the console'
display_modifications_of_original_files(){

    if [ ! -f "$(pwd)/Found/modification_details.txt" ]
    then
        touch "$(pwd)/Found/modification_details.txt" 
    fi

    modified_by=$(stat -c %U "$1")
    modification_date=$(stat -c "%.19y" "$1")
    month=$(date -d "$modification_date" +'%B')
    day=$(date -d "$modification_date" +'%d')
    year=$(date -d "$modification_date" +'%Y')
    hour=$(date -d "$modification_date" +'%H')
    minute=$(date -d "$modification_date" +'%M')

    echo "File $counter: found_${1##*/} was modified by $modified_by on $month $day, $year at $hour.$minute." >> "$(pwd)/Found/modification_details.txt"
    counter=$((counter+1))
}

: 'here is main'
exist_dir=1
while [ $exist_dir -eq 1 ]
do
    read -p "Enter the name of the directory: " dir;
    if [ ! -d $dir ]
    then
        echo "$dir not exist!"
    else
        break
    fi  
done
read -p "Enter the keyword: " keyword;

find_all_files_of_directory_by_keyword $dir $keyword
found_file=$?
if [ $found_file -eq 1 ] 
then
    echo "Files were copied to Found directory!"
    for f in "$(pwd)/Found"/*
    do  
        echo "${f##*/}"
    done
else
    echo "Keyword not found in files!"    
fi

if [ -f "$(pwd)/Found/modification_details.txt" ]
then
    cat "$(pwd)/Found/modification_details.txt"
fi
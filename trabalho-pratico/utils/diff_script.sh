#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Error: script requires two arguments (the paths to the two folders to compare)"
    exit 1
fi

folder1=$1
folder2=$2

if [ ! -d "$folder1" ] || [ ! -d "$folder2" ]; then
    echo "Error: one or both of the provided paths is not a directory"
    exit 1
fi

files1=$(find "$folder1" -type f)
files2=$(find "$folder2" -type f)

for file1 in $files1; do
    file2="${file1/$folder1/$folder2}"

    if [ ! -f "$file2" ]; then
        echo "Error: corresponding file $file2 does not exist in second folder"
        continue
    fi

    diff_output=$(diff "$file1" "$file2")

    if [ ! -z "$diff_output" ]; then
        echo "File $file1 is different in the two folders:"
        echo "$diff_output"
    fi
done

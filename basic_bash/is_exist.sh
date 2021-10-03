#!/bin/bash
filename="Linux"
if test -f $filename ; then
    echo "course"
else
    echo "very easy"
    echo "course is easy" > $filename
fi
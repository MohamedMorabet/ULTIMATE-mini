#!/bin/bash

# Check if a filename is provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <pid_file>"
    exit 1
fi

PID_FILE="$1"

# Check if the file exists
if [ ! -f "$PID_FILE" ]; then
    echo "Error: File '$PID_FILE' not found!"
    exit 1
fi

# Read each PID line by line and kill the process
while read -r PID; do
    # Validate if it's a number
    if [[ "$PID" =~ ^[0-9]+$ ]]; then
        kill -KILL "$PID" && echo "Killed PID: $PID" || echo "Failed to kill PID: $PID"
    else
        echo "Skipping invalid PID: $PID"
    fi
done < "$PID_FILE"

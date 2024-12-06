#!/bin/bash
#
# Helper function to exit script on failed command
exit_on_fail() {
    if [[ $? -ne 0 ]]; then
        if [[ ! -z $1 ]]; then
            echo -e "\n$1"
        fi
        echo_subsection "Build failed!"
        exit 1
    fi
}

if ! command -v xclip &> /dev/null; then
    echo "Error: xclip is not installed. Install it using 'sudo apt install xclip' or equivalent."
    exit 1
fi

# Check if a number argument is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <number between 1 and 25>"
    exit 1
fi

# Get the number from the argument
X=$1

# Check if the input is a valid number between 1 and 25
if [[ "$X" =~ ^[1-9]$|^1[0-9]$|^2[0-5]$ ]]; then
    
    # Go to the AOC folder
    cd "$AOC_FOLDER" || { echo "Folder not found"; exit 1; }

    # Create the directory for the day if it doesn't exist
    DAY_FOLDER="day_$X"
    
    if [ ! -d "$DAY_FOLDER" ]; then
        # If the day folder does not exist, create it and initialize the .cpp file
        echo "Folder day_$X doesn't exist. Creating folder and initializing the .cpp file..."
        mkdir "$DAY_FOLDER"
        cp .template "$DAY_FOLDER/$DAY_FOLDER.cpp"
        sed -i "4s|.*|  std::string input = aoc::getInput(\"day_$X/input.txt\");|" "$DAY_FOLDER/$DAY_FOLDER.cpp"
        xclip -selection clipboard -o > "$DAY_FOLDER/input.txt"
        echo "Folder and file created. You can now add your code to $DAY_FOLDER/$DAY_FOLDER.cpp."
    fi

    # If the day folder exists, compile and run the code
    echo "Running day $X..."
    g++ -o ex -Wall -std=c++20 common/common.cpp "$DAY_FOLDER/$DAY_FOLDER.cpp" 
    exit_on_fail "Error while compiling..."
    echo "Correctly compiled!"
    time ./ex

else
    echo "Invalid input. Please enter a number between 1 and 25."
    exit 1
fi


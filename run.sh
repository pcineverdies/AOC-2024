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

Y=$1
X=$2

years=("2022" "2023" "2024")

found=false
for year in "${years[@]}"; do
  if [[ "$year" == "$1" ]]; then
    found=true
    break
  fi
done


if [[ "$found" == false ]]; then
    echo "Year is not valid"
    exit 1
fi

# Check if the input is a valid number between 1 and 25
if [[ "$X" =~ ^[1-9]$|^1[0-9]$|^2[0-5]$ ]]; then
    
    # Go to the AOC folder
    cd "$AOC_FOLDER" || { echo "Folder not found"; exit 1; }

    
    if [ ! -e "$Y/day_$X.cpp" ]; then
        # If the day folder does not exist, create it and initialize the .cpp file
        echo "day_$X doesn't exist. Creating folder and initializing the .cpp file..."
        cp .template "$Y/day_$X.cpp"
        sed -i "4s|.*|  std::string input = aoc::getInput(\"$Y/day_$X.txt\");|" "$Y/day_$X.cpp"
        xclip -selection clipboard -o > "$Y/day_$X.txt"
        echo "Folder and file created. You can now add your code to $DAY_FOLDER/$DAY_FOLDER.cpp."
        sleep 1
        nvim -p "$Y/day_$X.cpp" "$Y/day_$X.txt" 
      else
      # If the day folder exists, compile and run the code
      echo "Running day $X..."

      g++ -o ex -Wall \
        -march=native -funroll-loops \
        -O3 -std=c++20 common/common.cpp \
        "$Y/day_$X.cpp" 

      exit_on_fail "Error while compiling..."
      echo "Correctly compiled!"
      time ./ex
    fi

else
    echo "Invalid input. Please enter a number between 1 and 25."
    exit 1
fi


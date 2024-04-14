if [[ -d bin ]]; then
  echo "bin directory exists."
else
    mkdir bin
    echo "created bin directory"
fi

if [[ -d imgs/results ]]; then
  echo "imgs/results directory exists."
else
    mkdir imgs/results
    echo "created results directory"
fi

g++ -Iheaders demo.cpp ./src/*.cpp -o ./bin/main
chmod +x ./bin/main && ./bin/main

echo "Demo results are stored in ./imgs/results"
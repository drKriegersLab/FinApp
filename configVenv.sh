#!/bin/bash

LBLUE='\033[1;36m' # coloring starts
NC='\033[0m' # end of coloring


echo -e "${LBLUE}create virtual environment${NC}"
python3 -m venv ./venv
echo -e "${LBLUE}install PyQt5 with virtual environment's pip3${NC}"
./venv/bin/pip3 install PyQt5
echo -e "${LBLUE}install PyQtChart with virtual environment's pip3${NC}"
./venv/bin/pip3 install PyQtChart
echo -e "${LBLUE}install numpy with virtual environment's pip3${NC}"
./venv/bin/pip3 install numpy
echo -e "${LBLUE}install scipy with virtual environment's pip3${NC}"
./venv/bin/pip3 install scipy
echo -e "${LBLUE}install matplotlib with virtual environment's pip3${NC}"
./venv/bin/pip3 install matplotlib


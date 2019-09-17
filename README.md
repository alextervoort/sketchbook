# Sketchbook

On both windows and linux create a portable directory, the GUI will automatically create a sketchbook directory in it to keep all sketches.


The portable directory will also contain adidional packages added through the board manager that normally reside in ~/.arduino15 under linux.

Steps to connect a new Arduino IDE sketchbook directory to github

start with empty portable, then clone BEFORE starting the ide
from portable directory;
  git clone https://github.com/alextervoort/sketchbook.git
  
start IDE and install libraries and boards, these will be installed in portable but are in gitignore

IDE will save to portable sketchbook by default

If first git project on this machine; 
    git config --global user.email "alex.tervoort@gmail.com"
    git config --global user.name "alextervoort"
    git config credential.helper store
Add a project;
    git add NeoPixel_Star
    git commit -m "add first sketch "
    git push

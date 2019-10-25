# Sketchbook
On both windows and linux create a portable directory, the GUI will automatically create a sketchbook directory in it to keep all sketches.
The portable directory will also contain adidional packages added through the board manager that normally reside in ~/.arduino15 under linux.
## Steps to connect a new Arduino IDE sketchbook directory to github

Start with empty portable, then clone the repo **BEFORE** starting the IDE.
From the portable directory clone the repo;
```
  git clone https://github.com/alextervoort/sketchbook.git
```  
start IDE and install libraries and boards, these will be installed in portable but are in gitignore

IDE will save to portable sketchbook by default

### If this is the first git repo on this machine
Setup user account and credential helper to avoid having to login on every push.
```
    git config --global user.email "alex.tervoort@mail.com"
    git config --global user.name "alextervoort"
    git config credential.helper store
```
### Add an existing project
Copy the directory containing the project files to the sketchbook, then;
```  
    git add NeoPixel_Star
    git commit -m "add first sketch "
    git push
```

#!/usr/bin/env bash

sudo apt-get -y install build-essential cmake freeglut3 freeglut3-dev libglew1.5 libglew1.5-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx libgl1-mesa-dev libglfw3-dev libxmu-dev libxi-dev subversion mercurial libarchive-dev python3-dev libois-dev libsdl2-dev libsfml-dev yasm scons libfontconfig1-dev libfreetype6-dev libpng-dev libcairo2-dev libtiff5-dev libxaw7-dev libfreeimage-dev qt5-default libglm-dev libglfw3-dev

cd drivers
cmake .
make GoogleTest
make OgreDeps
make Ogre
make Boost
make BoostProcess
make sfeMovie
make GMTL
make CEGUI
cd ..

# Create links to CEGUI
#ln -s /usr/lib/libCEGUIBase-0.so.2.3.0 ./install/lib/libCEGUIBase-0.so
#ln -s /usr/lib/libCEGUIOpenGLRenderer-0.so.2.3.0 ./install/lib/libCEGUIOpenGLRenderer-0.so

# We don't require anaconda right now, but probably will at some point. This
# downlaods and installs the correct version
#CONTREPO=https://repo.continuum.io/archive/
#ANACONDAURL=$(wget -q -O - $CONTREPO index.html | grep "Anaconda3-" | grep "Linux" | grep "86_64" | head -n 1 | cut -d \" -f 2)
#wget -O ~/Downloads/anaconda.sh $CONTREPO$ANACONDAURL
#bash ~/Downloads/anaconda.sh -b



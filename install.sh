#!/bin/sh
#dependencies =sudo apt-get install         \
#    libfreetype6-dev    \ #    libx11-dev          \ #    libxrandr-dev       \ #    libgl1-mesa-dev     \ #    libudev-dev         \ #    libopenal-dev       \ #    libflac-dev         \ #    libogg-dev          \ #    libvorbis-dev -y
depend="build-essentials ,libfreetype6-dev, libx11-dev, libxrandr-dev, libgl1-mesa-dev, libudev-dev, libopenal-dev, libflac-dev, libogg-dev, libvorbis-dev" 
wget https://codeload.github.com/texus/TGUI/zip/v0.8.5 -O TGUI-0.8.5.zip
wget https://www.sfml-dev.org/files/SFML-2.5.1-sources.zip
while true; do
    read -p "Do you wish to install ${depend} , requires sudo?(y/n) " yn
    case $yn in
        [Yy]* ) sudo apt-get install         \
                    build-essential    \
                    libfreetype6-dev    \
                    libx11-dev          \
                    libxrandr-dev       \
                    libgl1-mesa-dev     \
                    libudev-dev         \
                    libopenal-dev       \
                    libflac-dev         \
                    libogg-dev          \
                    libvorbis-dev -y; break;;
        [Nn]* ) break;;
        * ) echo "Please answer yes or no.";;
    esac
done

#version=$(lsb_release -r | grep -o "1.*")
version=$(lsb_release -r)
if  [ "$?" -eq 127 ]; then
    echo "OS not supported, linux only for now =( "
    exit;
fi
version=$(echo $version | grep -o "1.*" )
echo "version is ${version}"

if [ "$version" = "16.04" ]; then
    echo "yes ${version}"  
    while true; do
        read -p "Do you wish to install Boost system, timer, dev and cmake requires sudo?(y/n) " yn
        case $yn in
            [Yy]* ) sudo apt-get install         \
                        libboost-dev    \
                        cmake-qt-gui    \
                        libboost-filesystem1.58.0          \
                        libboost-timer1.58.0 -y; break;;          \
            [Nn]* ) break;;
            * ) echo "Please answer yes or no.";;
        esac
    done
elif [ "$version" = "18.04" ]; then
    while true; do
        read -p "Do you wish to install Boost system, timer and dev , requires sudo?(y/n) " yn
        case $yn in
            [Yy]* ) sudo apt-get install         \
                        libboost-filesystem-dev          \
                        cmake-gui          \
                        libboost-timer-dev -y; break;;          \
            [Nn]* ) break;;
            * ) echo "Please answer yes or no.";;
        esac
    done
else
    echo "OS not supported, Ubuntu 16.04 and 18.04 only for now =("
fi

current_dir=$(pwd)
cores=$(( $(lscpu | awk '/^Socket\(s\)/{ print $2 }') * $(lscpu | awk '/^Core\(s\) per socket/{ print $4 }') ))

unzip SFML-2.5.1-sources.zip

cd SFML-2.5.1

mkdir build && cd build

cmake ../ -DCMAKE_INSTALL_PREFIX:PATH=${current_dir}/SFML-2.5.1-build && make -j${cores}
make install    

cd ${current_dir}
unzip TGUI-0.8.5.zip 

cd TGUI-0.8.5
mkdir build && cd build

cmake ../ -DCMAKE_INSTALL_PREFIX:PATH=${current_dir}/TGUI-0.8.5-build -DSFML_DIR:PATH=${current_dir}/SFML-2.5.1-build/lib/cmake/SFML && make -j${cores}
make install    



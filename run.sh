#!/bin/bash

sudo docker build ./ -t data-mining-toolbox

xhost +local:root

sudo docker run -it --net=host --env="DISPLAY" --env="QT_X11_NO_MITSHM=1" --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" data-mining-toolbox 

xhost -local:root

FROM ubuntu
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get -y update && \
    apt-get -y install g++ && \
    apt-get -y install make && \
    apt-get -y install cmake && \
    apt-get -y install libsfml-dev && \
    apt-get -y install libglu1-mesa-dev freeglut3-dev mesa-common-dev && \
    apt-get -y install mesa-utils xterm x11-apps xauth && \
    apt-get -y install build-essential && \
    apt-get -y install qt5-default && \
    apt-get -y install libqt5charts5-dev && \
    apt-get -y install libopenblas-dev && \
    apt-get -y install liblapack-dev && \
    apt-get -y install libarmadillo-dev && \
    apt-get -y install libboost-math-dev libboost-test-dev libboost-serialization-dev \
    binutils-dev python3-pandas python3-numpy cython3 python3-setuptools && \        
    apt-get -y install libmlpack-dev
    
RUN mkdir DMTBuild
WORKDIR DMTBuild

COPY ./*.cpp ./
COPY ./*.hpp ./
COPY ./*.ui ./
COPY ./CMakeLists.txt ./
COPY ./Resources.qrc ./
COPY ./Resources ./Resources
COPY ./iris.csv ./


RUN ls

RUN mkdir build
WORKDIR build
RUN cmake ..
RUN make

CMD ["./DataMiningToolbox"]

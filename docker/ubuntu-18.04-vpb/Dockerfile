FROM ubuntu:18.04

RUN apt update
RUN apt install -y git build-essential cmake libopenscenegraph100v5 libopenscenegraph-dev libgdal20 libgdal-dev
RUN mkdir /src
RUN git clone https://github.com/openscenegraph/VirtualPlanetBuilder.git /src
RUN mkdir /src/build
RUN cd /src/build; cmake .. -DCMAKE_BUILD_TYPE=Release
RUN cd /src/build; make -j 4
RUN cd /src/build; make install
RUN rm -r /src
RUN apt purge -y git build-essential cmake libopenscenegraph-dev libgdal-dev
RUN apt autoremove -y
RUN apt clean

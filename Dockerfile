FROM ubuntu:18.04

# Install dependencies
RUN apt-get update -y && apt-get install -y software-properties-common
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test && apt-get update -y
RUN apt-get install -y libgtest-dev cmake valgrind gcc-8 g++-8 libasan5 google-mock git libssl-dev
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 800 --slave /usr/bin/g++ g++ /usr/bin/g++-8

# Compile GTest
WORKDIR /usr/src/gtest
RUN cmake CMakeLists.txt && make -j$(nproc)
RUN cp *.a /usr/lib
WORKDIR /usr/src/gmock
RUN cmake CMakeLists.txt && make -j$(nproc)
RUN cp *.a /usr/lib

# Compile libwebsockets
RUN git clone https://github.com/warmcat/libwebsockets.git
WORKDIR libwebsockets
RUN cmake . && make -j$(nproc) && make install

RUN ldconfig

RUN mkdir /src
COPY . /src/
RUN rm -rf /src/build
RUN mkdir -p /src/build

WORKDIR /src/build

RUN cmake -DCMAKE_BUILD_TYPE=Release .. && make -j$(nproc)

CMD ["Tests/Tests", "--gtest_repeat=10", "--gtest_shuffle", "--gtest_color=yes"]
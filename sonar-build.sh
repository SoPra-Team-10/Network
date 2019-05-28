#!/bin/bash
cd /src
echo "REMOVE PREVIOUS BUILD"
rm -rf sonar-build

echo "BUILDING"
mkdir sonar-build
cd sonar-build

cmake ..
make

RC=$?

if [ $RC -ne 0 ]; then
  echo "BUILD FAILURE"
else
  echo "BUILD SUCCESS"
fi

cd ..
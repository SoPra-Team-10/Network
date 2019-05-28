#!/bin/bash

echo "Current Branch: $TRAVIS_BRANCH"

if [ "$TRAVIS_BRANCH" == "master" ] || [ "$TRAVIS_BRANCH" == "develop" ] || [ "$TRAVIS_BRANCH" == "sonarcloud" ]; then

    echo "INSTALLING SOME TOOLS"
    apt-get install -y  wget unzip bash

    echo "INSTALLING SONAR CUBE SANNER & WRAPPER"

    mkdir /sonar
    cd /sonar
    wget https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-3.3.0.1492-linux.zip
    wget https://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip

    unzip sonar-scanner-cli-3.3.0.1492-linux.zip
    unzip build-wrapper-linux-x86.zip

    cd sonar-scanner-3.3.0.1492-linux/bin
    chmod +x sonar-scanner
    cd ../..

    cd build-wrapper-linux-x86
    chmod +x build-wrapper-linux-x86-64
    cd ..

    cd /src

    echo "RUNNING SONARCLOUD BUILD WRAPPER"

    chmod +x sonar-build.sh
    /sonar/build-wrapper-linux-x86/build-wrapper-linux-x86-64 --out-dir bw-outputs ./sonar-build.sh

    echo "RUNNING SONARCLOUD SCANNER"
    /sonar/sonar-scanner-3.3.0.1492-linux/bin/sonar-scanner \
    -Dsonar.login=$SONAR_TOKEN -Dsonar.branch.name=$TRAVIS_BRANCH \
    -X

    rm -rf sonar-build
    rm -rf ./bw-outputs

else
	echo "No Code Analysis for $TRAVIS_BRANCH Branch."
	exit 0
fi

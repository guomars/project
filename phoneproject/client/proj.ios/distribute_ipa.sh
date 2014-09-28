#!/bin/sh

rm -rf "${HOME}/Desktop/mokachuanshuo.ipa"

cd ../

svn up

cd proj.ios

xcodebuild -configuration Release clean

xcodebuild -configuration Release

xcrun -sdk iphoneos PackageApplication -v ./build/Release-iphoneos/mokachuanshuo.app -o ${HOME}/Desktop/mokachuanshuo.ipa






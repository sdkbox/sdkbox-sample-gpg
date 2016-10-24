# Samples of Google Play Game Services with Cocos2d-x 

##Getting Started

###Setup
~~~bash
# run setup script
./setup
~~~

After setup your directory will looks like this
~~~
+-- sdkbox-cocos2d-x-binary
+-- sdkbox-sample-gpg
| +-- cpp
| +-- lua
| \-- js
~~~

* cpp: contains cocos2d-x c++ project sample
* js: contains cocos2d-x js project sample
* lua: contains cocos2d-x lua project sample

###Run

Under each sample project there are project files for different platform

* proj.ios_mac: project file for ios/mac platform
* proj.android: project file to android platform

Compile&Run with Cocos command line tool: 
* cocos run -p android 
* cocos run -p ios 

###Testing
You need a tester account in order to test google play functionalities
Make sure you opt-in as an alpha tester [here](https://play.google.com/apps/testing/com.sdkbox.gpg) before testing with your own google account.


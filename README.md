# Samples of Google Play Services with Cocos2d-x

##Getting Started

###Setup
~~~bash
# run setup script
./setup
~~~

After setup your directory will looks like this
~~~
+-- sdkbox-cocos2d-x-binary
+-- sdkbox-sample-googlplay
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

Compile with Cocos command line tool:
* cocos compile -p android
* cocos compile -p ios

You can also run the sample with commandline
~~~bash

# run sample with specified language and platform
# eg: cpp and ios
../sdkbox-cocos2d-x-binary/run_sample.sh googleplay cpp ios
## or
cd cpp && cocos run -p ios

# javascript and android
../sdkbox-cocos2d-x-binary/run_sample.sh googleplay js android
## or
cd js && cocos run -p android
~~~

### NOTE

1.  Get the `GPG` libs by:

    ```bash
    sdkbox update
    ```

2.  You MUST test app with **release** mode:

    ```bash
    cocos run -p android -m release
    ```


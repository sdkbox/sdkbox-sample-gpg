#!/usr/bin/env python
#coding:utf-8

import os
import shutil
import hashlib
import urllib2
import zipfile

MD5="3e139c7179338050cc8d545f60d0d042"
DOWNLOAD_URL='https://developers.google.com/games/services/downloads/gpg-cpp-sdk.v2.1.zip'
ZIP_FILENAME="gpg-cpp-sdk.v2.1.zip"
TMP_DIR = './tmp/'

def curl(url, file_name, md5 = None, callback=None):
    chunk_size = 1024
    data = ''

    try:
        response = urllib2.urlopen(url)
        size = 0
        total_size = response.headers['content-length']
        while True:
            chunk = response.read(chunk_size)
            if not chunk:
                break
            size += len(chunk)
            data += chunk
            if None != callback:
                callback(size, total_size)
    except Exception,e:
        print str(e)

    try:
        if len(data) > 0:
            f = open(file_name, 'wb')
            f.write(data)
            f.close()
    except Exception as e:
        print('save file failed: {0}'.format(e))

def md5(data):
    hash_md5 = hashlib.md5(data)
    return hash_md5.hexdigest()

def md5File(file_path):
    with open(file_path, mode='rb') as file: # b is important -> binary
        fileContent = file.read()
        return md5(fileContent)

def md5FileCheck(file_path, md5):
    md5_file = md5File(file_path)
    if md5_file == md5:
        return True
    else:
        return False

def unzip(zfile, dest_folder='./'):
    zip_ref = zipfile.ZipFile(zfile, 'r')
    zip_ref.extractall(dest_folder)
    zip_ref.close()

def rmFile(file):
    if not os.path.exists(file):
        return

    if os.path.isdir(file):
        shutil.rmtree(file)
    elif os.path.isfile(file):
        os.remove(file)
    else:
        print('rmFile faile, ({0})'.format(file))

def copyFile(src, dest):
    if os.path.isfile(src):
        shutil.copy2(src, dest)
    else:
        print('copyFile Fail, ({0})'.format(src))

def copyFolder(src, dst):

    if not os.path.exists(dst):
        os.makedirs(dst)

    for item in os.listdir(src):
        s = os.path.join(src, item)
        d = os.path.join(dst, item)
        if os.path.isfile(s):
            copyFile(s, d)
        elif os.path.isdir(s):
            copyFolder(s, d)
        else:
            print('copyFolder fail, ({0})'.format(s))

def main():

    # download if
    if not os.path.exists(ZIP_FILENAME):
        print('Download denpency file...')
        curl(DOWNLOAD_URL, ZIP_FILENAME, MD5)
        print('Download denpency file Finish')

    # check file valid
    if not md5FileCheck(ZIP_FILENAME, MD5):
        print('{0} is not valid'.format(ZIP_FILENAME))
        return

    # unzip file
    rmFile(TMP_DIR)
    os.makedirs(TMP_DIR)
    unzip(ZIP_FILENAME, TMP_DIR)

    # copy to cpp
    ios_src = os.path.join(TMP_DIR, 'gpg-cpp-sdk/ios/gpg.framework')
    android_src = os.path.join(TMP_DIR, 'gpg-cpp-sdk/android')
    ios_dst = './cpp/proj.ios_mac/gpg.framework'
    android_dst = './cpp/proj.android/jni/gpg'
    rmFile(ios_dst)
    rmFile(android_dst)
    copyFolder(ios_src, ios_dst)
    copyFolder(android_src, android_dst)

    # copy to lua
    ios_src = os.path.join(TMP_DIR, 'gpg-cpp-sdk/ios/gpg.framework')
    android_src = os.path.join(TMP_DIR, 'gpg-cpp-sdk/android')
    ios_dst = './lua/frameworks/runtime-src/proj.ios_mac/gpg.framework'
    android_dst = './lua/frameworks/runtime-src/proj.android/jni/gpg'
    rmFile(ios_dst)
    rmFile(android_dst)
    copyFolder(ios_src, ios_dst)
    copyFolder(android_src, android_dst)

    # copy to js
    ios_src = os.path.join(TMP_DIR, 'gpg-cpp-sdk/ios/gpg.framework')
    android_src = os.path.join(TMP_DIR, 'gpg-cpp-sdk/android')
    ios_dst = './js/frameworks/runtime-src/proj.ios_mac/gpg.framework'
    android_dst = './js/frameworks/runtime-src/proj.android/jni/gpg'
    rmFile(ios_dst)
    rmFile(android_dst)
    copyFolder(ios_src, ios_dst)
    copyFolder(android_src, android_dst)

if __name__ == '__main__':
    main()

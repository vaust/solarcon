#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import datetime
import time
import os

SVN     = '$Revision$'
SVN_URL = '$HeadURL: https://solarcon.googlecode.com/svn/trunk/HeizungRCA_NG/writeversion.py $'
# SVN_REV = SVN.split(':')[1].split('$')[0]

with open( './svn.txt', 'r' ) as file:
    revtxt = file.readline()
SVN_REV = revtxt.split('M')[0]
VERSION = '0.9.2'   #  +'SVN: '+SVN_REV
DEVPATH = SVN_URL.split('URL: ')[1].split('/write')[0]
# DEVPATH = SVN_URL.split('/write')[0]
now = datetime.datetime.now()
now = datetime.datetime( now.year, now.month, now.day, now.hour, now.minute, now.second )
jetzt = now.isoformat(' ')

fd = open( './inc/version.h', 'w' )
fd.write( '#ifndef _VERSION_H_\n' )
fd.write( '#define _VERSION_H_\n\n' )
fd.write( '#define VERSIONSTRING "'+VERSION+'\\n\\tBuild '+jetzt+'\\n"\n' )
fd.write( '#define VERSIONDEVPATH "'+DEVPATH+'\\n"\n' )
fd.write( '\n#endif\n' )
fd.close()

#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import datetime
import time

Filename_Prefix = str(int(time.time()))
VERSION = '0.6.5'
jetzt   = datetime.datetime.now().isoformat(' ')
 
fd = open( './inc/version.h', 'w' )
fd.write( '#ifndef _VERSION_H_\n' )
fd.write( '#define _VERSION_H_\n\n' )
fd.write( '#define VERSIONSTRING "'+VERSION+'\\n\\tBuild '+jetzt+'\\n"' )
fd.write( '\n\n#endif\n' )
fd.close()

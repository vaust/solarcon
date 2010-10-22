#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import datetime
import time

VERSION = '0.7.2'
jetzt1  = datetime.datetime.now().isoformat()
jetzt2  = str(int(time.time())-1287688700)

fd = open( './inc/version.h', 'w' )
fd.write( '#ifndef _VERSION_H_\n' )
fd.write( '#define _VERSION_H_\n\n' )
fd.write( '#define VERSIONSTRING "'+VERSION+'\\n\\tBuild '+jetzt2+'\\n\\t'+jetzt1+'\\n"' )
fd.write( '\n\n#endif\n' )
fd.close()

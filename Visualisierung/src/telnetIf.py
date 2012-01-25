'''
Created on 25.01.2012

@author: stegmann
'''

import telnetlib
import time

import signals

class TelnetInterface(telnetlib.Telnet):
    def __init__(self, host, port, timeout):
        telnetlib.Telnet.__init__(self, host, port, timeout)
        self.t_dict = dict()
        self.pu_dict = dict()
        self.mv_dict = dict()
        self.di_dict = dict()
        self.cnt_dict = dict()
        self.av_dict = dict()
        
    def HoleAntwort(self, cmdstr):
        self.write(cmdstr)
        time.sleep(1)
        buffer = self.read_very_eager()
        bufdecode = buffer.decode('utf8')
        lines = bufdecode.splitlines()
        return lines

    def ErmittleMesswerte(self):
        lines = self.HoleAntwort( b"GET T\n" )
        for t_name in signals.TEMP_NAMES:
            self.t_dict[t_name] = 0.0
            for line in lines:
                if (line.startswith(t_name)):
                    self.t_dict[t_name] = float( line.split('=')[1].split('°')[0] )
                
        lines = self.HoleAntwort( b"GET DO\n" )
        for pu_name in signals.PU_NAMES:
            for line in lines:
                if (line.startswith(pu_name)):
                    self.pu_dict[pu_name] = str( line.split('=')[1] )
                    
        for av_name in signals.AV_NAMES:
            for line in lines:
                if (line.startswith(av_name)):
                    self.av_dict[av_name] = str( line.split('=')[1] )

        lines = self.HoleAntwort( b"GET AO\n" )
        for mv_name in signals.MV_NAMES:
            for line in lines:
                if (line.startswith(mv_name)):
                    self.mv_dict[mv_name] = float( line.split('=')[1].split('p')[0] )

        lines = self.HoleAntwort( b"GET DI\n" )
        for di_name in signals.DI_NAMES:
            for line in lines:
                if (line.startswith(di_name)):
                    self.di_dict[di_name] = str( line.split('=')[1] )

        return (self.t_dict, self.pu_dict, self.mv_dict, self.di_dict, self.cnt_dict, self.av_dict)



if __name__ == '__main__':
    interface = TelnetInterface('192.168.2.102', 1969, 10)
    
    interface.ErmittleMesswerte()
    print (interface.t_dict)
    print (interface.av_dict)
    print (interface.cnt_dict)
    print (interface.di_dict)
    print (interface.pu_dict)
    print (interface.mv_dict)
    
    interface.close()
    
    
    
    
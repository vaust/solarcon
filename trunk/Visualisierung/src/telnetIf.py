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
        time.sleep(0.5)
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
            self.pu_dict[pu_name] = ''
            for line in lines:
                if (line.startswith(pu_name)):
                    self.pu_dict[pu_name] = str( line.split('=')[1] ).lstrip()
                    
        for av_name in signals.AV_NAMES:
            self.av_dict[av_name]=''
            for line in lines:
                if (line.startswith(av_name)):
                    self.av_dict[av_name] = str( line.split('=')[1] ).lstrip()

        lines = self.HoleAntwort( b"GET AO\n" )
        for mv_name in signals.MV_NAMES:
            self.mv_dict[mv_name] = 0.0
            for line in lines:
                if (line.startswith(mv_name)):
                    self.mv_dict[mv_name] = float( line.split('=')[1].split('p')[0] )

        lines = self.HoleAntwort( b"GET DI\n" )
        for di_name in signals.DI_NAMES:
            self.di_dict[di_name] = ''
            for line in lines:
                if (line.startswith(di_name)):
                    self.di_dict[di_name] = str( line.split('=')[1] ).lstrip()
        
        self.cnt_dict['WW_WZ_MW'] = 0
        return (self.t_dict, self.pu_dict, self.mv_dict, self.di_dict, self.cnt_dict, self.av_dict)

    def Fb_MvReglerParamSchreiben(self, kp, ki, ap):
        command = "put vfb 00="+str(kp)        
        self.write( command.encode('utf-8') )
        time.sleep(0.5)
        command = "put vfb 01="+str(ki)
        self.write( command.encode('utf-8') )
        time.sleep(0.5)
        command = "put vfb 02="+str(ap)
        self.write( command.encode('utf-8') )
        time.sleep(0.5) 
    
    def Fb_MvReglerParamLesen(self):
        command = "get vfb -1" 
        self.write( command.encode('utf-8') )
        time.sleep(3.0)
        buffer = self.read_very_eager()
        bufdecode = buffer.decode('utf8')
        lines = bufdecode.splitlines()
        ap = kp = ki = 0.0
        for line in lines:
            if (line.startswith('(00)')):
                kp = float(line.split('=')[1])
            if (line.startswith('(01)')):
                ki = float(line.split('=')[1])
            if (line.startswith('(02)')):
                ap = float(line.split('=')[1])
        
        return (kp, ki, ap)


if __name__ == '__main__':
    iface = TelnetInterface('stegmann.homelinux.org', 1969, 10)   
    iface.ErmittleMesswerte()
    print(iface.t_dict)
    print(iface.av_dict)
    print(iface.cnt_dict)
    print(iface.di_dict)
    print(iface.pu_dict)
    print(iface.mv_dict)
    iface.close()
    
    
    
    
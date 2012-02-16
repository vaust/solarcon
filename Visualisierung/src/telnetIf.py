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
        self.t = dict()
        self.pu = dict()
        self.mv = dict()
        self.di = dict()
        self.cnt = dict()
        self.av = dict()
        
    def HoleAntwort(self, cmdstr):
        self.write(cmdstr)
        time.sleep(0.5)
        buffer = self.read_very_eager()
        bufdecode = buffer.decode('utf8')
        lines = bufdecode.splitlines()
        return lines
    
    def beenden(self):
        self.write(b"END\n")
    
    def get_T(self):
        lines = self.HoleAntwort( b"GET T\n" )
        for name in signals.TEMP_NAMES:
            self.t[name] = 0.0
            for line in lines:
                if (line.startswith(name)):
                    self.t[name] = float( line.split('=')[1].split('°')[0] )
        
        return(self.t)
    
    def get_DO(self):
        lines = self.HoleAntwort( b"GET DO\n" )
        for name in signals.PU_NAMES:
            self.pu[name] = ''
            for line in lines:
                if (line.startswith(name)):
                    self.pu[name] = str( line.split('=')[1] ).lstrip()

        for name in signals.AV_NAMES:
            self.av[name]=''
            for line in lines:
                if (line.startswith(name)):
                    self.av[name] = str( line.split('=')[1] ).lstrip()

        return(self.pu, self.av)

    def get_AO(self):     
        lines = self.HoleAntwort( b"GET AO\n" )
        for name in signals.AO_NAMES:
            self.mv[name] = 0.0
            for line in lines:
                if (line.startswith(name)):
                    self.mv[name] = float( line.split('=')[1].split('p')[0] )
        
        return(self.mv)
    
    def get_DI(self):
        lines = self.HoleAntwort( b"GET DI\n" )
        for name in signals.DI_NAMES:
            self.di[name] = ''
            for line in lines:
                if (line.startswith(name)):
                    self.di[name] = str( line.split('=')[1] ).lstrip()
        
        self.cnt['WW_WZ_MW'] = 0
        
        return(self.di, self.cnt)
        
    def ErmittleMesswerte(self):
        self.get_T()
        self.get_AO()
        self.get_DO()
        self.get_DI()
        return (self.t, self.pu, self.mv, self.di, self.cnt, self.av)

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
        bufdecode = buffer.decode('utf-8')
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

    def WW_PuReglerParamSchreiben(self, kp, ki, ap):
        command = "put vww 00="+str(kp)        
        self.write( command.encode('utf-8') )
        time.sleep(0.5)
        command = "put vww 01="+str(ki)
        self.write( command.encode('utf-8') )
        time.sleep(0.5)
        command = "put vww 02="+str(ap)
        self.write( command.encode('utf-8') )
        time.sleep(0.5) 
    
    def WW_PuReglerParamLesen(self):
        command = "get vww -1" 
        self.write( command.encode('utf-8') )
        time.sleep(3.0)
        buffer = self.read_very_eager()
        bufdecode = buffer.decode('utf-8')
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

    def Param_GetParam(self, values): # Parameter values ist ein dict, das CallbyRef uebergeben wird
        command = "get param"
        self.write( command.encode('utf-8') )
        time.sleep(3.0)
        buffer = self.read_very_eager()
        bufdecode = buffer.decode('utf-8')
        lines = bufdecode.splitlines()
        for line in lines:
            for name in signals.PARAMETERS:
                if (line.startswith(name)):
                    values[name] = str(line.split('=')[1])

    def Param_PutParam(self, values):
        pass
        
if __name__ == '__main__':
    iface = TelnetInterface('stegmann.homelinux.org', 1969, 10)   
    iface.ErmittleMesswerte()
    print(iface.t)
    print(iface.av)
    print(iface.cnt)
    print(iface.di)
    print(iface.pu)
    print(iface.mv)
    iface.close()
    
    
    
    
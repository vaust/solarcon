'''
Created on 23.01.2012

@author: stegmann
'''

import threading

class iTimer(threading.Thread):
    def __init__(self, interval, target):
        threading.Thread.__init__(self)
        self.event = threading.Event()
        self.interval = interval
        self.target = target
        
    def run(self):
        while not self.event.is_set():
            """ The things I want to do go here. """
            self.target()
            """ Event abwarten """
            self.event.wait(self.interval)

    def stop(self):
        self.event.set()

#----

if __name__ == '__main__':
    pass
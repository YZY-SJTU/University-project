#!/usr/bin/python

"""
Simple example of setting network and CPU parameters
"""


from mininet.topo import Topo
from mininet.net import Mininet
from mininet.node import OVSBridge
from mininet.node import CPULimitedHost
from mininet.link import TCLink
from mininet.util import dumpNodeConnections
from mininet.log import setLogLevel, info
from mininet.cli import CLI

from sys import argv

# It would be nice if we didn't have to do this:
# pylint: disable=arguments-differ

class SingleSwitchTopo( Topo ):
    def build( self , client_num):
        server = self.addHost('h1', cpu=.25, mac='00:00:00:00:00:01')
        switch = self.addSwitch('s1',stp=True)
        self.addLink(switch, server, bw=10, delay='5ms', loss=0, use_htb=True)
        for i in range(0,client_num):
           host = self.addHost('h'+str(i+2), cpu=.25)
           self.addLink(host, switch, bw=10, delay='5ms', loss=0, use_htb=True)

def Test(client_num):
    "Create network and run simple performance test"
    topo = SingleSwitchTopo(client_num)
    net = Mininet( topo=topo,
                   host=CPULimitedHost, link=TCLink,
                   autoStaticArp=False )
    net.start()
    info( "Dumping host connections\n" )
    dumpNodeConnections(net.hosts)
    #info( "Testing bandwidth between h1 and h4\n" )
    #h1, h2 = net.getNodeByName('h1', 'h2')
    #net.iperf( [ h1, h2 ], seconds=10, l4Type='TCP')
    CLI(net)
    net.stop()

if __name__ == '__main__':
    # setLogLevel( 'debug' )
    setLogLevel('info')
    # Prevent test_simpleperf from failing due to packet loss
    client_num = input("input the num of clients(<=20): ")
    Test(int(client_num))

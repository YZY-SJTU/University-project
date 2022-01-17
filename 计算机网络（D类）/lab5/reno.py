#!/usr/bin/python
"""Simple example of setting network and CPU parameters  """
from mininet.topo import Topo
from mininet.net import Mininet
from mininet.node import OVSBridge
from mininet.node import CPULimitedHost
from mininet.link import TCLink
from mininet.util import quietRun, dumpNodeConnections
from mininet.log import setLogLevel, info
from mininet.cli import CLI
from sys import argv
import time
# It would be nice if we didn't have to do this:
# pylint: disable=arguments-differ


class SingleSwitchTopo(Topo):
    def build(self,pair_num):
        switch1 = self.addSwitch('s1')
        switch2 = self.addSwitch('s2')
        for i in range(pair_num):
            sender = self.addHost('h'+str(2*i+1), cpu=.25)
            receiver = self.addHost('h'+str(2*i+2), cpu=.25)
            self.addLink(sender, switch1, bw=100, delay='5ms', loss=0, use_htb=True)
            self.addLink(receiver, switch2, bw=100, delay='5ms', loss=0, use_htb=True)
        self.addLink(switch1, switch2, bw=100,delay='200ms', loss=0.1, use_htb=True)

def Test(tcp, pair_num):
    "Create network and run simple performance test"
    topo = SingleSwitchTopo(pair_num)
    net = Mininet(topo=topo,host=CPULimitedHost, link=TCLink,autoStaticArp=False)
    net.start()
    info( "Dumping host connections\n" )
    dumpNodeConnections(net.hosts)
    # set up tcp congestion control algorithm    
    output = quietRun( 'sysctl -w net.ipv4.tcp_congestion_control=' + tcp )
    assert tcp in output
    info( "Testing bandwidth under TCP " + tcp + "\n" )
    for i in range(pair_num):
        h1, h2 = net.getNodeByName('h'+str(2*i+1), 'h'+str(2*i+2))
        _serverbw, clientbw = net.iperf( [ h1, h2 ], seconds=10 )
        info( 'receiver:',clientbw, '\n' )
    # CLI(net)
    net.stop()
            
if __name__ == '__main__':
    setLogLevel('info')
    pair_num = input('input the sender-receiver pair nums:')
    # pick a congestion control algorithm, for example, 'reno', 'cubic', 'bbr', 'vegas', 'hybla', etc.    
    tcp = 'reno'
    Test(tcp, int(pair_num))

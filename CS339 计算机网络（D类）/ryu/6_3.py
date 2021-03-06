# Copyright (C) 2011 Nippon Telegraph and Telephone Corporation.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
# implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from ryu.base import app_manager
from ryu.controller import ofp_event
from ryu.controller.handler import CONFIG_DISPATCHER, MAIN_DISPATCHER
from ryu.controller.handler import set_ev_cls
from ryu.ofproto import ofproto_v1_3
from ryu.lib.packet import packet
from ryu.lib.packet import ethernet
from ryu.lib.packet import ether_types
from ryu.lib.packet import  in_proto as inet


class SimpleSwitch13(app_manager.RyuApp):
    OFP_VERSIONS = [ofproto_v1_3.OFP_VERSION]

    def __init__(self, *args, **kwargs):
        super(SimpleSwitch13, self).__init__(*args, **kwargs)
        self.mac_to_port = {}
        self.switch1_flag = False
        self.switch2_flag = False
        self.switch3_flag = False
        self.h2_mac = ""

    @set_ev_cls(ofp_event.EventOFPSwitchFeatures, CONFIG_DISPATCHER)
    def switch_features_handler(self, ev):
        datapath = ev.msg.datapath
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser

        # install table-miss flow entry
        #
        # We specify NO BUFFER to max_len of the output action due to
        # OVS bug. At this moment, if we specify a lesser number, e.g.,
        # 128, OVS will send Packet-In with invalid buffer_id and
        # truncated packet data. In that case, we cannot output packets
        # correctly.  The bug has been fixed in OVS v2.1.0.
        match = parser.OFPMatch()
        actions = [parser.OFPActionOutput(ofproto.OFPP_CONTROLLER,
                                          ofproto.OFPCML_NO_BUFFER)]#OFPActionOutput???????????????out?????????message??????????????????????????????????????????
        self.add_flow(datapath, 0, match, actions)

    def add_flow(self, datapath, priority, match, actions, buffer_id=None):
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser

        inst = [parser.OFPInstructionActions(ofproto.OFPIT_APPLY_ACTIONS,
                                             actions)]
        if buffer_id:
            mod = parser.OFPFlowMod(datapath=datapath, buffer_id=buffer_id,
                                    priority=priority, match=match,
                                    instructions=inst)
        else:
            mod = parser.OFPFlowMod(datapath=datapath, priority=priority,
                                    match=match, instructions=inst)
        datapath.send_msg(mod)

    @set_ev_cls(ofp_event.EventOFPPacketIn, MAIN_DISPATCHER)#??????packet??????????????????????????????MAIN_DISPATCHER?????????????????????????????????
    def _packet_in_handler(self, ev):
        # If you hit this you might want to increase
        # the "miss_send_length" of your switch  
        if ev.msg.msg_len < ev.msg.total_len:
            self.logger.debug("packet truncated: only %s of %s bytes",
                              ev.msg.msg_len, ev.msg.total_len)
        msg = ev.msg#?????????packet???????????????
        datapath = msg.datapath#???????????????switch???
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser#ryu???switch???????????????openflow protocol
        in_port = msg.match['in_port']#??????msg??????source port
        pkt = packet.Packet(msg.data)
        eth = pkt.get_protocols(ethernet.ethernet)[0]#get_protocols?????????????????????protocol???match???protocol??????
	#??????????????????????????????packet????????????
        if eth.ethertype == ether_types.ETH_TYPE_LLDP:
            # ignore lldp packet
            return
        dst = eth.dst
        src = eth.src
        dpid = format(datapath.id, "d").zfill(16)
        self.mac_to_port.setdefault(dpid, {})#???mac_to_port??????????????????
        # learn a mac address to avoid FLOOD next time.
        self.mac_to_port[dpid][src] = in_port
        if dst in self.mac_to_port[dpid]:
            out_port = self.mac_to_port[dpid][dst]
            self.logger.info("packet in %s %s %s %s %s", dpid, src, dst, in_port, out_port)
            actions = [parser.OFPActionOutput(out_port)]#????????????packet????????????????????????
            data = None
            if msg.buffer_id == ofproto.OFP_NO_BUFFER:
                data = msg.data
            out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id, in_port=in_port, actions=actions, data=data)#OFPPacketOut??????????????????????????????out packet???????????????
            datapath.send_msg(out)#?????????switch?????????????????????????????????
	#if some packet have reached the destination,record it and attach the corresponding port
        elif (dpid == str(1).zfill(16)):
            if (in_port == 1):
                if (not self.switch1_flag):
                    port1 = 2
                    actions1 = [parser.OFPActionOutput(port1)]
                    port2 = 3
                    actions2 = [parser.OFPActionOutput(port2)]
                    weight1 = 0
                    weight2 = 0
                    watch_port1 = 2
                    watch_port2 = 3
                    watch_group = ofproto.OFPG_ANY
                    buckets = [parser.OFPBucket(weight1, watch_port1, watch_group, actions1), parser.OFPBucket(weight2, watch_port2, watch_group, actions2)]
                    group_id = 1
                    req = parser.OFPGroupMod(datapath, ofproto.OFPGC_ADD, ofproto.OFPGT_FF, group_id, buckets)
                    datapath.send_msg(req)#modify group table
                    actions = [parser.OFPActionGroup(group_id=1)]
                    match = parser.OFPMatch(in_port=in_port, eth_src = src)
                    self.add_flow(datapath, 1, match, actions)#add flow table
                    self.switch1_flag =True
                self.logger.info("packet in %s %s %s %s out in two ways", dpid, src, dst, in_port)
                actions = [parser.OFPActionGroup(group_id=1)]
                data = None
                if msg.buffer_id == ofproto.OFP_NO_BUFFER:
                    data = msg.data
                out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id,in_port=in_port, actions=actions, data=data)
                return
            else:
                out_port = 1
                self.logger.info("packet in %s %s %s %s %s", dpid, src, dst, in_port, out_port)
                actions = [parser.OFPActionOutput(out_port)]
                data = None
                if msg.buffer_id == ofproto.OFP_NO_BUFFER:
                    data = msg.data
                out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id, in_port=in_port, actions=actions, data=data)#OFPPacketOut??????????????????????????????out packet???????????????
                datapath.send_msg(out)#?????????switch?????????????????????????????????
        elif (dpid == str(2).zfill(16)):
            if (in_port == 1):
                if (not self.switch2_flag):
                    self.h2_mac = src
                    port1 = 2
                    actions1 = [parser.OFPActionOutput(port1)]
                    port2 = 3
                    actions2 = [parser.OFPActionOutput(port2)]
                    weight1 = 0
                    weight2 = 0
                    watch_port1 = 2
                    watch_port2 = 3
                    watch_group = ofproto.OFPG_ANY
                    buckets = [parser.OFPBucket(weight1, watch_port1, watch_group, actions1), parser.OFPBucket(weight2, watch_port2, watch_group, actions2)]
                    group_id = 2
                    req = parser.OFPGroupMod(datapath, ofproto.OFPGC_ADD, ofproto.OFPGT_SELECT, group_id, buckets)
                    datapath.send_msg(req)#modify group table

                    actions = [parser.OFPActionGroup(group_id=2)]
                    match = parser.OFPMatch(in_port=in_port, eth_src = src)
                    self.add_flow(datapath, 1, match, actions)#Add flow table
                    #self.switch2_flag = True
                self.logger.info("packet in %s %s %s %s out in two ways", dpid, src, dst, in_port)
                actions = [parser.OFPActionGroup(group_id=2)]
                data = None
                if msg.buffer_id == ofproto.OFP_NO_BUFFER:
                    data = msg.data
                out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id,in_port=in_port, actions=actions, data=data)
                return
            else:
                if(self.h2_mac == src):
                    out_port = 3
                else:
                    out_port = 1
                self.logger.info("packet in %s %s %s %s %s", dpid, src, dst, in_port, out_port)
                actions = [parser.OFPActionOutput(out_port)]#????????????packet????????????????????????
                data = None
                if msg.buffer_id == ofproto.OFP_NO_BUFFER:
                    data = msg.data
                out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id, in_port=in_port, actions=actions, data=data)#OFPPacketOut??????????????????????????????out packet???????????????
                datapath.send_msg(out)#?????????switch?????????????????????????????????
        elif(dpid == str(3).zfill(16)):
            if (in_port == 1):
                out_port = 2
            else:
                if (not self.switch3_flag):
                    port1 = 1
                    actions1 = [parser.OFPActionOutput(port1)]
                    port2 = 2
                    actions2 = [parser.OFPActionOutput(port2)]
                    weight1 = 0
                    weight2 = 0
                    watch_port1 = 1
                    watch_port2 = 2
                    watch_group = ofproto.OFPG_ANY
                    buckets = [parser.OFPBucket(weight1, watch_port1, watch_group, actions1), parser.OFPBucket(weight2, watch_port2, watch_group, actions2)]
                    group_id = 3
                    req = parser.OFPGroupMod(datapath, ofproto.OFPGC_ADD, ofproto.OFPGT_SELECT, group_id, buckets)
                    datapath.send_msg(req)#modify group table

                    actions = [parser.OFPActionGroup(group_id=3)]
                    match = parser.OFPMatch(in_port=in_port, eth_src = src)
                    self.add_flow(datapath, 1, match, actions)#Add flow table
                self.logger.info("packet in %s %s %s %s out in two ways", dpid, src, dst, in_port)
                actions = [parser.OFPActionGroup(group_id=3)]
                data = None
                if msg.buffer_id == ofproto.OFP_NO_BUFFER:
                    data = msg.data
                out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id,in_port=in_port, actions=actions, data=data)
                return
            self.logger.info("packet in %s %s %s %s %s", dpid, src, dst, in_port, out_port)
            actions = [parser.OFPActionOutput(out_port)]#????????????packet????????????????????????
            data = None
            if msg.buffer_id == ofproto.OFP_NO_BUFFER:
                data = msg.data
            out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id, in_port=in_port, actions=actions, data=data)#OFPPacketOut??????????????????????????????out packet???????????????
            datapath.send_msg(out)#?????????switch?????????????????????????????????
        elif(dpid == str(4).zfill(16)):
            if (in_port == 1):
                out_port = 2
            else:
                out_port = 1
            self.logger.info("packet in %s %s %s %s %s", dpid, src, dst, in_port, out_port)
            actions = [parser.OFPActionOutput(out_port)]#????????????packet????????????????????????
            data = None
            if msg.buffer_id == ofproto.OFP_NO_BUFFER:
                data = msg.data
            out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id, in_port=in_port, actions=actions, data=data)#OFPPacketOut??????????????????????????????out packet???????????????
            datapath.send_msg(out)#?????????switch?????????????????????????????????
        else:
            out_port = ofproto.OFPP_FLOOD
            self.logger.info("packet in %s %s %s %s %s", dpid, src, dst, in_port, out_port)
            actions = [parser.OFPActionOutput(out_port)]#????????????packet????????????????????????
            data = None
            if msg.buffer_id == ofproto.OFP_NO_BUFFER:
                data = msg.data
            out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id, in_port=in_port, actions=actions, data=data)#OFPPacketOut??????????????????????????????out packet???????????????
            datapath.send_msg(out)#?????????switch?????????????????????????????????

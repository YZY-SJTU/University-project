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
                                          ofproto.OFPCML_NO_BUFFER)]#OFPActionOutput函数与一个out相关的message，确认输入信息应当发送的端口
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

    @set_ev_cls(ofp_event.EventOFPPacketIn, MAIN_DISPATCHER)#每当packet进来时调用下列函数，MAIN_DISPATCHER代表仅在连接建立后调用
    def _packet_in_handler(self, ev):
        # If you hit this you might want to increase
        # the "miss_send_length" of your switch  
        if ev.msg.msg_len < ev.msg.total_len:
            self.logger.debug("packet truncated: only %s of %s bytes",
                              ev.msg.msg_len, ev.msg.total_len)
        msg = ev.msg#进来的packet的数据结构
        datapath = msg.datapath#代表路径（switch）
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser#ryu与switch之间协商的openflow protocol
        in_port = msg.match['in_port']#获取msg中的source port
        pkt = packet.Packet(msg.data)
        eth = pkt.get_protocols(ethernet.ethernet)[0]#get_protocols函数返回与参数protocol相match的protocol列表
	#物理层上的一种特殊的packet可以忽略
        if eth.ethertype == ether_types.ETH_TYPE_LLDP:
            # ignore lldp packet
            return
        dst = eth.dst
        src = eth.src
        dpid = format(datapath.id, "d").zfill(16)
        self.mac_to_port.setdefault(dpid, {})#在mac_to_port字典中添加键

        # learn a mac address to avoid FLOOD next time.
        self.mac_to_port[dpid][src] = in_port
        if dst in self.mac_to_port[dpid]:
            out_port = self.mac_to_port[dpid][dst]
            self.logger.info("packet in %s %s %s %s %s", dpid, src, dst, in_port, out_port)
            actions = [parser.OFPActionOutput(out_port)]#将对应的packet输出到对应的端口
            data = None
            if msg.buffer_id == ofproto.OFP_NO_BUFFER:
                data = msg.data
            out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id, in_port=in_port, actions=actions, data=data)#OFPPacketOut函数用于建立一个关于out packet的信息数据
            datapath.send_msg(out)#向目标switch相应信息并等待返回结果
	#if some packet have reached the destination,record it and attach the corresponding port
        elif (dpid == str(1).zfill(16)):
            if (in_port == 1):
                if (not self.switch1_flag):
                    port1 = 2
                    actions1 = [parser.OFPActionOutput(port1)]
                    port2 = 3
                    actions2 = [parser.OFPActionOutput(port2)]
                    weight1 = 50
                    weight2 = 50
                    watch_port = 1
                    watch_group = 0
                    buckets = [parser.OFPBucket(weight1, watch_port, watch_group, actions1), parser.OFPBucket(weight2, watch_port, watch_group, actions2)]
                    group_id = 1
                    req = parser.OFPGroupMod(datapath, ofproto.OFPGC_ADD, ofproto.OFPGT_SELECT, group_id, buckets)
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
                out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id, in_port=in_port, actions=actions, data=data)#OFPPacketOut函数用于建立一个关于out packet的信息数据
                datapath.send_msg(out)#向目标switch相应信息并等待返回结果
        elif (dpid == str(2).zfill(16)):
            if (in_port == 1):
                if (not self.switch2_flag):
                    port1 = 2
                    actions1 = [parser.OFPActionOutput(port1)]
                    port2 = 3
                    actions2 = [parser.OFPActionOutput(port2)]
                    weight1 = 50
                    weight2 = 50
                    watch_port = 1
                    watch_group = 0
                    buckets = [parser.OFPBucket(weight1, watch_port, watch_group, actions1), parser.OFPBucket(weight2, watch_port, watch_group, actions2)]
                    group_id = 2
                    req = parser.OFPGroupMod(datapath, ofproto.OFPGC_ADD, ofproto.OFPGT_SELECT, group_id, buckets)
                    datapath.send_msg(req)#modify group table
                    actions = [parser.OFPActionGroup(group_id=group_id)]
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
                out_port = 1
                self.logger.info("packet in %s %s %s %s %s", dpid, src, dst, in_port, out_port)
                actions = [parser.OFPActionOutput(out_port)]#将对应的packet输出到对应的端口
                data = None
                if msg.buffer_id == ofproto.OFP_NO_BUFFER:
                    data = msg.data
                out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id, in_port=in_port, actions=actions, data=data)#OFPPacketOut函数用于建立一个关于out packet的信息数据
                datapath.send_msg(out)#向目标switch相应信息并等待返回结果
        elif(dpid == str(3).zfill(16)):
            if (in_port == 1):
                out_port = 2
            else:
                out_port = 1
            self.logger.info("packet in %s %s %s %s %s", dpid, src, dst, in_port, out_port)
            actions = [parser.OFPActionOutput(out_port)]#将对应的packet输出到对应的端口
            data = None
            if msg.buffer_id == ofproto.OFP_NO_BUFFER:
                data = msg.data
            out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id, in_port=in_port, actions=actions, data=data)#OFPPacketOut函数用于建立一个关于out packet的信息数据
            datapath.send_msg(out)#向目标switch相应信息并等待返回结果
        elif(dpid == str(4).zfill(16)):
            if (in_port == 1):
                out_port = 2
            else:
                out_port = 1
            self.logger.info("packet in %s %s %s %s %s", dpid, src, dst, in_port, out_port)
            actions = [parser.OFPActionOutput(out_port)]#将对应的packet输出到对应的端口
            data = None
            if msg.buffer_id == ofproto.OFP_NO_BUFFER:
                data = msg.data
            out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id, in_port=in_port, actions=actions, data=data)#OFPPacketOut函数用于建立一个关于out packet的信息数据
            datapath.send_msg(out)#向目标switch相应信息并等待返回结果
        else:
            out_port = ofproto.OFPP_FLOOD
            self.logger.info("packet in %s %s %s %s %s", dpid, src, dst, in_port, out_port)
            actions = [parser.OFPActionOutput(out_port)]#将对应的packet输出到对应的端口
            data = None
            if msg.buffer_id == ofproto.OFP_NO_BUFFER:
                data = msg.data
            out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id, in_port=in_port, actions=actions, data=data)#OFPPacketOut函数用于建立一个关于out packet的信息数据
            datapath.send_msg(out)#向目标switch相应信息并等待返回结果

#!/bin/bash
# encoding: utf-8


import rospy
import rosbag
import os, sys
import csv

# bag_name = '/driving_2019_03_15-16_16_53.bag'
base_dir = './'
# bag_file = 'driving_2019_03_09-15_18_31.bag'
# bag_name = base_dir + bag_file


headers = ['stamp']
for i in range(4):
    headers.extend(['index', 'C0', 'C1', 'C2', 'C3'])

def gen_lane_csv():
    print base_dir
    file_list = os.listdir(base_dir)
    # print file_list
    for fn in file_list:
        if not ('driving' in fn and 'bag' in fn):
            continue
        fb , fe = os.path.splitext(fn)
        if fe != '.bag':
            continue  
        fcsv = fn.replace('bag', 'csv')
        cv_file             = base_dir + fcsv.replace('driving', 'lane_cv')
        hdmap_file          = base_dir + fcsv.replace('driving', 'lane_hdmap')
        send_file           = base_dir + fcsv.replace('driving', 'lane_send')
        
        cv_csv_writer       = csv.writer(open(cv_file, 'w'))
        hdmap_csv_writer    = csv.writer(open(hdmap_file, 'w'))
        send_csv_writer     = csv.writer(open(send_file, 'w'))

        cv_csv_writer.writerow(headers)
        hdmap_csv_writer.writerow(headers)
        send_csv_writer.writerow(headers)
        
        print 'process :', fn
        with rosbag.Bag(base_dir + fn) as bag:
            for topic, msg, t in bag.read_messages():
                if 'lane_boundary_cv' in topic:
                    txt = [ msg.header.stamp.secs + msg.header.stamp.nsecs / 1000000000.0]
                    for lane in msg.lane_boundarys:
                        if txt is None:
                            txt = [lane.index, lane.C0, lane.C1, lane.C2, lane.C3]
                        else:
                            txt.extend([lane.index, lane.C0, lane.C1, lane.C2, lane.C3])
                    for i in range(4-len(msg.lane_boundarys)):
                        txt.extend([0, 0, 0, 0, 0])
                    cv_csv_writer.writerow(txt)
                if 'lane_boundary_hdmap' in topic:
                    txt = [msg.header.stamp.secs + msg.header.stamp.nsecs / 1000000000.0]
                    for lane in msg.lane_boundarys:
                        if txt is None:
                            txt = [lane.index, lane.C0, lane.C1, lane.C2, lane.C3]
                        else:
                            txt.extend([lane.index, lane.C0, lane.C1, lane.C2, lane.C3])
                    for i in range(4-len(msg.lane_boundarys)):
                        txt.extend([0, 0, 0, 0, 0])
                    hdmap_csv_writer.writerow(txt)
                if 'lane_boundary_with_source' in topic:
                    txt = [msg.header.stamp.secs + msg.header.stamp.nsecs / 1000000000.0]
                    for lane in msg.lane_boundarys:
                        if txt is None:
                            txt = [lane.index, lane.C0, lane.C1, lane.C2, lane.C3]
                        else:
                            txt.extend([lane.index, lane.C0, lane.C1, lane.C2, lane.C3])
                    for i in range(4-len(msg.lane_boundarys)):
                        txt.extend([0, 0, 0, 0, 0])
                    send_csv_writer.writerow(txt)
                    # break
    print 'gen over'


if __name__ == "__main__":
    _len = len(sys.argv)
    if _len > 1:
        base_dir = sys.argv[1]
    gen_lane_csv()

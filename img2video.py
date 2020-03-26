#!/usr/bin/env python
# coding=utf-8
import numpy as np
import cv2
import os
import sys
import re   # 正则表达式

images_dir  = '/home/andy/08_Data/2019-10-04/image_back/'
output_name = 'output'
pattern_str = r'0-2019-10-04_09-39-[0-9][0-9]_00027[6-8](.*)'

if len(sys.argv) > 1:
    images_dir = sys.argv[1]
if len(sys.argv) > 2:
    output_name = sys.argv[2]

fn_l = os.listdir(images_dir)
fn_l.sort()
# cap = cv2.VideoCapture(0)

# Define the codec and create VideoWriter object
# fourcc = cv2.VideoWriter_fourcc(*'XVID')
fourcc = cv2.VideoWriter_fourcc('M','J','P','G')
# out = cv2.VideoWriter('output.avi',fourcc, 30.0, (1280, 720))

out_created = False
for fn in fn_l:
    # ret, frame = cap.read()
    if re.match(pattern_str, fn) is None:
        continue
    print(fn)
    frame = cv2.imread(images_dir + '/' + fn)

    if not out_created:
        #frame = cv2.flip(frame,0)
        sp = frame.shape
        # print(sp)
        out = cv2.VideoWriter('%s.avi' % output_name, fourcc, 30, (sp[1], sp[0]))
        out_created = True
        
        # write the flipped frame
    out.write(frame)
    cv2.imshow('frame',frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    
# Release everything if job is finished
# cap.release()
out.release()
cv2.destroyAllWindows()

# !/bin/env python
# -*- coding: utf-8 -*-



import cv2

img         = cv2.imread('autojump.png')
img_gray    = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

def im_show(im):
    cv2.imshow('show', cv2.resize(im, (int(im.shape[1]/2), int(im.shape[0]/2))))
    cv2.waitKey()

print(img_gray.shape[0])
# cv2.imshow('show', cv2.resize(img_gray, (int(img_gray.shape[1]/2), int(img_gray.shape[0]/2))))
# cv2.waitKey()

roi         = img_gray[850:2000, :]
im_show(roi)



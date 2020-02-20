# !/bin/env python
# -*- coding: utf-8 -*-

# from common import debug, config, screenshot, UnicodeStreamFilter
from common.auto_adb import auto_adb
from common import screenshot

import numpy as np
import cv2

def process(img):
    image = cv2.cvtColor(np.asarray(img), cv2.COLOR_RGB2BGR)
    cv2.imshow("show" ,image)
    cv2.waitKey()

def test():
    print('test')
    adb = auto_adb()
    adb.test_device()

    screenshot.check_screenshot()

    while True:
        im = screenshot.pull_screenshot()
        print(type(im))
        process(im)


if __name__ == '__main__':
    test()
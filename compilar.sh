#!/bin/bash

gcc basic-tutorial-1.c -o basic-tutorial-1 `pkg-config --cflags --libs gstreamer-1.0` && ./basic-tutorial-1

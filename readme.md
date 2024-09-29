# Project: dev-gl
# Author: Saurabh Tripathi (saurabhtripathi1102000@gmail.com)

## Introduction
`dev-gl` is a repository designed to help developers set up an OpenGL development environment and run OpenGL programs in Linux. This repo provides plug n play privilage for OpenGL apps and a collection of OpenGL example programs for learning and experimentation.

## How to add your own project:
* mkdir <my_app> && cd <my_app>
* mkdir <src>
* touch <my_app.c> && touch meson.build
* Write your app and modify meson.build with all required deps


## How to use:
* ./dev-gl.py download deps (Feel free to add more deps)
* Add your project info in `./dev-gl.py`
  For eg: self.projects = {
            "app": "app/src",
            "advanced_app": "advanced_app/src",
            "colorful_triangle": "colorful_triangle/src",
            "<app_name>": "<app_name/src>",
            }
* ./dev-gl.py run <app_name>


In case your are using WSL1 and install some X server app:
For eg: 
`VcXsrv`: One of the most common X servers for WSL.
Download and install VcXsrv and
`export DISPLAY=localhost:0`

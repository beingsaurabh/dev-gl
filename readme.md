# Project: dev-gl
## Author: Saurabh Tripathi (saurabhtripathi1102000@gmail.com)

## Introduction
`dev-gl` is a repository designed to help developers set up an OpenGL development environment and run OpenGL programs in Linux (debian based, x86 arch). This repo provides plug n play privilage for OpenGL apps and a collection of OpenGL example programs for learning and experimentation.

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

![image](https://github.com/user-attachments/assets/3bc506bc-2957-4f46-9113-c71ea2f4f7fd)

![image](https://github.com/user-attachments/assets/86714b6e-ecc4-4b5d-840b-129ff1abd714)

![image](https://github.com/user-attachments/assets/109ebbed-641f-4a45-a429-b4b9f34e51a7)

![image](https://github.com/user-attachments/assets/ea16f382-e252-4b64-a873-b4f7c26866c0)




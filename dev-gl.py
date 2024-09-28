#!/usr/bin/env python3
"""
dev-gl.py: A script to manage OpenGL development environment for Linux and macOS.
Allows downloading dependencies, building, and running OpenGL applications.
"""

import os
import sys
import subprocess


class DevGL:
    """
    A class to handle OpenGL environment setup and program management.
    """

    def __init__(self):
        """
        Initialize the class with platform-specific settings.
        """
        self.platform = sys.platform
        self.supported_platforms = ['linux', 'darwin']

    def download_deps(self):
        """
        Install OpenGL dependencies based on the platform.
        """
        if self.platform not in self.supported_platforms:
            print(f"Unsupported platform: {self.platform}")
            sys.exit(1)

        if self.platform.startswith('linux'):
            print("Installing OpenGL dependencies for Linux...")
            os.system('sudo apt update && sudo apt install -y build-essential libgl1-mesa-dev libglew-dev libglfw3 libglfw3-dev mesa-utils x11-apps libfreetype6-dev pciutils libbox2d-dev')
        elif self.platform == 'darwin':
            print("Installing OpenGL dependencies for macOS...")
            os.system('brew install glfw glew glm')

    def build_app(self, source_file):
        """
        Build the OpenGL program using GCC.

        Args:
            source_file (str): The path to the source file (C program) to compile.
        """
        if not source_file.endswith('.c'):
            print(f"Error: {source_file} is not a C file.")
            sys.exit(1)

        output_file = source_file.replace('.c', '')

        if self.platform == 'linux' or self.platform == 'linux2':
            command = f"gcc {source_file} -lGL -lglfw -lGLEW -lbox2d -lm -o {output_file}"
        elif self.platform == 'darwin':
            command = f"gcc {source_file} -I/usr/local/include -L/usr/local/lib -lGL -lglfw -lGLEW -o {output_file}"
        else:
            print(f"Unsupported platform: {self.platform}")
            sys.exit(1)

        print(f"Building {source_file}...")
        try:
            subprocess.run(command, shell=True, check=True)
            print(f"Built {output_file}")
        except subprocess.CalledProcessError as error:
            print(f"Error occurred while building: {error}")
            sys.exit(1)

    def run_app(self, source_file):
        """
        Run the compiled OpenGL program.

        Args:
            source_file (str): The path to the source file (C program) to run.
        """
        output_file = source_file.replace('.c', '')
        if os.path.exists(output_file):
            print(f"Running {output_file}...")
            try:
                subprocess.run(f"./{output_file}", shell=True)
            except subprocess.CalledProcessError as error:
                print(f"Error occurred while running: {error}")
                sys.exit(1)
        else:
            print(f"Error: {output_file} not found. Build the app first.")
            sys.exit(1)

    @staticmethod
    def print_usage():
        """
        Print the usage of the script.
        """
        print("Usage:")
        print("  ./dev-gl.py download deps  - Download OpenGL dependencies")
        print("  ./dev-gl.py build <file.c> - Build an OpenGL program")
        print("  ./dev-gl.py run <file.c>   - Run an OpenGL program")


def main():
    """
    Main function to handle command-line arguments and execute the corresponding methods.
    """
    if len(sys.argv) < 3:
        DevGL.print_usage()
        sys.exit(1)

    command = sys.argv[1]
    dev_gl = DevGL()

    if command == 'download' and sys.argv[2] == 'deps':
        dev_gl.download_deps()
    elif command == 'build':
        dev_gl.build_app(sys.argv[2])
    elif command == 'run':
        dev_gl.run_app(sys.argv[2])
    else:
        print("Invalid command or arguments.")
        DevGL.print_usage()
        sys.exit(1)


if __name__ == "__main__":
    main()

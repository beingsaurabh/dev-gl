#!/usr/bin/env python3

import os
import subprocess
import sys


class DevGL:
    def __init__(self):
        self.projects = {
            "app": "app/src",
            "advanced_app": "advanced_app/src",
            "colorful_triangle": "colorful_triangle/src",
        }

    # Function to print help/usage information
    def print_help(self):
        print("Usage: ./dev-gl.py [command] [options]\n")
        print("Commands:")
        print("  download dependencies   Install necessary dependencies.")
        print("  run [project_name]      Build and run an OpenGL project (e.g., app).\n")
        print("Available Projects:")
        for project in self.projects:
            print(f"  {project}")
        print("\nExamples:")
        print("  ./dev-gl.py download dependencies")
        print("  ./dev-gl.py run app")

    # Function to download dependencies based on the OS
    def download_dependencies(self):
        print("Installing dependencies...")
        result = subprocess.run(["sudo", "apt-get", "install", "-y",
                                 "build-essential", "libgl1-mesa-dev", "libglew-dev",
                                 "libglfw3", "libglfw3-dev", "mesa-utils", "x11-apps",
                                 "libfreetype6-dev", "pciutils", "libbox2d-dev", 
                                 "meson", "ninja-build", "pkg-config"])
        if result.returncode != 0:
            print("Error occurred during dependencies installation.")
            sys.exit(1)
        print("Dependencies installed successfully.")

    # Function to set up the Meson build directory for a specific project
    def setup_meson(self, project_name):
        project_dir = self.projects.get(project_name)
        if not project_dir:
            print(f"Project {project_name} does not exist.")
            sys.exit(1)

        build_dir = os.path.join(project_dir, "../build")
        if not os.path.exists(build_dir):
            print(f"Setting up Meson build directory for {project_name}...")
            result = subprocess.run(['meson', 'setup', build_dir, project_dir])
            if result.returncode != 0:
                print(f"Failed to set up Meson for {project_name}.")
                sys.exit(1)
            print(f"Meson build directory created for {project_name}.")
        else:
            print(f"Meson build directory already exists for {project_name}.")

    # Function to build the project using Meson
    def build_project(self, project_name):
        project_dir = self.projects.get(project_name)
        if not project_dir:
            print(f"Project {project_name} does not exist.")
            sys.exit(1)

        build_dir = os.path.join(project_dir, "../build")
        print(f"Building {project_name} using Meson...")
        result = subprocess.run(['meson', 'compile', '-C', build_dir])
        if result.returncode != 0:
            print(f"Error occurred while building {project_name}.")
            sys.exit(1)
        print(f"Built {project_name} successfully.")

    # Function to run the built project
    def run_project(self, project_name):
        project_dir = self.projects.get(project_name)
        if not project_dir:
            print(f"Project {project_name} does not exist.")
            sys.exit(1)

        executable_path = os.path.join(project_dir, "../build", project_name)
        if os.path.exists(executable_path):
            print(f"Running {project_name}...")
            subprocess.run([executable_path])
        else:
            print(f"Executable for {project_name} not found. Please build it first.")
            sys.exit(1)

    # Function to handle command-line arguments
    def handle_command(self, args):
        if len(args) < 2:
            self.print_help()
            sys.exit(1)

        command = args[1]

        if command == "--help":
            self.print_help()
        elif command == "download":
            if len(args) == 3 and args[2] == "dependencies":
                self.download_dependencies()
            else:
                print("Invalid command. Use './dev-gl.py --help' to see usage.")
                sys.exit(1)
        elif command == "run":
            if len(args) != 3:
                print("Please provide a project to run (e.g., app).")
                sys.exit(1)
            project_name = args[2]
            self.setup_meson(project_name)
            self.build_project(project_name)
            self.run_project(project_name)
        else:
            print(f"Unknown command: {command}")
            print("Use './dev-gl.py --help' to see usage.")
            sys.exit(1)


# Main function
def main():
    dev_gl = DevGL()
    dev_gl.handle_command(sys.argv)


if __name__ == "__main__":
    main()

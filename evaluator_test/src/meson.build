project('dev-gl', 'c', version: '0.1.0')

# Dependencies

gl_dep = dependency('gl', required: true) # OpenGL
glew_dep = dependency('glew', required: true) # GLEW
glfw_dep = dependency('glfw3', required: true) # GLFW
glut_dep = declare_dependency
        ( include_directories: include_directories('/usr/include'),
        link_args: ['-L/usr/lib/x86_64-linux-gnu', '-lglut'] )
freetype_dep = dependency('freetype2', required: true) # FreeType for font rendering 

executable('evaluator_test', 'evaluator_test.c',
            dependencies: [gl_dep, glew_dep, glfw_dep, glut_dep, freetype_dep], 
            install: true)

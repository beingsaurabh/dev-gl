project('dev-gl', 'c', version: '0.1.0')

# Dependencies
gl_dep = dependency('gl', required: true)         # OpenGL
glew_dep = dependency('glew', required: true)     # GLEW
glfw_dep = dependency('glfw3', required: true)    # GLFW
glut_dep = dependency('glut', required: true)    # GLFW
box2d_dep = dependency('box2d', required: true)   # Box2D
freetype_dep = dependency('freetype2', required: true)  # FreeType for font rendering

executable('evaluator_test', 'evaluator_test.c',
    dependencies: [gl_dep, glew_dep, glfw_dep, glut_dep], install: true)

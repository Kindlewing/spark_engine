package main

import "core:log"
import "core:os"
import gl "vendor:OpenGL"
import "vendor:glfw"

GLFW_MAJOR_VERSION :: 3
GLFW_MINOR_VERSION :: 3

WINDOW_WIDTH :: 800
WINDOW_HEIGHT :: 600
GL_VIEWPORT_WIDTH :: 800
GL_VIEWPORT_HEIGHT :: 600

process_input :: proc(window: glfw.WindowHandle) {
	if glfw.GetKey(window, glfw.KEY_ESCAPE) == glfw.PRESS {
		glfw.SetWindowShouldClose(window, true)
	}
}


main :: proc() {
	context.logger = log.create_console_logger()
	if !glfw.Init() {
		log.fatal("Unable to initialize GLFW")
		glfw.Terminate()
		return
	}
	log.debug("GLFW initialized successfully")
	glfw.WindowHint(glfw.RESIZABLE, true)
	glfw.WindowHint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)
	glfw.WindowHint(glfw.CONTEXT_VERSION_MAJOR, 3)
	glfw.WindowHint(glfw.CONTEXT_VERSION_MINOR, 3)

	log.debug("About to create the window")
	window := glfw.CreateWindow(800, 600, "Spark Engine", nil, nil)
	if window == nil {
		log.fatal("Error creating window")
		glfw.Terminate()
		return
	}
	log.debug("Window created successfully")
	glfw.MakeContextCurrent(window)


	log.debug("Loading GLAD procs")
	proc_addr := glfw.gl_set_proc_address
	gl.load_up_to(GLFW_MAJOR_VERSION, GLFW_MINOR_VERSION, proc_addr)
	log.debug("Set the viewport")
	gl.Viewport(0, 0, 800, 600)


	verticies := [9]f32{-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0}

	vbo: u32
	gl.GenBuffers(1, &vbo)
	gl.BindBuffer(gl.ARRAY_BUFFER, vbo)
	gl.BufferData(vbo, size_of(verticies), &verticies, gl.STATIC_DRAW)

	shader_vert_file: string = "shaders/triangle_vert.glsl"
	shader_src, ok := os.read_entire_file_from_filename(shader_vert_file)
	if !ok {
		log.fatalf("Err reading file\n")
	}

	v_shader: u32
	v_shader = gl.CreateShader(gl.VERTEX_SHADER)

	gl.ShaderSource(v_shader, 1, cast(^cstring)&shader_src, nil)
	gl.CompileShader(v_shader)

	// TODO: Fragment shader

	for !glfw.WindowShouldClose(window) {
		process_input(window)

		gl.ClearColor(18 / 255.0, 18 / 255.0, 18 / 255.0, 1)
		gl.Clear(gl.COLOR_BUFFER_BIT)

		glfw.SwapBuffers(window)
		glfw.PollEvents()
	}

	glfw.Terminate()
	return
}

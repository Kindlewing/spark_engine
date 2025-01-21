package main

import "core:log"
import "core:os"
import gl "vendor:OpenGL"
import "vendor:glfw"

GLFW_MAJOR_VERSION :: 3
GLFW_MINOR_VERSION :: 3

process_input :: proc(window: glfw.WindowHandle) {
	if glfw.GetKey(window, glfw.KEY_ESCAPE) == glfw.PRESS {
		glfw.SetWindowShouldClose(window, true)
	}
}


main :: proc() {
	context.logger = log.create_console_logger()
	glfw.Init()
	glfw.WindowHint(glfw.RESIZABLE, true)
	glfw.WindowHint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)
	glfw.WindowHint(glfw.CONTEXT_VERSION_MAJOR, 3)
	glfw.WindowHint(glfw.CONTEXT_VERSION_MINOR, 3)

	window := glfw.CreateWindow(800, 600, "Spark Engine", nil, nil)
	if window == nil {
		log.fatal("Error creating window")
		glfw.Terminate()
		return
	}
	glfw.MakeContextCurrent(window)

	proc_addr := glfw.gl_set_proc_address
	gl.load_up_to(GLFW_MAJOR_VERSION, GLFW_MINOR_VERSION, proc_addr)

	gl.Viewport(0, 0, 800, 600)


	verticies := [9]f32{-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0}

	vbo: u32
	gl.GenBuffers(1, &vbo)
	gl.BindBuffer(gl.ARRAY_BUFFER, vbo)
	gl.BufferData(vbo, size_of(verticies), &verticies, gl.STATIC_DRAW)


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

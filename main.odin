package main

import "core:log"
import "core:os"
import "spark"
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

resize_callback :: proc "c" (window: glfw.WindowHandle, width, height: i32) {
	gl.Viewport(0, 0, width, height)
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


	glfw.SetFramebufferSizeCallback(window, resize_callback)

	log.debug("Loading GLAD procs")
	proc_addr := glfw.gl_set_proc_address
	gl.load_up_to(GLFW_MAJOR_VERSION, GLFW_MINOR_VERSION, proc_addr)
	log.debug("Set the viewport")
	gl.Viewport(0, 0, 800, 600)

	// SHADERS
	vt_shader: u32 = spark.compile_vertex_shader("shaders/triangle_vert.glsl")
	fr_shader: u32 = spark.compile_fragment_shader("shaders/triangle_frag.glsl")

	shader_program: u32
	shader_program = gl.CreateProgram()
	gl.AttachShader(shader_program, vt_shader)
	gl.AttachShader(shader_program, fr_shader)
	gl.LinkProgram(shader_program)
	ok: i32
	info: [512]u8

	gl.GetProgramiv(shader_program, gl.LINK_STATUS, &ok)
	if (ok == 0) {
		gl.GetProgramInfoLog(shader_program, 512, nil, raw_data(&info))
		log.errorf("Shader program linking failed: %s\n", info)
	}
	gl.DeleteShader(vt_shader)
	gl.DeleteShader(fr_shader)

	// Setup buffer objects
	verticies := [9]f32{-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0}
	vbo: u32
	vao: u32
	gl.GenVertexArrays(1, &vao)
	gl.GenBuffers(1, &vbo)

	gl.BindVertexArray(vao)
	gl.BindBuffer(gl.ARRAY_BUFFER, vbo)
	gl.BufferData(vbo, size_of(verticies), &verticies, gl.STATIC_DRAW)


	gl.VertexAttribPointer(0, 3, gl.FLOAT, false, 3 * size_of(f32), 0)
	gl.EnableVertexAttribArray(0)


	for !glfw.WindowShouldClose(window) {
		gl.ClearColor(18 / 255.0, 18 / 255.0, 18 / 255.0, 1)
		gl.Clear(gl.COLOR_BUFFER_BIT)

		process_input(window)

		// UPDATE

		//END UPDATE

		// DRAWING
		gl.UseProgram(shader_program)
		gl.BindVertexArray(vao)
		gl.DrawArrays(gl.TRIANGLES, 0, 3)


		// END DRAWING

		glfw.SwapBuffers(window)
		glfw.PollEvents()
	}

	glfw.Terminate()
	return
}

package main

import "base:runtime"
import "core:log"
import "core:os"
import "spark"
import gl "vendor:OpenGL"
import "vendor:glfw"

GLFW_MAJOR_VERSION :: 4
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
	extern_context := runtime.Context {
		logger = context.logger,
	}

	if !glfw.Init() {
		log.fatal("Unable to initialize GLFW")
		glfw.Terminate()
		return
	}
	log.debug("GLFW initialized successfully")
	glfw.WindowHint(glfw.RESIZABLE, true)
	glfw.WindowHint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)
	glfw.WindowHint(glfw.CONTEXT_VERSION_MAJOR, GLFW_MAJOR_VERSION)
	glfw.WindowHint(glfw.CONTEXT_VERSION_MINOR, GLFW_MINOR_VERSION)

	when ODIN_DEBUG {
		glfw.WindowHint(glfw.OPENGL_DEBUG_CONTEXT, true)
		flags: i32
		if flags & gl.CONTEXT_FLAG_DEBUG_BIT == 1 {
			gl.Enable(gl.DEBUG_OUTPUT)
			gl.Enable(gl.DEBUG_OUTPUT_SYNCHRONOUS)
			gl.DebugMessageCallback(spark.gl_debug_output, &extern_context)
		}
	}
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
	gl.load_up_to(GLFW_MAJOR_VERSION, GLFW_MINOR_VERSION, proc(p: rawptr, name: cstring) {
		(^rawptr)(p)^ = glfw.GetProcAddress(name)
	})


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
	verticies := [?]f32{0.5, 0.5, 0.0, 0.5, -0.5, 0.0, -0.5, -0.5, 0.0, -0.5, 0.5, 0.0}
	indices := [?]u32{0, 1, 3, 1, 2, 3}
	vao: u32
	gl.GenVertexArrays(1, &vao)
	gl.BindVertexArray(vao)

	vbo: u32
	gl.GenBuffers(1, &vbo)
	gl.BindBuffer(gl.ARRAY_BUFFER, vbo)
	gl.BufferData(gl.ARRAY_BUFFER, size_of(verticies), &verticies, gl.STATIC_DRAW)

	ebo: u32
	gl.GenBuffers(1, &ebo)
	gl.BindBuffer(gl.ELEMENT_ARRAY_BUFFER, ebo)
	gl.BufferData(gl.ELEMENT_ARRAY_BUFFER, size_of(indices), &indices, gl.STATIC_DRAW)

	gl.VertexAttribPointer(0, 3, gl.FLOAT, false, 3 * size_of(f32), uintptr(0))
	gl.EnableVertexAttribArray(0)
	gl.UseProgram(shader_program)

	for !glfw.WindowShouldClose(window) {
		process_input(window)
		glfw.PollEvents()

		gl.ClearColor(18 / 255.0, 18 / 255.0, 18 / 255.0, 1)
		gl.Clear(gl.COLOR_BUFFER_BIT)

		// UPDATE

		//END UPDATE

		// DRAWING
		gl.UseProgram(shader_program)
		gl.BindVertexArray(vao)
		gl.BindBuffer(gl.ELEMENT_ARRAY_BUFFER, ebo)
		gl.DrawElements(gl.TRIANGLES, 6, gl.UNSIGNED_INT, cast(rawptr)cast(uintptr)0)


		// END DRAWING

		glfw.SwapBuffers(window)
	}

	glfw.Terminate()
	log.destroy_console_logger(context.logger)
	return
}

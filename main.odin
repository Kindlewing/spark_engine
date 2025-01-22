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


	verticies := [9]f32{-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0}

	vbo: u32
	gl.GenBuffers(1, &vbo)
	gl.BindBuffer(gl.ARRAY_BUFFER, vbo)
	gl.BufferData(vbo, size_of(verticies), &verticies, gl.STATIC_DRAW)


	// SHADERS
	shader_vt_file: string = "shaders/triangle_vert.glsl"
	shader_src_vt, vt_ok := os.read_entire_file_from_filename(shader_vt_file)
	if !vt_ok {
		log.fatalf("Err reading file\n")
	}

	vt_shader: u32
	fr_shaer: u32

	vt_shader = gl.CreateShader(gl.VERTEX_SHADER)
	gl.ShaderSource(vt_shader, 1, cast(^cstring)&shader_src_vt, nil)

	{
		log.debugf("About to compile shader defined in: %s\n", shader_vt_file)
		gl.CompileShader(vt_shader)
		ok: i32
		info: [512]u8
		gl.GetShaderiv(vt_shader, gl.COMPILE_STATUS, &ok)
		if ok == 0 {
			gl.GetShaderInfoLog(vt_shader, 512, nil, raw_data(&info))
			log.errorf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", info)
		}
	}

	shader_fr_file: string = "shaders/triangle_frag.glsl"
	shader_src_fr, fr_ok := os.read_entire_file_from_filename(shader_fr_file)
	if !fr_ok {
		log.fatalf("Err reading file\n")
	}
	log.debugf("Shader source:\n\n %s\n\n", shader_src_fr)
	fr_shader: u32
	fr_shader = gl.CreateShader(gl.FRAGMENT_SHADER)
	gl.ShaderSource(fr_shader, 1, cast(^cstring)&shader_src_fr, nil)

	{
		log.debugf("About to compile shader defined in: %s\n", shader_fr_file)
		gl.CompileShader(fr_shader)
		ok: i32
		info: [512]u8
		gl.GetShaderiv(fr_shader, gl.COMPILE_STATUS, &ok)
		if ok == 0 {
			gl.GetShaderInfoLog(fr_shader, 512, nil, raw_data(&info))
			log.errorf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", info)
		}
	}


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

package spark

import "core:log"
import "core:os"

import gl "vendor:OpenGL"

compile_vertex_shader :: proc(src: string) -> u32 {
	shader_src, ok := os.read_entire_file_from_filename(src)
	if !ok {
		log.fatalf("Err reading file\n")
	}
	shader: u32

	shader = gl.CreateShader(gl.VERTEX_SHADER)
	gl.ShaderSource(shader, 1, cast(^cstring)&shader_src, nil)

	{
		log.debugf("About to compile vertex shader defined in: %s\n", src)
		gl.CompileShader(shader)
		ok: i32
		info: [512]u8
		gl.GetShaderiv(shader, gl.COMPILE_STATUS, &ok)
		if ok == 0 {
			gl.GetShaderInfoLog(shader, 512, nil, raw_data(&info))
			log.errorf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", info)
		}
		log.debugf("Compilation of vertex shader successful.\n")
	}
	return shader
}

compile_fragment_shader :: proc(src: string) -> u32 {
	shader_src, ok := os.read_entire_file_from_filename(src)
	if !ok {
		log.fatalf("Err reading file\n")
	}
	shader: u32

	shader = gl.CreateShader(gl.FRAGMENT_SHADER)
	gl.ShaderSource(shader, 1, cast(^cstring)&shader_src, nil)

	{
		log.debugf("About to compile fragment shader defined in: %s\n", src)
		gl.CompileShader(shader)
		ok: i32
		info: [512]u8
		gl.GetShaderiv(shader, gl.COMPILE_STATUS, &ok)
		if ok == 0 {
			gl.GetShaderInfoLog(shader, 512, nil, raw_data(&info))
			log.errorf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", info)
		}
		log.debugf("Compilation of fragment shader successful.\n")
	}
	return shader

}

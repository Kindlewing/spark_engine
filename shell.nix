{ pkgs ? import <nixpkgs> { } }:

pkgs.mkShell {
	nativeBuildInputs = with pkgs; [
		eza
		lazygit
		# C specific things
		cmake
		gcc
		glib
		glfw-wayland
		wayland
		libxkbcommon
		xorg.libX11
		xorg.libXrandr
		xorg.libXinerama
		xorg.libXcursor
		xorg.libXi
	];
	env = {
		CC="${pkgs.gcc}/bin/gcc";
		CXX="${pkgs.gcc}/bin/gcc";
	};
}

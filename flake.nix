{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs, ... }@modules: let 
    system = "x86_64-linux";
    pkgs = import nixpkgs {inherit system;};

    # program = pkgs.stdenv.mkDerivation {
    #   pname = "celeste2";
    #   version = "1.0.0";
    #   src = pkgs.fetchFromGithub {
    #     owner = "ExOK";
    #     repo = "Celeste2";
    #     rev = "f3820ba29c04e63813815c898dac60b18a3a8bd5";
    #     hash = "";
    #   };
    # };

    program = pkgs.callPackage ./app.nix {inherit self;};
  in {
    packages.${system}.default = program;
    devShells.${system}.default = pkgs.mkShell {
      buildInputs = with pkgs; [
        lua
        glfw3
        sfml
        fluidsynth
        poco
        lua
        libGLU
        glew
        openal
        flac
        xorg.libxcb
        xorg.xcbutil
        xorg.libXinerama
        xorg.libX11
        xorg.libXrandr 
        xorg.libXrender 
        xorg.xcbutilimage
        udev
        glib
        freetype
        libvorbis
      ];
    };
  };
}

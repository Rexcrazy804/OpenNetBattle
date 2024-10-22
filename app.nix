{ self
, stdenv
, fetchFromGitHub
, pkg-config
, cmake
, lua
, xorg
, glfw3
, sfml
, fluidsynth
, poco
, libGLU
, glew
, openal
, freetype
, udev
, flac
, glib
, libvorbis
}: stdenv.mkDerivation {
  pname = "open-battle-network";
  version = "2.0.0";
  src = self;

  # src = fetchFromGitHub {
  #   owner = "TheMaverickProgrammer";
  #   repo = "OpenNetBattle";
  #   rev = "1dbf7dbcc993c9f32445b77c70e2589a34a53d59";
  #   hash = "sha256-g0gXbJdUAYUysICjKnkOcZnU6+Jn1uVHprkWnF8srsY=";
  #   fetchSubmodules = true;

  #   postFetch = ''
  #     # i have no words for this
  #     substituteInPlace $out/BattleNetwork/bnHitProperties.h \
  #       --replace-fail "// forward declare" "#include <cstdint>"
  #   '';
  # };

  nativeBuildInputs = [
    cmake
    pkg-config
  ];

  buildInputs = [
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

  # some gcc13 compatibility
  CXXFLAGS = "-Wno-changes-meaning";
}

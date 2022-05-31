{
  description = "Planetary Toy";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-22.05";
    flake-utils.url = "github:numtide/flake-utils";

    tinycmmc.url = "github:grumbel/tinycmmc";
    tinycmmc.inputs.nixpkgs.follows = "nixpkgs";
    tinycmmc.inputs.flake-utils.follows = "flake-utils";

    logmich.url = "github:logmich/logmich";
    logmich.inputs.nixpkgs.follows = "nixpkgs";
    logmich.inputs.flake-utils.follows = "flake-utils";
    logmich.inputs.tinycmmc.follows = "tinycmmc";

    geomcpp.url = "github:grumbel/geomcpp";
    geomcpp.inputs.nixpkgs.follows = "nixpkgs";
    geomcpp.inputs.flake-utils.follows = "flake-utils";
    geomcpp.inputs.tinycmmc.follows = "tinycmmc";
  };

  outputs = { self, nixpkgs, flake-utils, tinycmmc, logmich, geomcpp }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        version_file = pkgs.lib.fileContents ./VERSION;
        gravisolar_has_version = ((builtins.substring 0 1) version_file) == "v";
        gravisolar_version = if !gravisolar_has_version
                           then ("0.1.0-${nixpkgs.lib.substring 0 8 self.lastModifiedDate}-${self.shortRev or "dirty"}")
                           else (builtins.substring 1 ((builtins.stringLength version_file) - 2) version_file);
       in rec {
         packages = flake-utils.lib.flattenTree rec {
           gravisolar = pkgs.stdenv.mkDerivation rec {
             pname = "gravisolar";
             version = gravisolar_version;
             src = nixpkgs.lib.cleanSource ./.;
             postPatch = ''
                if ${if gravisolar_has_version then "false" else "true"}; then
                  echo "${version}" > VERSION
                fi
                substituteInPlace CMakeLists.txt \
                  --replace "appstream-util" "appstream-util --nonet"
             '';
             cmakeFlags = [
               "-DWARNINGS=ON"
               "-DWERROR=ON"
               "-DBUILD_TESTS=ON"
             ];
             doCheck = true;
             postFixup = ''
               wrapProgram $out/bin/gravisolar \
                  --prefix LIBGL_DRIVERS_PATH ":" "${pkgs.mesa.drivers}/lib/dri" \
                  --prefix LD_LIBRARY_PATH ":" "${pkgs.mesa.drivers}/lib"
             '';
             nativeBuildInputs = with pkgs; [
               cmake
               makeWrapper
               pkgconfig
             ];
             checkInputs = with pkgs; [
               appstream-glib
             ];
             buildInputs = with pkgs; [
               fmt
               glm
               libGL
               libGLU
               SDL
             ] ++ [
               geomcpp.defaultPackage.${system}
               logmich.defaultPackage.${system}
               tinycmmc.defaultPackage.${system}
             ];
           };
        };
        defaultPackage = packages.gravisolar;
      });
}

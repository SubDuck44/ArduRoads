{
  outputs = { flake-utils, nixpkgs, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
        inherit (pkgs.lib.fileset) toSource unions;
        stdenv = pkgs.gccStdenv; # pkgs.clangStdenv;
      in
      rec {
        packages.default = stdenv.mkDerivation {
          pname = "arduino";
          version = "0.0.1";

          src = toSource {
            root = ./.;
            fileset = unions [
              ./src
            ];
          };

          nativeBuildInputs = with pkgs; [
            arduino-cli
          ];

          buildInputs = with pkgs; [
          ];
        };

        devShells.default = (pkgs.mkShell.override {
          inherit stdenv;
        }) {
          inputsFrom = [ packages.default ];
          packages = with pkgs; [
            arduino-language-server
            avrdude
            clang-tools
            just
            minicom
            usbutils
          ];
        };
      });
}

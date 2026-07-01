{
  outputs = { flake-utils, nixpkgs, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let pkgs = import nixpkgs { inherit system; }; in
      rec {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            arduino-cli
            avrdude
            usbutils
          ];
        };
      });
}

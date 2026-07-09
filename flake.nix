{
  outputs = { flake-utils, nixpkgs, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let pkgs = import nixpkgs { inherit system; }; in {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            arduino-cli
            avrdude
            bear
            clang-tools
            just
            picocom
            pkgsCross.avr.gcc # why is nix so based
            usbutils
          ];
        };
      });
}

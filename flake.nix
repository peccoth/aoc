{
  description = "A very basic flake";
  inputs.nixpkgs.url = "github:Nixos/nixpkgs/nixos-23.11";

  outputs = { self, nixpkgs }: 
  let
    system = "x86_64-linux";
    pkgs = import nixpkgs {
      inherit system;
    };
  in {
    devShells."x86_64-linux".default = pkgs.mkShell rec {
      name = "AOC Shell";
      buildInputs = with pkgs; [
        harePackages.hare
      ];

      buildPhase = ''
        make
      '';
    };
  };
}

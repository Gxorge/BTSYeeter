# Builds a .zip file for loading with BMBF
& $PSScriptRoot/build.ps1

if ($?) {
    Compress-Archive -Path "./libs/arm64-v8a/libbts-yeeter.so", "./bmbfmod.json" -DestinationPath "./bts-yeeter_v0.2.0.zip" -Update
}

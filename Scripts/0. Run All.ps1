Param(
    [String]$RootPath = "D:\Upscaling"
)

# Load the relevant DLL files
[Reflection.Assembly]::LoadWithPartialName(“System.IO”) | Out-Null

# Set the "default" path to the path of the script
$scriptpath = $MyInvocation.MyCommand.Path
$dir = Split-Path $scriptpath
cd $dir 

$ISO1Location = "$RootPath\ROMS\English\Utena_English1.iso"
$ISO2Location = "$RootPath\ROMS\English\Utena_English2.iso"
$RootOutputFolder = "$RootPath\Output"

$TempDir = [System.IO.Path]::Combine($RootOutputFolder, "temp")
$ROM1OutputDir = [System.IO.Path]::Combine($TempDir, "ROM1")
$ROM2OutputDir = [System.IO.Path]::Combine($TempDir, "ROM2")


& '.\1. Initial Extract and Clean.ps1' -RootPath $RootPath
& '.\2. Convert Images.ps1' -RootPath $RootPath

& '.\3. Convert Audio.ps1' -RootPath $RootPath

& '.\4. Convert Videos.ps1' -RootPath $RootPath

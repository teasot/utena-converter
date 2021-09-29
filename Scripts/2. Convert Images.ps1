Param(
    [String]$RootPath = "C:\Users\Anthony\Documents\GitHub\utena-converter"
)

# Load the relevant DLL files
[Reflection.Assembly]::LoadWithPartialName(“System.IO”) | Out-Null

# Set the "default" path to the path of the script
$scriptpath = $MyInvocation.MyCommand.Path
$dir = Split-Path $scriptpath
cd $dir 

[String]$ISO1Location = "$RootPath\ROMS\English\Utena_English1.iso"
[String]$RootOutputFolder = "$RootPath\Output"

# Extract ROM files
& '..\tools\utena translator 1.04\utena.exe' extract_all_images $ISO1Location $RootOutputFolder
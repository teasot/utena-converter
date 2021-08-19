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

# Clear Output directory
Get-ChildItem -Path $RootOutputFolder -Recurse| Foreach-object {Remove-item -Recurse -path $_.FullName }

# Extract ISO 1
& "C:\Program Files\7-Zip\7z.exe" x "$ISO1Location" -o"$ROM1OutputDir"

# Extract ISO 2
& "C:\Program Files\7-Zip\7z.exe" x "$ISO2Location" -o"$ROM2OutputDir"
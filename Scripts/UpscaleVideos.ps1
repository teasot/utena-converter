Param(
    $scale = 3
)

# Load the relevant DLL files
[Reflection.Assembly]::LoadWithPartialName(“System.IO”) | Out-Null

# Set the "default" path to the path of the script
$scriptpath = $MyInvocation.MyCommand.Path
$dir = Split-Path $scriptpath
cd $dir 

# Set the source and target directories for "MOVIE"
$SourceDirectory = "$dir\Utena ROM\SSCD\MOVIE"
$TargetDirectory = "$dir\Output\SSCD\MOVIE"
$UpscaleDirectory = "$dir\Output\SSCD\MOVIE\Upscaled"

# Get the movie files in the source directory
$DirectoryFiles = Get-ChildItem $SourceDirectory

# Loop through each file
foreach ($File in $DirectoryFiles){
    $NameWithoutExtension = $File.Name.Replace($File.Extension, "")
    $TargetFile = $TargetDirectory + "\" + $NameWithoutExtension + ".mp4"
    $UpscaleFile = $UpscaleDirectory + "\" + $NameWithoutExtension + ".mp4"

    Copy-Item -Path $File.FullName -Destination $TargetFile
    cd ../tools/video2x-4.8.1-win32-full
    ./video2x.exe -i $TargetFile -o $UpscaleFile -r $scale -d waifu2x_caffe
    cd ..
    # Navigate up a folder
}
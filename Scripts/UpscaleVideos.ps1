Param(
    [String]$RootPath = "D:\Upscaling",
    $scale = 2
)

# Load the relevant DLL files
[Reflection.Assembly]::LoadWithPartialName(“System.IO”) | Out-Null

# Set the "default" path to the path of the script
$scriptpath = $MyInvocation.MyCommand.Path
$dir = Split-Path $scriptpath
cd $dir 

# Set the source and target directories for "MOVIE"
$SourceDirectory = "$RootPath\Output\SSCD\MOVIE"
$UpscaleDirectory = "$RootPath\Output\SSCD\MOVIE\Upscaled"

# Create the output directory if it doesn't exist
if([System.IO.Directory]::Exists($UpscaleDirectory) -eq $false){
    [System.IO.Directory]::CreateDirectory($UpscaleDirectory)
}

# Get the movie files in the source directory
$DirectoryFiles = Get-ChildItem $SourceDirectory

# Loop through each file
foreach ($File in $DirectoryFiles){
    if($File.Extension -eq ".webm"){
        # Output name of video
        Write-Host "Converting Video:"
        Write-Host $File.FullName

        # Define Input and upscaled file paths
        $NameWithoutExtension = $File.Name.Replace($File.Extension, "")
        $TargetFile = $File.FullName
        $UpscaleFile = $UpscaleDirectory + "\" + $NameWithoutExtension + ".mp4"

        # Convert the file
        cd "$RootPath\tools\video2x-4.8.1-win32-full"
        ./video2x.exe -i $TargetFile -o $UpscaleFile -r $scale -d waifu2x_caffe
        cd ..
    }
}
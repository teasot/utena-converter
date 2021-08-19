Param(
    [String]$RootPath = "D:\Upscaling"
)

# Load the relevant DLL files
[Reflection.Assembly]::LoadWithPartialName(“System.IO”) | Out-Null

# Set the "default" path to the path of the script
$scriptpath = $MyInvocation.MyCommand.Path
$dir = Split-Path $scriptpath
cd $dir 

[String]$RootOutputFolder = "$RootPath\Output"

# Derive the temp and ROM directories from the Root Directory
$TempDir = [System.IO.Path]::Combine($RootOutputFolder, "temp")
$ROM1OutputDir = [System.IO.Path]::Combine($TempDir, "ROM1")
$ROM2OutputDir = [System.IO.Path]::Combine($TempDir, "ROM2")


# Set the source directories from each ROM
$SourceDirectories = [System.IO.Path]::Combine($ROM1OutputDir, "SSCD\MOVIE"), [System.IO.Path]::Combine($ROM2OutputDir, "SSCD\MOVIE")

# Set the target directory
$TargetDirectory = "$RootOutputFolder\SSCD\MOVIE"

if(![System.IO.Directory]::Exists($TargetDirectory)){
    [System.IO.Directory]::CreateDirectory($TargetDirectory)
}

foreach($SourceDirectory in $SourceDirectories){
    $MovieFiles = Get-ChildItem $SourceDirectory
    foreach($MovieFile in $MovieFiles){
        # Only fetch .CAK files: there are a few ACX files in the directory too which are handled by the audio converter
        if($MovieFile.Extension -eq ".CAK"){
            # Generate the target file name
            $NameWithoutExtension = $MovieFile.Name.Replace($MovieFile.Extension, "")

            # We want a .webm file cos its relatively common, and more specifically is usable in the .webm player I am using for GameMaker
            $TargetFile = $TargetDirectory + "\" + $NameWithoutExtension + ".webm"
            #$TargetFile = $TargetDirectory + "\" + $NameWithoutExtension + ".mp4"

            $SourceFile = $MovieFile.FullName
            if(![System.IO.File]::Exists($TargetFile)){
                # Convert the movie using ffmpeg
                ..\tools\ffmpeg-4.4-full_build\bin\ffmpeg.exe -i "$SourceFile" -c:v libvpx-vp9 -lossless 1  -pix_fmt yuv420p -acodec libvorbis "$TargetFile"
                 
            }
        }
    }
}
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

$TempDir = [System.IO.Path]::Combine($RootOutputFolder, "temp")
$ROM1OutputDir = [System.IO.Path]::Combine($TempDir, "ROM1")
$ROM2OutputDir = [System.IO.Path]::Combine($TempDir, "ROM2")

$SourceDirectories = "$ROM1OutputDir\SSCD\BGM",
"$ROM1OutputDir\SSCD\VOICE",
"$ROM1OutputDir\SSCD\MOVIE",
"$ROM1OutputDir\SSCD\SE",
"$ROM2OutputDir\SSCD\BGM",
"$ROM2OutputDir\SSCD\VOICE",
"$ROM2OutputDir\SSCD\MOVIE",
"$ROM2OutputDir\SSCD\SE"

$TargetDirectories = "$RootOutputFolder\SSCD\BGM",
"$RootOutputFolder\SSCD\VOICE",
"$RootOutputFolder\SSCD\MOVIE",
"$RootOutputFolder\SSCD\SE",
"$RootOutputFolder\SSCD\BGM",
"$RootOutputFolder\SSCD\VOICE",
"$RootOutputFolder\SSCD\MOVIE",
"$RootOutputFolder\SSCD\SE"


for ($i=0; $i -lt $SourceDirectories.Count; $i++) {
    $SourceDirectory = $SourceDirectories[$i]
    $TargetDirectory = $TargetDirectories[$i]

    $DirectoryFiles = Get-ChildItem $SourceDirectory
    
    # Loop through each file
    foreach ($File in $DirectoryFiles){
        if($File.Extension -eq ".ACX"){
            $NameWithoutExtension = $File.Name.Replace($File.Extension, "")
            $SourceArchive = $File.FullName
            $ACXDirectory = $TargetDirectory + "\" + $NameWithoutExtension
            ..\tools\ACXTool\ACXTool.exe -u $SourceArchive $ACXDirectory

            $ADXFiles = Get-ChildItem $ACXDirectory
            foreach($ADXFile in $ADXFiles){
                $NameWithoutExtension = $ADXFile.Name.Replace($ADXFile.Extension, "")

                $DirectoryName = [System.IO.Path]::GetFileName($ACXDirectory);
                $AudioIndex = [System.Int32]::Parse($NameWithoutExtension) + 1;
                
                $Prefix = ""
                if($AudioIndex -lt 10){
                    $Prefix = "00"
                }
                elseif($AudioIndex -lt 100){
                    $Prefix = "0"
                }
                $NameWithoutExtension = $DirectoryName + $Prefix + $AudioIndex.ToString()


                $WavFilePath = $ACXDirectory + "\" + $NameWithoutExtension + ".wav"
                $OGGFilePath = $ACXDirectory + "\" + $NameWithoutExtension + ".ogg"
                $ADXFilePath = $ADXFile.FullName

                Write-Host "Writing $WavFilePath"
                if(![System.IO.File]::Exists($WavFilePath)){
                    ..\tools\ADXDecode\radx_decode.exe $ADXFilePath $WavFilePath
                }
                if(![System.IO.File]::Exists($OGGFilePath)){
                    ..\tools\ffmpeg-4.4-full_build\bin\ffmpeg.exe -i "$WavFilePath" -acodec libvorbis "$OGGFilePath"
                }
                Remove-Item $ADXFile.FullName
                # Keep wav just in case I learn audio_create_buffer_sound, though it looks tough
                Remove-Item $WavFilePath
                
            }
        }
        elseif($File.Extension -eq ".ADX"){
            $NameWithoutExtension = $File.Name.Replace($File.Extension, "")
            $SourceFile = $File.FullName
            $WavFilePath = $TargetDirectory + "\" + $NameWithoutExtension + ".wav"
            $OGGFilePath = $TargetDirectory + "\" + $NameWithoutExtension + ".ogg"
        
a
            Write-Host "Writing $WavFilePath"
            if(![System.IO.File]::Exists($WavFilePath)){
                ..\tools\ADXDecode\radx_decode.exe $SourceFile $WavFilePath
            }
            if(![System.IO.File]::Exists($OGGFilePath)){
                ..\tools\ffmpeg-4.4-full_build\bin\ffmpeg.exe -i "$WavFilePath" -acodec libvorbis "$OGGFilePath"
            }
            # Keep wav just in case I learn audio_create_buffer_sound, though it looks tough
            Remove-Item $WavFilePath
        }
    }
}
Param(
    [String]$RootPath = "D:\Upscaling"
)
[Reflection.Assembly]::LoadWithPartialName(“System.Windows.Forms”) | Out-Null
[Reflection.Assembly]::LoadWithPartialName(“System.IO”) | Out-Null

$scriptpath = $MyInvocation.MyCommand.Path
$dir = Split-Path $scriptpath
cd $dir 

$RootPath = [System.IO.Directory]::GetParent($dir)

# Set the source and target directories for "BG"
# Make sure to include $dir, not relative paths as it causes issues when converting the BMP files
$SourceDirectories = "$RootPath\Output\SSCD\ROSE",
"$RootPath\Output\SSCD\NAMETAG"

for($i = 0; $i -lt $SourceDirectories.Count; $i++){
    # Loop through each file
    $SourceDirectory = $SourceDirectories[$i]
    $DirectoryFiles = Get-ChildItem $SourceDirectory
    foreach ($File in $DirectoryFiles){
        # Get the file name without an extension - i.e. "MyFile" instead of "MyFile.DGP"
        $NameWithoutExtension = $File.Name.Replace($File.Extension, "")

        if($SourceDirectory -eq "$RootPath\Output\SSCD\NAMETAG"){
            $Number = [System.Int32]::Parse($NameWithoutExtension.Substring(5, 2))
            Write-Host $Number
            if($Number -eq 1 -or $Number -gt 8){
                $NameWithoutExtension = $NameWithoutExtension.Substring(0, 7)
            }
        }
        # Set the file names
        $SourceFile = $SourceDirectory + "\" + $File.Name
        $TargetFile = $SourceDirectory + "\" + $NameWithoutExtension + ".png"

        # Remove background and convert
        if($NameWithoutExtension -eq "NAME_37"){
            & "$RootPath\tools\ImageMagick\magick.exe" convert $SourceFile -transparent "rgb(0,8,0)" $TargetFile
        }
        else{
            & "$RootPath\tools\ImageMagick\magick.exe" convert $SourceFile -transparent "rgb(0,0,0)" $TargetFile
        }

        Remove-Item $SourceFile
    }
}

$MiscellaneousBlackFiles = "$RootPath\Output\SSCD\UTENASYS_00001828.bmp",
"$RootPath\Output\SSCD\UTENASYS_00000040.bmp",
"$RootPath\Output\SSCD\UTENASYS_00002570.bmp",
"$RootPath\Output\SSCD\UTENASYS_00004274.bmp",
"$RootPath\Output\SSCD\KEDAKASA_00000D3C.bmp",
"$RootPath\Output\SSCD\KEDAKASA_0000AC0C.bmp",
"$RootPath\Output\SSCD\KEDAKASA_0000DE1C.bmp",
"$RootPath\Output\SSCD\KEDAKASA_0000004C.bmp",
"$RootPath\Output\SSCD\KEDAKASA_000008EC.bmp",
"$RootPath\Output\SSCD\KEDAKASA_000015DC.bmp",
"$RootPath\Output\SSCD\KEDAKASA_000047EC.bmp",
"$RootPath\Output\SSCD\KEDAKASA_0000049C.bmp",
"$RootPath\Output\SSCD\KEDAKASA_000079FC.bmp",
"$RootPath\Output\SSCD\KEDAKASA_0000118C.bmp",
"$RootPath\Output\SSCD\KEDAKASA_0001102C.bmp",
"$RootPath\Output\SSCD\KEDAKASA_0001423C.bmp",
"$RootPath\Output\SSCD\MENU_00000A20.bmp",
"$RootPath\Output\SSCD\MENU_00000AD0.bmp",
"$RootPath\Output\SSCD\MENU_00000B80.bmp",
"$RootPath\Output\SSCD\MENU_000006B0.bmp",
"$RootPath\Output\SSCD\MENU_000008C0.bmp",
"$RootPath\Output\SSCD\MENU_00000044.bmp",
"$RootPath\Output\SSCD\MENU_00000760.bmp",
"$RootPath\Output\SSCD\MENU_00000810.bmp",
"$RootPath\Output\SSCD\MENU_00000970.bmp",
"$RootPath\Output\SSCD\PAUSE_000000EC.bmp",
"$RootPath\Output\SSCD\PAUSE_000002FC.bmp",
"$RootPath\Output\SSCD\PAUSE_0000003C.bmp",
"$RootPath\Output\SSCD\PAUSE_000003AC.bmp",
"$RootPath\Output\SSCD\PAUSE_0000019C.bmp",
"$RootPath\Output\SSCD\PAUSE_0000024C.bmp",
"$RootPath\Output\SSCD\PAUSE_0000045C.bmp",
"$RootPath\Output\SSCD\PAUSE_0000050C.bmp"

$MiscellaneousGreenFiles = "$RootPath\Output\SSCD\UTENASYS_0000EA04.bmp",
"$RootPath\Output\SSCD\UTENASYS_0000EAEC.bmp",
"$RootPath\Output\SSCD\UTENASYS_0000EBD4.bmp",
"$RootPath\Output\SSCD\UTENASYS_0000ECBC.bmp"
"$RootPath\Output\SSCD\UTENASYS_0000EDA4.bmp"
"$RootPath\Output\SSCD\UTENASYS_0000EE8C.bmp"
"$RootPath\Output\SSCD\UTENASYS_0000EF74.bmp"
"$RootPath\Output\SSCD\UTENASYS_0000F05C.bmp"

$SourceDirectory = "$RootPath\Output\SSCD\"

$MiscellaneousFiles = $MiscellaneousBlackFiles + $MiscellaneousGreenFiles

$DirectoryFiles = Get-ChildItem $MiscellaneousFiles
foreach ($File in $DirectoryFiles){
    $NameWithoutExtension = $File.Name.Replace($File.Extension, "")
    # Set the file names
    $SourceFile = $SourceDirectory + "\" + $File.Name
    $TargetFile = $SourceDirectory + "\" + $NameWithoutExtension + ".png"
    $File.FullName
    # Remove background and convert
    if($MiscellaneousGreenFiles.Contains($File.FullName)){
        & "$RootPath\tools\ImageMagick\magick.exe" convert $SourceFile -transparent "rgb(0,248,0)" $TargetFile
    }
    else{
        & "$RootPath\tools\ImageMagick\magick.exe" convert $SourceFile -transparent "rgb(0,0,0)" $TargetFile
    }
}

# Convert sprites
$SourceDirectory = "$RootPath\Output\SSCD\FC"
$DirectoryFiles = Get-ChildItem $SourceDirectory

foreach ($File in $DirectoryFiles){
    $NameWithoutExtension = $File.Name.Replace($File.Extension, "")
    # Set the file names
    $SourceFile = $SourceDirectory + "\" + $File.Name
    $TargetFile = $SourceDirectory + "\" + $NameWithoutExtension + ".png"
    $File.FullName
    # Remove background and convert
    if($NameWithoutExtension.StartsWith("FC01")){
        & "$RootPath\tools\ImageMagick\magick.exe" convert $SourceFile -transparent "rgb(0,0,248)" $TargetFile
    }
    else{
        & "$RootPath\tools\ImageMagick\magick.exe" convert $SourceFile -transparent "rgb(0,248,0)" $TargetFile
    }
}
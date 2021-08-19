# utena-converter
Converter for RGU game images, audio and movies.

WARNING:

Running these scripts can take 5+ hours depending on hardware. 

PREREQUISITES:
1. Create the following folders:

Output
ROMS\English
ROMS\Japanese

2. Copy your ROMS ripped from a legally purchased copy of the game, with the translated english ROMs going to ROMS\English:

ROMS\English\Utena_English1.iso
ROMS\English\Utena_English2.iso
ROMS\English\Utena_Sega1.iso
ROMS\English\Utena_Sega2.iso

3. Download ffmpeg-4.4-full_build, and extract its contents/install it to the following folder:

tools\ffmpeg-4.4-full_build

4. Ensure you have 7zip installed, and modify the following scripts to point to its executable:

Scripts\1. Initial Extract and Clean.ps1

5. Modify the RootPath parameter of the following script to your path containing the repository:

Scripts\0. Run All.ps1

6. Run the following script, being aware that it will throw some unskippable errors and take SEVERAL HOURS to complete:

Scripts\0. Run All.ps1


@echo off

:: Replace these values with desired name for your character. Otherwise, the (limited) one from game input will be used.
set name=default
set surname=default

:: Disc 1
echo --------Translating Disc 1--------
utena translate Utena_Sega1.iso Utena_English1.iso utena_eng.ini %name% %surname%
IF %ERRORLEVEL% NEQ 0 (
   set /p=Press ENTER to continue...
   EXIT
)
utena insert_mato Utena_English1.iso /SSCD/CHG.TEX resources_english/SSCD/CHG unused true
utena insert_mato Utena_English1.iso /SSCD/ST_MENU.TEX resources_english/SSCD/ST_MENU
utena insert_mato Utena_English1.iso /SSCD/SAVEP.TEX resources_english/SSCD/SAVEP false
utena insert_lzss_dc Utena_English1.iso /SSCD/BG/BG_NINP2.DGP resources_english/SSCD/BG/BG_NINP2.bmp
utena insert_lzss_dc Utena_English1.iso /SSCD/EV/EVA32.DGP resources_english/SSCD/EV/EVA32.bmp
utena insert_lzss_dc Utena_English1.iso /SSCD/EV/EVA32B.DGP resources_english/SSCD/EV/EVA32B.bmp
utena insert_lzss_dc Utena_English1.iso /SSCD/EV/EVD113.DGP resources_english/SSCD/EV/EVD113.bmp
utena insert_lzss_dc Utena_English1.iso /SSCD/EV/EVD114.DGP resources_english/SSCD/EV/EVD114.bmp
utena insert_lzss_mato Utena_English1.iso /SSCD/SPECIAL/NAMEINP.TEP resources_english/SSCD/SPECIAL/NAMEINP false true
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/DT22.DG2 resources_english/SSCD/PLACETAG/DT22.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/DT23.DG2 resources_english/SSCD/PLACETAG/DT23.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/DT24.DG2 resources_english/SSCD/PLACETAG/DT24.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/DT25.DG2 resources_english/SSCD/PLACETAG/DT25.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/DT26.DG2 resources_english/SSCD/PLACETAG/DT26.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT00.DG2 resources_english/SSCD/PLACETAG/PT00.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT01.DG2 resources_english/SSCD/PLACETAG/PT01.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT02.DG2 resources_english/SSCD/PLACETAG/PT02.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT03.DG2 resources_english/SSCD/PLACETAG/PT03.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT04.DG2 resources_english/SSCD/PLACETAG/PT04.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT05.DG2 resources_english/SSCD/PLACETAG/PT05.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT06.DG2 resources_english/SSCD/PLACETAG/PT06.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT07.DG2 resources_english/SSCD/PLACETAG/PT07.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT08.DG2 resources_english/SSCD/PLACETAG/PT08.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT09.DG2 resources_english/SSCD/PLACETAG/PT09.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT10.DG2 resources_english/SSCD/PLACETAG/PT10.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT11.DG2 resources_english/SSCD/PLACETAG/PT11.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT12.DG2 resources_english/SSCD/PLACETAG/PT12.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT13.DG2 resources_english/SSCD/PLACETAG/PT13.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT14.DG2 resources_english/SSCD/PLACETAG/PT14.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT15.DG2 resources_english/SSCD/PLACETAG/PT15.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT16.DG2 resources_english/SSCD/PLACETAG/PT16.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT17.DG2 resources_english/SSCD/PLACETAG/PT17.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT18.DG2 resources_english/SSCD/PLACETAG/PT18.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT19.DG2 resources_english/SSCD/PLACETAG/PT19.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT20.DG2 resources_english/SSCD/PLACETAG/PT20.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT21.DG2 resources_english/SSCD/PLACETAG/PT21.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT22.DG2 resources_english/SSCD/PLACETAG/PT22.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT23.DG2 resources_english/SSCD/PLACETAG/PT23.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT24.DG2 resources_english/SSCD/PLACETAG/PT24.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT25.DG2 resources_english/SSCD/PLACETAG/PT25.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT26.DG2 resources_english/SSCD/PLACETAG/PT26.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT27.DG2 resources_english/SSCD/PLACETAG/PT27.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT28.DG2 resources_english/SSCD/PLACETAG/PT28.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT29.DG2 resources_english/SSCD/PLACETAG/PT29.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT30.DG2 resources_english/SSCD/PLACETAG/PT30.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT31.DG2 resources_english/SSCD/PLACETAG/PT31.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT32.DG2 resources_english/SSCD/PLACETAG/PT32.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT33.DG2 resources_english/SSCD/PLACETAG/PT33.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT34.DG2 resources_english/SSCD/PLACETAG/PT34.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT35.DG2 resources_english/SSCD/PLACETAG/PT35.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT36.DG2 resources_english/SSCD/PLACETAG/PT36.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT37.DG2 resources_english/SSCD/PLACETAG/PT37.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT38.DG2 resources_english/SSCD/PLACETAG/PT38.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT39.DG2 resources_english/SSCD/PLACETAG/PT39.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT40.DG2 resources_english/SSCD/PLACETAG/PT40.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT41.DG2 resources_english/SSCD/PLACETAG/PT41.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT42.DG2 resources_english/SSCD/PLACETAG/PT42.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT43.DG2 resources_english/SSCD/PLACETAG/PT43.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT44.DG2 resources_english/SSCD/PLACETAG/PT44.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT45.DG2 resources_english/SSCD/PLACETAG/PT45.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT46.DG2 resources_english/SSCD/PLACETAG/PT46.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT47.DG2 resources_english/SSCD/PLACETAG/PT47.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT48.DG2 resources_english/SSCD/PLACETAG/PT48.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT49.DG2 resources_english/SSCD/PLACETAG/PT49.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT50.DG2 resources_english/SSCD/PLACETAG/PT50.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT51.DG2 resources_english/SSCD/PLACETAG/PT51.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT52.DG2 resources_english/SSCD/PLACETAG/PT52.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT53.DG2 resources_english/SSCD/PLACETAG/PT53.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT54.DG2 resources_english/SSCD/PLACETAG/PT54.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT55.DG2 resources_english/SSCD/PLACETAG/PT55.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT56.DG2 resources_english/SSCD/PLACETAG/PT56.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT57.DG2 resources_english/SSCD/PLACETAG/PT57.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT58.DG2 resources_english/SSCD/PLACETAG/PT58.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT59.DG2 resources_english/SSCD/PLACETAG/PT59.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT60.DG2 resources_english/SSCD/PLACETAG/PT60.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT61.DG2 resources_english/SSCD/PLACETAG/PT61.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT62.DG2 resources_english/SSCD/PLACETAG/PT62.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT63.DG2 resources_english/SSCD/PLACETAG/PT63.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT64.DG2 resources_english/SSCD/PLACETAG/PT64.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT65.DG2 resources_english/SSCD/PLACETAG/PT65.bmp 0 fix_palette
utena insert_pp Utena_English1.iso /SSCD/PLACETAG/PT66.DG2 resources_english/SSCD/PLACETAG/PT66.bmp 0 fix_palette
utena insert_mato Utena_English1.iso /SSCD/TECHOU/TEB.TEX resources_english/SSCD/TECHOU/TEB fix_palette true
utena insert_mato Utena_English1.iso /SSCD/TECHOU/TEP06.TEX resources_english/SSCD/TECHOU/TEP06 fix_palette true
utena insert_mato Utena_English1.iso /SSCD/TECHOU/TEP07.TEX resources_english/SSCD/TECHOU/TEP07 fix_palette true
utena insert_mato Utena_English1.iso /SSCD/TECHOU/TES06.TEX resources_english/SSCD/TECHOU/TES06 fix_palette true
utena insert_mato Utena_English1.iso /SSCD/TECHOU/TES07.TEX resources_english/SSCD/TECHOU/TES07 fix_palette true
utena insert_mato Utena_English1.iso /SSCD/TECHOU/TES08.TEX resources_english/SSCD/TECHOU/TES08 fix_palette true
utena replace_file Utena_English1.iso /0.BIN resources_english/0.BIN
echo --------Disc 1 translated--------

:: Disc2
echo --------Translating Disc 2--------
utena translate Utena_Sega2.iso Utena_English2.iso utena_eng.ini %name% %surname%
IF %ERRORLEVEL% NEQ 0 (
   set /p=Press ENTER to continue...
   EXIT
)
utena insert_mato Utena_English2.iso /SSCD/CHG.TEX resources_english/SSCD/CHG unused true
utena insert_mato Utena_English2.iso /SSCD/ST_MENU.TEX resources_english/SSCD/ST_MENU
utena insert_mato Utena_English2.iso /SSCD/SAVEP.TEX resources_english/SSCD/SAVEP false
utena insert_lzss_dc Utena_English2.iso /SSCD/BG/BG_NINP2.DGP resources_english/SSCD/BG/BG_NINP2.bmp
utena insert_lzss_dc Utena_English2.iso /SSCD/EV/EVA32.DGP resources_english/SSCD/EV/EVA32.bmp
utena insert_lzss_dc Utena_English2.iso /SSCD/EV/EVA32B.DGP resources_english/SSCD/EV/EVA32B.bmp
utena insert_lzss_dc Utena_English2.iso /SSCD/EV/EVD113.DGP resources_english/SSCD/EV/EVD113.bmp
utena insert_lzss_dc Utena_English2.iso /SSCD/EV/EVD114.DGP resources_english/SSCD/EV/EVD114.bmp
utena insert_lzss_mato Utena_English2.iso /SSCD/SPECIAL/NAMEINP.TEP resources_english/SSCD/SPECIAL/NAMEINP false true
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/DT22.DG2 resources_english/SSCD/PLACETAG/DT22.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/DT23.DG2 resources_english/SSCD/PLACETAG/DT23.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/DT24.DG2 resources_english/SSCD/PLACETAG/DT24.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/DT25.DG2 resources_english/SSCD/PLACETAG/DT25.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/DT26.DG2 resources_english/SSCD/PLACETAG/DT26.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT00.DG2 resources_english/SSCD/PLACETAG/PT00.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT01.DG2 resources_english/SSCD/PLACETAG/PT01.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT02.DG2 resources_english/SSCD/PLACETAG/PT02.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT03.DG2 resources_english/SSCD/PLACETAG/PT03.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT04.DG2 resources_english/SSCD/PLACETAG/PT04.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT05.DG2 resources_english/SSCD/PLACETAG/PT05.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT06.DG2 resources_english/SSCD/PLACETAG/PT06.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT07.DG2 resources_english/SSCD/PLACETAG/PT07.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT08.DG2 resources_english/SSCD/PLACETAG/PT08.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT09.DG2 resources_english/SSCD/PLACETAG/PT09.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT10.DG2 resources_english/SSCD/PLACETAG/PT10.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT11.DG2 resources_english/SSCD/PLACETAG/PT11.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT12.DG2 resources_english/SSCD/PLACETAG/PT12.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT13.DG2 resources_english/SSCD/PLACETAG/PT13.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT14.DG2 resources_english/SSCD/PLACETAG/PT14.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT15.DG2 resources_english/SSCD/PLACETAG/PT15.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT16.DG2 resources_english/SSCD/PLACETAG/PT16.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT17.DG2 resources_english/SSCD/PLACETAG/PT17.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT18.DG2 resources_english/SSCD/PLACETAG/PT18.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT19.DG2 resources_english/SSCD/PLACETAG/PT19.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT20.DG2 resources_english/SSCD/PLACETAG/PT20.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT21.DG2 resources_english/SSCD/PLACETAG/PT21.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT22.DG2 resources_english/SSCD/PLACETAG/PT22.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT23.DG2 resources_english/SSCD/PLACETAG/PT23.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT24.DG2 resources_english/SSCD/PLACETAG/PT24.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT25.DG2 resources_english/SSCD/PLACETAG/PT25.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT26.DG2 resources_english/SSCD/PLACETAG/PT26.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT27.DG2 resources_english/SSCD/PLACETAG/PT27.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT28.DG2 resources_english/SSCD/PLACETAG/PT28.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT29.DG2 resources_english/SSCD/PLACETAG/PT29.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT30.DG2 resources_english/SSCD/PLACETAG/PT30.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT31.DG2 resources_english/SSCD/PLACETAG/PT31.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT32.DG2 resources_english/SSCD/PLACETAG/PT32.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT33.DG2 resources_english/SSCD/PLACETAG/PT33.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT34.DG2 resources_english/SSCD/PLACETAG/PT34.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT35.DG2 resources_english/SSCD/PLACETAG/PT35.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT36.DG2 resources_english/SSCD/PLACETAG/PT36.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT37.DG2 resources_english/SSCD/PLACETAG/PT37.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT38.DG2 resources_english/SSCD/PLACETAG/PT38.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT39.DG2 resources_english/SSCD/PLACETAG/PT39.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT40.DG2 resources_english/SSCD/PLACETAG/PT40.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT41.DG2 resources_english/SSCD/PLACETAG/PT41.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT42.DG2 resources_english/SSCD/PLACETAG/PT42.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT43.DG2 resources_english/SSCD/PLACETAG/PT43.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT44.DG2 resources_english/SSCD/PLACETAG/PT44.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT45.DG2 resources_english/SSCD/PLACETAG/PT45.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT46.DG2 resources_english/SSCD/PLACETAG/PT46.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT47.DG2 resources_english/SSCD/PLACETAG/PT47.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT48.DG2 resources_english/SSCD/PLACETAG/PT48.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT49.DG2 resources_english/SSCD/PLACETAG/PT49.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT50.DG2 resources_english/SSCD/PLACETAG/PT50.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT51.DG2 resources_english/SSCD/PLACETAG/PT51.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT52.DG2 resources_english/SSCD/PLACETAG/PT52.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT53.DG2 resources_english/SSCD/PLACETAG/PT53.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT54.DG2 resources_english/SSCD/PLACETAG/PT54.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT55.DG2 resources_english/SSCD/PLACETAG/PT55.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT56.DG2 resources_english/SSCD/PLACETAG/PT56.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT57.DG2 resources_english/SSCD/PLACETAG/PT57.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT58.DG2 resources_english/SSCD/PLACETAG/PT58.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT59.DG2 resources_english/SSCD/PLACETAG/PT59.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT60.DG2 resources_english/SSCD/PLACETAG/PT60.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT61.DG2 resources_english/SSCD/PLACETAG/PT61.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT62.DG2 resources_english/SSCD/PLACETAG/PT62.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT63.DG2 resources_english/SSCD/PLACETAG/PT63.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT64.DG2 resources_english/SSCD/PLACETAG/PT64.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT65.DG2 resources_english/SSCD/PLACETAG/PT65.bmp 0 fix_palette
utena insert_pp Utena_English2.iso /SSCD/PLACETAG/PT66.DG2 resources_english/SSCD/PLACETAG/PT66.bmp 0 fix_palette
utena insert_mato Utena_English2.iso /SSCD/TECHOU/TEB.TEX resources_english/SSCD/TECHOU/TEB fix_palette true
utena insert_mato Utena_English2.iso /SSCD/TECHOU/TEP06.TEX resources_english/SSCD/TECHOU/TEP06 fix_palette true
utena insert_mato Utena_English2.iso /SSCD/TECHOU/TEP07.TEX resources_english/SSCD/TECHOU/TEP07 fix_palette true
utena insert_mato Utena_English2.iso /SSCD/TECHOU/TES06.TEX resources_english/SSCD/TECHOU/TES06 fix_palette true
utena insert_mato Utena_English2.iso /SSCD/TECHOU/TES07.TEX resources_english/SSCD/TECHOU/TES07 fix_palette true
utena insert_mato Utena_English2.iso /SSCD/TECHOU/TES08.TEX resources_english/SSCD/TECHOU/TES08 fix_palette true
utena replace_file Utena_English2.iso /0.BIN resources_english/0.BIN
echo --------Disc 2 translated--------

set /p=Press ENTER to continue...
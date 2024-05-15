del *.wixobj
del *.wixpdb
del *.msi

call "%WIX%bin\heat.exe" dir ".\bin" -gg -ke -sfrag -template fragment -var var.SourceDir -dr dir_main -cg cg_dir_bin -out dir_bin.wxs 

call "%WIX%bin\candle.exe" -ext WiXUtilExtension -dSourceDir=".\bin" dir_bin.wxs
call "%WIX%bin\candle.exe" -ext WiXUtilExtension installer.wxs

call "%WIX%bin\light.exe" -ext WiXUtilExtension -ext WixUIExtension -cultures:en-us -out testapp-1.0.msi dir_bin.wixobj installer.wixobj

pause

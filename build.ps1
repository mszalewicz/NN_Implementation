if ( !(Get-Command "cmake" -errorAction SilentlyContinue) )
{
	Write-Host "`nCMake is not installed. Build cannot continue.`n" -ForegroundColor Red
	Exit
}

if ( ($args[0] -eq "clean") -and (Test-Path -Path './build') )
{
	Write-Host "`n--------- Cleaning solution ---------" -ForegroundColor Cyan
	rm -r .\build\ 
}

if ( !(Test-Path -Path './build') )
{
	Write-Host "`n--- Bootstrapping CMake ---" -ForegroundColor Yellow
	mkdir build
	cd ./build 	

	Write-Host "`n"
	cmake .. 
	cd ..
}

if($args -contains "release")
{
	Write-Host "`n--- Building ---`n" -ForegroundColor Yellow
	cmake --build  .\build\ --config Release
}
else
{
	Write-Host "`n--- Building ---`n" -ForegroundColor Yellow
	cmake --build  .\build\	
}

if(($args -contains "run") -and ($?))
{
	Write-Host "`nApp starting ...`n" -ForegroundColor Magenta
	.\build\src\Debug\nni.exe
}
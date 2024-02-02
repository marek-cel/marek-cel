$CurrentDir = Get-Location
$CurrentDir

if (Test-Path -Path $CurrentDir\deathstar) {
    Remove-Item -Path $CurrentDir\deathstar -Recurse
}

New-Item -Path $CurrentDir\ewok.txt -Type "file" -Value "C3PO!"

New-Item -Path $CurrentDir -Name "deathstar" -Type "directory"

Copy-Item -Path $CurrentDir\ewok.txt -Destination $CurrentDir\deathstar\r2d2.txt
Move-Item -Path $CurrentDir\ewok.txt -Destination $CurrentDir\deathstar\ewok.txt

Rename-Item -Path $CurrentDir\deathstar\ewok.txt -NewName "chewbacca.txt"
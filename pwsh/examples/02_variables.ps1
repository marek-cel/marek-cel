$FavCharacter = "spongebob"
$FavCharacter

$FavCharacter | Out-File favcharacter.txt

$FavCharacter.Length

$FavCharacter.GetType()
$FavCharacter = 5
$FavCharacter.GetType()
$FavCharacter = 5.5
$FavCharacter.GetType()

$BooleanVar = $true
if ($BooleanVar) {
    Write-Host "The variable is true."
}

$BooleanVar = $false
if ($BooleanVar) {
    Write-Host "The variable is true."
} else {
    Write-Host "The variable is false."
}


$x = 5
$y = 3
$x * $y

Write-Host 'Single quatation marks $x'
Write-Host "Double quatation marks `$x = $x"
Write-Host "Double quatation marks `$(`$x + 1) = $($x + 1)"
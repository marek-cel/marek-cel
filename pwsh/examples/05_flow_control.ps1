$PokemonCaught = "1025"
$PokemonCaught
if ($PokemonCaught -eq 1025) {
    Write-Host "You caught them all!"
} else {
    Write-Host "You still have some work to do."
}

################################################################################

Write-Host
$PokemonNum = 25
if ($PokemonNum -ge 1 -and $PokemonNum -le 151) {
    Write-Host "Your Pokemone is from Kanto."
}
elseif ($PokemonNum -ge 152 -and $PokemonNum -le 251) {
    Write-Host "Your Pokemone is from Johto."
}
else {
    Write-Host "Your Pokemone is from an unknown region."
}

################################################################################

Write-Host
$House = "Targaryen"
switch ($House) {
    "Stark" {
        Write-Host "Winter is coming."
        break
    }
    "Lannister" {
        Write-Host "A Lannister always pays his debts."
        break
    }
    "Targaryen" {
        Write-Host "Fire and Blood."
        break
    }
    default {
        Write-Host "You know nothing, Jon Snow."
        break
    }
}

################################################################################

Write-Host
$ConCrew = @("Picard", "Riker", "Data", "Worf")
for ($i = 0; $i -lt $ConCrew.Count; $i++) {
    Write-Host "Welcome aboard, $($ConCrew[$i])!"
}

Write-Host
$OrinCrew = @("Kirk", "Spock", "McCoy", "Scotty")
foreach ($CrewMember in $OrinCrew) {
    Write-Host "Welcome aboard, $CrewMember!"
}

Write-Host
$Avengers = @("Iron Man", "Captain America", "Thor", "Hulk")
$index = 0
while ($index -lt $Avengers.Count) {
    Write-Host "Avengers Assemble! Welcome, $($Avengers[$index])!"
    $index++
}

Write-Host
$XMen = @("Wolverine", "Cyclops", "Storm", "Proffesor X")
$index = 0
do {
    Write-Host "Welcome to the X-Men, $($XMen[$index])!"
    $index++
} while ($index -lt $XMen.Count)
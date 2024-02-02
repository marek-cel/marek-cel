$Jedi = @("Luke Skywalker", "Yoda", "Obi-Wan Kenobi")
$Jedi
$Jedi.Length

$Jedi[0]
$Jedi[0].Length

$Jedi += "Mace Windu"
$Jedi
$Jedi.Length

$Fellowship = @{"Ring-bearer" = "Frodo"; "Wizard" = "Gandalf"; "Elf" = "Legolas"; "Dwarf" = "Gimli"}
$Fellowship
$Fellowship["Elf"]

$Fellowship.Remove("Dwarf")
$Fellowship
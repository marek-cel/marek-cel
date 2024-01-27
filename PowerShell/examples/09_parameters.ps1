Param (
    [Parameter(Mandatory, HelpMessage="Enter your first name")]
    [string]$FirstName,
    
    $LastName
)

Write-Host "Hello $FirstName $LastName!"

# 09_parameters.ps1 -FirstName "Marek" -LastName "Cel"
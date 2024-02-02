Try {
    Throw "Admiral Ackbar: It's a trap!"
} Catch {
    Write-Error "Caught an exception: $($_.Exception.Message)" -ErrorAction Stop
} Finally {
    Write-Host "This is the end of the Try-Catch-Finally block."
}

Write-Host "This is the end of the script."
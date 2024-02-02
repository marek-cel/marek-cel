function Test-SpaceX {
    Param(
        [Parameter(Mandatory)]
        $PingCount
    )
    Test-Connection spacex.com -Count $PingCount
}

Test-SpaceX -PingCount 10
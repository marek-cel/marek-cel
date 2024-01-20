function Test-SpaceX {
    param(
        $PingCount
    )
    Test-Connection spacex.com -Count $PingCount
}

Test-SpaceX -PingCount 10
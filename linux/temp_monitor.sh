#!/usr/bin/env bash

################################################################################

# Configuration
TEMP_LIMIT=95  # Temperature limit in Celsius
EMAIL=$USER_EMAIL_ADDRESS
HOSTNAME=$(hostname)
LOG_FILE=$HOME"/temp_monitor.log"

################################################################################

# Function to log messages
function log_message()
{
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" >> "$LOG_FILE"
}

# Get CPU temperature
function get_cpu_temp()
{
    # Try different methods to get CPU temperature
    if command -v sensors >/dev/null 2>&1; then
        # Method 1: Using sensors command
        TEMP=$(sensors | grep -E "(Core|Package|Tctl)" | head -1 | grep -o '+[0-9]\+\.[0-9]\+°C' | head -1 | sed 's/+\([0-9]\+\)\.[0-9]\+°C/\1/')

        # Method 2: If first method fails, try alternative parsing
        if [ -z "$TEMP" ]; then
            TEMP=$(sensors | grep -E "temp[0-9]+" | head -1 | grep -o '+[0-9]\+\.[0-9]\+°C' | sed 's/+\([0-9]\+\)\.[0-9]\+°C/\1/')
        fi
    fi

    # Method 3: Direct reading from thermal zone (fallback)
    if [ -z "$TEMP" ] && [ -f "/sys/class/thermal/thermal_zone0/temp" ]; then
        TEMP_MILLIC=$(cat /sys/class/thermal/thermal_zone0/temp)
        TEMP=$((TEMP_MILLIC / 1000))
    fi

    echo "$TEMP"
}

################################################################################

# Get current temperature
CURRENT_TEMP=$(get_cpu_temp)

# Check if we got a valid temperature reading
if [ -z "$CURRENT_TEMP" ] || ! [[ "$CURRENT_TEMP" =~ ^[0-9]+$ ]]; then
    log_message "ERROR: Could not read CPU temperature"
    echo "ERROR: Could not read CPU temperature"
    exit 1
fi

# log_message "Current CPU temperature: ${CURRENT_TEMP}°C"

RAW_SENSOR_OUTPUT=$(sensors)

# Check if temperature exceeds limit
if [ "$CURRENT_TEMP" -gt "$TEMP_LIMIT" ]; then
    log_message "ALERT: Temperature ${CURRENT_TEMP}°C exceeds limit of ${TEMP_LIMIT}°C"

    # Get additional system information
    UPTIME=$(uptime)
    LOAD_AVG=$(cat /proc/loadavg)
    TOP_PROCESSES=$(top -bn1 | head -20)

    # Send email alert
    echo "Subject: HIGH CPU TEMPERATURE ALERT - $HOSTNAME" | mail -s "CPU Temperature Alert" "$EMAIL" << EOF
ALERT: High CPU temperature detected on $HOSTNAME

Current Temperature: ${CURRENT_TEMP}°C
Temperature Limit: ${TEMP_LIMIT}°C
Time: $(date)

System Information:
$UPTIME
Load Average: $LOAD_AVG

Sensors Output:
$RAW_SENSOR_OUTPUT

Please check the system immediately.
EOF

    log_message "Alert email sent to $EMAIL"
fi
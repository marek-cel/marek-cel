#!/bin/bash

################################################################################

source install_common.sh

################################################################################

# https://forums.linuxmint.com/viewtopic.php?t=369092
function installVnc()
{
    readBold "Do you want to install VNC?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        readBold "Do you want to install VNC SERVER?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing VNC SERVER ..."
            sudo apt install -y x11vnc
            x11vnc -storepasswd
            sudo x11vnc -auth guess -forever -loop -noxdamage -repeat -rfbauth $HOME/.vnc/passwd -rfbport 5900 -shared

            echo -e "\e[1;33m"
            echo "To enable auto-start at system boot-up Paste following code into \"/etc/systemd/system/x11vnc.service\":"
            echo "[Unit]"
            echo "Description=x11vnc remote desktop server"
            echo "After=multi-user.target"
            echo ""
            echo "[Service]"
            echo "Type=simple"
            echo "ExecStart=/usr/bin/x11vnc -auth guess -forever -loop -noxdamage -repeat -rfbauth $HOME/.vnc/passwd -rfbport 5900 -shared"
            echo ""
            echo "Restart=on-failure"
            echo ""
            echo "[Install]"
            echo "WantedBy=multi-user.target"
            echo -e "\e[0m"
            read -p "Press any key to continue... " -n1 -s
            sudo vim /etc/systemd/system/x11vnc.service

            sudo systemctl daemon-reload
            sudo systemctl start x11vnc
            sudo systemctl status x11vnc

            readBold "Did it say \"active\"?"
            if [[ $REPLY =~ ^[Yy]$ ]]
            then
                sudo systemctl enable x11vnc.service
            fi

            echo -e "\e[1;33m"
            echo "Use Remmina as a client."
            echo -e "\e[0m"
            read -p "Press any key to continue... " -n1 -s
        fi
    fi
}

installVnc
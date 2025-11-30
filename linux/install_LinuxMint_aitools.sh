#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

function installAiTools()
{
    readBold "Do you want to install AI TOOLS?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing AI TOOLS ..."

        sudo apt install -y \
            libmlpack-dev
        pipx install deep-daze
    fi

    readBold "Do you want to install OLLAMA?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing OLLAMA ..."

        # install NVidia Container Toolkit
        curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | sudo gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg \
        && curl -s -L https://nvidia.github.io/libnvidia-container/stable/deb/nvidia-container-toolkit.list | \
            sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
            sudo tee /etc/apt/sources.list.d/nvidia-container-toolkit.list
        sudo apt update
        sudo apt install -y nvidia-container-toolkit


        curl -fsSL https://ollama.com/install.sh | sh

        readBold "Do you want to install OLLAMA MODELS?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing OLLAMA MODELS ..."
            ollama pull llama3.1:8b
            ollama pull deepseek-r1:7b
            ollama pull deepseek-r1:14b
            ollama pull codellama:7b-instruct
            ollama pull deepseek-coder:6.7b
            ollama pull qwen2.5-coder:7b
        fi

        readBold "Do you want to install OPEN WEBUI?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing OPEN WEBUI ..."
            docker run -d -p 3000:8080 --add-host=host.docker.internal:host-gateway -v open-webui:/app/backend/data --name open-webui --restart always ghcr.io/open-webui/open-webui:main

            docker network inspect bridge
            echo "Add line: Environment=\"OLLAMA_HOST=0.0.0.0\" to the ollama.service file."
            read -p "Press any key to continue... " -n1 -s
            sudo vi /etc/systemd/system/ollama.service
            sudo systemctl daemon-reload
            sudo systemctl restart ollama
        fi
    fi
}

installAiTools

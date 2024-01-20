echo off
:: Kill all running Docker containers
FOR /F %%i IN ('docker ps -aq') DO docker kill %%i

:: Remove all Docker containers (running or not)
FOR /F %%i IN ('docker ps -aq') DO docker rm %%i

:: Remove all Docker images
FOR /F %%i IN ('docker images -q') DO docker rmi -f %%i

:: Prune all Docker system resources
docker system prune -a
FROM php:7.2-apache

RUN apt update
RUN apt install -y subversion
RUN mkdir /src
RUN svn export --force https://github.com/marek-cel/marek-cel.git/trunk/docker/01_test/src/ /src
RUN cp /src/index.php /var/www/html/index.php
RUN rm -r /src
RUN apt purge -y subversion 
RUN apt autoremove -y
RUN apt clean

EXPOSE 80

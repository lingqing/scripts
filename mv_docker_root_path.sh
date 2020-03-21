#!/bin/bash
mkdir /etc/systemd/system/docker.service.d
touch /etc/systemd/system/docker.service.d/docker-overlay.conf
echo "[Service]
ExecStart=
ExecStart=/usr/bin/dockerd --graph=/spc/docker_vol --storage-driver=overlay" >> /etc/systemd/system/docker.service.d/docker-overlay.conf
sudo systemctl daemon-reload
sudo systemctl restart docker

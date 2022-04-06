---
layout: default
title: Overview
nav_order: 1
---

# Inlaserworld engine
{: .no_toc }

Let's build the best lasergame game scenarious and epic experiance ever.
{: .fs-6 .fw-300 }

[Get started](http://example.com/){: .btn .btn-purple }
[View it on github](https://github.com/High-tech-digital-modules/inlaserworld_engine){: .btn }

---
## Introduction

This is the documentation of Inlaserworld engine. It is the API which enables to
create really custom game scenario. There are four main parts:
- API for main unit also called arena written in C/C++.
- API for device written in C.
- API for online game results written in javascript/React
- API for final game result written in javascript/Nodejs with PdfKit

APIs can handle various of scenarios and everything can be controlled. You become
director of the game and you can create light or sounds efect, rules or just some funny
stuff. The whole system is based on events e.g. somebody hit me what should I do? Play sound?
decrement life? strobe effect? or just ignore it because shield was activated in previous time.

## Instalation
We provide full featured simulation of our system. This enable anybody to create source code
for game scenario debug it and publish it for review or just use it with real devices.

Of course there is an docker container including everything but unfortunately two linux kernel
modules needs to be used. So only linux host is currently available for running docker container.
Linux host can be virtualized using virtual box or e.g. AWS lightsail.
- [tty0tty](https://github.com/freemed/tty0tty.git) we use it for simulation of xbee network used
  for communication with device.
- vcan used for communication with static devices at arena e.g. control lights or bonuses.

```shell
# install packages
sudo apt-get update
sudo apt-get install git docker docker.io gcc make -y

# if AWS lightsail used 
sudo apt-get install linux-modules-extra-aws && sudo reboot
```

Install kernel headers
```shell
sudo apt-get install linux-headers-`uname -r`
```

Install tty0tty
```shell
git clone https://github.com/freemed/tty0tty.git
cd tty0tty/module
sed -i 's|static unsigned int tty0tty_write_room|static int tty0tty_write_room|g' tty0tty.c
make
sudo cp tty0tty.ko /lib/modules/$(uname -r)/kernel/drivers/misc/
sudo depmod
sudo modprobe tty0tty
sudo chmod 666 /dev/tnt*
```

Install vcan (every linux machine should have it by default)
```shell
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
```

To load tty0tty and vcan after boot
```shell
sudo bash -c 'echo "#/bin/bash" > /etc/init.d/enableTty0.sh'
sudo bash -c 'echo "chmod 666 /dev/tnt*" >> /etc/init.d/enableTty0.sh'
sudo bash -c 'echo "ip link add dev vcan0 type vcan" >> /etc/init.d/enableTty0.sh'
sudo bash -c 'echo "ip link set up vcan0" >> /etc/init.d/enableTty0.sh'
sudo bash -c 'echo "tty0tty" >> /etc/modules'
sudo bash -c 'echo "vcan" >> /etc/modules'
sudo bash -c 'crontab -l | { cat; echo "@reboot /etc/init.d/enableTty0.sh"; } | crontab -'
```

If user is not already in group add it
```shell
sudo usermod -aG docker $USER
# Logout and login again
```

Now finally let's run docker
```shell
docker run --cap-add=NET_ADMIN --workdir /home/inlaserworld/ -u inlaserworld \
  --detach --name inlaserworld -t -e DISPLAY=:0 \
  --security-opt apparmor=unconfined --privileged \
  -p 7777:7777 -p 7778:7778 -p 5900:5900  docker.htdm.net/inlaserworld:1.0.0
```

Final step go to docker and install our lasergame app
```shell
docker exec -it -u inlaserworld inlaserworld /bin/bash
sudo apt-get install /home/inlaserworld/laser*.deb
```

You will be asked during installation to fill your email. This email is used for admin account.
Navigate to your browser and write use your ip adress and port 7778. If you use some of server
machine please check also firewall rules.
Now if you see login screen your installation is ready to go and you can continue.




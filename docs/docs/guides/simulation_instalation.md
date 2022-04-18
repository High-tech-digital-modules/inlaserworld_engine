---
layout: default
title: Simulation get started
nav_order: 5
---

# Simulation get started

To connect simulation the standard RDP can be used. This guide will show it on MAC OS using 
microsoft remote desktop application. To get the best performance use resolution 1280x800 and lower the color
quality. On windows there is native remote desktop and on linux remmina could be used.
![rdp_config](../../assets/images/RDP_base.png "RDP setup")
Than connect it. The credentials are:
- username: **inlaserworld**
- password: **inlaserworld** (It is recommended to change password using ```passwd``` later)

First double-click on install. During installation email will be required used for default admin user.
Once installation is done continue with start simulation.

![simulation_main](../../assets/images/SIM_rdp_main.png "Simulation main")

Then add new device and select chest. This will create full simulation of real hardware device.

![simulation_add_chest](../../assets/images/SIM_add_chest.png "Add simulation chest")

Then next picture describes chest device its action buttons and visualization elements.

![simulation_chest_description](../../assets/images/SIM_chest_description.png "Chest description")

Just a showcase of chest device presentation mode. Note: segments on real device creates really nice
effects :) 

![chest_presentation](../../assets/images/SIM_chest_presentation.png "Chest presentation")

## Simulation console
This part describes how to use real console. There is no different with real console used in production
except first user registration. Your docker image should expose port 7778 so please open your broswer
and fill <IP Adress>:7778 and you should see:

![console_login](../../assets/images/CON_login.png "Console login")

1. Follow up to **Sign up** and fill **"registrationToken"** than you will be asked to fill some 
information (used only for simulation).
2. Then for email validation use **"validationtoken"**
3. Finally, log in
4. Navigate to device list and you should see devices as shown on picture bellow

![console_device_list](../../assets/images/CON_device_list.png "Console device list")



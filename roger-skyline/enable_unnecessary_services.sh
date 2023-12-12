#!/bin/sh

# Disables Advanced Linux Sound Architecture
sudo systemctl --now enable alsa-utils

# Disables bluetooth
sudo systemctl --now enable bluetooth

# Disables HDD temp
sudo systemctl --now enable hddtemp

# Disables HWclock
sudo systemctl --now enable hwclock

# Disables lm-sensors
sudo systemctl --now enable lm-sensors

# Disables rsync
sudo systemctl --now enable rsync

# Disables saned
sudo systemctl --now enable saned

# Disables speech-dispatcher
sudo systemctl --now enable speech-dispatcher

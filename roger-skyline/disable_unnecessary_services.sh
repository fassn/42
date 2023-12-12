#!/bin/sh

# Disables Advanced Linux Sound Architecture
sudo systemctl --now disable alsa-utils

# Disables bluetooth
sudo systemctl --now disable bluetooth

# Disables HDD temp
sudo systemctl --now disable hddtemp

# Disables HWclock
sudo systemctl --now disable hwclock

# Disables lm-sensors
sudo systemctl --now disable lm-sensors

# Disables rsync
sudo systemctl --now disable rsync

# Disables saned
sudo systemctl --now disable saned

# Disables speech-dispatcher
sudo systemctl --now disable speech-dispatcher

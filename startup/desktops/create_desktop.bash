#!/bin/bash

here=$PWD

echo [Desktop Entry] > f.desktop
echo Version=1.0 >> f.desktop
echo Name=FCS test >> f.desktop
echo GenericName=Application >> f.desktop
#This script has two inputs spacenav and keyboard (default is false)
echo Exec=$here/startup/scripts/flexcraft_onboard_start.sh false false >> f.desktop
echo Terminal=true >> f.desktop
echo Icon=$here/startup/icons/flexyside.png >> f.desktop
echo Type=Application >> f.desktop
echo Comment=Currently a test of desktop files, but launches FlexCraft Software >> f.desktop

chmod +x f.desktop

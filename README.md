flexcraft
=========

Control software for the FlexCraft Simulator (FCS), a robotic platform located in the Flight Robotics Laboratory at NASA's Marshall Space Flight Center.

After cloning into your local filesystem, here are steps to help you get going:
```
#initialize the workspace
cd path/to/flexcraft/src
catkin_init_workspace

#build the project for the first time
cd ../
catkin_make

#if things seem to not be working
source flexcraft/devel/setup.bash
```

<h4>Note on thruster naming conventions:</h4>
side (Left/Right) - side (front/rear) - direction it makes the craft go (backwards/forwards/right/left)
```
 1 ^ -------------- ^ 3
 2  <              > 4
     \            /
      \          /
       \        /
        \      /
     5 < \    / > 7
       6 v\  /v 8
           \/
```
<ol>
<li>LFB</li>
<li>LFR</li>
<li>RFB</li>
<li>RFL</li>
<li>LRR</li>
<li>LRF</li>
<li>RRL</li>
<li>RRF</li>
</ol>

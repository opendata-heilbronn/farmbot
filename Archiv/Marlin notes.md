# Toolmount Positions 
(current crappy ones)

Current Mount 1: X1145 Y200 Z209

# Sending G Code to Marlin
Command | Description | Notes
--- | --- | ---
`G0 X(mm) Y(mm) Z(mm) F(mm/m)` | Move to Position | Warning: Feedrate is in mm/Minute not mm/s
`G28` | Home all axes
`G28 X [Y [Z] ]` | Move given axis | Can home single or multiple axes (delimeted by a space)
`M114` | Get current position
`M119` | Get endstop states

More commands can be found in the [Marlin Command Cheat Sheet](https://thingiverse-production-new.s3.amazonaws.com/assets/87/b0/2c/f5/4c/CheatSheet.pdf)

# Maximum feed rate 
(mm/s, Configuraion.h @L494)

X 300 (quite fast speed, works without loosing steps)  
Y 300  
Z 50 (at 100 it was skipping steps)

# Maximum acceleration 
(Configuraion.h @L502)

X 200 (has to move quite some weight, 200 accelerates it very smootly  
Y 300  
Z 300 (could be higher because of spindle, but is fast enough)

# Maximum bed size of current setup
(mm, Configuration.h @L738)

X 1145  
Y 720  
Z 280 (value just before seeder hits the floor)

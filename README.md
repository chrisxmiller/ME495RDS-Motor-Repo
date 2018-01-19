# ME495RDS-Motor-Repo
ME495 Robotic Design Studio Motor Project Repository.

This repo is for documenting and storing all coding/design ideas relating to the Week 1 Motor Project.

## Mechanical Design

The large, square neodymium magnets were used for maximum magnetic force, which implies maximum torque. The magnets were super-glued to the rotor element to prevent them from coming off as other magnets were attached.

Each coil consists  of about 18 ft of magnet wire, which translates to about 500 turns per coil. There are 6 coils mounted at 60 degrees relative to each other, wired to form 3 phases. The provided motor base was used to assemble the coil/rotor unit.

The overall structure was then mounted on a hand-made "shelf", which allows the motor assembly to rest directly above the breadboard, which minimized wire crossing and allowed for clean wire management.

## Electrical Design

A standard Wye format was used to wire the motor coils. Each main coil was attached to a half H-bridge, and its conjugate was wired accordingly. See image for overall structure.

![Wye format motor coils](https://github.com/chrisxmiller/ME495RDS-Motor-Repo/blob/master/wye_design)

## Software

The code that was originally provided was used. Enabled PORTF because that is where our RGB LEDs are, and used a bitmask to flash different colors at every step.

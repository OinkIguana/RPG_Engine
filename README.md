[Room Editor]: http://github.com/OinkIguana/Room_Editor

# RPG Engine (WIP)

An engine for making RPG games in C++ using SDL 2.0.

Current Features:
* Basic resources
    * Sprites
    * Backgrounds / Tiles
    * Actors
        * With collision detection and animation
    * Audio
        * SFX, Music and Voice acting
    * Fonts
* Dialog
    * Changeable colours and fonts
    * Display text letter by letter
    * Sound effects and voice acting
* Inventory
    * Sorting by various properties
    * Items grouped by type in stacks
    * Add/remove/count items easily
* Stat lists
* Skill trees (untested)
    * Skill point tracking
    * Prerequisites
        * Skills along an edge; or
        * Total skills behind
    * Branches and merges
* Rooms
    * [Room Editor]
        * Lay out tiles/actors
        * Save to JSON
        * ERB template to any format
* Keyboard/Mouse events
* Progress tracker
    * Quests
* Some utility classes
    * Point, Rect, Angle, Sequence

There is a very simple demo in place to show one way things can be done.

Planned features:
* Map
* Viewports
* Menus
* Pausing/Disabling of actors
* Save/Load
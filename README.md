A scratch of a mini game where a few players collect props.
To check in editor use "Listening Server" mode not "Dedicated Server".
On begin play the interface will show which type of shape you should collect.
Press E to pickup a prop
Press E to use teleport (Yellow disk) to move between platforms.
Press E to open a door.


Interface implementation for interact is bound to collision component which is shit. Better use base actor inherited from Interface with aggrigated collision box.

# hm01b0_machikania
Arducam HM01B0 camera interface for MachiKania
## How to use this code in MachiKania
Copy "auxcode" directory to MachiKania source code and build entier MachiKania. The version of MachiKania must be 1.4 or later.
## Connection
Connect the camera to Pi Pico as follows:
```console
Ardcam   Pico

   VCC   3V3 Out
   SCL   GP4
   SDA   GP5
 VSYNC   GP27
  HREF   GP6
  PCLK   GP5
    D0   GP1
   GND   GND
```
## MachiKania statements
Following statements will be added to MachiKania BASIC
```console
HM01BO_INIT x
    Initialize camera interface. x is the pointer to 104976(324x324) bytes buffer.
HM01BO_CAPTURE
    Capture an image and store to buffer.
```

## Example BASIC code
Note that mirror images will be shown in MachiKania LCD.
```console
print "Start"
dim b(324*324/4)
HM01BO_INIT b
print "HM01BO_INIT done"
HM01BO_CAPTURE
print "HM01BO_CAPTURE done"
wait 60
do
  gosub set_palette
  gosub show_image
  HM01BO_CAPTURE
loop
end

label show_image
  var x,y
  for y=0 to 239
    for x=0 to 319
      pset x,y,peek(b+y*324+x)
    next
  next
return

label set_palette
  var i
  for i=0 to 255
    palette i,i,i,i
  next
return
```

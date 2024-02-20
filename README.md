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
  HREF   GP7
  PCLK   GP6
    D0   GP1
   GND   GND
```
## MachiKania statements
Following statements will be added to MachiKania BASIC
```console
HM01B0_INIT x
    Initialize camera interface. x is the pointer to 104976(324x324) bytes buffer.
HM01B0_CAPTURE
    Capture an image and store to buffer.
HM01B0_DRAW
    Draw the image on LCD.
HM01B0_REG_WRITE x,y
    Write the value (y; 8 bit integer) to the register (x; 16 bit integer).
HM01B0_ZOOM x,y
    Zoom (2x) into rectangle area starting from (x,y). This statement must be used after HM01B0_CAPTURE statement.
HM01B0_ANALYZE([x])
	Returns the pointer to dimension containing 8 integer, which are numbers of pixels with value of 0x00-0x1f, 0x20-0x3f, 0x40-0x5f, 0x60-0x7f, 0x80-0x9f, 0xa0-0xbf, 0xc0-0xdf, and 0xe0-0xff, respectively. x is the number of rows analyzed (default: 240).
```

## Example BASIC code
```console
print "Start"
dim b(324*324/4)
HM01B0_INIT b
HM01B0_REG_WRITE 0x0101,0x00 : REM Disable horizontal mirror
HM01B0_REG_WRITE 0x2100,0x00 : REM Disable automatic exposure
rem HM01B0_REG_WRITE 0x0202,0x00 : REM Set integration time (upper 8 bit)
rem HM01B0_REG_WRITE 0x0203,0x02 : REM Set integration time (lower 8 bit)
rem HM01B0_REG_WRITE 0x0205,0x30 : REM Set analog gain (either 0x00, 0x10, 0x20, or 0x30)
HM01B0_REG_WRITE 0x0104,0x01 : REM Hold parameter (required to send above register values)
print "HM01B0_INIT done"
HM01B0_CAPTURE
print "HM01B0_CAPTURE done"
wait 60
gosub set_palette
do
  HM01B0_DRAW
  wait 1
  HM01B0_CAPTURE
loop
end

label set_palette
  var i
  for i=8 to 255
    palette i,i,i,i
  next
return
```
## License of files in this repository.
The license of codes here is LGPL ver 2.1.
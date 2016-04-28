# How-To display the Wemos logo on the 64x48 OLED Shield
http://www.wemos.cc/
## initial investigation
I followed [@mcauser's](http://forum.wemos.cc/user/mcauser) [post](http://forum.wemos.cc/topic/73/d1-mini-oled-shield/2) on how to get the OLED shield functional.

I saw his picture of the WeMos logo and wanted to do that.
I learned it was a bitmap, and found his github [repository](https://github.com/mcauser/WeMos-D1-mini-Nokia-5110-PCD8544/tree/master/bitmaps) for a larger image
I used gimp and/or Microsoft Paint to resize the image then edit the letters so they aren't as squished, saving the resulting file.
I then read on the [AdaFruit website](https://learn.adafruit.com/monochrome-oled-breakouts/arduino-library-and-examples) about how to convert the bitmap to hex using [LCD Assistant](http://en.radzio.dxp.pl/bitmap_converter/)
One key point, I had to set "**Byte orientation**" to (*Horizontal*)

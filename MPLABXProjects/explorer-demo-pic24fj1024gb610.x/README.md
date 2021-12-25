Microchip Explorer 16/32 Board Demo Code
========================================

Parn number: DM240001-3
uController: PIC24FJ1024GB610

Recommendation
--------------
Download Microchip's latest demo code (released under Apache 2.0 License)

https://www.microchip.com/en-us/development-tool/dm240001-3#Software

Notes:
------
* Dev Kit comes with demo installed.
* Connect with USB-A/micro-B cable
* Download demo software and select pic24fj1024gb610_pim.X.
* Open with with MPLAB X IDE and build. There are some issues. Click "resolve" a few time and it builds.
* Build and run project.  It works... no issues
* Tweak print statement.  If you make the message too long then the LCD wraps badly.
* 

I got this error message after switching to a new project and the returning to th project.
make[2]: *** No rule to make target 'dist/default/production/explorer-demo-pic24fj1024gb610.x.production.null'.  Stop.

The fix was: File -> Project Properties -> Apply
Then 'Clean and Build Project'

USB Notes:
----------
* Used MCC defaults. When generating it gave a warning about clocks not valid.  This video provide the answer: https://vimeo.com/204554501

* The code with USB built and loaded, and showed up on COM4. But how do you use the USB?  Download the MLA and use example 
C:\microchip\mla\v2018_11_26\apps\usb\device\cdc_basic\firmware\exp16_pic24fj1024gb610_pim.x

* I copied and hacked "app_device_cdc_basic.c" into my main until it compiled. And it amazingly transmitted to PUTTY.
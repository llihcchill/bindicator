# bindicator
### Something my mum found on facebook I thought would be really cool to recreate :)
A silicone model of a bin that lights up the colour of what bin (or both, one colour on top and one on bottom) to put out by web scraping your local council's website.
---
*(btw during the making of this privately I kinda doxxed myself in the source code so that's why it's pretty much finished, yea, oh well)*

# Installation and Setup
This project uses the ESP8266, so go ahead and buy on of those if you don't already have one (make sure it has on board wifi). As there will be some webscraping, a computer will be needed and the code in the 
[API folder](https://github.com/llihcchill/bindicator/tree/main/API) to be copied and pasted there. Next, if you don't have a code editor already, install one of those (i'd recommend [VSCodium](https://vscodium.com))

### Installing Libraries
Now to the fun part, installing librariesssrsrseresitir
For each of the "import ..." in both files, you'll want to input to your python terminal:
```
pip install *library name*
```

### Installing Arduino IDE
At the same computer (or a different one), from the [Arduino website](https://www.arduino.cc/en/software), download the Arduino IDE, create a new project/.ino file, and copy and paste [this code](https://github.com/llihcchill/bindicator/blob/main/bindicator.ino) into it.

![image](https://github.com/llihcchill/bindicator/assets/125551072/3a9e3b21-5f06-4185-91fa-7a7490ded320)

Plug the ESP8266 into the computer and up the top of the IDE, find the ESP8266 USB port:

![image](https://github.com/llihcchill/bindicator/assets/125551072/13368b42-259e-4e63-8b98-22565334b036)

Once the text box has come up, input the make of the ESP8266 (in my case it was a NodeMCU)

![image](https://github.com/llihcchill/bindicator/assets/125551072/7c1ad27b-4e49-449a-966d-016c3751d0f8)

Then press on the upload arrow in the upper left hand corner, and once it has, you're all ready to configure the development board :)

### Development Board Configuration
At a development board, you want it to look like this:

![image](https://github.com/llihcchill/bindicator/assets/125551072/c18c5dbe-72b7-4009-b1c4-941d8ce58f3b)

Once everything is wired up, you can design the case around the development board and plug it in while having the API running on the computer. The API will only need to be running on Tuesday, so you can safely shut it down every other day to have the program function as normal, or you can leave it on 24/7, it's up to you :)


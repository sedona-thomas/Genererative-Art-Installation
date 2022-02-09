# TTGO Text Visualization
## ESP32 TTGO T-Display text visualization

A generative art installation on an  ESP32 TTGO T-Display that visualizes the UDHR in English and French for Professor Mark Santolucito's Creative Embedded Systems (COMS 3930) Course in Spring 2022

![ESP32 TTGO T-Display with the UDHR in English and French with a pride flag](./Images/TTGO_Text_Visualization_3.jpg)

More Information can be found here: https://medium.com/@sedonathomas/generative-art-9378c338fe06

Youtube Demo: https://www.youtube.com/watch?v=hJqq8oLx8cU&feature=youtu.be

### Overview

My generative art installation was designed in collaboration with Professor Mark Santolucito’s Creative Embedded Systems course. Each student displayed their own representative text on their ESP32 TTGO T-Display for a collective installation in the fifth-floor hallway of Barnard’s Milstein Center.

### Inspiration

As a student studying computer science and human rights through Columbia University’s 4–1 Program (a dual-degree program between Columbia’s engineering and liberal arts schools), I designed this project to represent my intersectional academic focuses. I chose to display the Universal Declaration of Human Rights (UDHR) in its two original languages — English and French — because those are the two languages I speak (English as a native speaker and French as an intermediate student). My portion of the class installation incorporates all of my most significant academic passions — computer science, human rights, and the French language and culture.

### Design Choices

I began by programming a simple display in C++ with a white background and black text that flashes on and off. From this, I began breaking down the pieces of my intended project — scrolling text across the display. Once I had the program printing a single line of text, I added to this functionality, so two lines could be displayed simultaneously. Once this was working, I began cleaning up my code by making helper methods to reduce redundancy. Lastly, I decided to personalize the display by randomly generating a background color every 10 frames. At the very end, I decided to add my name in the lower right-hand corner as a form of signature for my work.

### Learned

First, I learned how to set up and load example programs onto an Arduino display. Once this was working, I began researching how to use the TFT_eSPI library and was able to change the background and text color, add text to the screen, and change text size. I practiced using both the drawString() and print() methods which helped me to debug issues with less control of the position of strings using the print() method over the drawString() method when using long strings. This also helped me to realize that there is an issue with the drawString() method and using the size parameter, so I was able to increase the size of my text by changing the overall font size rather than inputting the size of each string. I also learned that the Arduino String class only allows for ASCII characters and this posed some problems with properly displaying the French text.

### Intended Improvements

I had initially attempted to write the program to read in a file saved on the ESP32 which could then be displayed on the screen, but I ran into many issues with my attempts to read in the file. Due to time constraints and since this is my first attempt at programming an Arduino Development Board, I decided to focus on the main functionality of the scrolling text, but future iterations of this project will involve dynamic text input that can be read directly from the file rather than hardcoded into the main program. The other major issue I ran into dealt with the accented characters in the French text. After attempting to research how to use Unicode instead of ASCII for an Arduino and attempting to convert all accented characters into non-accented characters, I was unable to get the text to render properly, so I was forced to leave the accented characters as they automatically rendered. In future iterations of this project, I will start from scratch to see how I can either print accented characters or properly remove them before designing the entire program. I also intend to learn how to create a seamless transition between frames. Currently, each frame displays a black screen between them, and my attempts to remove this were unsuccessful. I believe this is due to a lag in the calculation of the next frame once the previous frame has ended.

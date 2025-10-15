# ChessExtended
All information that is parsed from console is managed by a sceond thread that communicates only with main
Commands for debug console:
exit - The same as exit button
show - show debug info on screen
  - For show to work, you must add a second keyword, the data that you want to see.
  - Here is the list of options for info: (cursor, TPS, rects)
      - cursor gives the position of cursor in (x|y) within program
        - add the option '-' between 'show' and 'cursor' to continously show on the screen the cursor's position
        - add the option '-s' between the same keywords to stop printing on screen this info
      - TPS gives you Ticks Per Second, the ammount of time it takes for one cycle of game logic to pass
        - add the option '-' between 'show' and 'TPS' to continously show on screen TPS
        - add the option '-s' between the same keywords to stop printing on screen this info
        - add the option '-a' between 'show' and 'TPS' to continously show the average TPS, this command needs a number after 'TPS' to work, working as the accuracy of this command
      - rects, is used only in the context of a screen, so for it to work add '-'(meaning show on screen) between 'show' and 'rects' and the parameter for rectangle corner size after 'rects'
        - shows the borders of rectangle that are drawn on screen

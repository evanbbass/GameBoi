[Back to Home](../../README.md)

[Back to Week 8](Week8.md)

## 7/20/2017
Today I have a quick update: I managed to track down the two remaining show-stopping bugs and now the emulator is running Tetris!

It was two stupid mistakes. The sprites not rendering was caused by faulty logic in an `if` check:
```c++
// before
if (attributes.IsAboveBackground() && mDisplay.GetPixel(mCurrentScanline, pixel) == Display::Color::White)

// after
if (attributes.IsAboveBackground() || mDisplay.GetPixel(mCurrentScanline, pixel) == Display::Color::White)
```

Originally it would only draw sprites if both the sprite was marked as above the background AND the current color was white (i.e. transparent). It should be true in either case.

----

As for the divider always returning 0, it was a C++ problem. My `GameBoy` class had a `Timer` member which was getting updated, while the `Timer` inside of the IO class was being read from (without ever being updated since it is a separate instance).

This wasn't immediately apparent since setting a breakpoint would fire for either `Timer` instance, which made it seem like they were being called on the same object.

The fix was to change the `Timer` member variable in the `GameBoy` class to a reference, and update the constructor appropriately.

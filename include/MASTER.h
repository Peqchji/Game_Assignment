#ifndef MASTER_H
#define MASTER_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdbool>
#include <cmath>
#include <iostream>
#include <stdio.h>

#define setFPS 144
#define ScreenScale 65
#define PIXEL 16
#define ScaleUp 3 // if testing pls set to 1         else set it to 3
const float CellPixelSize = PIXEL; // 16*16 Pixel per Cell
const float GridPixelSize = CellPixelSize*33; // 33 * 33 Cell per Grid
const float ScreenWidth = ScreenScale * 16;
const float ScreenHeight = ScreenScale * 9;
const float movementSpeed = 400/ScaleUp;


#endif
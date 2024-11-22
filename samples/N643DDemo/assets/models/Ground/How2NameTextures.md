### Naming Textures, and recommended techniques

textures for your models should all follow this convention:
`texture.format.png`
mksprite (the tool libdragon uses to generate .sprite files), relies on the .png palette index

example:
`grass.ci4.png`

#### What kind of format should I use?

first, take a look at this table:

| Format | Limit (square) | Limit (texels) | Description                         |
| ------ | -------------- | -------------- | ----------------------------------- |
| RGBA16 | 44x44          | 2048           | 16-bit texels, only 1 bit of alpha. |
| RGBA32 | 32x32          | 1024           | 32-bit texels                       |
| CI8    | 43x43          | 2048           | 256 colors, with palette            |
| CI4    | 64x64          | 4096           | 16 colors, with palette             |

kinda useless, I will explain.

##### RGBA32
For materials that need a gradient of transparency, or slightly transparent colors, like water, or stained glass, you want to use rgba32.
this then means you are limited to a 32x32 texture resolution, you can go smaller if you want, just keep it to a power of 2

##### RGBA16
for materials that only need full transparency, like cutouts, think of king bobomb from SM64, or the wings on Kazooie from Banjo Kazooie. you should use rgba16.
this expands your max texture size to 44x44 pixels, you can go smaller, just keep it a power of 2

##### CI8
This stands for color index 8-bit, the biggest size of texture you can use is 43x43, this is good for textures that need a lot of color. 
I can't really think of any good reasons to use this, except when you need a really colorful, detailed image, like maybe a poster, or painting.
you cannot use transparency with this format. you get a total of 256 indexed colors, a little overkill imo

##### CI4
My favorite texture format, and best for a wide range of applications. this is the biggest res image you can use on N64, clocking in at a whopping 64x64!
however, this is limited to only 16 indexed colors. this is good for most textures, such as grass, dirt, anything that does not need a lot of color. and, if you focus more on contrast levels instend of chromanace (color), you can make these textures look really good!
kinda sounds limiting, but, remember that you can combine this with vertex colors to get more colors.

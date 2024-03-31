# NSimpleCrusher

NSimpleCrusher is a basic bit-crusher/quantizer VST plugin designed for audio processing.

## Installation

You can download the x64 VST3 file from the [Releases page](https://github.com/noahdominic/NSimpleCrusher/releases).  Installation instructions vary depending on your digital audio workstation&nbsp;(DAW).  Generally, you should place the VST3 file in `C:\Program Files\Common Files\VST3` as most DAWs search for plugins there.  In any case, please refer to your DAW's documentation for specific instructions.

## Usage

NSimpleCrusher features the following parameters:

- **Pre-Gain**: Adjusts the input gain level before saturation.
- **Crush**: Sets the crush level of the audio signal.
- **Post-gain**: Adjusts the output gain level after clipping.
- **Mix**: Controls the blend between the dry and wet signals.

Simply adjust these parameters according to your preferences to shape the processed audio signal.

## How crushing works

The algorithm for NSimpleCrusher uses a floor function manipulated by two parameters to limit the number of possible values in a given signal.  The equation is as follows:

$$ h(x) = a^b \empheqbiglfloor \frac{x}{a^b} + 0.5 \empheqbigrfloor $$

where $x \in [-1,1]$ is the raw signal, $a \in [0,1]$ is the crush level, and $b \in \Re+$ is what I call the 'linearity inertia factor'.  At $a=0$, $h(x)$ is a completely linear, unprocessed signal, and as $a$ approaches $1$, the number of possible values for $h$ decreases to three: $\{-1, 0, 1\}$.  The linearity inertia factor $b$ controls how 'fast' the possible values for $h$ decreases to three.  The interplay between the two factors can be hard to express in pure text form, so I encourage readers to play with the function and these variables in a graphing calculator.

Currently only $a$ is controllable with a VST parameter.  Control of $b$ is being considered for future versions.  Alternative relationships between $a$ and $b$ are also being considered (Currently $b$ serves as an exponent to $a$.  Maybe we can consider other forms, like $a * b$?).

## Compatibility

NSimpleCrusher has been tested on 64-bit Windows 11 with PreSonus Studio One and Ableton Live.  While compatibility is not guaranteed, this plugin should be compatible with most DAWs.  Currently, I do not have the resources to test this on macOS.

## Licence

This plugin is distributed under the GPLv3 licence.  See the [LICENSE](https://github.com/noahdominic/NSimpleCrusher/LICENSE.txt) file for details.

## Contact

For support, bug reports, or feature requests, please [send me an email](mailto:noah@noahdominic.com).
